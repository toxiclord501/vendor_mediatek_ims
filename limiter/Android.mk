LOCAL_PATH := $(my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := libmtklimiter
LOCAL_MODULE_OWNER := mtk
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE_CLASS := SHARED_LIBRARIES
LOCAL_SRC_FILES_arm := libmtklimiter.so
LOCAL_MODULE_SUFFIX := .so
LOCAL_SRC_FILES_arm64 := lib64mtklimiter.so
LOCAL_MULTILIB := both
LOCAL_CHECK_ELF_FILES := false
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE := libmtklimiter_vendor
LOCAL_PROPRIETARY_MODULE := true
LOCAL_MODULE_OWNER := mtk
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE_CLASS := SHARED_LIBRARIES
LOCAL_SRC_FILES_arm := libmtklimiter_vendor.so
LOCAL_MODULE_SUFFIX := .so
LOCAL_SRC_FILES_arm64 := lib64mtklimiter_vendor.so
LOCAL_MULTILIB := both
LOCAL_SHARED_LIBRARIES := libmtk_drvb
LOCAL_CHECK_ELF_FILES := false
include $(BUILD_PREBUILT)
