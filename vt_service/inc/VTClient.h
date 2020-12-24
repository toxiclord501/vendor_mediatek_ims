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

#ifndef VT_CLIENT_H
#define VT_CLIENT_H

#include <utils/Log.h>
#include <stdint.h>

#include "IVTClient.h"
#include "IVTService.h"

namespace VTService {

class VTClient: public BnVTClient, public IBinder::DeathRecipient, public IVTInterface {
 public:
  ~VTClient() {}
  void init();

  static sp<VTClient> getVTClient();
  void releaseVTClient();

  DECLARE_IVTINTERFACE

  void notifyCallback(
          int32_t id,
          int32_t msgType,
          int32_t arg1,
          int32_t arg2,
          int32_t arg3,
          const String8 & obj1,
          const String8 & obj2,
          const sp<IGraphicBufferProducer> & obj3);

  class DeathNotifier: public IBinder::DeathRecipient {
   public:
    DeathNotifier() {}
    virtual void binderDied(const wp<IBinder>& who);
  };

 private:
  VTClient() {}
  VTClient(const VTClient&) {}
  VTClient& operator=(const VTClient);
  virtual void binderDied(const wp<IBinder>& who);
  static sp<DeathNotifier> mDeathNotifier;
  static const sp<IVTService>& getVTService();
  static sp<IVTService> mVTService;

  static Mutex      mLock;
  status_t          mStatus     = UNKNOWN_ERROR;

  friend class DeathNotifier;
};

}  // namespace VTService

#endif
