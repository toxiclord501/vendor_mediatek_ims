ifeq ($(TARGET_PROVIDES_MEDIATEK_IMS_STACK),true)

MTK_IMS_ROOT_PATH := $(call my-dir)

# MTK IMS
include $(MTK_IMS_ROOT_PATH)/avsync/Android.mk
include $(MTK_IMS_ROOT_PATH)/comutils/Android.mk
include $(MTK_IMS_ROOT_PATH)/imsma/Android.mk
include $(MTK_IMS_ROOT_PATH)/libimsma_adapt/Android.mk
include $(MTK_IMS_ROOT_PATH)/libvcodec_capenc/Android.mk
include $(MTK_IMS_ROOT_PATH)/rtp/Android.mk

endif # TARGET_PROVIDES_MEDIATEK_IMS_STACK
