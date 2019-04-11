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
 * @file        cmsis_os2_eventflag.c
 * @brief       CMSIS RTOS Event Flags wrapper of FreeRTOS.
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
#include "event_groups.h"

/**************************************************************
**  Interface
**************************************************************/

/** 
 * @brief               Create and Initialize an Event Flags object.
 * @param[in]           attr            event flags attributes; NULL: default values.
 * @retval              event flags ID for reference by other functions or NULL in case of error.
 * @author              zhaozhenge@outlook.com
 * @date                2019/04/01
 * @note                Currently not support Event Flags name
 */
extern osEventFlagsId_t osEventFlagsNew (
    const osEventFlagsAttr_t*   attr    )
{
    osEventFlagsId_t    ret =   NULL;

    do
    {
        if(IS_IRQ())
        {
            ret =   NULL;
            break;
        }
        if( (attr) && (attr->cb_mem) && (0 < attr->cb_size) && (sizeof(StaticEventGroup_t) > attr->cb_size) )
        {
            ret =   NULL;
            break;
        }
        if( attr && attr->cb_mem && attr->cb_size)
        {
#if( configSUPPORT_STATIC_ALLOCATION == 1 )
            /* use memory allowed by user */
            ret =   xEventGroupCreateStatic( (StaticEventGroup_t*)attr->cb_mem );
#else
            ret =   NULL;
#endif
        }
        else
        {
#if( configSUPPORT_DYNAMIC_ALLOCATION == 1 )
            /* use memory alloc in heap */
            ret =   xEventGroupCreate();
#else
            ret =   NULL;
#endif
        }
    }while(0);

    return (osEventFlagsId_t)ret;
}

/** 
 * @brief               Get name of an Event Flags object.
 * @param[in]           ef_id           event flags ID obtained by \ref osEventFlagsNew.
 * @retval              name as null-terminated string.
 * @author              zhaozhenge@outlook.com
 * @date                2019/04/01
 * @note                Currently not support this feature
 */
extern const char* osEventFlagsGetName  (
    osEventFlagsId_t    ef_id   )
{
    (void)ef_id;
    return NULL;
}

/** 
 * @brief               Set the specified Event Flags.
 * @param[in]           ef_id           event flags ID obtained by \ref osEventFlagsNew.
 * @param[in]           flags           specifies the flags that shall be set.
 * @return              event flags after setting or error code if highest bit set.
 * @author              zhaozhenge@outlook.com
 * @date                2019/04/01
 */
extern uint32_t osEventFlagsSet (
    osEventFlagsId_t    ef_id,
    uint32_t            flags   )
{
    uint32_t    ret     =   0;
    BaseType_t  yield   =   pdFALSE;

    do
    {
        if( (!ef_id) || (flags & osFlagsError) )
        {
            ret =   (uint32_t)osFlagsErrorParameter;
            break;
        }
        if(IS_IRQ())
        {
            if(pdPASS != xEventGroupSetBitsFromISR( (EventGroupHandle_t)ef_id, (EventBits_t)flags, &yield ))
            {
                ret = (uint32_t)osFlagsErrorResource;
                break;
            }
            portYIELD_FROM_ISR(yield);
            ret =   flags;
        }
        else
        {
            ret =   (uint32_t)xEventGroupSetBits((EventGroupHandle_t)ef_id, (EventBits_t)flags);
        }
    }while(0);

    return ret;
}

/** 
 * @brief               Clear the specified Event Flags.
 * @param[in]           ef_id           event flags ID obtained by \ref osEventFlagsNew.
 * @param[in]           flags           specifies the flags that shall be cleared.
 * @return              event flags before clearing or error code if highest bit set.
 * @author              zhaozhenge@outlook.com
 * @date                2019/04/01
 */
extern uint32_t osEventFlagsClear   (
    osEventFlagsId_t    ef_id,
    uint32_t            flags   )
{
    uint32_t    ret =   0;

    do
    {
        if( (!ef_id) || (flags & osFlagsError) )
        {
            ret =   (uint32_t)osFlagsErrorParameter;
            break;
        }
        if(IS_IRQ())
        {
            ret =   (uint32_t)xEventGroupGetBitsFromISR ((EventGroupHandle_t)ef_id);
            if(pdPASS != xEventGroupClearBitsFromISR( (EventGroupHandle_t)ef_id, (EventBits_t)flags ))
            {
                ret =   (uint32_t)osFlagsErrorResource;
                break;
            }
        }
        else
        {
            ret =   (uint32_t)xEventGroupClearBits((EventGroupHandle_t)ef_id, (EventBits_t)flags);
        }
    }while(0);

    return ret;
}

/** 
 * @brief               Get the current Event Flags.
 * @param[in]           ef_id           event flags ID obtained by \ref osEventFlagsNew.
 * @return              current event flags.
 * @author              zhaozhenge@outlook.com
 * @date                2019/04/01
 */
extern uint32_t osEventFlagsGet (
    osEventFlagsId_t    ef_id   )
{
    uint32_t    ret =   0;
    
    do
    {
        if(!ef_id)
        {
            ret =   (uint32_t)osFlagsErrorParameter;
            break;
        }
        if(IS_IRQ())
        {
            ret =   (uint32_t)xEventGroupGetBitsFromISR ((EventGroupHandle_t)ef_id);
        }
        else
        {
            ret =   (uint32_t)xEventGroupGetBits((EventGroupHandle_t)ef_id);
        }
    }while(0);

    return ret;
}

/** 
 * @brief               Wait for one or more Event Flags to become signaled.
 * @param[in]           ef_id           event flags ID obtained by \ref osEventFlagsNew.
 * @param[in]           flags           specifies the flags that shall be cleared.
 * @param[in]           options         specifies flags options (osFlagsXxxx).
 * @param[in]           timeout         \ref CMSIS_RTOS_TimeOutValue or 0 in case of no time-out.
 * @return              event flags before clearing or error code if highest bit set.
 * @author              zhaozhenge@outlook.com
 * @date                2019/04/01
 * @note                Cannot call in Interrupt Service Routines.
 */
extern uint32_t osEventFlagsWait(
    osEventFlagsId_t    ef_id,
    uint32_t            flags,
    uint32_t            options,
    uint32_t            timeout )
{
    uint32_t    ret             =   0;
    BaseType_t  waitAll         =   pdFALSE;
    BaseType_t  exitClr         =   pdTRUE;
    TickType_t  xTicksToWait    =   (osWaitForever == timeout)?timeout:portMAX_DELAY;

    do
    {
        if( (!ef_id) || (flags & osFlagsError) )
        {
            ret =   (uint32_t)osFlagsErrorParameter;
            break;
        }
        if(IS_IRQ())
        {
            ret =   (uint32_t)osFlagsErrorISR;
            break;
        }
        if (options & osFlagsWaitAll)
        {
            waitAll =   pdTRUE;
        }
        if (options & osFlagsNoClear)
        {
            exitClr =   pdFALSE;
        }
        ret =   (uint32_t)xEventGroupWaitBits ((EventGroupHandle_t)ef_id, (EventBits_t)flags, exitClr, waitAll, xTicksToWait);
        if(pdTRUE == waitAll)
        {
            if(flags != (flags & ret))
            {
                if(timeout)
                {
                    ret =   (uint32_t)osFlagsErrorTimeout;
                }
                else
                {
                    ret =   (uint32_t)osFlagsErrorResource;
                }
            }
        }
        else
        {
            if( !(flags & ret) )
            {
                if(timeout)
                {
                    ret =   (uint32_t)osFlagsErrorTimeout;
                }
                else
                {
                    ret =   (uint32_t)osFlagsErrorResource;
                }
            }
        }
    }while(0);

    return ret;
}

/** 
 * @brief               Delete an Event Flags object.
 * @param[in]           ef_id           event flags ID obtained by \ref osEventFlagsNew.
 * @retval              osOK
 * @retval              osErrorISR
 * @retval              osErrorParameter
 * @author              zhaozhenge@outlook.com
 * @date                2019/04/02
 */
extern osStatus_t osEventFlagsDelete(
    osEventFlagsId_t    ef_id   )
{
    osStatus_t  ret =   osOK;

    do
    {
        if(IS_IRQ())
        {
            ret =   osErrorISR;
            break;
        }
        if(!ef_id)
        {
            ret =   osErrorParameter;
            break;
        }
        vEventGroupDelete((EventGroupHandle_t)ef_id);
        ret =   osOK;
    }while(0);

    return ret;
}
