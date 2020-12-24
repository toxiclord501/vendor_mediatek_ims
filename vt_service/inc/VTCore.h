/*
 * Copyright (C) 2016 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef VT_CORE_H
#define VT_CORE_H

#include "VTDef.h"
#include "IVTService.h"
#include "IVTClient.h"
#include "IVTInterface.h"
#include "VTCoreHelper.h"
#include "VTMALStub.h"
#include "VTAVSync.h"

// for HiDL
#include <vendor/mediatek/hardware/videotelephony/1.0/IVideoTelephony.h>

using namespace android;

// for HiDL
using ::android::hidl::base::V1_0::DebugInfo;
using ::android::hidl::base::V1_0::IBase;
using ::vendor::mediatek::hardware::videotelephony::V1_0::IVideoTelephony;
using ::android::hardware::hidl_array;
using ::android::hardware::hidl_memory;
using ::android::hardware::hidl_string;
using ::android::hardware::hidl_vec;
using ::android::hardware::Return;
using ::android::hardware::Void;
using ::android::sp;

namespace VTService {

void vt_callback(int type, void *data, int len);
void vt_rtp_codec_2_ua(int mode, VT_IMCB_CAP * ua, int ssid, int opid);
void vt_ua_2_rtp(int mode, VT_IMCB_CONFIG * ua, rtp_rtcp_config_t * rtp);
void vt_ua_2_codec(int mode, VT_IMCB_CONFIG * ua, video_codec_fmtp_t * codec);
void vt_ut_ua_2_rtp(int mode, VT_IMCB_CAP * ua, rtp_rtcp_config_t * rtp);
void vt_ut_ua_2_codec(int mode, VT_IMCB_CAP * ua, video_codec_fmtp_t * codec);

class IVTServiceCallBack:virtual public RefBase{
 public:
  virtual sp<IVTClient> getClient()=0;
  virtual void notifyCallback(
          int32_t id,
          int32_t msgType,
          int32_t arg1,
          int32_t arg2,
          int32_t arg3,
          const String8 & obj1,
          const String8 & obj2,
          const sp<IGraphicBufferProducer> & obj3)=0;
};

class VTCore: public IVTInterface, virtual public RefBase{
 public:
  explicit VTCore(const sp<IVTServiceCallBack> & user);
  VTCore();
  virtual ~VTCore();

  DECLARE_IVTINTERFACE

  status_t open(VT_SRV_CALL_MODE mode, const int id, const int sim_id);
  status_t init(const int id);
  status_t init_internal(const int id);
  status_t update(const int id);
  status_t updateCallMode(const int id);
  status_t updateTxRxMode(const int id, int new_mode, vt_srv_call_update_info_struct *info);
  status_t deinit(const int id);
  status_t close(const int id, int close_mode);
  status_t close_internal(const int id, int close_mode);
  status_t clearAll(void);
  status_t setHandoverState(bool state);
  status_t setHandoverStateBySimId(int sim_id, bool state);
  status_t setHandoverStateByNetworkId(int network_id, bool state);
  status_t requestCancelSessionModify(const int id, sp<VideoProfile> Vp);

  void notifyError(int id, const char* action);

  virtual void notifyCallback(
          int32_t id,
          int32_t msgType,
          int32_t arg1,
          int32_t arg2,
          int32_t arg3,
          const String8 & obj1,
          const String8 & obj2,
          const sp<IGraphicBufferProducer> & obj3);

  virtual void notifyCallback(
          int32_t id,
          int32_t msgType,
          int32_t arg1,
          int32_t arg2);

  void notifyCallback(
          int32_t id,
          int32_t msgType);

  void getUpdateInfo(int id, VT_IMCB_UPD* pre_config, VT_IMCB_UPD* new_config);
  void resetUpdateInfo(int id);

  sp<IVTServiceCallBack>                  mUser;
  static sp<VTCoreHelper>                 mHelper;

  unsigned int                            mUserID;

 private:
  int                                     mLastRet      = VT_SRV_RET_ERR;
  int                                     mLastNotify   = VT_SRV_ERROR_SERVICE;

  // The map hold the locks for open/init/start/stop/close VTService, App may call them at the same time
  // The different call has the dedicated different lock
  Mutex*                                  mCallFlowLocks[VT_SRV_MA_NR];
  // Lock for Notifycallback(), multiple MA may pass notify to VTcore at the same time
  mutable Mutex                           mNotifyLock;
  // Lock for Notifycallback(), only for error notify event
  mutable Mutex                           mNotifyErrorLock;
  // Lock for MA operation which need to sync each others bwtween MAs
  mutable Mutex                           mMAOperationLock;

  Mutex* getCallFlowLock(int id);
  status_t retriggerUpdate(int id);
};

}  // namespace VTService

#endif
