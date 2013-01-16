LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

# json
LOCAL_CFLAGS += -I$(LOCAL_PATH)/../../../inc/3rdLib/json

LOCAL_MODULE    := libjson

# json src
LOCAL_SRC_FILES :=  arraylist.c\
					json.c\
					linkhash.c\
			
include $(BUILD_STATIC_LIBRARY)

