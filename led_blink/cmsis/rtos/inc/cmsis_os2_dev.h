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

#define IS_IRQ()    (g_KernelIsIRQ)

/**************************************************************
**  Global Param
**************************************************************/

extern uint16_t g_KernelIsIRQ;
