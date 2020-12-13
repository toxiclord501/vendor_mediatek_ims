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

#define LOG_TAG "[VT]VcodecCap"

#include <utils/KeyedVector.h>
#include <unistd.h>

#include "IVcodecCap.h"
#include "VcodecCap.h"

using namespace android;

static const int MAX_HEVC_MEDIA_PROFILE_NUM  = 5;
static video_media_profile_t rmedia_profile[MAX_HEVC_MEDIA_PROFILE_NUM] =
{
    {VIDEO_HEVC, VIDEO_PROFILE_MAIN, VIDEO_LEVEL_1,  176,  144, 15,  145 * 1000, 270 * 1000, 1},
    {VIDEO_HEVC, VIDEO_PROFILE_MAIN, VIDEO_LEVEL_2,  352,  288, 30,  360 * 1000, 526 * 1000, 1},
    {VIDEO_HEVC, VIDEO_PROFILE_MAIN, VIDEO_LEVEL_2_1,  480,  320, 30,  495 * 1000, 654 * 1000, 1},
    {VIDEO_HEVC, VIDEO_PROFILE_MAIN, VIDEO_LEVEL_3,    640,  480, 30,  742 * 1000, 974 * 1000, 1},
    {VIDEO_HEVC, VIDEO_PROFILE_MAIN, VIDEO_LEVEL_3_1,  1280,  720, 30,  1314 * 1000, 1714 * 1000, 1},
};
///////////////////////////////////////////////////////////////////////////////////
// OP01 (CMCC)

static const int MAX_HEVC_MEDIA_PROFILE_NUM_OP01  = 4;
static video_media_profile_t rmedia_profile_op01[MAX_HEVC_MEDIA_PROFILE_NUM_OP01] =
{
    {VIDEO_HEVC, VIDEO_PROFILE_MAIN, VIDEO_LEVEL_1,    320,  240, 10,  145 * 1000, 270 * 1000, 1},
    {VIDEO_HEVC, VIDEO_PROFILE_MAIN, VIDEO_LEVEL_2,    320,  240, 20,  327 * 1000, 462 * 1000, 1},
    {VIDEO_HEVC, VIDEO_PROFILE_MAIN, VIDEO_LEVEL_2_1,  480,  320, 30,  450 * 1000, 594 * 1000, 1},
    {VIDEO_HEVC, VIDEO_PROFILE_MAIN, VIDEO_LEVEL_3,    640,  480, 30,  450 * 1000, 670 * 1000, 1},
};
static const int MAX_QUALITY_NUM  = 4;
static QualityInfo_t rQualityInfo_OP01[MAX_QUALITY_NUM] =
{
    {VIDEO_QUALITY_FINE,   VIDEO_HEVC, VIDEO_PROFILE_MAIN, VIDEO_LEVEL_3},
    {VIDEO_QUALITY_HIGH,   VIDEO_HEVC, VIDEO_PROFILE_MAIN, VIDEO_LEVEL_3},
    {VIDEO_QUALITY_MEDIUM, VIDEO_HEVC, VIDEO_PROFILE_MAIN, VIDEO_LEVEL_2_1},
    {VIDEO_QUALITY_LOW,    VIDEO_HEVC, VIDEO_PROFILE_MAIN, VIDEO_LEVEL_2},
};

///////////////////////////////////////////////////////////////////////////////////
void getDefaultHEVCMediaProfileByOperator(int opid, video_media_profile_t **ppvideo_media_profile_t, int *pCount)
{
    switch(opid)
    {
        case 1: // CMCC
            *ppvideo_media_profile_t = rmedia_profile_op01;
            *pCount = MAX_HEVC_MEDIA_PROFILE_NUM_OP01;
            break;
        default:
            *ppvideo_media_profile_t = rmedia_profile;
            *pCount = MAX_HEVC_MEDIA_PROFILE_NUM;
            break;
    }
}

void createHEVCQualityMediaProfileByOperator(int opid, QualityInfo_t *pQualityInfo)
{
    switch (opid)
    {
        case 1: // CMCC
            {
                memcpy(pQualityInfo, rQualityInfo_OP01, sizeof(QualityInfo_t) * MAX_QUALITY_NUM);
            }
            break;
        default:
            {
                memcpy(pQualityInfo, rQualityInfo_OP01, sizeof(QualityInfo_t) * MAX_QUALITY_NUM);
            }
            break;
    }
}
