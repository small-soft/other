#
#by lih £¬for linux x86
#
CC := gcc
AR := ar

#GENERIC_CFLAGS := '-march=armv5' '-mno-thumb-interwork'
GENERIC_CFLAGS :=  
GENERIC_LDFLAGS :=

NDK_HEADER_DIR =/include /lih/dev/ndk/android-ndk-r7b/platforms/android-14/arch-x86/usr

PRJ_ROOT := .

ZLIBSRC_ROOT := $(PRJ_ROOT)/AMII/src/3rdLib/zlib2
UTILSRC_ROOT := $(PRJ_ROOT)/AMII/src/3rdLib/util
CSTLSRC_ROOT := $(PRJ_ROOT)/AMII/src/3rdLib/cstl
HTTPSRC_ROOT := $(PRJ_ROOT)/AMII/src/3rdLib/ghttp/linux
SQLITE_ROOT := $(PRJ_ROOT)/AMII/src/3rdLib/sqlite3/src
ADAPTER_ROOT := $(PRJ_ROOT)/AMII/src/Platform/src

C_SOURCE := $(PRJ_ROOT)/IAIMServiceGrp/src/AMAccountModel.c \
					$(PRJ_ROOT)/IAIMServiceGrp/src/AMImUtil.c \
					$(PRJ_ROOT)/IAIMServiceGrp/src/IAccount.c \
					$(PRJ_ROOT)/IAIMServiceGrp/src/IAContact.c \
					$(PRJ_ROOT)/IAIMServiceGrp/src/IAContactModel.c \
					$(PRJ_ROOT)/IAIMServiceGrp/src/IAGroup.c \
					$(PRJ_ROOT)/IAIMServiceGrp/src/IAIM.c \
					$(PRJ_ROOT)/IAIMServiceGrp/src/IAIMessage.c \
					$(PRJ_ROOT)/IAIMServiceGrp/src/IASession.c \
					$(PRJ_ROOT)/IAIMServiceGrp/src/IASessionModel.c \
					$(PRJ_ROOT)/IAIMServiceGrp/src/IAIMSignature.c\
					\
					$(PRJ_ROOT)/IAIMServiceGrp/jni/CallbackAdapter.c \
					$(PRJ_ROOT)/IAIMServiceGrp/jni/ChatSession.c \
					$(PRJ_ROOT)/IAIMServiceGrp/jni/ConnectionAdapter.c \
					$(PRJ_ROOT)/IAIMServiceGrp/jni/IMService.c \
					\
					$(PRJ_ROOT)/IMProtocolApi/MIMNet/src/IMnetCallback.c \
					$(PRJ_ROOT)/IMProtocolApi/MIMNet/src/IMnetMain.c \
					$(PRJ_ROOT)/IMProtocolApi/MIMNet/src/IMnetPacket.c \
					$(PRJ_ROOT)/IMProtocolApi/MIMNet/src/IMnetRequest.c \
					$(PRJ_ROOT)/IMProtocolApi/MIMNet/src/IMnetUtility.c \
					\
					$(PRJ_ROOT)/PacketConnection/src/PCContext.c \
					$(PRJ_ROOT)/PacketConnection/src/PCCore.c \
					$(PRJ_ROOT)/PacketConnection/src/PCEvent.c \
					$(PRJ_ROOT)/PacketConnection/src/PCMgr.c \
					$(PRJ_ROOT)/PacketConnection/src/PCUtility.c \
					\
					$(ZLIBSRC_ROOT)/src/adler32.c \
					$(ZLIBSRC_ROOT)/src/compress.c \
					$(ZLIBSRC_ROOT)/src/crc32.c \
					$(ZLIBSRC_ROOT)/src/deflate.c \
					$(ZLIBSRC_ROOT)/src/gzio.c \
					$(ZLIBSRC_ROOT)/src/infback.c \
					$(ZLIBSRC_ROOT)/src/inffast.c \
					$(ZLIBSRC_ROOT)/src/inflate.c \
					$(ZLIBSRC_ROOT)/src/inftrees.c \
					$(ZLIBSRC_ROOT)/src/trees.c \
					$(ZLIBSRC_ROOT)/src/uncompr.c \
					$(ZLIBSRC_ROOT)/src/zutil.c \
					\
					$(UTILSRC_ROOT)/src/charset/ascii.c \
					$(UTILSRC_ROOT)/src/charset/utf8.c \
					$(UTILSRC_ROOT)/src/charset/asciitbl.c \
					$(UTILSRC_ROOT)/src/r_keygen.c \
					$(UTILSRC_ROOT)/src/r_random.c \
					$(UTILSRC_ROOT)/src/base64.c \
					$(UTILSRC_ROOT)/src/r_stdlib.c \
					$(UTILSRC_ROOT)/src/des_help.c \
					$(UTILSRC_ROOT)/src/rsa.c \
					$(UTILSRC_ROOT)/src/desc.c \
					$(UTILSRC_ROOT)/src/shsc.c \
					$(UTILSRC_ROOT)/src/md5c.c \
					$(UTILSRC_ROOT)/src/charset/utf16.c \
					$(UTILSRC_ROOT)/src/nn.c \
					$(UTILSRC_ROOT)/src/prime.c \
					\
					$(CSTLSRC_ROOT)/src/clist.c \
					$(CSTLSRC_ROOT)/src/conversions.c \
					$(CSTLSRC_ROOT)/src/hashtable.c \
					$(CSTLSRC_ROOT)/src/node.c \
					$(CSTLSRC_ROOT)/src/binary_tree.c \
					$(CSTLSRC_ROOT)/src/deque.c \
					$(CSTLSRC_ROOT)/src/heap.c \
					$(CSTLSRC_ROOT)/src/priority_queue.c \
					$(CSTLSRC_ROOT)/src/queue.c \
					$(CSTLSRC_ROOT)/src/stack.c \
					$(CSTLSRC_ROOT)/src/vector.c \
					\
					$(HTTPSRC_ROOT)/ghttp.c\
					$(HTTPSRC_ROOT)/http_base64.c\
					$(HTTPSRC_ROOT)/http_date.c\
					$(HTTPSRC_ROOT)/http_hdrs.c\
					$(HTTPSRC_ROOT)/http_req.c\
					$(HTTPSRC_ROOT)/http_resp.c\
					$(HTTPSRC_ROOT)/http_trans.c\
					$(HTTPSRC_ROOT)/http_uri.c\
					\
					$(ADAPTER_ROOT)/linux/AMFs.c\
					$(ADAPTER_ROOT)/linux/AMLog.c\
					$(ADAPTER_ROOT)/linux/AMMemory.c\
					$(ADAPTER_ROOT)/linux/AMMemoryTable.c\
					$(ADAPTER_ROOT)/linux/AMSocket.c\
					$(ADAPTER_ROOT)/linux/AMThread.c\
					$(ADAPTER_ROOT)/linux/AMThreadMutex.c\
					$(ADAPTER_ROOT)/linux/AMThreadCond.c\
					$(ADAPTER_ROOT)/linux/AMTime.c\
					$(ADAPTER_ROOT)/linux/AMString.c\
					$(ADAPTER_ROOT)/linux/AMStdlib.c \
					$(ADAPTER_ROOT)/linux/AMLooper.c\
					$(ADAPTER_ROOT)/linux/AMLooperMessage.c\
					$(ADAPTER_ROOT)/AMTask.c

C_OBJECTS := $(C_SOURCE:.c=.o)
CPP_OBJECTS := $(CPP_SOURCE:.cpp=.o)

INCLUDE_PATH := $(PRJ_ROOT)/IAIMServiceGrp/include \
				$(PRJ_ROOT)/IMProtocolApi/MIMNet/inc \
				$(PRJ_ROOT)/PacketConnection/inc \
				$(PRJ_ROOT)/AMII/inc/3rdLib/cstl \
				$(PRJ_ROOT)/AMII/inc/3rdLib/cstl\gen \
				$(PRJ_ROOT)/AMII/inc/3rdLib/zlib2 \
				$(PRJ_ROOT)/AMII/inc/3rdLib/ghttp \
				$(PRJ_ROOT)/AMII/inc/Platform \
				$(PRJ_ROOT)/AMII/src/Platform/inc \
				$(PRJ_ROOT)/AMII/inc/3rdLib/util \
				$(PRJ_ROOT)/AMII/inc/3rdLib/sqlite3 \
				$(NDK_HEADER_DIR)/include

#CFLAGS := $(GENERIC_CFLAGS) $(addprefix -I, $(INCLUDE_PATH)) -DADAPTER_API=  -DDLLTEST_API= -DAMOS= -DAMOS_DEBUG -DTARGET_VMKIT
CFLAGS := $(GENERIC_CFLAGS) $(addprefix -I, $(INCLUDE_PATH)) -DAMOS -DAMOS_DEBUG  -DAPM_MACRO_GET_OPERATION_MSG -DANDROID_BUILD -DADAPTER_API= -DANDROID  
LDFLAGS := $(GENERIC_LDFLAGS) 


.PHONY: clean
.PHONY: all

all: $(C_OBJECTS) $(CPP_OBJECTS)
	@$(AR) -r libiaimapi.a $(C_OBJECTS) $(CPP_OBJECTS)
	@$(CC) -shared $(LDFLAGS) -o libiaimapi.so $(C_OBJECTS) $(CPP_OBJECTS)

$(C_OBJECTS): %.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

$(CPP_OBJECTS): %.o: %.cpp
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	@rm -f $(C_OBJECTS)
	@rm -f $(CPP_OBJECTS)
	@rm -f lib*.a lib*.so

