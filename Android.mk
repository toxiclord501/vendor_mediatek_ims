ifeq ($(TARGET_PROVIDES_MEDIATEK_IMS_STACK),true)

MTK_IMS_ROOT_PATH := $(call my-dir)

# MTK IMS
include $(MTK_IMS_ROOT_PATH)/audio_utils/Android.mk
include $(MTK_IMS_ROOT_PATH)/avsync/Android.mk
include $(MTK_IMS_ROOT_PATH)/comutils/Android.mk
include $(MTK_IMS_ROOT_PATH)/imsma/Android.mk
include $(MTK_IMS_ROOT_PATH)/libimsma_adapt/Android.mk
include $(MTK_IMS_ROOT_PATH)/libvcodec_capenc/Android.mk
include $(MTK_IMS_ROOT_PATH)/limiter/Android.mk
include $(MTK_IMS_ROOT_PATH)/rtp/Android.mk
include $(MTK_IMS_ROOT_PATH)/signal/Android.mk
include $(MTK_IMS_ROOT_PATH)/sink/Android.mk
include $(MTK_IMS_ROOT_PATH)/socketwrapper/Android.mk
include $(MTK_IMS_ROOT_PATH)/source/Android.mk
include $(MTK_IMS_ROOT_PATH)/vcodeccap/Android.mk

endif # TARGET_PROVIDES_MEDIATEK_IMS_STACK
