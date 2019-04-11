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
 * @file        cmsis_os2_wait.c
 * @brief       CMSIS RTOS Generic Wait Functions wrapper of FreeRTOS.
 * @author      zhaozhenge@outlook.com
 *
 * @version     00.00.01 
 *              - 2019/04/03 : zhaozhenge@outlook.com 
 *                  -# New
 */

/**************************************************************
**  Include
**************************************************************/

#include <limits.h>

#include "cmsis_os2_dev.h"
#include "FreeRTOS.h"
#include "task.h"

/**************************************************************
**  Interface
**************************************************************/

/** 
 * @brief               Wait for Timeout (Time Delay).
 * @param[in]           ticks           \ref CMSIS_RTOS_TimeOutValue "time ticks" value.
 * @retval              osOK
 * @retval              osErrorISR
 * @author              zhaozhenge@outlook.com
 * @date                2019/04/01
 */
extern osStatus_t osDelay   (
    uint32_t    ticks   )
{
#if ( INCLUDE_vTaskDelay == 1 )
    osStatus_t  ret =   osOK;

    do
    {
        if(IS_IRQ())
        {
            ret =   osErrorISR;
            break;
        }
        if(ticks)
        {
            vTaskDelay((TickType_t)ticks);
        }
        ret =   osOK;
    }while(0);

    return ret;
#else
    (void)ticks;
    return (osError);
#endif
}

/** 
 * @brief               Wait until specified time.
 * @param[in]           ticks           absolute time in ticks
 * @retval              osOK
 * @retval              osErrorISR
 * @author              zhaozhenge@outlook.com
 * @date                2019/04/01
 */
extern osStatus_t osDelayUntil  (
    uint32_t    ticks   )
{
#if ( ( INCLUDE_vTaskDelayUntil == 1 ) || (INCLUDE_vTaskDelay == 1) )
    osStatus_t  ret     =   osOK;
    TickType_t  tcnt    =   0;

    do
    {
        if(IS_IRQ())
        {
            ret =   osErrorISR;
            break;
        }
        tcnt    =   xTaskGetTickCount();
        if( tcnt > ticks)
        {
#if ( INCLUDE_vTaskDelayUntil == 1 )
            vTaskDelayUntil( &tcnt, (TickType_t)(ULONG_MAX - tcnt + ticks) );
#else
            vTaskDelay((TickType_t)(ULONG_MAX - tcnt + ticks));
#endif
        }
        else if(tcnt == ticks)
        {
            ret =   osOK;
        }
        else
        {
#if ( INCLUDE_vTaskDelayUntil == 1 )
            vTaskDelayUntil( &tcnt, (TickType_t)(ticks - tcnt) );
#else
            vTaskDelay((TickType_t)(ticks - tcnt));
#endif
            ret =   osOK;
        }
    }while(0);

    return ret;
#else
    (void)ticks;
    return (osError);
#endif
}
