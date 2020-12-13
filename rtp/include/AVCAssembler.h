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

#ifndef _IMS_AVC_ASSEMBLER_H_

#define _IMS_AVC_ASSEMBLER_H_

#include "RTPAssembler.h"

#include <utils/List.h>
#include <utils/RefBase.h>
#include <media/stagefright/foundation/ABuffer.h>
#include <media/stagefright/foundation/ADebug.h>
#include <media/stagefright/foundation/AMessage.h>
#include <media/stagefright/foundation/AString.h>
#include <media/stagefright/foundation/AHandler.h>
#include <media/stagefright/foundation/ALooper.h>
using namespace android;
using android::status_t;
#define DEBUG_DUMP_ACCU
#define PACKETLOSTRECORDNUM 16
namespace imsma
{


struct AVCAssembler : public RTPAssembler {
    //ToDo: why shouldn't we define const sp<AMessage> & notify as parameter
    //struct NALFragMentsInfo;

    AVCAssembler(const sp<AMessage> notify);

    uint32_t getLostCount() {
        return mLostCount;
    }

    uint32_t getIDamageCount() {
        return mIDamageNum;
    }


    bool isCSD(const sp<ABuffer>& accessUnit);

protected:
    virtual ~AVCAssembler();
private:
    sp<AMessage> mNotifyMsg;

    //uint32_t mAccessUnitRTPTime;
    bool mNextExpectedSeqNoValid;
    uint32_t mNextExpectedSeqNo;
    bool mAccessUnitDamaged;

    uint64_t mLastPacketReceiveTime;
    List<uint32_t> mPackLostList; //at present, we only register 16 packets
    int64_t mLastLost;

    int32_t mAccuCount;
    int32_t mLostCount;

    int32_t mIDamageNum;

    struct NALFragMentsInfo: public RefBase {

        NALFragMentsInfo() {
            mIsCompleted = false;
            mIsDamaged = false;
            mStartSeqNum = 0;
            mStopSeqNum = 0;
            mTotalCount = 0;
            mNALSize = 0;
            mNALType = 0;
            mNRI = 1;

        }

    protected:
        ~NALFragMentsInfo() {
            if(!mNALFragments.empty()) {
                mNALFragments.clear();
            }
        }

    public:
        bool mIsCompleted;
        bool mIsDamaged;
        uint32_t mStartSeqNum;
        uint32_t mStopSeqNum;
        uint32_t mTotalCount;
        uint32_t mNALSize;
        uint32_t mNALType;
        uint32_t mNRI;
        List<sp<ABuffer> > mNALFragments;


    };

    sp<NALFragMentsInfo> mpNALFragmentInfo;

public:
    virtual AssemblyStatus assembleMore(const sp<RTPSource> source);
    //virtual void onByeReceived();
    virtual void packetLost();
    virtual void packetLostRegister();
    virtual void reset();
    virtual void flushQueue();
private:
    AssemblyStatus addNALUnit(const sp<RTPSource> &source);
    void addSingleNALUnit(const sp<ABuffer> &buffer);
    AssemblyStatus addFragmentedNALUnit(List<sp<ABuffer> > *queue);
    bool addSingleTimeAggregationPacket(const sp<ABuffer> &buffer);
    sp<ABuffer> assembleToNAL(sp<NALFragMentsInfo> nalFragmentInfo);
    void submitAccessUnit(const sp<ABuffer>& accessUnit);

#ifdef DEBUG_DUMP_ACCU
    int64_t mDumpAcuu;
    int mAccuFd;
#endif
    DISALLOW_EVIL_CONSTRUCTORS(AVCAssembler);

};

}  // namespace android

#endif  // _IMS_AVC_ASSEMBLER_H_
