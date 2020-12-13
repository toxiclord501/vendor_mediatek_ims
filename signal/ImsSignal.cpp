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
#undef LOG_TAG
#include "ImsSignal.h"


namespace android {

//signal
//===================

Mutex gDefaultImsSignalLock;
sp<ImsSignal> gDefaultImsSignal = NULL;
int32_t  gDefaultImsSignalCnt = 0;

sp<ImsSignal> getDefaultImsSignal(){
    ALOGI("getDefaultImsSignal+++");
    AutoMutex _l(gDefaultImsSignalLock);//multithread or signal thread?

    if (gDefaultImsSignal != NULL){
        gDefaultImsSignalCnt++;
        ALOGI("[VT][ImsSignal]aleady getDefaultImsSignal %p,gDefaultImsSignal %d",gDefaultImsSignal.get(),gDefaultImsSignalCnt);
        return gDefaultImsSignal;
    }

    {
        if (gDefaultImsSignal == NULL) {
		gDefaultImsSignal = new ImsSignal;
		gDefaultImsSignal->start();
		gDefaultImsSignalCnt++;
		ALOGI("[VT][ImsSignal]1th getDefaultImsSignal %p gDefaultImsSignalCnt %d",gDefaultImsSignal.get(),gDefaultImsSignalCnt);
        }
    }

      return gDefaultImsSignal;
}

void deleteDefaultImsSignal()//if no delete it ,we always
{
    AutoMutex _l(gDefaultImsSignalLock);
    gDefaultImsSignalCnt--;
    ALOGI("[deleteDefaultImsSignal]gDefaultImsSignal %p gDefaultImsSignalCnt %d",gDefaultImsSignal.get(),gDefaultImsSignalCnt);
    if (gDefaultImsSignalCnt == 0 &&  gDefaultImsSignal.get() != NULL)   {
        gDefaultImsSignal.clear();
        gDefaultImsSignal = NULL;
    }
}


}
