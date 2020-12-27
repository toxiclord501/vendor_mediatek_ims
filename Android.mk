ifeq ($(TARGET_PROVIDES_MEDIATEK_IMS_STACK),true)

MTK_IMS_ROOT_PATH := $(call my-dir)

# MTK IMS
include $(MTK_IMS_ROOT_PATH)/avsync/Android.mk
include $(MTK_IMS_ROOT_PATH)/comutils/Android.mk
include $(MTK_IMS_ROOT_PATH)/imsma/Android.mk
include $(MTK_IMS_ROOT_PATH)/libimsma_adapt/Android.mk
include $(MTK_IMS_ROOT_PATH)/libvcodec_capenc/Android.mk
include $(MTK_IMS_ROOT_PATH)/limiter/Android.mk
include $(MTK_IMS_ROOT_PATH)/packages/Android.mk
include $(MTK_IMS_ROOT_PATH)/rtp/Android.mk
include $(MTK_IMS_ROOT_PATH)/shifter/Android.mk
include $(MTK_IMS_ROOT_PATH)/signal/Android.mk
include $(MTK_IMS_ROOT_PATH)/sink/Android.mk
include $(MTK_IMS_ROOT_PATH)/socketwrapper/Android.mk
include $(MTK_IMS_ROOT_PATH)/source/Android.mk
include $(MTK_IMS_ROOT_PATH)/vcodeccap/Android.mk
include $(MTK_IMS_ROOT_PATH)/vt_process/Android.mk
include $(MTK_IMS_ROOT_PATH)/vt_service/Android.mk
include $(MTK_IMS_ROOT_PATH)/vt_wrapper/Android.mk

# MTK IMS INC
include $(MTK_IMS_ROOT_PATH)/include/audio_utils/Android.mk
include $(MTK_IMS_ROOT_PATH)/include/power_util/Android.mk

endif # TARGET_PROVIDES_MEDIATEK_IMS_STACK
