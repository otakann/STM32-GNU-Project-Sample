/*
 *  Copyright (C) 2018, ZhaoZhenge, All Rights Reserved
 *  SPDX-License-Identifier: Apache-2.0
 *
 *  Licensed under the Apache License, Version 2.0 (the "License"); you may
 *  not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 *  WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */
 
/**************************************************************
**  STM32 MCU program develop platform
**************************************************************/
/** 
 * @file        wrapper_api.h
 * @brief       common wrapper API
 * @author      zhaozhenge@outlook.com
 *
 * @version     00.00.01 
 *              - 2019/04/08 : zhaozhenge@outlook.com 
 *                  -# New
 */

#ifndef _WRAP_API_H_
#define _WRAP_API_H_

#ifdef __cplusplus
extern "C" {
#endif

/**************************************************************
**  Include
**************************************************************/

#include "FreeRTOS.h"

/**************************************************************
**  Symbol
**************************************************************/

#define SAFE_MALLOC pvPortMalloc
#define SAFE_FREE   vPortFree
#define THREAD_CB   StaticTask_t
#define EVENT_CB    StaticEventGroup_t
#define MQ_CB       StaticQueue_t
#define SEM_CB      StaticSemaphore_t

#ifdef __cplusplus
}
#endif

#endif /* _WRAP_API_H_ */
