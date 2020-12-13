LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
MY_IMS_PATH :=  vendor/mediatek/ims
MY_OMX_PATH :=  vendor/mediatek/ims/include/media/openmax

LOCAL_SRC_FILES:= \
        Sink.cpp \
        Recorder.cpp \
        Renderer.cpp \
        EncoderContext.cpp \
        MediaAdapter.cpp \
        MediaMuxer.cpp

LOCAL_C_INCLUDES:= \
        frameworks/av/media/libstagefright \
        frameworks/av/media \
        frameworks/av/include \
        frameworks/av/media/libmediametrics/include \
        frameworks/av/media/libstagefright/include \
        frameworks/av/drm/libmediadrm/interface \
        $(MY_OMX_PATH) \
        frameworks/native/include/media/openmax \
        $(MY_IMS_PATH)/comutils \

LOCAL_SHARED_LIBRARIES:= \
        libbinder \
        libcutils \
        libgui \
        libmedia \
        libstagefright \
        libstagefright_foundation \
        libui \
        libutils \
        libcomutils  \
        libvcodec_cap \
        libvt_avsync \
        liblog \
        libmedia \
        libmedia_omx \
        libaudioclient

LOCAL_CFLAGS += -DPLATFORM_VERSION=$(PLATFORM_VERSION)
LOCAL_CFLAGS += -Werror -Wno-error=deprecated-declarations -Wall

LOCAL_MODULE:= libsink

include $(BUILD_SHARED_LIBRARY)

################################################################################

 include $(CLEAR_VARS)

LOCAL_SRC_FILES:= \
        main.cpp

LOCAL_SHARED_LIBRARIES:= \
        libbinder \
        libcutils \
        libgui \
        libmedia \
        libstagefright \
        libstagefright_foundation \
        libui \
        libutils\
        libsink\
        liblog \
        libmedia\
        libaudioclient

LOCAL_MODULE:= sink

include $(BUILD_EXECUTABLE)
