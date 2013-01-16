
LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_CFLAGS += -I$(LOCAL_PATH)/inc \
				-I$(LOCAL_PATH)/../../PacketConnection/inc \
				-I$(LOCAL_PATH)/../../AMII/inc/3rdLib/cstl \
				-I$(LOCAL_PATH)/../../AMII/inc/3rdLib/cstl\gen \
				-I$(LOCAL_PATH)/../../AMII/inc/3rdLib/ghttp \
				-I$(LOCAL_PATH)/../../AMII/inc/Platform \
				-I$(LOCAL_PATH)/../../AMII/inc/3rdLib/util \
				-I$(LOCAL_PATH)/../../AMII/inc/3rdLib/sqlite3 \
				-DAMOS \
				-DAMOS_DEBUG \
				-DAPM_MACRO_GET_OPERATION_MSG \
				-DANDROID_BUILD

LOCAL_MODULE    := libaliwwapi

# libwwapi src
LOCAL_SRC_FILES := 	src/IMnetCallback.c \
					src/IMnetMain.c \
					src/IMnetPacket.c \
					src/IMnetRequest.c \
					src/IMnetUtility.c 
										
				
LOCAL_STATIC_LIBRARIES :=  libaliplatform 

include $(BUILD_STATIC_LIBRARY)

