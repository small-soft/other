LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_CFLAGS += -I$(LOCAL_PATH)/../../../../inc/3rdLib/ghttp\
                -I$(LOCAL_PATH)/../../../../inc/Platform\
		-DANDROID_BUILD

LOCAL_MODULE    := libghttp

# amsp src
LOCAL_SRC_FILES :=  ghttp.c\
					http_date.c\
					http_hdrs.c\
					http_req.c\
					http_resp.c\
					http_trans.c\
					http_uri.c\
					http_base64.c
			
include $(BUILD_STATIC_LIBRARY)
