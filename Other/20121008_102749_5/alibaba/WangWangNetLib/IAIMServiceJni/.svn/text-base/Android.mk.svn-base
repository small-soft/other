
LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_CFLAGS += -I$(LOCAL_PATH)/../IAIMServiceGrp/include \
				-I$(LOCAL_PATH)/../IMProtocolApi/MIMNet/inc \
				-I$(LOCAL_PATH)/../PacketConnection/inc \
				-I$(LOCAL_PATH)/../AMII/inc/3rdLib/cstl \
				-I$(LOCAL_PATH)/../AMII/inc/3rdLib/cstl\gen \
				-I$(LOCAL_PATH)/../AMII/inc/3rdLib/ghttp \
				-I$(LOCAL_PATH)/../AMII/inc/Platform \
				-I$(LOCAL_PATH)/../AMII/inc/3rdLib/util \
				-I$(LOCAL_PATH)/../AMII/inc/3rdLib/sqlite3 \
				-DAMOS \
				-DAMOS_DEBUG \
				-DAPM_MACRO_GET_OPERATION_MSG \
				-DANDROID_BUILD

LOCAL_MODULE    := libaliiaimapi

# libiaimjni src
LOCAL_SRC_FILES := ChatSession.c \
					ConnectionAdapter.c \
					IMService.c	\
					CallbackAdapter.c 
										
LOCAL_LDLIBS    := -llog -lsqlite
				
LOCAL_STATIC_LIBRARIES :=  libaliww

include $(BUILD_SHARED_LIBRARY)


