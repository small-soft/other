LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

# util
LOCAL_CFLAGS += -I$(LOCAL_PATH)/../../../inc/3rdLib/util

LOCAL_MODULE := libutil
# util
LOCAL_SRC_FILES +=  src/charset/ascii.c \
					src/charset/utf8.c \
					src/charset/asciitbl.c \
					src/r_keygen.c \
					src/r_random.c \
					src/base64.c \
					src/r_stdlib.c \
					src/des_help.c \
					src/rsa.c \
					src/desc.c \
					src/shsc.c \
					src/md5c.c \
					src/charset/utf16.c \
					src/nn.c \
					src/prime.c

include $(BUILD_STATIC_LIBRARY)
