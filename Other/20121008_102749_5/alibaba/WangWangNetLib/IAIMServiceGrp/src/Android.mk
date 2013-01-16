LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_CFLAGS += -I$(LOCAL_PATH)/../include \
				-I$(LOCAL_PATH)/../../MProtocol/MIMNet/inc \
				-I$(LOCAL_PATH)/../../PacketConnection/inc \
				-I$(LOCAL_PATH)/../../../../AMII/inc/3rdLib/cstl \
				-I$(LOCAL_PATH)/../../../../AMII/inc/3rdLib/cstl\gen \
				-I$(LOCAL_PATH)/../../../../AMII/inc/3rdLib/ghttp \
				-I$(LOCAL_PATH)/../../../../AMII/inc/Platform \
				-DAMOS \
				-DAMOS_DEBUG

LOCAL_MODULE    := libiaim

# libiaimjni src
LOCAL_SRC_FILES :=  AMAccountModel.c \
										AMImUtil.c \
										IAccount.c \
										IAContact.c \
										IAContactModel.c \
										IAGroup.c \
										IAIM.c \
										IAIMessage.c \
										IASession.c \
										IASessionModel.c \
										IAIMSignature.c
				
LOCAL_SHARED_LIBRARIES := libcstl libghttp libadapter libimprotocol libpacketconnection

include $(BUILD_SHARED_LIBRARY)
