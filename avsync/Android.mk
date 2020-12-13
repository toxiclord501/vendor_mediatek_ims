LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_C_INCLUDES := \
   vendor/mediatek/ims/avsync/include \
   frameworks/av/media/libstagefright/foundation/include \

LOCAL_CFLAGS += -D__PRODUCTION_RELEASE__ -Werror -Wswitch

LOCAL_SRC_FILES := \
   src/VTAVSync.cpp

LOCAL_SHARED_LIBRARIES := \
   libbinder \
   libutils \
   libcutils \
   liblog

LOCAL_EXPORT_C_INCLUDE_DIRS := \
   $(LOCAL_PATH)/include

LOCAL_MODULE:= libvt_avsync
LOCAL_MODULE_TAGS:= optional
include $(BUILD_SHARED_LIBRARY)
