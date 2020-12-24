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

#ifndef VT_SERVICE_H
#define VT_SERVICE_H

#include "IVTClient.h"
#include "IVTService.h"
#include "VTCore.h"

namespace VTService {

class VTService: public BnVTService, public IBinder::DeathRecipient, public IVTServiceCallBack {
 public:
  VTService() :BnVTService() {}
  virtual ~VTService() {}

  virtual status_t onTransact(uint32_t code, const Parcel& data, Parcel* reply, uint32_t flags);

  const sp<IVTClient>& getVTSClient() const;
  status_t setupVTService(const sp<IVTClient> & VTClient);
  void releaseVTService();
  sp<IVTClient> getClient();

  DECLARE_IVTINTERFACE

  virtual void notifyCallback(
          int32_t id,
          int32_t msgType,
          int32_t arg1,
          int32_t arg2,
          int32_t arg3,
          const String8 & obj1,
          const String8 & obj2,
          const sp<IGraphicBufferProducer> & obj3);

  static sp<VTCore>         mVTCore;

 private:
  virtual void binderDied(const wp<IBinder>& who);

  sp<IBinder>               mPhoneBinder;
  mutable Mutex             mLock;
  wp<IVTClient>             mVTClient;
};

}  // namespace VTService

#endif
