LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
MY_IMS_PATH :=  vendor/mediatek/ims

LOCAL_SRC_FILES:= \
        SocketWrapper.cpp \

LOCAL_C_INCLUDES:= \
	$(MY_IMS_PATH)/imsma \
	frameworks/av/media/libstagefright \
	system/netd/include \

LOCAL_CFLAGS += -Werror

LOCAL_SHARED_LIBRARIES := \
      libbinder \
      libmedia \
      libutils \
      libcutils \
      libstagefright \
      libstagefright_foundation \
      libnetd_client \
      liblog

LOCAL_MODULE:= libimsma_socketwrapper

include $(BUILD_SHARED_LIBRARY)
