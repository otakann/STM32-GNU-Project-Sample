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
**  CMSIS RTOS V2 configuration for STM32 device
**************************************************************/
/** 
 * @file        cmsis_os2_dev.h
 * @brief       CMSIS RTOS V2 configuration for STM32 device
 * @author      zhaozhenge@outlook.com
 *
 * @version     00.00.01 
 *              - 2019/04/03 : zhaozhenge@outlook.com 
 *                  -# New
 */

/**************************************************************
**  Include
**************************************************************/

#include "stm32l4xx.h"
#include "cmsis_os2.h"

/**************************************************************
**  Symbol
**************************************************************/

#ifndef __ARM_ARCH_6M__
#define __ARM_ARCH_6M__         0
#endif
#ifndef __ARM_ARCH_7M__
#define __ARM_ARCH_7M__         0
#endif
#ifndef __ARM_ARCH_7EM__
#define __ARM_ARCH_7EM__        0
#endif
#ifndef __ARM_ARCH_8M_MAIN__
#define __ARM_ARCH_8M_MAIN__    0
#endif
#ifndef __ARM_ARCH_7A__
#define __ARM_ARCH_7A__         0
#endif

#if     (   (__ARM_ARCH_7M__        ==  1U) || \
            (__ARM_ARCH_7EM__       ==  1U) || \
            (__ARM_ARCH_8M_MAIN__   ==  1U) )
#define IS_IRQ_MASKED()     ((0U != __get_PRIMASK()) || ((osKernelRunning == g_KernelState) && (0U != __get_BASEPRI())))
#elif   (   __ARM_ARCH_6M__         ==  1U  )
#define IS_IRQ_MASKED()     ((0U != __get_PRIMASK()) && (osKernelRunning == g_KernelState))
#elif   (   __ARM_ARCH_7A__         ==  1U  )
#define IS_IRQ_MASKED()     (0U)
#else
#define IS_IRQ_MASKED()     (0U != __get_PRIMASK())
#endif

#if     (   __ARM_ARCH_7A__         ==  1U  )
/* CPSR mode bitmasks */
#define CPSR_MODE_USER      (0x10U)
#define CPSR_MODE_SYSTEM    (0x1FU)
#define IS_IRQ_MODE()       ((CPSR_MODE_USER != __get_mode()) && (CPSR_MODE_SYSTEM != __get_mode()))
#else
#define IS_IRQ_MODE()       (0U != __get_IPSR())
#endif

#define IS_IRQ()            (IS_IRQ_MODE() || IS_IRQ_MASKED())

/**************************************************************
**  Global Param
**************************************************************/

extern osKernelState_t      g_KernelState;
