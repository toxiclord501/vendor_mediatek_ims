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

#include <utils/Log.h>
#include <stdint.h>
#include "IVTClient.h"
#include "IVTInterface.h"

namespace VTService {

enum {
    TRANS_BEGIN = IBinder::FIRST_CALL_TRANSACTION,
    NOTIFY_CALLBACK,
};

class BpVTClient: public BpInterface<IVTClient> {
 public:
  explicit BpVTClient(const sp<IBinder>& impl):BpInterface<IVTClient>(impl) {}

  virtual void notifyCallback(
          int32_t id,
          int32_t msgType,
          int32_t arg1,
          int32_t arg2,
          int32_t arg3,
          const String8 & obj1,
          const String8 & obj2,
          const sp<IGraphicBufferProducer> & obj3) {
      Parcel data, reply;
      data.writeInterfaceToken(IVTClient::getInterfaceDescriptor());
      data.writeInt32(id);
      data.writeInt32(msgType);
      data.writeInt32(arg1);
      data.writeInt32(arg2);
      data.writeInt32(arg3);
      data.writeString8(obj1);
      data.writeString8(obj2);
      data.writeStrongBinder(obj3->asBinder(obj3));
      remote()->transact(NOTIFY_CALLBACK, data, &reply);
  }
};

IMPLEMENT_META_INTERFACE(VTClient, "android.hardware.IVTClient");

status_t BnVTClient::onTransact(uint32_t code, const Parcel& data, Parcel * reply, uint32_t flags) {
    switch (code) {
        case NOTIFY_CALLBACK: {
            CHECK_INTERFACE(IVTClient, data, reply);
            int32_t id = data.readInt32();
            int32_t msgType = data.readInt32();
            int32_t arg1 = data.readInt32();
            int32_t arg2 = data.readInt32();
            int32_t arg3 = data.readInt32();
            const String8 obj1(data.readString8());
            const String8 obj2(data.readString8());
            sp<IGraphicBufferProducer> obj3
                    = interface_cast<IGraphicBufferProducer> (data.readStrongBinder());

            notifyCallback(
                    id,
                    msgType,
                    arg1,
                    arg2,
                    arg3,
                    obj1,
                    obj2,
                    obj3);

            return NO_ERROR;
        }
        break;

        default:
            return BBinder::onTransact(code, data, reply, flags);
    }
}

}
