LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
MY_IMS_PATH :=  vendor/mediatek/ims

LOCAL_SRC_FILES:= \
        Source.cpp \
        EncoderSource.cpp \
        VTCameraSource.cpp

LOCAL_C_INCLUDES:= \
        frameworks/native/include/media/openmax \
        frameworks/native/include/media/hardware \
        frameworks/av/media/libstagefright \
        frameworks/av/media \
        frameworks/av/include \
        frameworks/av/drm/libmediadrm/interface \
        frameworks/av/media/libmediametrics/include \
        system/core/include/utils \
        $(MY_IMS_PATH)/comutils \
        $(MY_IMS_PATH)/signal

LOCAL_SHARED_LIBRARIES:= \
        libbinder \
        libcutils \
        libgui \
        libmedia \
        libstagefright \
        libstagefright_foundation \
        libmedia_omx \
        libui \
        libutils \
        libcamera_client \
        libcomutils \
        libvcodec_cap \
        liblog \
        libsignal \
        libhardware

LOCAL_CFLAGS += -Werror -Wno-error=deprecated-declarations -Wall

# Cross crypto handeling
LOCAL_CFLAGS += -DPLATFORM_VERSION=$(PLATFORM_VERSION)

LOCAL_MODULE:= libsource

LOCAL_MODULE_TAGS:= optional

include $(BUILD_SHARED_LIBRARY)
################################################################################

include $(CLEAR_VARS)

LOCAL_C_INCLUDES:= \
    frameworks/av/camera/ndk/include/camera \
    frameworks/av/media/ndk/include/media \
    frameworks/native/libs/nativewindow/include \
    frameworks/native/include/media/hardware \
    $(MY_IMS_PATH)/comutils \
    $(MY_IMS_PATH)/source

LOCAL_SRC_FILES:= \
        main.cpp

LOCAL_SHARED_LIBRARIES:= \
        libbinder \
        libcutils \
        libcamera_client \
        libgui \
        libmedia \
        libstagefright \
        libstagefright_foundation \
        libui \
        libutils \
        libcamera2ndk \
        libcamera_metadata \
        libsource \
        libcomutils \
        liblog \
        libmedia

LOCAL_MODULE:= source
LOCAL_32_BIT_ONLY := true
LOCAL_MODULE_TAGS:= optional

include $(BUILD_EXECUTABLE)
