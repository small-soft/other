
LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_CFLAGS += -I$(LOCAL_PATH)/inc \
				-I$(LOCAL_PATH)/../AMII/inc/Platform \
				-I$(LOCAL_PATH)/../AMII/inc/3rdLib/util \
				-I$(LOCAL_PATH)/../AMII/inc/3rdLib/cstl \
				-I$(LOCAL_PATH)/../AMII/inc/3rdLib/cstl/gen \
				-DAMOS \
				-DAMOS_DEBUG \
				-DANDROID_BUILD

LOCAL_MODULE    := libaliplatform

# libplatform src
LOCAL_SRC_FILES :=	src/PCContext.c \
					src/PCCore.c \
					src/PCEvent.c \
					src/PCMgr.c \
					src/PCUtility.c													

LOCAL_STATIC_LIBRARIES := libaliadapter


include $(BUILD_STATIC_LIBRARY)

