LOCAL_PATH:= $(call my-dir)
MY_IMS_PATH :=  vendor/mediatek/ims

include $(CLEAR_VARS)

LOCAL_MODULE_TAGS := optional

LOCAL_SRC_FILES:= \
    src/VcodecCap.cpp \
    src/VcodecCap_h264mp.cpp \
    src/VcodecCap_hevcmp.cpp \
    src/VcodecCap_utility.cpp \
    src/VcodecCap_inst.cpp

LOCAL_C_INCLUDES := \
    $(MY_IMS_PATH)/vcodeccap/include

LOCAL_EXPORT_C_INCLUDE_DIRS := $(LOCAL_PATH)/include

LOCAL_SHARED_LIBRARIES := \
    libui libcutils libutils libbinder libexpat liblog libvcodec_capenc libstagefright_omx_utils libstagefright_foundation libion

LOCAL_SHARED_LIBRARIES += android.hardware.graphics.bufferqueue@2.0

LOCAL_MODULE := libvcodec_cap
LOCAL_PRELINK_MODULE := false
include $(BUILD_SHARED_LIBRARY)
