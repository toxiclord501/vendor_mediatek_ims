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

#ifndef _IMS_IRTPCONTROLLER_H_
#define _IMS_IRTPCONTROLLER_H_

#include "RTPBase.h"

#include <utils/List.h>
#include <utils/Vector.h>

#include <media/stagefright/foundation/AHandler.h>
#include <media/stagefright/foundation/ABuffer.h>
#include <media/stagefright/foundation/AMessage.h>
#include <media/stagefright/foundation/ALooper.h>


#include <utils/Errors.h>


namespace android
{

class IRTPController :virtual public RefBase
{

public:
    enum decoder_err {
        DecErr_Start                 = 0,
        DecErr_PictureLossIndication = 1,
        DecErr_SliceLossIndication   = 2,
        DecErr_FullIntraRequest      = 3,

        //add here
        DecErr_End                   = 10,
    };
    enum rtp_notification_reason {
        //reason for rtp notify
        kWhatError = 'erro',  //when RTP Reciever have some error
        kWhatTimeOut = 'tiou', //when no packet received during timeout,with trackindex number as param

        kWhatByeReceived = 'rBye',//receive bye rtcp from remote side

        //AVPF notify
        //kWhatNeedRefreshPoint = 'refP',//if receive FIR,PLI and the packet lost info in Generic NAKC is too serious                           // need notify this mess
        kWhatFIR            = 'firn', //full intra request notify
        kWhatSLI            = 'slin', //slice loss indication notify
        kWhatPLI            =  'plin',//picture loss indication notify
        kWhatBandWithChanged = 'badw', // when serveral continuous sending operation consum too much time and too many packet delayed

        kWhatAdjustEncBitRate = 'enbr',
        /*network explicit indication of MBR changed*/
        kWhatUpdateVB       ='upvb', //inform UA to update b=AS
        kWhatDropCall       = 'drop', //recv bitrate less than 172K should downgrade (TMO)
        kWhatUpdateDebugInfo='upde', //updateInfo
        kWhatCoverImg       = 'cvim',
    };

    /**
      *@ Description: static function of get RTP module capability, RTP may support serveral media type
      *@                    and for each media type may be support serverl packetization mode,rtcp fds
      *@
      *@ Parameters:
      *@        [in/out]pRTPCapArray: pointer of pointer  pointing to the first item of the cap array
      *@                              caller can access to the next cap by *pRTPCapArray +1
      *@        [in/out]pNumOfCap: the cap number
      *@        [in]uiMediaType: the media type of which caller wish to get capability, default value is Video
      *@ Return:
      *@    status_t, OK or UNKNOWN_ERROR
      */
    static status_t getCapability(rtp_rtcp_capability_t** pRTPCapArray,uint8_t *pNumOfCap,uint8_t uiMediaType = IMSMA_RTP_VIDEO, uint32_t operatorID = 0);


    /**
      *@ Description: another static function of get RTP module capability, RTP may support serveral media type
      *@                    and for each media type may be support serverl packetization mode,rtcp fds
      *@                caller can choose either one getCapability
      *@ Parameters:
      *@        [in/out]pRTPCapArray: pointer pointing to array of pointers which need allocated by caller
      *@        [in]uiMaxNumOfCap: the entry number of the pointer array from caller
      *@        [in]uiMediaType: the media type of which caller wish to get capability, default value is Video
      *@ Return:
      *@    uint8_t, the actual number of the capability entrys, <= uiMaxNumOfCap
      */
    static uint8_t getCapability(rtp_rtcp_capability_t** pRTPCapArray,uint8_t uiMaxNumOfCap,uint8_t uiMediaType = IMSMA_RTP_VIDEO, uint32_t operatorID = 0);

    /**
      *@ Description: another static function of get RTP module capability, RTP may support serveral media type
      *@                    and for each media type may be support serverl packetization mode,rtcp fds
      *@                caller can choose either one getCapability
      *@ Parameters:
      *@        [in]uiMediaType: the media type of which caller wish to get capability, default value is Video
      *@ Return:
      *@    List<rtp_rtcp_capability_t*>: List of rtp capability pointers
      */
    static List<rtp_rtcp_capability_t*> getCapability(uint8_t uiMediaType = IMSMA_RTP_VIDEO, uint32_t operatorID = 0);

    /**
      *@ Description: static function for create RTP Controller Object
      *@
      *@ Parameters: operatorID
      *@
      *@ Return:
      *@    sp<IRTPController>: a smart pointer pointing to RTP controller oject
      */
    static sp<IRTPController> createRTPController(uint32_t simID,uint32_t operatorID);

    /**
      *@ Description: set event notify, there are maybe some info/error event notify to caller
      *@
      *@ Parameters:
      *@        eventNotify: event notify AMessage,
      *@        caller can get the specific message type by findInt32("what",xxx);
      *@
      *@ Return:
      *@    status_t type, OK indicate successful, otherwise error type will return
      */
    virtual status_t setEventNotify(const sp<AMessage> &eventNotify) = 0;

    /**
      *@ Description: set config params after handshake
      *@
      *@ Parameters:
      *@        [in]pRTPNegotiatedParams: pointer pointing to param struct
      *@        [in]uiMediaType: the media type of which caller wish to set params, default value is Video
      *@ Return:
      *@    status_t type, OK indicate successful, otherwise error type will return
      */
    virtual status_t setConfigParams(rtp_rtcp_config_t* pRTPNegotiatedParams,uint8_t uiMediaType = IMSMA_RTP_VIDEO) = 0;


    /**
      *@ Description: update config params after handshake
      *@                 the params of handshake maybe updated during calling
      *@ Parameters:
      *@        [in]pRTPNegotiatedParams: pointer pointing to param struct
      *@        [in]uiMediaType: the media type of which caller wish to set params, default value is Video
      *@ Return:
      *@    status_t type, OK indicate successful, otherwise error type will return
      */
    virtual status_t updateConfigParams(rtp_rtcp_config_t* pRTPNegotiatedParams,uint8_t uiMediaType = IMSMA_RTP_VIDEO) = 0;


    /**
      *@ Description: set accu notify AMessage to RTP Controller
      *@                 RTP controller will notify the accu buffer containing in the acessUnitNotify
      *@                 accu obeserver can get the accu buffer by findBuffer("access-unit",&accu)
      *@ Parameters:
      *@        [in]accessUnitNotify: AMessage used to notify the accu buffer
      *@        [in]uiMediaType: the media type of which observer wish to listen, default value is Video
      *@ Return:
      *@        status_t type, OK indicate successful, otherwise error type will return
      */
    virtual status_t setAccuNotify(const sp<AMessage> &accessUnitNotify,uint8_t uiMediaType = IMSMA_RTP_VIDEO) = 0;

    /**
      *@ Description: add stream to RTP Controller
      *@
      *@ Parameters:
      *@        [in]rtpPath: path need to add.IMSMA_RTP_UPLINK for uplink path; IMSMA_RTP_DOWNLINK for downlink path
      *@            default is IMSMA_RTP_UP_DOWN_LINK which means both uplink and downlink path
      *@        [in]trackIndex: the media type wish to add, default value is Video
      *@ Return:
      *@        status_t type, OK indicate successful, otherwise error type will return
      */
    virtual status_t addStream(uint8_t rtpPath = IMSMA_RTP_UP_DOWN_LINK, uint8_t trackIndex = IMSMA_RTP_VIDEO) = 0;

    /**
      *@ Description: remove stream from RTP Controller
      *@
      *@ Parameters:
      *@        [in]rtpPath: path need to remove.IMSMA_RTP_UPLINK for uplink path; IMSMA_RTP_DOWNLINK for downlink path
      *@            default is IMSMA_RTP_UP_DOWN_LINK which means both uplink and downlink path
      *@        [in]trackIndex: the media type wish to remove, default value is Video
      *@ Return:
      *@        status_t type, OK indicate successful, otherwise error type will return
      */
    virtual status_t removeStream(uint8_t rtpPath = IMSMA_RTP_UP_DOWN_LINK, uint8_t trackIndex = IMSMA_RTP_VIDEO) = 0;

    /**
      *@ Description: start RTP stream with specific path and media type
      *@
      *@ Parameters:
      *@        [in]rtpPath: path need to start.IMSMA_RTP_UPLINK for uplink path; IMSMA_RTP_DOWNLINK for downlink path
      *@            default is IMSMA_RTP_UP_DOWN_LINK which means both uplink and downlink path
      *@        [in]trackIndex: the media type wish to start, default value is Video
      *@ Return:
      *@        status_t type, OK indicate successful, otherwise error type will return
      */
    virtual status_t start(uint8_t rtpPath = IMSMA_RTP_UP_DOWN_LINK, uint8_t trackIndex = IMSMA_RTP_VIDEO) = 0;

    /**
      *@ Description: pause RTP stream with specific path and media type
      *@
      *@ Parameters:
      *@        [in]rtpPath: path need to pause.IMSMA_RTP_UPLINK for uplink path; IMSMA_RTP_DOWNLINK for downlink path
      *@            default is IMSMA_RTP_UP_DOWN_LINK which means both uplink and downlink path
      *@        [in]trackIndex: the media type wish to pause, default value is Video
      *@ Return:
      *@        status_t type, OK indicate successful, otherwise error type will return
      */
    //virtual status_t pause(uint8_t rtpPath = IMSMA_RTP_UP_DOWN_LINK, uint8_t trackIndex = IMSMA_RTP_VIDEO ) = 0;

    /**
      *@ Description: resume RTP stream with specific path and media type
      *@
      *@ Parameters:
      *@        [in]rtpPath: path need to resume.IMSMA_RTP_UPLINK for uplink path; IMSMA_RTP_DOWNLINK for downlink path
      *@            default is IMSMA_RTP_UP_DOWN_LINK which means both uplink and downlink path
      *@        [in]trackIndex: the media type wish to resume, default value is Video
      *@ Return:
      *@        status_t type, OK indicate successful, otherwise error type will return
      */
    //virtual status_t resume(uint8_t rtpPath = IMSMA_RTP_UP_DOWN_LINK, uint8_t trackIndex = IMSMA_RTP_VIDEO ) = 0;

    /**
      *@ Description: stop RTP stream with specific path and media type
      *@
      *@ Parameters:
      *@        [in]rtpPath: path need to stop.IMSMA_RTP_UPLINK for uplink path; IMSMA_RTP_DOWNLINK for downlink path
      *@            default is IMSMA_RTP_UP_DOWN_LINK which means both uplink and downlink path
      *@        [in]trackIndex: the media type wish to stop, default value is Video
      *@ Return:
      *@        status_t type, OK indicate successful, otherwise error type will return
      */
    virtual status_t stop(uint8_t rtpPath = IMSMA_RTP_UP_DOWN_LINK, uint8_t trackIndex = IMSMA_RTP_VIDEO) = 0;

    /**
      *@ Description: queue access unit to RTP controller
      *@
      *@ Parameters:
      *@        [in]buffer: access unit buffer
      *@        [in]trackIndex: the media type the buffer related to, default value is Video
      *@ Return:
      *@        status_t type, OK indicate successful, otherwise error type will return
      */
    virtual status_t queueAccessUnit(const sp<ABuffer> &buffer,uint8_t trackIndex = IMSMA_RTP_VIDEO) = 0;

    /**
      *@ Description: if caller received the message of peer has paused sending Stream
      *@                 for example: peer camera off, mute event
      *@ Parameters:
      *@        [in]trackIndex: the media type related to, default value is Video
      *@ Return:
      *@        status_t type, OK indicate successful, otherwise error type will return
      */
    virtual status_t peerPausedSendStream(uint8_t trackIndex = IMSMA_RTP_VIDEO) = 0;

    /**
      *@ Description: if caller received the message of peer has resume sending Stream
      *@                 for example: peer camera re-on, un-mute event
      *@ Parameters:
      *@        [in]trackIndex: the media type related to, default value is Video
      *@ Return:
      *@        status_t type, OK indicate successful, otherwise error type will return
      */
    virtual status_t peerResumedSendStream(uint8_t trackIndex = IMSMA_RTP_VIDEO) = 0;


    /**
      *@ Description: set CVO(Coordination of Video Orientation)
      *@                 RTP controller will contain orientation info to each rtp packet after receive thie message
      *@                 But the suggested way is that the caller contain the orientation related to a buffer
      *@                 into the buffer meta when queueAccessUnit
      *@
      *@ Parameters:
      *@        [in]rotation: rotation info,in Clockwise angle
      *@        [in] camera_facing: camer facing info, default is 0 (Front-facing camera)
      *@        [in] flip: flip info, default is 0 (No flip operation)
      *@ Return:
      *@        status_t type, OK indicate successful, otherwise error type will return
      */
    virtual status_t setVideoOrientation(uint8_t rotation,uint8_t camera_facing = 0,uint8_t flip = 0) = 0;

    /************************ AVPF **************************************
    ********************************************************************/
    /**
      *@ Description: decoder inform some decoder error info to RTP,
      *@                 error info like sli,pli,fir, which need inform to peer encoder to enhance error resilience
      *@
      *@ Parameters:
      *@        [in]errInfo:errInfo
      *@        RTP will find specific err by the following method
      *@        errInfo->findInt32("err",&err_type);
      *@        err_type value is like this defined above
      *@            DecErr_PictureLossIndication = 1,
      *@            DecErr_SliceLossIndication   = 2,
      *@            DecErr_FullIntraRequest      = 3,
      *@ Return:
      *@        void
      */
    virtual void feedBackDecoderError(sp<AMessage> errInfo,uint8_t trackIndex = IMSMA_RTP_VIDEO) = 0;

    /**
      *@ Description: decoder inform RTP decoder refresh point received,
      *@ Parameters:
      *@        default video track
      *@ Return:
      *@        void
      */
    virtual void recvDecoderRefreshPoint(uint8_t trackIndex = IMSMA_RTP_VIDEO) = 0;


    /**
    *@ Description: set handover state for disable downgrade check
    *@ Parameters:
    *@      state: 1-start handover 0-stop handover
    *@ Return:
    *@      void
    */
    virtual status_t setHandoverState(int32_t state) = 0;

    IRTPController();


protected:
    virtual ~IRTPController();

private:
    static uint8_t sVideoCapParamsNum;
    static uint32_t opID;

    static rtp_rtcp_capability_t* sVideoCapParamsFirstItem;

    //another way getCap
    static rtp_rtcp_capability_t** sVideoCapParams;

    //another way getCap
    static List<rtp_rtcp_capability_t*> sVideoCapParamsList;
    static List<rtp_rtcp_capability_t*> sAudioCapParamsList;

    static uint8_t getRtpProfile(uint32_t operatorID);
};
}//namespace imsma
#endif // _IMS_IRTPCONTROLLER_H_
