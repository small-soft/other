#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include "json.h"

#define JSON_OBJECT_DEF_HASH_ENTIRES 16
#define JSON_TOKENER_MAX_DEPTH 32

struct json_tokener_srec
{
	enum json_tokener_state state;
	enum json_tokener_state saved_state;
	struct json_object *obj;
	struct json_object *current;
	char *obj_field_name;
};

struct json_tokener
{
	char *str;
	struct printbuf *pb;
	int depth, is_double, st_pos, char_offset;
	ptrdiff_t err;
	unsigned int ucs_char;
	char quote_char;
	struct json_tokener_srec stack[JSON_TOKENER_MAX_DEPTH];
};

/*typedef void (json_object_delete_fn)(struct json_object *o);
typedef int (json_object_to_json_string_fn)(struct json_object *o, struct printbuf *pb);
*/
/*struct json_object
{
	enum json_type o_type;
	json_object_delete_fn *_delete;
	json_object_to_json_string_fn *_to_json_string;
	int _ref_count;
	struct printbuf *_pb;
	union data {
		boolean c_boolean;
		double c_double;
		int c_int;
		struct lh_table *c_object;
		struct array_list *c_array;
		char *c_string;
	} o;
};*/

/* CAW: added for ANSI C iteration correctness */
struct json_object_iter
{
	char *key;
	struct json_object *val;
	struct lh_entry *entry;
};

#if !HAVE_STRNDUP
  char* strndup(const char* str, size_t n);
#endif /* !HAVE_STRNDUP */

char *json_number_chars = "0123456789.+-eE";
char *json_hex_chars = "0123456789abcdef";

#ifdef REFCOUNT_DEBUG
static char* json_type_name[] = {
  "null",
  "boolean",
  "double",
  "int",
  "object",
  "array",
  "string",
};
#endif /* REFCOUNT_DEBUG */

static void json_object_generic_delete(struct json_object* this);
static struct json_object* json_object_new(enum json_type o_type);

/************************************************************************/
// printbuf
/************************************************************************/
/*struct printbuf {
	char *buf;
	int bpos;
	int size;
};*/

static struct printbuf* printbuf_new(void);
static int printbuf_memappend(struct printbuf *p, char *buf, int size);
static int sprintbuf(struct printbuf *p, const char *msg, ...);
static void printbuf_reset(struct printbuf *p);
static void printbuf_free(struct printbuf *p);

#if HAVE_STDARG_H
# include <stdarg.h>
#else /* !HAVE_STDARG_H */
# error Not enough var arg support!
#endif /* HAVE_STDARG_H */

struct printbuf* printbuf_new()
{
	struct printbuf *p;

	if(!(p = calloc(1, sizeof(struct printbuf)))) return NULL;
	p->size = 32;
	p->bpos = 0;
	if(!(p->buf = malloc(p->size))) {
		free(p);
		return NULL;
	}
	return p;
}


int printbuf_memappend(struct printbuf *p, char *buf, int size)
{
	char *t;
	if(p->size - p->bpos <= size) {
		int new_size = max(p->size * 2, p->bpos + size + 8);
#ifdef PRINTBUF_DEBUG
		MC_DEBUG("printbuf_memappend: realloc "
			"bpos=%d wrsize=%d old_size=%d new_size=%d\n",
			p->bpos, size, p->size, new_size);
#endif /* PRINTBUF_DEBUG */
		if(!(t = realloc(p->buf, new_size))) return -1;
		p->size = new_size;
		p->buf = t;
	}
	memcpy(p->buf + p->bpos, buf, size);
	p->bpos += size;
	p->buf[p->bpos]= '\0';
	return size;
}

#if !HAVE_VSNPRINTF && defined(WIN32)
# define vsnprintf _vsnprintf
#elif !HAVE_VSNPRINTF /* !HAVE_VSNPRINTF */
# error Need vsnprintf!
#endif /* !HAVE_VSNPRINTF && defined(WIN32) */

#if !HAVE_VASPRINTF
/* CAW: compliant version of vasprintf */
static int vasprintf(char **buf, const char *fmt, va_list ap)
{
#ifndef WIN32
	static char _T_emptybuffer = '\0';
#endif /* !defined(WIN32) */
	int chars;
	char *b;

	if(!buf) { return -1; }

#ifdef WIN32
	chars = _vscprintf(fmt, ap)+1;
#else /* !defined(WIN32) */
	/* CAW: RAWR! We have to hope to god here that vsnprintf doesn't overwrite
	our buffer like on some 64bit sun systems.... but hey, its time to move on */
	chars = vsnprintf(&_T_emptybuffer, 0, fmt, ap)+1;
	if(chars < 0) { chars *= -1; } /* CAW: old glibc versions have this problem */
#endif /* defined(WIN32) */

	b = (char*)malloc(sizeof(char)*chars);
	if(!b) { return -1; }

	if((chars = vsprintf(b, fmt, ap)) < 0)
	{
		free(b);
	} else {
		*buf = b;
	}

	return chars;
}
#endif /* !HAVE_VASPRINTF */

int sprintbuf(struct printbuf *p, const char *msg, ...)
{
	va_list ap;
	char *t;
	int size;
	char buf[128];

	/* user stack buffer first */
	va_start(ap, msg);
	size = vsnprintf(buf, 128, msg, ap);
	va_end(ap);
	/* if string is greater than stack buffer, then use dynamic string
	with vasprintf.  Note: some implementation of vsnprintf return -1
	if output is truncated whereas some return the number of bytes that
	would have been writen - this code handles both cases. */
	if(size == -1 || size > 127) {
		int ret;
		va_start(ap, msg);
		size = vasprintf(&t, msg, ap);
		va_end(ap);
		if(size == -1) return -1;
		ret = printbuf_memappend(p, t, size);
		free(t);
		return ret;
	} else {
		return printbuf_memappend(p, buf, size);
	}
}

void printbuf_reset(struct printbuf *p)
{
	p->buf[0] = '\0';
	p->bpos = 0;
}

void printbuf_free(struct printbuf *p)
{
	if(p) {
		free(p->buf);
		free(p);
	}
}
/************************************************************************/
// end of printbuf
/************************************************************************/

/* ref count debugging */

#ifdef REFCOUNT_DEBUG

static struct lh_table *json_object_table;

//static void json_object_init(void) __attribute__ ((constructor));
static void json_object_init(void) {
  MC_DEBUG("json_object_init: creating object table\n");
  json_object_table = lh_kptr_table_new(128, "json_object_table", NULL);
}

//static void json_object_fini(void) __attribute__ ((destructor));
static void json_object_fini(void) {
  struct lh_entry *ent;
  if(MC_GET_DEBUG()) {
    if (json_object_table->count) {
      MC_DEBUG("json_object_fini: %d referenced objects at exit\n",
  	       json_object_table->count);
      lh_foreach(json_object_table, ent) {
        struct json_object* obj = (struct json_object*)ent->v;
        MC_DEBUG("\t%s:%p\n", json_type_name[obj->o_type], obj);
      }
    }
  }
  MC_DEBUG("json_object_fini: freeing object table\n");
  lh_table_free(json_object_table);
}
#endif /* REFCOUNT_DEBUG */


/* string escaping */

static int json_escape_str(struct printbuf *pb, char *str)
{
  int pos = 0, start_offset = 0;
  unsigned char c;
  do {
    c = str[pos];
    switch(c) {
    case '\0':
      break;
    case '\b':
    case '\n':
    case '\r':
    case '\t':
    case '"':
    case '\\':
    case '/':
      if(pos - start_offset > 0)
	printbuf_memappend(pb, str + start_offset, pos - start_offset);
      if(c == '\b') printbuf_memappend(pb, "\\b", 2);
      else if(c == '\n') printbuf_memappend(pb, "\\n", 2);
      else if(c == '\r') printbuf_memappend(pb, "\\r", 2);
      else if(c == '\t') printbuf_memappend(pb, "\\t", 2);
      else if(c == '"') printbuf_memappend(pb, "\\\"", 2);
      else if(c == '\\') printbuf_memappend(pb, "\\\\", 2);
      else if(c == '/') printbuf_memappend(pb, "\\/", 2);
      start_offset = ++pos;
      break;
    default:
      if(c < ' ') {
	if(pos - start_offset > 0)
	  printbuf_memappend(pb, str + start_offset, pos - start_offset);
	sprintbuf(pb, "\\u00%c%c",
		  json_hex_chars[c >> 4],
		  json_hex_chars[c & 0xf]);
	start_offset = ++pos;
      } else pos++;
    }
  } while(c);
  if(pos - start_offset > 0)
    printbuf_memappend(pb, str + start_offset, pos - start_offset);
  return 0;
}


/* reference counting */

extern struct json_object* json_object_get(struct json_object *this)
{
  if(this) {
    this->_ref_count++;
  }
  return this;
}

extern void json_object_put(struct json_object *this)
{
  if(this) {
    this->_ref_count--;
    if(!this->_ref_count) this->_delete(this);
  }
}


/* generic object construction and destruction parts */

static void json_object_generic_delete(struct json_object* this)
{
#ifdef REFCOUNT_DEBUG
  MC_DEBUG("json_object_delete_%s: %p\n",
	   json_type_name[this->o_type], this);
  lh_table_delete(json_object_table, this);
#endif /* REFCOUNT_DEBUG */
  printbuf_free(this->_pb);
  free(this);
}

static struct json_object* json_object_new(enum json_type o_type)
{
  struct json_object *this = calloc(sizeof(struct json_object), 1);
  if(!this) return NULL;
  this->o_type = o_type;
  this->_ref_count = 1;
  this->_delete = &json_object_generic_delete;
#ifdef REFCOUNT_DEBUG
  lh_table_insert(json_object_table, this, this);
  MC_DEBUG("json_object_new_%s: %p\n", json_type_name[this->o_type], this);
#endif /* REFCOUNT_DEBUG */
  return this;
}


/* type checking functions */

int json_object_is_type(struct json_object *this, enum json_type type)
{
  return (this->o_type == type);
}

enum json_type json_object_get_type(struct json_object *this)
{
  return this->o_type;
}


/* json_object_to_json_string */

char* json_object_to_json_string(struct json_object *this)
{
  if(!this) return "null";
  if(!this->_pb) 
  {
    if(!(this->_pb = printbuf_new())) 
		return NULL;
  } 
  else 
  {
    printbuf_reset(this->_pb);
  }
  
  if(this->_to_json_string(this, this->_pb) < 0) 
	  return NULL;
  return this->_pb->buf;
}


/* json_object_object */

static int json_object_object_to_json_string(struct json_object* this,
					     struct printbuf *pb)
{
  int i=0;
  struct json_object_iter iter;
  sprintbuf(pb, "{");

  /* CAW: scope operator to make ANSI correctness */
  /* CAW: switched to json_object_object_foreachC which uses an iterator struct */
	json_object_object_foreachC(this, iter) {
			if(i) sprintbuf(pb, ",");
			sprintbuf(pb, " \"");
			json_escape_str(pb, iter.key);
			sprintbuf(pb, "\": ");
			if(iter.val == NULL) sprintbuf(pb, "null");
			else iter.val->_to_json_string(iter.val, pb);
			i++;
	}

  return sprintbuf(pb, " }");
}

static void json_object_lh_entry_free(struct lh_entry *ent)
{
  free(ent->k);
  json_object_put((struct json_object*)ent->v);
}

static void json_object_object_delete(struct json_object* this)
{
  lh_table_free(this->o.c_object);
  json_object_generic_delete(this);
}

struct json_object* json_object_new_object()
{
  struct json_object *this = json_object_new(json_type_object);
  if(!this) return NULL;
  this->_delete = &json_object_object_delete;
  this->_to_json_string = &json_object_object_to_json_string;
  this->o.c_object = lh_kchar_table_new(JSON_OBJECT_DEF_HASH_ENTIRES,
					NULL, &json_object_lh_entry_free);
  return this;
}

struct lh_table* json_object_get_table(struct json_object *this)
{
  if(!this) return NULL;
  switch(this->o_type) {
  case json_type_object:
    return this->o.c_object;
  default:
    return NULL;
  }
}

void json_object_object_add(struct json_object* this, char *key,
			    struct json_object *val)
{
  lh_table_delete(this->o.c_object, key);
  lh_table_insert(this->o.c_object, strdup(key), val);
}

struct json_object* json_object_object_get(struct json_object* this, char *key)
{
  return (struct json_object*) lh_table_lookup(this->o.c_object, key);
}

void json_object_object_del(struct json_object* this, char *key)
{
  lh_table_delete(this->o.c_object, key);
}


/* json_object_boolean */

static int json_object_boolean_to_json_string(struct json_object* this,
					      struct printbuf *pb)
{
  if(this->o.c_boolean) return sprintbuf(pb, "true");
  else return sprintbuf(pb, "false");
}

struct json_object* json_object_new_boolean(jsonboolean b)
{
  struct json_object *this = json_object_new(json_type_boolean);
  if(!this) return NULL;
  this->_to_json_string = &json_object_boolean_to_json_string;
  this->o.c_boolean = b;
  return this;
}

jsonboolean json_object_get_boolean(struct json_object *this)
{
  if(!this) return FALSE;
  switch(this->o_type) {
  case json_type_boolean:
    return this->o.c_boolean;
  case json_type_int:
    return (this->o.c_int != 0);
  case json_type_double:
    return (this->o.c_double != 0);
  case json_type_string:
    if(strlen(this->o.c_string)) return TRUE;
  default:
    return TRUE;
  }
}


/* json_object_int */

static int json_object_int_to_json_string(struct json_object* this,
					  struct printbuf *pb)
{
  return sprintbuf(pb, "%d", this->o.c_int);
}

struct json_object* json_object_new_int(int i)
{
  struct json_object *this = json_object_new(json_type_int);
  if(!this) return NULL;
  this->_to_json_string = &json_object_int_to_json_string;
  this->o.c_int = i;
  return this;
}

int json_object_get_int(struct json_object *this)
{
  int cint;

  if(!this) return 0;
  switch(this->o_type) {
  case json_type_int:
    return this->o.c_int;
  case json_type_double:
    return (int)this->o.c_double;
  case json_type_boolean:
    return this->o.c_boolean;
  case json_type_string:
    if(sscanf(this->o.c_string, "%d", &cint) == 1) return cint;
  default:
    return 0;
  }
}


/* json_object_double */

static int json_object_double_to_json_string(struct json_object* this,
					     struct printbuf *pb)
{
  return sprintbuf(pb, "%lf", this->o.c_double);
}

struct json_object* json_object_new_double(double d)
{
  struct json_object *this = json_object_new(json_type_double);
  if(!this) return NULL;
  this->_to_json_string = &json_object_double_to_json_string;
  this->o.c_double = d;
  return this;
}

double json_object_get_double(struct json_object *this)
{
  double cdouble;

  if(!this) return 0.0;
  switch(this->o_type) {
  case json_type_double:
    return this->o.c_double;
  case json_type_int:
    return this->o.c_int;
  case json_type_boolean:
    return this->o.c_boolean;
  case json_type_string:
    if(sscanf(this->o.c_string, "%lf", &cdouble) == 1) return cdouble;
  default:
    return 0.0;
  }
}


/* json_object_string */

static int json_object_string_to_json_string(struct json_object* this,
					     struct printbuf *pb)
{
  sprintbuf(pb, "\"");
  json_escape_str(pb, this->o.c_string);
  sprintbuf(pb, "\"");
  return 0;
}

static void json_object_string_delete(struct json_object* this)
{
  free(this->o.c_string);
  json_object_generic_delete(this);
}

struct json_object* json_object_new_string(char *s)
{
  struct json_object *this = json_object_new(json_type_string);
  if(!this) return NULL;
  this->_delete = &json_object_string_delete;
  this->_to_json_string = &json_object_string_to_json_string;
  this->o.c_string = strdup(s);
  return this;
}

struct json_object* json_object_new_string_len(char *s, int len)
{
  struct json_object *this = json_object_new(json_type_string);
  if(!this) return NULL;
  this->_delete = &json_object_string_delete;
  this->_to_json_string = &json_object_string_to_json_string;
  this->o.c_string = strndup(s, len);
  return this;
}

char* json_object_get_string(struct json_object *this)
{
  if(!this) return NULL;
  switch(this->o_type) {
  case json_type_string:
    return this->o.c_string;
  default:
    return json_object_to_json_string(this);
  }
}


/* json_object_array */

static int json_object_array_to_json_string(struct json_object* this,
					    struct printbuf *pb)
{
  int i;
  sprintbuf(pb, "[");
  for(i=0; i < json_object_array_length(this); i++) {
	  struct json_object *val;
	  if(i) { sprintbuf(pb, ", "); }
	  else { sprintbuf(pb, " "); }

      val = json_object_array_get_idx(this, i);
	  if(val == NULL) { sprintbuf(pb, "null"); }
	  else { val->_to_json_string(val, pb); }
  }
  return sprintbuf(pb, " ]");
}

static void json_object_array_entry_free(void *data)
{
  json_object_put((struct json_object*)data);
}

static void json_object_array_delete(struct json_object* this)
{
  array_list_free(this->o.c_array);
  json_object_generic_delete(this);
}

struct json_object* json_object_new_array()
{
  struct json_object *this = json_object_new(json_type_array);
  if(!this) return NULL;
  this->_delete = &json_object_array_delete;
  this->_to_json_string = &json_object_array_to_json_string;
  this->o.c_array = array_list_new(&json_object_array_entry_free);
  return this;
}

struct array_list* json_object_get_array(struct json_object *this)
{
  if(!this) return NULL;
  switch(this->o_type) {
  case json_type_array:
    return this->o.c_array;
  default:
    return NULL;
  }
}

int json_object_array_length(struct json_object *this)
{
  return array_list_length(this->o.c_array);
}

int json_object_array_add(struct json_object *this,struct json_object *val)
{
  return array_list_add(this->o.c_array, val);
}

int json_object_array_put_idx(struct json_object *this, int idx,
			      struct json_object *val)
{
  return array_list_put_idx(this->o.c_array, idx, val);
}

struct json_object* json_object_array_get_idx(struct json_object *this,
					      int idx)
{
  return (struct json_object*)array_list_get_idx(this->o.c_array, idx);
}

/************************************************************************/
// 从json string构建一个json object.                                                                 
/************************************************************************/

#define hexdigit(x) (((x) <= '9') ? (x) - '0' : ((x) & 7) + 9)

#if !HAVE_STRNCASECMP && defined(_MSC_VER)
/* MSC has the version as _strnicmp */
# define strncasecmp _strnicmp
#elif !HAVE_STRNCASECMP
# error You do not have strncasecmp on your system.
#endif /* HAVE_STRNCASECMP */


static const char* json_null_str = "null";
static const char* json_true_str = "true";
static const char* json_false_str = "false";

const char* json_tokener_errors[] = 
{
	"success",
	"continue",
	"nesting to deep",
	"unexpected end of data",
	"unexpected character",
	"null expected",
	"boolean expected",
	"number expected",
	"array value separator ',' expected",
	"quoted object property name expected",
	"object property name separator ':' expected",
	"object value separator ',' expected",
	"invalid string sequence",
	"expected comment",
};


struct json_tokener* json_tokener_new()
{
	struct json_tokener *tok = calloc(1, sizeof(struct json_tokener));
	tok->pb = printbuf_new();
	json_tokener_reset(tok);
	return tok;
}

void json_tokener_free(struct json_tokener *tok)
{
	json_tokener_reset(tok);
	if(tok) printbuf_free(tok->pb);
	free(tok);
}

static void json_tokener_reset_level(struct json_tokener *tok, int depth)
{
	tok->stack[depth].state = json_tokener_state_eatws;
	tok->stack[depth].saved_state = json_tokener_state_start;
	json_object_put(tok->stack[depth].current);
	tok->stack[depth].current = NULL;
	free(tok->stack[depth].obj_field_name);
	tok->stack[depth].obj_field_name = NULL;
}

void json_tokener_reset(struct json_tokener *tok)
{
	int i;
	for(i = tok->depth; i >= 0; i--)
		json_tokener_reset_level(tok, i);
	tok->depth = 0;
	tok->err = json_tokener_success;
}

struct json_object* json_object_create(char *str)
{
	struct json_tokener* tok;
	struct json_object* obj;

	tok = json_tokener_new();
	obj = json_tokener_parse_ex(tok, str, -1);
	if(!obj) 
	{
		json_tokener_free(tok);
		return NULL;
	}

	if(tok->err != json_tokener_success)
		obj = error_ptr(0);
	json_tokener_free(tok);
	return obj;
}


#if !HAVE_STRNDUP
/* CAW: compliant version of strndup() */
char* strndup(const char* str, size_t n)
{
	if(str) {
		size_t len = strlen(str);
		size_t nn = min(len,n);
		char* s = (char*)malloc(sizeof(char) * (nn + 1));

		if(s) {
			memcpy(s, str, nn);
			s[nn] = '\0';
		}

		return s;
	}

	return NULL;
}
#endif


#define state  tok->stack[tok->depth].state
#define saved_state  tok->stack[tok->depth].saved_state
#define current tok->stack[tok->depth].current
#define obj_field_name tok->stack[tok->depth].obj_field_name

struct json_object* json_tokener_parse_ex(struct json_tokener *tok,
	char *str, int len)
{
	struct json_object *obj = NULL;
	char c;

	tok->char_offset = 0;
	tok->err = json_tokener_success;

	do {
		if(tok->char_offset == len) {
			if(tok->depth == 0 && state == json_tokener_state_eatws &&
				saved_state == json_tokener_state_finish)
				tok->err = json_tokener_success;
			else
				tok->err = json_tokener_continue;
			goto out;
		}

		c = *str;
redo_char:
		switch(state) {

		case json_tokener_state_eatws:
			if(isspace(c)) {
				/* okay */
			} else if(c == '/') {
				printbuf_reset(tok->pb);
				printbuf_memappend(tok->pb, &c, 1);
				state = json_tokener_state_comment_start;
			} else {
				state = saved_state;
				goto redo_char;
			}
			break;

		case json_tokener_state_start:
			switch(c) {
		case '{':
			state = json_tokener_state_eatws;
			saved_state = json_tokener_state_object_field_start;
			current = json_object_new_object();
			break;
		case '[':
			state = json_tokener_state_eatws;
			saved_state = json_tokener_state_array;
			current = json_object_new_array();
			break;
		case 'N':
		case 'n':
			state = json_tokener_state_null;
			printbuf_reset(tok->pb);
			tok->st_pos = 0;
			goto redo_char;
		case '"':
		case '\'':
			state = json_tokener_state_string;
			printbuf_reset(tok->pb);
			tok->quote_char = c;
			break;
		case 'T':
		case 't':
		case 'F':
		case 'f':
			state = json_tokener_state_boolean;
			printbuf_reset(tok->pb);
			tok->st_pos = 0;
			goto redo_char;
		#if defined(__GNUC__)
		case '0' ... '9':
		#else
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		#endif
		case '-':
			state = json_tokener_state_number;
			printbuf_reset(tok->pb);
			tok->is_double = 0;
			goto redo_char;
		default:
			tok->err = json_tokener_error_parse_unexpected;
			goto out;
			}
			break;

		case json_tokener_state_finish:
			if(tok->depth == 0) goto out;
			obj = json_object_get(current);
			json_tokener_reset_level(tok, tok->depth);
			tok->depth--;
			goto redo_char;

		case json_tokener_state_null:
			printbuf_memappend(tok->pb, &c, 1);
			if(strncasecmp(json_null_str, tok->pb->buf,
				min(tok->st_pos+1, strlen(json_null_str))) == 0) {
					if(tok->st_pos == strlen(json_null_str)) {
						current = NULL;
						saved_state = json_tokener_state_finish;
						state = json_tokener_state_eatws;
						goto redo_char;
					}
			} else {
				tok->err = json_tokener_error_parse_null;
				goto out;
			}
			tok->st_pos++;
			break;

		case json_tokener_state_comment_start:
			if(c == '*') {
				state = json_tokener_state_comment;
			} else if(c == '/') {
				state = json_tokener_state_comment_eol;
			} else {
				tok->err = json_tokener_error_parse_comment;
				goto out;
			}
			printbuf_memappend(tok->pb, &c, 1);
			break;

		case json_tokener_state_comment:
			if(c == '*') state = json_tokener_state_comment_end;
			printbuf_memappend(tok->pb, &c, 1);
			break;

		case json_tokener_state_comment_eol:
			if(c == '\n') {
		#ifdef REFCOUNT_DEBUG
				MC_DEBUG("json_tokener_comment: %s\n", tok->pb->buf);
		#endif
				state = json_tokener_state_eatws;
			} else {
				printbuf_memappend(tok->pb, &c, 1);
			}
			break;

		case json_tokener_state_comment_end:
			printbuf_memappend(tok->pb, &c, 1);
			if(c == '/') {
		#ifdef REFCOUNT_DEBUG
				MC_DEBUG("json_tokener_comment: %s\n", tok->pb->buf);
		#endif
				state = json_tokener_state_eatws;
			} else {
				state = json_tokener_state_comment;
			}
			break;

		case json_tokener_state_string:
			if(c == tok->quote_char) {
				current = json_object_new_string(tok->pb->buf);
				saved_state = json_tokener_state_finish;
				state = json_tokener_state_eatws;
			} else if(c == '\\') {
				saved_state = json_tokener_state_string;
				state = json_tokener_state_string_escape;
			} else {
				printbuf_memappend(tok->pb, &c, 1);
			}
			break;

		case json_tokener_state_string_escape:
			switch(c) {
		case '"':
		case '\\':
		case '/':
			printbuf_memappend(tok->pb, &c, 1);
			state = saved_state;
			break;
		case 'b':
		case 'n':
		case 'r':
		case 't':
			if(c == 'b') printbuf_memappend(tok->pb, "\b", 1);
			else if(c == 'n') printbuf_memappend(tok->pb, "\n", 1);
			else if(c == 'r') printbuf_memappend(tok->pb, "\r", 1);
			else if(c == 't') printbuf_memappend(tok->pb, "\t", 1);
			state = saved_state;
			break;
		case 'u':
			tok->ucs_char = 0;
			tok->st_pos = 0;
			state = json_tokener_state_escape_unicode;
			break;
		default:
			tok->err = json_tokener_error_parse_string;
			goto out;
			}
			break;

		case json_tokener_state_escape_unicode:
			if(strchr(json_hex_chars, c)) {
				tok->ucs_char += ((unsigned int)hexdigit(c) << ((3-tok->st_pos++)*4));
				if(tok->st_pos == 4) {
					unsigned char utf_out[3];
					if (tok->ucs_char < 0x80) {
						utf_out[0] = tok->ucs_char;
						printbuf_memappend(tok->pb, (char*)utf_out, 1);
					} else if (tok->ucs_char < 0x800) {
						utf_out[0] = 0xc0 | (tok->ucs_char >> 6);
						utf_out[1] = 0x80 | (tok->ucs_char & 0x3f);
						printbuf_memappend(tok->pb, (char*)utf_out, 2);
					} else {
						utf_out[0] = 0xe0 | (tok->ucs_char >> 12);
						utf_out[1] = 0x80 | ((tok->ucs_char >> 6) & 0x3f);
						utf_out[2] = 0x80 | (tok->ucs_char & 0x3f);
						printbuf_memappend(tok->pb, (char*)utf_out, 3);
					}
					state = saved_state;
				}
			} else {
				tok->err = json_tokener_error_parse_string;
				goto out;
			}
			break;

		case json_tokener_state_boolean:
			printbuf_memappend(tok->pb, &c, 1);
			if(strncasecmp(json_true_str, tok->pb->buf,
				min(tok->st_pos+1, strlen(json_true_str))) == 0) {
					if(tok->st_pos == strlen(json_true_str)) {
						current = json_object_new_boolean(1);
						saved_state = json_tokener_state_finish;
						state = json_tokener_state_eatws;
						goto redo_char;
					}
			} else if(strncasecmp(json_false_str, tok->pb->buf,
				min(tok->st_pos+1, strlen(json_false_str))) == 0) {
					if(tok->st_pos == strlen(json_false_str)) {
						current = json_object_new_boolean(0);
						saved_state = json_tokener_state_finish;
						state = json_tokener_state_eatws;
						goto redo_char;
					}
			} else {
				tok->err = json_tokener_error_parse_boolean;
				goto out;
			}
			tok->st_pos++;
			break;

		case json_tokener_state_number:
			if(c && strchr(json_number_chars, c)) {
				printbuf_memappend(tok->pb, &c, 1);	
				if(c == '.' || c == 'e' || c == 'E') tok->is_double = 1;
			} else {
				int numi;
				double numd;
				if(!tok->is_double && sscanf(tok->pb->buf, "%d", &numi) == 1) {
					current = json_object_new_int(numi);
				} else if(tok->is_double && sscanf(tok->pb->buf, "%lf", &numd) == 1) {
					current = json_object_new_double(numd);
				} else {
					tok->err = json_tokener_error_parse_number;
					goto out;
				}
				saved_state = json_tokener_state_finish;
				state = json_tokener_state_eatws;
				goto redo_char;
			}
			break;

		case json_tokener_state_array:
			if(c == ']') {
				saved_state = json_tokener_state_finish;
				state = json_tokener_state_eatws;
			} else {
				if(tok->depth >= JSON_TOKENER_MAX_DEPTH-1) {
					tok->err = json_tokener_error_depth;
					goto out;
				}
				state = json_tokener_state_array_add;
				tok->depth++;
				json_tokener_reset_level(tok, tok->depth);
				goto redo_char;
			}
			break;

		case json_tokener_state_array_add:
			json_object_array_add(current, obj);
			saved_state = json_tokener_state_array_sep;
			state = json_tokener_state_eatws;
			goto redo_char;

		case json_tokener_state_array_sep:
			if(c == ']') {
				saved_state = json_tokener_state_finish;
				state = json_tokener_state_eatws;
			} else if(c == ',') {
				saved_state = json_tokener_state_array;
				state = json_tokener_state_eatws;
			} else {
				tok->err = json_tokener_error_parse_array;
				goto out;
			}
			break;

		case json_tokener_state_object_field_start:
			if(c == '}') {
				saved_state = json_tokener_state_finish;
				state = json_tokener_state_eatws;
			} else if (c == '"' || c == '\'') {
				tok->quote_char = c;
				printbuf_reset(tok->pb);
				state = json_tokener_state_object_field;
			} else {
				tok->err = json_tokener_error_parse_object_key_name;
				goto out;
			}
			break;

		case json_tokener_state_object_field:
			if(c == tok->quote_char) {
				obj_field_name = strdup(tok->pb->buf);
				saved_state = json_tokener_state_object_field_end;
				state = json_tokener_state_eatws;
			} else if(c == '\\') {
				saved_state = json_tokener_state_object_field;
				state = json_tokener_state_string_escape;
			} else {
				printbuf_memappend(tok->pb, &c, 1);
			}
			break;

		case json_tokener_state_object_field_end:
			if(c == ':') {
				saved_state = json_tokener_state_object_value;
				state = json_tokener_state_eatws;
			} else {
				tok->err = json_tokener_error_parse_object_key_sep;
				goto out;
			}
			break;

		case json_tokener_state_object_value:
			if(tok->depth >= JSON_TOKENER_MAX_DEPTH-1) {
				tok->err = json_tokener_error_depth;
				goto out;
			}
			state = json_tokener_state_object_value_add;
			tok->depth++;
			json_tokener_reset_level(tok, tok->depth);
			goto redo_char;

		case json_tokener_state_object_value_add:
			json_object_object_add(current, obj_field_name, obj);
			free(obj_field_name);
			obj_field_name = NULL;
			saved_state = json_tokener_state_object_sep;
			state = json_tokener_state_eatws;
			goto redo_char;

		case json_tokener_state_object_sep:
			if(c == '}') {
				saved_state = json_tokener_state_finish;
				state = json_tokener_state_eatws;
			} else if(c == ',') {
				saved_state = json_tokener_state_object_field_start;
				state = json_tokener_state_eatws;
			} else {
				tok->err = json_tokener_error_parse_object_value_sep;
				goto out;
			}
			break;

		}
		str++;
		tok->char_offset++;
	} while(c);

	if(state != json_tokener_state_finish &&
		saved_state != json_tokener_state_finish)
		tok->err = json_tokener_error_parse_eof;

out:
	if(tok->err == json_tokener_success) 
		return json_object_get(current);

#ifdef REFCOUNT_DEBUG
	MC_DEBUG("json_tokener_parse_ex: error %s at offset %d\n",
		json_tokener_errors[tok->err], tok->char_offset);
#endif
	return NULL;
}
