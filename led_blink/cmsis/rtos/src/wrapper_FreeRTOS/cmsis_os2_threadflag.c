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
**  CMSIS RTOS V2 implement via FreeRTOS
**************************************************************/
/** 
 * @file        cmsis_os2_threadflag.c
 * @brief       CMSIS RTOS Thread Flags wrapper of FreeRTOS.
 * @author      zhaozhenge@outlook.com
 *
 * @version     00.00.01 
 *              - 2019/04/03 : zhaozhenge@outlook.com 
 *                  -# New
 */

/**************************************************************
**  Include
**************************************************************/

#include "cmsis_os2_dev.h"
#include "FreeRTOS.h"

/**************************************************************
**  Interface
**************************************************************/

/** 
 * @brief               Set the specified Thread Flags of a thread.
 * @param[out]          thread_id       thread ID obtained by \ref osThreadNew or \ref osThreadGetId.
 * @param[in]           flags           specifies the flags of the thread that shall be set.
 * @return              thread flags after setting or error code if highest bit set.
 * @author              zhaozhenge@outlook.com
 * @date                2019/04/01
 * @note                Currently not support this feature
 */
extern uint32_t osThreadFlagsSet(
    osThreadId_t    thread_id,
    uint32_t        flags   )
{
    (void)thread_id;
    (void)flags;
    return (uint32_t)osFlagsErrorUnknown;
}

/** 
 * @brief               Clear the specified Thread Flags of current running thread.
 * @param[in]           flags           specifies the flags of the thread that shall be cleared.
 * @return              thread flags before clearing or error code if highest bit set.
 * @author              zhaozhenge@outlook.com
 * @date                2019/04/01
 * @note                Currently not support this feature
 */
extern uint32_t osThreadFlagsClear  (
    uint32_t    flags   )
{
    (void)flags;
    return (uint32_t)osFlagsErrorUnknown;
}

/** 
 * @brief               Get the current Thread Flags of current running thread.
 * @return              current thread flags.
 * @author              zhaozhenge@outlook.com
 * @date                2019/04/01
 * @note                Currently not support this feature
 */
extern uint32_t osThreadFlagsGet (void)
{
    return (uint32_t)osFlagsErrorUnknown;
}

/** 
 * @brief               Wait for one or more Thread Flags of the current running thread to become signaled.
 * @param[in]           flags           specifies the flags to wait for.
 * @param[in]           options         specifies flags options (osFlagsXxxx).
 * @param[in]           timeout         \ref CMSIS_RTOS_TimeOutValue or 0 in case of no time-out.
 * @return              thread flags before clearing or error code if highest bit set.
 * @author              zhaozhenge@outlook.com
 * @date                2019/04/01
 * @note                Currently not support this feature
 */
extern uint32_t osThreadFlagsWait   (
    uint32_t    flags,
    uint32_t    options,
    uint32_t    timeout )
{
    (void)flags;
    (void)options;
    (void)timeout;
    return (uint32_t)osFlagsErrorUnknown;
}
