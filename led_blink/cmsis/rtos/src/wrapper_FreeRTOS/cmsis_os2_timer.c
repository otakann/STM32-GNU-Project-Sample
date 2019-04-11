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
 * @file        cmsis_os2_timer.c
 * @brief       CMSIS RTOS Timer Management wrapper of FreeRTOS.
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
 * @brief               Create and Initialize a timer.
 * @param[in]           func            function pointer to callback function.
 * @param[in]           type            \ref osTimerOnce for one-shot or \ref osTimerPeriodic for periodic behavior.
 * @param[in]           argument        argument to the timer callback function.
 * @param[in]           attr            timer attributes; NULL: default values.
 * @return              timer ID for reference by other functions or NULL in case of error.
 * @author              zhaozhenge@outlook.com
 * @date                2019/04/01
 * @note                Currently not support this feature
 */
extern osTimerId_t osTimerNew   (
    osTimerFunc_t           func,
    osTimerType_t           type,
    void*                   argument,
    const osTimerAttr_t*    attr)
{
    (void)func;
    (void)type;
    (void)argument;
    (void)attr;
    return (osTimerId_t)NULL;
}

/** 
 * @brief               Get name of a timer.
 * @param[in]           timer_id        timer ID obtained by \ref osTimerNew.
 * @return              name as null-terminated string.
 * @author              zhaozhenge@outlook.com
 * @date                2019/04/01
 * @note                Currently not support this feature
 */
extern const char* osTimerGetName   (
    osTimerId_t timer_id    )
{
    (void)timer_id;
    return NULL;
}

/** 
 * @brief               Start or restart a timer.
 * @param[in]           timer_id        timer ID obtained by \ref osTimerNew.
 * @param[in]           ticks           \ref CMSIS_RTOS_TimeOutValue "time ticks" value of the timer.
 * @retval              osError
 * @author              zhaozhenge@outlook.com
 * @date                2019/04/01
 * @note                Currently not support this feature
 */
extern osStatus_t osTimerStart  (
    osTimerId_t timer_id,
    uint32_t    ticks   )
{
    (void)timer_id;
    (void)ticks;
    return (osError);
}

/** 
 * @brief               Stop a timer.
 * @param[in]           timer_id        timer ID obtained by \ref osTimerNew.
 * @retval              osError
 * @author              zhaozhenge@outlook.com
 * @date                2019/04/01
 * @note                Currently not support this feature
 */
extern osStatus_t osTimerStop   (
    osTimerId_t timer_id    )
{
    (void)timer_id;
    return (osError);
}

/** 
 * @brief               Check if a timer is running.
 * @param[in]           timer_id        timer ID obtained by \ref osTimerNew.
 * @retval              0 not running
 * @retval              1 running
 * @author              zhaozhenge@outlook.com
 * @date                2019/04/01
 * @note                Currently not support this feature
 */
extern uint32_t osTimerIsRunning(
    osTimerId_t timer_id    )
{
    (void)timer_id;
    return (0);
}

/** 
 * @brief               Delete a timer.
 * @param[in]           timer_id        timer ID obtained by \ref osTimerNew.
 * @retval              osError
 * @author              zhaozhenge@outlook.com
 * @date                2019/04/01
 * @note                Currently not support this feature
 */
extern osStatus_t osTimerDelete (
    osTimerId_t timer_id    )
{
    (void)timer_id;
    return (osError);
}
