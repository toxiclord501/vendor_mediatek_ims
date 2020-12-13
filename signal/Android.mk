LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

MY_IMS_PATH :=  vendor/mediatek/ims

LOCAL_SRC_FILES := \
    ImsSignal.cpp

LOCAL_C_INCLUDES := \
    $(MY_IMS_PATH)/signal \
    frameworks/av/media/libstagefright \
    system/core/include/utils

LOCAL_SHARED_LIBRARIES := \
    libcutils\
    libutils \
    libstagefright_foundation \
    liblog

LOCAL_CFLAGS += -Werror -Wno-error=deprecated-declarations -Wall

LOCAL_MODULE := libsignal

LOCAL_MODULE_TAGS := optional

include $(BUILD_SHARED_LIBRARY)
