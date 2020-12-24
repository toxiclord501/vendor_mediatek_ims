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

#ifndef IVT_INTERFACE_H
#define IVT_INTERFACE_H

#include "VTDef.h"
#include <Surface.h>
#include <binder/IMemory.h>
#include <utils/String8.h>
#include <utils/Errors.h>
#include <utils/RefBase.h>

using namespace android;

namespace VTService {

class IVTInterface: virtual public RefBase {
 public:
  virtual status_t initialization(int mode, int id, int sim_id)=0;
  virtual status_t finalization(int id)=0;
  virtual status_t setCamera(int id, int cam)=0;
  virtual status_t setPreviewSurface(int id, const sp<VTSurface> & surface)=0;
  virtual status_t setDisplaySurface(int id, const sp<VTSurface> & surface)=0;
  virtual status_t setCameraParameters(int sim_id, int sensorCnt, sensor_info_vilte_t *sensor)=0;
  virtual status_t setCameraParametersOnly(int sensorCnt, sensor_info_vilte_t *sensor)=0;
  virtual status_t setCameraParametersWithSim(int sim_id, int major_sim_id, int sensorCnt, sensor_info_vilte_t *sensor)=0;
  virtual status_t setDeviceOrientation(int id, int rotation)=0;
  virtual status_t setUIMode(int id, VT_SRV_UI_MODE mode)=0;

  virtual status_t requestSessionModify(int id, const String8 &  config)=0;
  virtual status_t responseSessionModify(int id, const String8 &  config)=0;

  virtual status_t snapshot(int id, VT_SRV_SNAPSHOT_TYPE type, String8 savingImgURI)=0;
  virtual status_t startRecording(int id, VT_SRV_RECORD_TYPE type, String8 path, int maxSize)=0;
  virtual status_t stopRecording(int id)=0;

  virtual status_t switchFeature(int id, int feature, int isOn)=0;
  virtual status_t updateNetworkTable(bool is_add, int network_id, String8 if_name)=0;

  virtual ~IVTInterface(){};
// ### You don't need a ; after a }
};

class IVTNotifyCallback: virtual public RefBase {
 public:
  virtual void notifyCallback(
      int id,
      int msg,
      int arg1,
      int arg2,
      int arg3,
      const String8 & obj1,
      const String8 & obj2,
      const sp<IGraphicBufferProducer> & obj3)=0;

  virtual ~IVTNotifyCallback(){};
// ### You don't need a ; after a }
};

#define DECLARE_IVTINTERFACE \
    virtual status_t initialization(int mode, int id, int sim_id); \
    virtual status_t finalization(int id); \
    virtual status_t setCamera(int id, int cam); \
    virtual status_t setPreviewSurface(int id, const sp<VTSurface> & surface); \
    virtual status_t setDisplaySurface(int id, const sp<VTSurface> & surface); \
    virtual status_t setCameraParameters(int sim_id, int sensorCnt, sensor_info_vilte_t *sensor); \
    virtual status_t setCameraParametersOnly(int sensorCnt, sensor_info_vilte_t *sensor); \
    virtual status_t setCameraParametersWithSim(int sim_id, int major_sim_id, int sensorCnt, sensor_info_vilte_t *sensor); \
    virtual status_t setDeviceOrientation(int id, int rotation); \
    virtual status_t setUIMode(int id, VT_SRV_UI_MODE mode); \
    virtual status_t requestSessionModify(int id, const String8 &  config); \
    virtual status_t responseSessionModify(int id, const String8 &  config); \
    virtual status_t switchFeature(int id, int feature, int isOn); \
    virtual status_t snapshot(int id, VT_SRV_SNAPSHOT_TYPE type, String8 savingImgURI); \
    virtual status_t startRecording(int id, VT_SRV_RECORD_TYPE type, String8 path, int maxSize); \
    virtual status_t stopRecording(int id); \
    virtual status_t updateNetworkTable(bool is_add, int network_id, String8 if_name);
}  // namespace VTService

#endif
