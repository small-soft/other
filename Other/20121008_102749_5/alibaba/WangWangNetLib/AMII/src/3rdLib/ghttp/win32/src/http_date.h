/*
 * http_date.h -- Routines for parsing and generating http dates
 */

#ifndef HTTP_DATE_H
#define HTTP_DATE_H

#include <time.h>

time_t
http_date_to_time(const char *a_date);

#endif /* HTTP_DATE_H */
