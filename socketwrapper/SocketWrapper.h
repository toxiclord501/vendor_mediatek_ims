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

#ifndef __SOCKETWRAPPER_H__
#define __SOCKETWRAPPER_H__

#include <media/stagefright/foundation/ABuffer.h>
#include <media/stagefright/foundation/ADebug.h>
#include <utils/RefBase.h>
#include <utils/threads.h>
#include <assert.h>

#define CONNECT_UDP

using namespace android;

#define VOLTE_IPADDR_LENGTH 16
#define VOLTE_LOOP_EBI 100
#define VOLTE_WIFI_EBI 200
#define VOLTE_VT_DEV_NAME "/dev/ccci_imsv"
#define VOLTE_AV_DEV_NAME "/dev/ccci_imsdc"

enum VoLTE_Event_IP_Version_e {
    VoLTE_Event_IPv4 = 0,
    VoLTE_Event_IPv6,
    /*add here*/
    VoLTE_Event_IPv_Max,
};


#define SOCKETWRAPPER_LOGI(fmt, arg...)  ALOGI("" fmt, ##arg);
#define SOCKETWRAPPER_LOGW(fmt, arg...)  ALOGW("" fmt, ##arg);
#define SOCKETWRAPPER_LOGE(fmt, arg...)  ALOGE("" fmt, ##arg);

#define SOCKETWRAPPER_ASSERT(expr, M, ...) while(!(expr)) { SOCKETWRAPPER_LOGE("@@@ ASSERT @@@: (%s:%d)" M, __FILE__, __LINE__, ##__VA_ARGS__); fflush(stdout); LOG_ALWAYS_FATAL("ASSERT!!!!"); assert(0); exit(-11);}

typedef int (*Sock_RxCB_t)(void* cookie, const sp<ABuffer>& buffer);

typedef struct Sock_param {
    /*IPv4 or IPv6*/
    uint32_t protocol_version;

    /*Socket FD*/
    int32_t  sockfd;

    uint32_t  dscp;
    uint32_t  priority;

    bool isBlock;

    uint32_t sendBufferSize;    /* 0 for ignore */
    uint32_t receiveBufferSize; /* 0 for ignore */

    uint32_t network_id;
    char ifname[16];
    uid_t uid;
    uint32_t tag;
    uint8_t  local_address[VOLTE_IPADDR_LENGTH];
    uint16_t local_port;

    uint8_t  peer_address[VOLTE_IPADDR_LENGTH];
    uint16_t peer_port;
} Sock_param_t;

class SocketWrapper : public RefBase
{
public:
    SocketWrapper();
    virtual ~SocketWrapper();
    int setParam(Sock_param_t param);
    int getParam(Sock_param_t *param);
    int setRxCallBack(void *cookie, Sock_RxCB_t rx_cb);
    int writeSock(const sp<ABuffer>& buffer);
private:
    int readSock(int fd, const sp<ABuffer>& buffer);
    int setSock(void);
    int createSock(void);
    int dumpAddr(struct sockaddr *addr_ptr);
    void setUdpConnect(void);

    Sock_param_t mParam;
    Sock_RxCB_t mRxCb;
    void        *mCookie;
    bool        m_bStarted;
    bool        m_bSelfCreate;
    pthread_t   m_Tid;
    static void * receiveThread(void *pParam);
    /* for thread wakeup */
    int mReadPipe;
    int mWritePipe;
    uint64_t mSendDataUasage;
    uint64_t mrecvDataUasage;
    bool mError;

    //for debug
    unsigned int mWriteCount;
    unsigned int mWriteFail;
    unsigned int mReceiveCount;
};
#endif /* __SOCKETWRAPPER_H__ */
