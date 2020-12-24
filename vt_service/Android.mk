LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_PRELINK_MODULE := false

FRAMEWORKS_NATIVE_INLCUDE_GUI_PATH:= frameworks/native/include/gui
FRAMEWORKS_NATIVE_INLCUDE_PATH:= frameworks/native/include
FRAMEWORKS_MEDIA_INLCUDE_PATH1:= frameworks/av/media/libmediametrics/include
FRAMEWORKS_MEDIA_INLCUDE_PATH2:= frameworks/av/include/media/stagefright/foundation
FRAMEWORKS_PATH:= frameworks/av
AVSYNC_PATH:= vendor/mediatek/ims/avsync/include
IMS_MD_INC:= vendor/mediatek/ims/include/volte_header/volte_imcb/sap
HAL_PATH:= vendor/mediatek/ims/vt_hal/inc
IMSMA_INC1:= vendor/mediatek/ims/imsma
IMSMA_INC2:= frameworks/native/include/binder
RTP_INC:= vendor/mediatek/ims/rtp/include
SOURCE_INC:= vendor/mediatek/ims/source
SINK_INC:= vendor/mediatek/ims/sink
RIL_INC_PATH:= vendor/mediatek/ims/include/ril/include
SERVICE_INC_PATH:= $(LOCAL_PATH)/inc
SERVICE_SRC_PATH:= src

LOCAL_LDLIBS :=  -L$(SYSROOT)/usr/lib -llog

LOCAL_C_INCLUDES += \
  $(SERVICE_INC_PATH) \
  $(JNI_H_INCLUDE) \
  $(FRAMEWORKS_MEDIA_INLCUDE_PATH1) \
  $(FRAMEWORKS_NATIVE_INLCUDE_GUI_PATH) \
  $(FRAMEWORKS_NATIVE_INLCUDE_PATH) \
  $(FRAMEWORKS_MEDIA_INLCUDE_PATH2) \
  $(FRAMEWORKS_PATH)/include/media \
  $(AVSYNC_PATH) \
  $(IMS_MD_INC) \
  $(HAL_PATH) \
  $(IMSMA_INC1) \
  $(IMSMA_INC2) \
  $(SOURCE_INC) \
  $(SINK_INC) \
  $(RTP_INC) \
  $(RIL_INC_PATH)

LOCAL_SRC_FILES:= \
  $(SERVICE_SRC_PATH)/IVTClient.cpp \
  $(SERVICE_SRC_PATH)/IVTService.cpp \
  $(SERVICE_SRC_PATH)/VTMALStub.cpp \
  $(SERVICE_SRC_PATH)/VTCore.cpp \
  $(SERVICE_SRC_PATH)/VTCoreHelper.cpp \
  $(SERVICE_SRC_PATH)/VTService.cpp \
  $(SERVICE_SRC_PATH)/VTMsgDispatcher.cpp

LOCAL_SHARED_LIBRARIES:= \
  libc \
  libandroid_runtime \
  libbinder \
  libutils \
  libcutils \
  libnativehelper \
  libui \
  libgui \
  libmedia \
  libandroid_runtime \
  libbase \
  libfmq \
  vendor.mediatek.hardware.videotelephony@1.0 \
  libhidlbase \
  libimsma \
  libsource \
  libimsma_rtp \
  libvt_avsync \
  libstagefright_foundation \
  libvcodec_cap

LOCAL_MODULE:= libmtk_vt_service
LOCAL_MULTILIB := 32

# For Imcb Needed
LOCAL_CFLAGS += -D __IMCF_MTK_VA__=1 -D __IMCF_NO_UA__=1

ifeq ($(TARGET_SIMULATOR),true)
LOCAL_CFLAGS += -DSINGLE_PROCESS
endif

include $(BUILD_SHARED_LIBRARY)
