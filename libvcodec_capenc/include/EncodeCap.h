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

#ifndef ENCODECAP_H
#define ENCODECAP_H

enum resolution_type
{
    Resolution_VGA = 0,
    Resolution_QVGA = 1,
    Resolution_QQVGA = 2,
    Resolution_OTHERS = 3,

};

typedef enum CONFIG_VCODECCAPTYPE {

    CONFIG_VCODECCAPTYPE_GED_VILTE_MODE,
} CONFIG_INDEXTYPE;

int32_t getAdaptativeEncodeInfo(uint32_t modify_expected_bitrate, uint32_t minbitrate,
                                          uint32_t init_framerate, uint32_t *target_framerate);


int32_t getH264AdaptativeEncodeInfo(uint32_t expected_bitrate, uint32_t *target_bitrate, uint32_t minbitrate,
                                          uint32_t init_framerate, uint32_t *target_framerate,
                                          uint32_t AdaptiveResolution = 0, uint32_t init_resolution = 0, uint32_t width = 0, uint32_t height = 0,
                                          uint32_t *target_width = 0, uint32_t *target_height = 0);

int32_t getHEVCAdaptativeEncodeInfo(uint32_t expected_bitrate, uint32_t *target_bitrate, uint32_t minbitrate,
                                          uint32_t init_framerate, uint32_t *target_framerate);

int32_t SetcEncodeconfig(int32_t config_index, int32_t param);

uint32_t getH264ResolutionChangeCapabiltiy();

uint32_t getHEVCResolutionChangeCapabiltiy();

uint32_t getH264AdaptiveDropFrameCapabiltiy();

uint32_t getHEVCAdaptiveDropFrameCapabiltiy();

#endif
