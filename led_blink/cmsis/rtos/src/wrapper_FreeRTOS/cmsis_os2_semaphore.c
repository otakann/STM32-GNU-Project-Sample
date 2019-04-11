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
 * @file        cmsis_os2_semaphore.c
 * @brief       CMSIS RTOS Semaphores wrapper of FreeRTOS.
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
#include "semphr.h"

/**************************************************************
**  Interface
**************************************************************/

/** 
 * @brief               Create and Initialize a Semaphore object.
 * @param[in]           max_count       maximum number of available tokens.
 * @param[in]           initial_count   initial number of available tokens.
 * @param[in]           attr            semaphore attributes; NULL: default values.
 * @return              semaphore ID for reference by other functions or NULL in case of error.
 * @author              zhaozhenge@outlook.com
 * @date                2019/04/02
 * @note                Currently not support Semaphore name
 */
extern osSemaphoreId_t osSemaphoreNew   (
    uint32_t                    max_count,
    uint32_t                    initial_count,
    const osSemaphoreAttr_t*    attr    )
{
#if( configUSE_COUNTING_SEMAPHORES == 1 )
    SemaphoreHandle_t   ret =   NULL;
    
    do
    {
        if(IS_IRQ())
        {
            ret =   NULL;
            break;
        }
        if( (0 >= max_count) || (initial_count >max_count) )
        {
            ret =   NULL;
            break;
        }
        if( (attr) && (attr->cb_mem) && (0 < attr->cb_size) && (sizeof(StaticSemaphore_t) > attr->cb_size) )
        {
            ret =   NULL;
            break;
        }
        if( attr && attr->cb_mem && attr->cb_size)
        {
#if( configSUPPORT_STATIC_ALLOCATION == 1 )
            /* use memory allowed by user */
            ret =   xSemaphoreCreateCountingStatic( (UBaseType_t)max_count, (UBaseType_t)initial_count, (StaticSemaphore_t*)attr->cb_mem );
#else
            ret =   NULL;
#endif
        }
        else
        {
#if( configSUPPORT_DYNAMIC_ALLOCATION == 1 )
            /* use memory alloc in heap */
            ret =   xSemaphoreCreateCounting((UBaseType_t)max_count, (UBaseType_t)initial_count);
#else
            ret =   NULL;
#endif
        }
    }while(0);

    return (osSemaphoreId_t)ret;
#else
    (void)max_count;
    (void)initial_count;
    (void)attr;
    return (osSemaphoreId_t)NULL;
#endif
}

/** 
 * @brief               Get name of a Semaphore object.
 * @param[in]           semaphore_id    semaphore ID obtained by \ref osSemaphoreNew.
 * @return              name as null-terminated string.
 * @author              zhaozhenge@outlook.com
 * @date                2019/04/02
 * @note                Currently not support this feature
 */
extern const char* osSemaphoreGetName   (
    osSemaphoreId_t semaphore_id    )
{
    (void)semaphore_id;
    return NULL;
}

/** 
 * @brief               Acquire a Semaphore token or timeout if no tokens are available.
 * @param[in]           semaphore_id    semaphore ID obtained by \ref osSemaphoreNew.
 * @param[in]           timeout         \ref CMSIS_RTOS_TimeOutValue or 0 in case of no time-out.
 * @retval              osOK
 * @retval              osErrorParameter
 * @retval              osErrorISR
 * @retval              osErrorResource
 * @retval              osErrorTimeout
 * @author              zhaozhenge@outlook.com
 * @date                2019/04/02
 */
extern osStatus_t osSemaphoreAcquire(
    osSemaphoreId_t semaphore_id,
    uint32_t        timeout )
{
#if( configUSE_COUNTING_SEMAPHORES == 1 )
    osStatus_t  ret         =   osError;
    BaseType_t  yield       =   pdFALSE;
    TickType_t  xBlockTime  =   (osWaitForever==timeout)?portMAX_DELAY:timeout;

    do
    {
        if(!semaphore_id)
        {
            ret =   osErrorParameter;
            break;
        }
        if(IS_IRQ())
        {
            if(timeout)
            {
                ret =   osErrorParameter;
                break;
            }
            if(pdPASS != xSemaphoreTakeFromISR((SemaphoreHandle_t)semaphore_id, &yield))
            {
                ret =   osErrorResource;
                break;
            }
            portYIELD_FROM_ISR(yield);
        }
        else
        {
            if(pdPASS != xSemaphoreTake((SemaphoreHandle_t)semaphore_id, xBlockTime))
            {
                if(timeout)
                {
                    ret =   osErrorTimeout;
                }
                else
                {
                    ret =   osErrorResource;
                }
                break;
            }
        }
        ret =   osOK;
    }while(0);

    return ret;
#else
    (void)semaphore_id;
    (void)timeout;
    return (osError);
#endif
}

/** 
 * @brief               Release a Semaphore token up to the initial maximum count.
 * @param[in]           semaphore_id    semaphore ID obtained by \ref osSemaphoreNew.
 * @retval              osOK
 * @retval              osErrorParameter
 * @retval              osErrorResource
 * @author              zhaozhenge@outlook.com
 * @date                2019/04/02
 */
extern osStatus_t osSemaphoreRelease(
    osSemaphoreId_t semaphore_id    )
{
#if( configUSE_COUNTING_SEMAPHORES == 1 )
    osStatus_t  ret     =   osError;
    BaseType_t  yield   =   pdFALSE;

    do
    {
        if(!semaphore_id)
        {
            ret =   osErrorParameter;
            break;
        }
        if(IS_IRQ())
        {
            if(pdPASS != xSemaphoreGiveFromISR((SemaphoreHandle_t)semaphore_id, &yield))
            {
                ret =   osErrorResource;
                break;
            }
            portYIELD_FROM_ISR(yield);
        }
        else
        {
            if(pdPASS != xSemaphoreGive((SemaphoreHandle_t)semaphore_id))
            {
                ret =   osErrorResource;
                break;
            }
        }
        ret =   osOK;
    }while(0);

    return ret;
#else
    (void)semaphore_id;
    return (osError);
#endif
}

/** 
 * @brief               Get current Semaphore token count.
 * @param[in]           semaphore_id    semaphore ID obtained by \ref osSemaphoreNew.
 * @return              number of tokens available.
 * @author              zhaozhenge@outlook.com
 * @date                2019/04/02
 */
extern uint32_t osSemaphoreGetCount (
    osSemaphoreId_t semaphore_id    )
{
#if( configUSE_COUNTING_SEMAPHORES == 1 )
    uint32_t    ret =   0;

    do
    {
        if(!semaphore_id)
        {
            ret =   0;
            break;
        }
        if(IS_IRQ())
        {
            ret =   (uint32_t)uxQueueMessagesWaitingFromISR ((SemaphoreHandle_t)semaphore_id);
        }
        else
        {
            ret =   (uint32_t)uxSemaphoreGetCount ((SemaphoreHandle_t)semaphore_id);
        }
    }while(0);

    return ret;
#else
    (void)semaphore_id;
    return (0);
#endif
}

/** 
 * @brief               Delete a Semaphore object.
 * @param[in]           semaphore_id    semaphore ID obtained by \ref osSemaphoreNew.
 * @retval              osOK
 * @retval              osErrorISR
 * @retval              osErrorParameter
 * @author              zhaozhenge@outlook.com
 * @date                2019/04/02
 */
extern osStatus_t osSemaphoreDelete (
    osSemaphoreId_t semaphore_id    )
{
#if( configUSE_COUNTING_SEMAPHORES == 1 )
    osStatus_t  ret =   osError;

    do
    {
        if(IS_IRQ())
        {
            ret =   osErrorISR;
        }
        if(!semaphore_id)
        {
            ret =   osErrorParameter;
            break;
        }
        vSemaphoreDelete((SemaphoreHandle_t)semaphore_id);
        ret =   osOK;
    }while(0);

    return ret;
#else
    (void)semaphore_id;
    return (osError);
#endif
}
