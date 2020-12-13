LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
MY_IMS_PATH :=  vendor/mediatek/ims

LOCAL_SRC_FILES := \
    src/IRTPController.cpp \
    src/RTPController.cpp \
    src/RTPSender.cpp \
    src/RTPReceiver.cpp \
    src/RTPSource.cpp \
    src/AVCAssembler.cpp \
    src/RTPAssembler.cpp \
    src/HEVCAssembler.cpp

LOCAL_C_INCLUDES := \
    $(MY_IMS_PATH)/rtp/include \
    $(MY_IMS_PATH)/socketwrapper \
    $(MY_IMS_PATH)/signal \
    frameworks/av/media/libstagefright

LOCAL_CFLAGS += -Werror

LOCAL_SHARED_LIBRARIES := \
    libbinder \
    libmedia  \
    libutils  \
    libcutils \
    libstagefright \
    libstagefright_foundation \
    libimsma_socketwrapper \
    libvcodec_cap \
    libimsma_adapt \
    liblog \
    libsignal

LOCAL_MODULE := libimsma_rtp

include $(BUILD_SHARED_LIBRARY)
