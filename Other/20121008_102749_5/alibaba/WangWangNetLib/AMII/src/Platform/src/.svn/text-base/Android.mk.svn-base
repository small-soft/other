#by tom.lih
LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

#for android platform
WITH_ANDROID_LOG = true
TAEGET_MODULE_STATIC =true

# adapter								
LOCAL_MODULE    := libaliadapter

# header
LOCAL_CFLAGS += -I$(LOCAL_PATH)/../inc \
                -I$(LOCAL_PATH)/../../../inc/Platform \
                -I$(LOCAL_PATH)/../../../inc/3rdLib/cstl \
                -DADAPTER_API= 

ifeq ($(WITH_ANDROID_LOG),true)  
	LOCAL_CFLAGS += -DANDROID_BUILD 
endif
								
# source
LOCAL_SRC_FILES :=  linux/AMFs.c \
					linux/AMLog.c \
					linux/AMLooper.c \
					linux/AMLooperMessage.c \
					linux/AMSocket.c \
					linux/AMString.c \
					linux/AMThread.c \
					linux/AMThreadCond.c \
					linux/AMThreadMutex.c \
					linux/AMTime.c \
					linux/AMTimer.c \
					linux/AMMemory.c \
					linux/AMMemoryTable.c \
					AMTask.c

#original dependency
#LOCAL_STATIC_LIBRARIES := libcstl 
LOCAL_STATIC_LIBRARIES := libcstl libzlib2 libutil  libghttp


ifeq ($(WITH_ANDROID_LOG),true)  
	LOCAL_LDLIBS := -llog 
endif

ifeq ($(TAEGET_MODULE_STATIC),true)  
	include $(BUILD_STATIC_LIBRARY)
else  
	include $(BUILD_SHARED_LIBRARY)	
endif





