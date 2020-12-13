LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
MY_IMS_PATH :=  vendor/mediatek/ims
MY_OMX_PATH :=  vendor/mediatek/ims/include/media/openmax
MY_DPF_PATH :=  vendor/mediatek/ims/include/dpframework

LOCAL_C_INCLUDES:= \
   $(MY_OMX_PATH) \
   $(MY_DPF_PATH) \
   frameworks/native/include/media/openmax \
   frameworks/av/media/libstagefright \
   frameworks/av/include/media/libstagefright/foundation

LOCAL_SRC_FILES := \
   comutils.cpp

LOCAL_CFLAGS += -Werror -Wno-error=deprecated-declarations -Wall

LOCAL_SHARED_LIBRARIES:= \
   libcutils \
   libstagefright_foundation \
   libutils  \
   libstagefright \
   libmedia \
   liblog \
   libhidlbase

USING_MDP_HIDL = yes
LOCAL_SHARED_LIBRARIES += \
   libion \
   vendor.mediatek.hardware.mms@1.0 \
   vendor.mediatek.hardware.mms@1.1

LOCAL_CPPFLAGS += -DUSING_MDP_BY_HIDL

LOCAL_MODULE:= libcomutils
LOCAL_MODULE_TAGS:= optional
include $(BUILD_SHARED_LIBRARY)
