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

#ifndef _IMS_RTP_ASSEMBLER_H_

#define _IMS_RTP_ASSEMBLER_H_

#include <media/stagefright/foundation/ABase.h>
#include <utils/List.h>
#include <utils/StrongPointer.h>
#include <utils/RefBase.h>

#include <utils/List.h>
#include <media/stagefright/foundation/ABuffer.h>
#include <media/stagefright/foundation/ADebug.h>
#include <media/stagefright/foundation/AMessage.h>
#include <media/stagefright/foundation/AString.h>
#include <media/stagefright/foundation/AHandler.h>
#include <media/stagefright/foundation/ALooper.h>
#include "RTPBase.h"
#include "RTPSource.h"
using namespace android;
using android::status_t;

namespace imsma
{

struct RTPAssembler : public RefBase {
    enum AssemblyStatus {
        MALFORMED_PACKET,
        WRONG_SEQUENCE_NUMBER,
        LARGE_SEQUENCE_GAP,
        NOT_ENOUGH_DATA,
        SKIP_MISS_PACKET,
        OK
    };
    enum {
        kWhatAccessUnit = 'accu',
        kWhatPacketLost = 'plst',
    };

    RTPAssembler();

    void onPacketReceived(const sp<RTPSource> &source);
    virtual void flushQueue() = 0;
    virtual void reset() = 0;
    virtual uint32_t getLostCount() = 0;
    virtual uint32_t getIDamageCount() = 0;
    virtual bool isCSD(const sp<ABuffer>& accessUnit) = 0;

    //virtual void onByeReceived() = 0;
protected:
    virtual AssemblyStatus assembleMore(const sp<RTPSource> source) = 0;
    virtual void packetLost() = 0;
    virtual void packetLostRegister() = 0;

    /*
    static void CopyTimes(const sp<ABuffer> &to, const sp<ABuffer> &from);

    static sp<ABuffer> MakeADTSCompoundFromAACFrames(
            unsigned profile,
            unsigned samplingFreqIndex,
            unsigned channelConfig,
            const List<sp<ABuffer> > &frames);

    static sp<ABuffer> MakeCompoundFromPackets(
            const List<sp<ABuffer> > &frames);
    */
private:
    int64_t mFirstFailureTimeUs;
    static const uint32_t kLargeSequenceGap = 20;

    DISALLOW_EVIL_CONSTRUCTORS(RTPAssembler);


    // do something before time established
    /*
    virtual void updatePacketReceived(const sp<RTPSource> &source,
            const sp<ABuffer> &buffer);
    virtual void setNextExpectedSeqNo(uint32_t rtpSeq) {rtpSeq++ ;return; };
    */

protected:
    static void CopyMetas(const sp<ABuffer> &to, const sp<ABuffer> &from);
    // notify ARTPSource to updateExpectedTimeoutUs, mainly for audio
    /*
    virtual void evaluateDuration(const sp<RTPSource> &source,
            const sp<ABuffer> &buffer) {
                  if(source.get()== NULL ||  buffer.get()==NULL)
                        return;

        }*/
    AssemblyStatus getAssembleStatus(List<sp<ABuffer> > *queue,
                                     uint32_t nextExpectedSeq) {
        sp<ABuffer> buffer = *--queue->end();
        uint32_t seq = buffer->int32Data();
        return seq - nextExpectedSeq > kLargeSequenceGap ?
               LARGE_SEQUENCE_GAP : WRONG_SEQUENCE_NUMBER;
    }

};

}  // namespace android

#endif  // _IMS_RTP_ASSEMBLER_H_
