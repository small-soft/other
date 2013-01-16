LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

include $(CLEAR_VARS)
# zlib2
LOCAL_CFLAGS += -I$(LOCAL_PATH)/../../../inc/3rdLib/zlib2

LOCAL_MODULE    := libzlib2

# zlib2 src
LOCAL_SRC_FILES :=  src/adler32.c \
					src/compress.c \
					src/crc32.c \
					src/deflate.c \
					src/gzio.c \
					src/infback.c \
					src/inffast.c \
					src/inflate.c \
					src/inftrees.c \
					src/trees.c \
					src/uncompr.c \
					src/zutil.c

include $(BUILD_STATIC_LIBRARY)