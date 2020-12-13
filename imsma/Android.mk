LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

MY_IMS_PATH :=  vendor/mediatek/ims

LOCAL_SRC_FILES := \
    ImsMediaReceiver.cpp  \
    ImsMediaSender.cpp \
    ImsMa.cpp \
    ImsMaDebugUtil.cpp

LOCAL_C_INCLUDES := \
    frameworks/native/include/media/hardware \
    frameworks/native/include/gui \
    frameworks/av/media/libstagefright \
    frameworks/av/media \
    frameworks/av/media/libmediametrics/include \
    $(MY_IMS_PATH)/sink \
    $(MY_IMS_PATH)/source \
    $(MY_IMS_PATH)/comutils \
    $(MY_IMS_PATH)/rtp/include \
    $(MY_IMS_PATH)/signal \
    system/netd/include \

LOCAL_SHARED_LIBRARIES := \
    libbinder \
    libcutils \
    libgui \
    libmedia \
    libstagefright \
    libstagefright_foundation \
    libui \
    libutils \
    libsink \
    libsource \
    libvcodec_cap \
    libimsma_rtp \
    libcomutils \
    liblog \
    libsignal	\
    libnetd_client

LOCAL_CFLAGS += -Werror -Wno-error=deprecated-declarations -Wall

LOCAL_MODULE := libimsma

include $(BUILD_SHARED_LIBRARY)
