LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
# cstl
LOCAL_CFLAGS += -I$(LOCAL_PATH)/../../../inc/3rdLib/cstl \
								-I$(LOCAL_PATH)/../../../inc/3rdLib/cstl/gen

LOCAL_MODULE    := libcstl

# cstl src
LOCAL_SRC_FILES :=  src/binary_tree.c \
					src/clist.c \
					src/conversions.c \
					src/deque.c \
					src/hashtable.c \
					src/heap.c \
					src/node.c \
					src/priority_queue.c \
					src/queue.c \
					src/stack.c \
					src/vector.c
			
include $(BUILD_STATIC_LIBRARY)
