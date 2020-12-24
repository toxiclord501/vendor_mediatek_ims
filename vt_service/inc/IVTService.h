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

#ifndef IVT_SERVICE_H
#define IVT_SERVICE_H

#include "IVTInterface.h"
#include "IVTClient.h"
#include <binder/IInterface.h>
#include <binder/Parcel.h>
#include <binder/IServiceManager.h>
#include <binder/IPCThreadState.h>

namespace VTService {
class IVTService:public IInterface, public IVTInterface {
 public:
  enum{
      SETUP_SERVICE  = IBinder::FIRST_CALL_TRANSACTION,
      RELEASE_SERVICE,
      INITIALIZATION,
      FINALIZATION,
      SET_CAMERA,
      SET_LOCAL_SURFACE,
      SET_PEER_SURFACE,
      SET_CAMERA_PARAM,
      SET_CAMERA_PARAM_ONLY,
      SET_CAMERA_PARAM_WITH_SIM,
      SET_ROTATION,
      SET_UI_MODE,
      REQ_SESSION_MODIFY,
      RES_SESSION_MODIFY,
      SNAPSHOT,
      START_RECORD,
      STOP_RECORD,
      SWITCH_FEATURE,
      UPDATE_NETWORK_TABLE
  };
  DECLARE_META_INTERFACE(VTService);
  virtual status_t setupVTService(const sp<IVTClient> & client)=0;
  virtual void releaseVTService()= 0;
};

class BnVTService: public BnInterface<IVTService> {
 public:
  virtual status_t onTransact(uint32_t code,
          const Parcel& data,
          Parcel * reply,
          uint32_t flags = 0);
};

}  // namespace VTService

#endif
