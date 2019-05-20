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
 * @file        wrapper_api.c
 * @brief       common wrapper API
 * @author      zhaozhenge@outlook.com
 *
 * @version     00.00.01 
 *              - 2019/04/28 : zhaozhenge@outlook.com
 *                  -# New
 */

/**************************************************************
**  Include
**************************************************************/

#include "cmsis_os2.h"

#include "wrapper_api.h"

/**************************************************************
**  Global param
**************************************************************/

uint16_t                g_KernelIsIRQ;

/**************************************************************
**  Interface
**************************************************************/

/** 
 * @brief               Initial system wrapper
 * @retval              0               success
 * @retval              -1              fail
 * @author              zhaozhenge@outlook.com
 * @date                2019/04/28
 */
extern int WRAPPER_INIT(void)
{
    g_KernelIsIRQ   =   0;
}

/**
 * @brief               Enter interrupt
 * @return              None
 * @author              zhaozhenge@outlook.com
 * @date                2019/05/16
 */
extern void EXIT_ENTRY(void)
{
    g_KernelIsIRQ++;
}

/**
 * @brief               Leave interrupt
 * @return              None
 * @author              zhaozhenge@outlook.com
 * @date                2019/05/16
 */
extern void EXIT_LEAVE(void)
{
    g_KernelIsIRQ--;
}
