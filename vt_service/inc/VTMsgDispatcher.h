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

#ifndef _VTMSGDISPATCHER_H
#define _VTMSGDISPATCHER_H

#include "VTDef.h"

using namespace android;

namespace VTService {

struct VTMsgHdlr : public AHandler {
 public:
  VTMsgHdlr(VT_Callback cb) {
      mCb = cb;
  };
  virtual ~VTMsgHdlr(){};
 protected:
  virtual void onMessageReceived(const sp<AMessage> &msg);
  void handleMessage(const sp<AMessage> &msg);
 private:
  VT_Callback  mCb;
};

struct VTPriMsgHdlr : public AHandler {
 public:
  VTPriMsgHdlr(sp<VTMsgHdlr> handler, VT_Callback cb) {
      mCb = cb;
      mHandler = handler;
  };
  virtual ~VTPriMsgHdlr(){};
  void clear();

 protected:
  void onMessageReceived(const sp<AMessage> &msg);

 private:
  VT_Callback  mCb;
  sp<VTMsgHdlr> mHandler;
  void dispatchMessage(const sp<AMessage> &msg);
};

class VTMsgDispatcher : public RefBase {
 public:
  VTMsgDispatcher(VT_Callback cb);
  virtual ~VTMsgDispatcher();
  void dispatchMessage(int type, unsigned char* buf, int len);

 private:
  void init(VT_Callback cb);

  sp<VTPriMsgHdlr>           mVTPriMsgHdlr;
  sp<VTMsgHdlr>              mVTMsgHdlr;
  sp<ALooper>                mDispatchLooper;
  sp<ALooper>                mHandleLooper;
  VT_Callback                mCb;

};

typedef struct {
  sp<VTMsgDispatcher>                 mDispatcher;
}vt_srv_msg_struct;

}

#endif
