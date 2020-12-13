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

#ifndef __VTAVSYNC_H__
#define __VTAVSYNC_H__

#include <utils/RefBase.h>
#include <utils/threads.h>
#include <media/stagefright/foundation/ADebug.h>
#include <assert.h>

using namespace android;

namespace VTService {

#define VOLTE_AV_DEV_NAME "/dev/ccci_imsdc"

#define NS_TO_NTP (4.3)
#define US_TO_NTP (4294)

// Hide Debug msg in user/userdebug load
#ifdef __PRODUCTION_RELEASE__
    #define VTAVSYNC_LOGD(...)
#else
    #define VTAVSYNC_LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG  , "AVSync ", ##__VA_ARGS__);
#endif

#define     VTAVSYNC_LOGI(...)  __android_log_print(ANDROID_LOG_INFO   , "AVSync ", ##__VA_ARGS__);
#define     VTAVSYNC_LOGW(...)  __android_log_print(ANDROID_LOG_WARN   , "AVSync ", ##__VA_ARGS__);
#define     VTAVSYNC_LOGE(...)  __android_log_print(ANDROID_LOG_ERROR  , "AVSync ", ##__VA_ARGS__);

#define VTAVSYNC_ASSERT(expr, M, ...) while(!(expr)) { VTAVSYNC_LOGE("@@@ ASSERT @@@: (%s:%d)" M, __FILE__, __LINE__, ##__VA_ARGS__); fflush(stdout); LOG_ALWAYS_FATAL("ASSERT!!!!"); assert(0); exit(-11);}

    typedef enum av_msg_type{
        AV_ZERO = 0,
        AV_UL_NTP,
        AV_DL_AUDIO_NTP,
        AV_DL_AUDIO_RESET,
        AV_MAX = 0xFFFFFFFF
    }av_msg_e;

    typedef struct av_msg{
        av_msg_e type; /* rtp or rtcp */
        unsigned integer;
        unsigned fraction;
    } av_msg_t;

    typedef struct av_param {
        /*System Time*/
        unsigned long long  st;
        /*NTP in nano second*/
        uint64_t nsNTP;
    }av_param_t;

    class VTAVSync : public RefBase {
        public:
            VTAVSync();
            virtual ~VTAVSync();
            static void getDLAudioTimeStamp(int64_t *pAudioTime);
        private:
            void resetParam(void);
            int openFD(void);
            int closeFD(void);
            int writeFD(int fd, void *buffer, int size);
            void checkFD(void);
            void HandleDLAVSync(unsigned char* buffer);
            void avInit(void);
            static void *downlinkThread(void *arg);

            static av_param_t mAV;
    };

}
#endif
