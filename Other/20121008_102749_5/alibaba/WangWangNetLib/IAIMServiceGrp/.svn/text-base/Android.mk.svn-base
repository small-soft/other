
LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_CFLAGS += -I$(LOCAL_PATH)/include \
				-I$(LOCAL_PATH)/../IMProtocolApi/MIMNet/inc \
				-I$(LOCAL_PATH)/../PacketConnection/inc \
				-I$(LOCAL_PATH)/../AMII/inc/3rdLib/cstl \
				-I$(LOCAL_PATH)/../AMII/inc/3rdLib/cstl/gen \
				-I$(LOCAL_PATH)/../AMII/inc/3rdLib/ghttp \
				-I$(LOCAL_PATH)/../AMII/inc/Platform \
				-I$(LOCAL_PATH)/../AMII/inc/3rdLib/util \
				-I$(LOCAL_PATH)/../AMII/inc/3rdLib/sqlite3 \
				-DAMOS \
				-DAMOS_DEBUG \
				-DAPM_MACRO_GET_OPERATION_MSG \
				-DANDROID_BUILD

# libiaimjni src
LOCAL_SRC_FILES :=  src/AMAccountModel.c \
					src/AMImUtil.c \
					src/IAccount.c \
					src/IAContact.c \
					src/IAContactModel.c \
					src/IAGroup.c \
					src/IAIM.c \
					src/IAIMessage.c \
					src/IASession.c \
					src/IASessionModel.c \
					src/IAIMSignature.c\
					src/AIMTransModule.c\
					src/AIMTrans.c\
					src/AIMAuthModule.c 
									
				
LOCAL_STATIC_LIBRARIES := libaliwwapi 
LOCAL_LDLIBS    := -llog -lsqlite

LOCAL_MODULE    := libaliww

include $(BUILD_STATIC_LIBRARY)

