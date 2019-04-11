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
 * @file        cmsis_os2_messagequeue.c
 * @brief       CMSIS RTOS Message Queue wrapper of FreeRTOS.
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
#include "queue.h"

/**************************************************************
**  Interface
**************************************************************/

/** 
 * @brief               Create and Initialize a Message Queue object.
 * @param[in]           msg_count       maximum number of messages in queue.
 * @param[in]           msg_size        maximum message size in bytes.
 * @param[in]           attr            message queue attributes; NULL: default values.
 * @return              message queue ID for reference by other functions or NULL in case of error.
 * @author              zhaozhenge@outlook.com
 * @date                2019/04/03
 * @note                Do not support MessageQueue name
 */
extern osMessageQueueId_t osMessageQueueNew (
    uint32_t                    msg_count,
    uint32_t                    msg_size,
    const osMessageQueueAttr_t* attr    )
{
    QueueHandle_t   ret         =   NULL;
    int32_t         dynamic_cb  =   1;
    int32_t         dynamic_mq  =   1;

    do
    {
        if(IS_IRQ())
        {
            ret =   NULL;
            break;
        }
        if( (attr) && (attr->cb_mem) && (0 < attr->cb_size) && (sizeof(StaticQueue_t) > attr->cb_size) )
        {
            ret =   NULL;
            break;
        }
        if( (attr) && (attr->mq_mem) && (0 < attr->mq_size) && ((msg_count * msg_size) > attr->mq_size) )
        {
            ret =   NULL;
            break;
        }
        if( attr && attr->cb_mem && attr->cb_size )
        {
            dynamic_cb  =   0;
        }
        if( attr && attr->mq_mem && attr->mq_size)
        {
            dynamic_mq  =   0;
        }
        if( (!dynamic_cb) && (!dynamic_mq) )
        {
#if( configSUPPORT_STATIC_ALLOCATION == 1 )
            /* use memory allowed by user */
            ret =   xQueueCreateStatic(msg_count, msg_size,
                                        (uint8_t*)attr->mq_mem,
                                        (StaticQueue_t*)attr->cb_mem );
#else
            ret =   NULL;
#endif
        }
        else if( dynamic_cb && dynamic_mq )
        {
#if( configSUPPORT_DYNAMIC_ALLOCATION == 1 )
            /* use memory alloc in heap */
            (void)xQueueCreate(msg_count, msg_size);
#else
            ret =   NULL;
#endif
        }
        else
        {
            /* FreeRTOS do not support this mode */
            ret =   NULL;
        }
    }while(0);

    return (osMessageQueueId_t)ret;
}

/** 
 * @brief               Get name of a Message Queue object.
 * @param[in]           mq_id           message queue ID obtained by \ref osMessageQueueNew.
 * @return              name as null-terminated string.
 * @author              zhaozhenge@outlook.com
 * @date                2019/04/03
 * @note                Currently do not support this feature
 */
extern const char* osMessageQueueGetName(
    osMessageQueueId_t  mq_id   )
{
    (void)mq_id;
    return NULL;
}

/** 
 * @brief               Put a Message into a Queue or timeout if Queue is full.
 * @param[in]           mq_id           message queue ID obtained by \ref osMessageQueueNew.
 * @param[in]           msg_ptr         pointer to buffer with message to put into a queue.
 * @param[in]           msg_prio        message priority.
 * @param[in]           timeout         \ref CMSIS_RTOS_TimeOutValue or 0 in case of no time-out.
 * @retval              osOK
 * @retval              osErrorParameter
 * @retval              osErrorResource
 * @retval              osErrorTimeout
 * @author              zhaozhenge@outlook.com
 * @date                2019/04/03
 * @note                Currently do not support msg_prio parameter
 */
extern osStatus_t osMessageQueuePut (
    osMessageQueueId_t  mq_id,
    const void*         msg_ptr,
    uint8_t             msg_prio,
    uint32_t            timeout )
{
    osStatus_t  ret         =   osError;
    BaseType_t  yield       =   pdFALSE;
    TickType_t  xBlockTime  =   (osWaitForever==timeout)?portMAX_DELAY:timeout;

    do
    {
        (void)msg_prio;
        if(!mq_id)
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
            if(pdPASS != xQueueSendFromISR((QueueHandle_t)mq_id, msg_ptr, &yield))
            {
                ret =   osErrorResource;
                break;
            }
            portYIELD_FROM_ISR(yield);
        }
        else
        {
            if(pdPASS != xQueueSend((QueueHandle_t)mq_id, msg_ptr, xBlockTime))
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
}

/** 
 * @brief               Get a Message from a Queue or timeout if Queue is empty.
 * @param[in]           mq_id           message queue ID obtained by \ref osMessageQueueNew.
 * @param[in]           msg_ptr         pointer to buffer for message to get from a queue.
 * @param[in]           msg_prio        pointer to buffer for message priority or NULL.
 * @param[in]           timeout         \ref CMSIS_RTOS_TimeOutValue or 0 in case of no time-out.
 * @retval              osOK
 * @retval              osErrorParameter
 * @retval              osErrorResource
 * @retval              osErrorTimeout
 * @author              zhaozhenge@outlook.com
 * @date                2019/04/03
 * @note                Currently do not support msg_prio parameter
 */
extern osStatus_t osMessageQueueGet (
    osMessageQueueId_t  mq_id,
    void*               msg_ptr,
    uint8_t*            msg_prio,
    uint32_t            timeout )
{
    osStatus_t  ret         =   osError;
    BaseType_t  yield       =   pdFALSE;
    TickType_t  xBlockTime  =   (osWaitForever==timeout)?portMAX_DELAY:timeout;

    do
    {
        (void)msg_prio;
        if( (!mq_id) || (!msg_ptr) )
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
            if(pdPASS != xQueueReceiveFromISR((QueueHandle_t)mq_id, msg_ptr, &yield))
            {
                ret =   osErrorResource;
                break;
            }
            portYIELD_FROM_ISR(yield);
        }
        else
        {
            if(pdPASS != xQueueReceive((QueueHandle_t)mq_id, msg_ptr, xBlockTime))
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
}

/** 
 * @brief               Get maximum number of messages in a Message Queue.
 * @param[in]           mq_id           message queue ID obtained by \ref osMessageQueueNew.
 * @return              maximum number of messages.
 * @author              zhaozhenge@outlook.com
 * @date                2019/04/03
 * @note                Currently do not support this feature
 */
extern uint32_t osMessageQueueGetCapacity   (
    osMessageQueueId_t  mq_id   )
{
    (void)mq_id;
    return (0);
}

/** 
 * @brief               Get maximum message size in a Memory Pool.
 * @param[in]           mq_id           message queue ID obtained by \ref osMessageQueueNew.
 * @return              maximum message size in bytes.
 * @author              zhaozhenge@outlook.com
 * @date                2019/04/03
 * @note                Currently do not support this feature
 */
extern uint32_t osMessageQueueGetMsgSize(
    osMessageQueueId_t  mq_id   )
{
    (void)mq_id;
    return (0);
}

/** 
 * @brief               Get number of queued messages in a Message Queue.
 * @param[in]           mq_id           message queue ID obtained by \ref osMessageQueueNew.
 * @return              number of queued messages.
 * @author              zhaozhenge@outlook.com
 * @date                2019/04/03
 */
extern uint32_t osMessageQueueGetCount  (
    osMessageQueueId_t  mq_id   )
{
    uint32_t    ret =   0;
    
    do
    {
        if(!mq_id)
        {
            ret =   0;
            break;
        }
        if(IS_IRQ())
        {
            ret =   (uint32_t)uxQueueMessagesWaitingFromISR((QueueHandle_t)mq_id);
        }
        else
        {
            ret =   (uint32_t)uxQueueMessagesWaiting((QueueHandle_t)mq_id);
        }
    }while(0);

    return ret;
}

/** 
 * @brief               Get number of available slots for messages in a Message Queue.
 * @param[in]           mq_id           message queue ID obtained by \ref osMessageQueueNew.
 * @return              number of available slots for messages.
 * @author              zhaozhenge@outlook.com
 * @date                2019/04/03
 * @note                Cannot call in Interrupt Service Routines.
 */
extern uint32_t osMessageQueueGetSpace  (
    osMessageQueueId_t  mq_id   )
{
    uint32_t    ret =   0;
    
    do
    {
        if(!mq_id)
        {
            ret =   0;
            break;
        }
        if(IS_IRQ())
        {
            ret =   0;
            break;
        }
        ret =   (uint32_t)uxQueueSpacesAvailable((QueueHandle_t)mq_id);
    }while(0);

    return ret;
}

/** 
 * @brief               Reset a Message Queue to initial empty state.
 * @param[in]           mq_id           message queue ID obtained by \ref osMessageQueueNew.
 * @retval              osOK
 * @retval              osErrorISR
 * @retval              osErrorParameter
 * @retval              osErrorResource
 * @author              zhaozhenge@outlook.com
 * @date                2019/04/03
 */
extern osStatus_t osMessageQueueReset   (
    osMessageQueueId_t  mq_id   )
{
    osStatus_t  ret =   osError;

    do
    {
        if(IS_IRQ())
        {
            ret =   osErrorISR;
            break;
        }
        if(!mq_id)
        {
            ret =   osErrorParameter;
            break;
        }
        if(pdPASS != xQueueReset((QueueHandle_t)mq_id))
        {
            ret =   osErrorResource;
            break;
        }
        ret =   osOK;
    }while(0);

    return ret;
}

/** 
 * @brief               Delete a Message Queue object.
 * @param[in]           mq_id           message queue ID obtained by \ref osMessageQueueNew.
 * @retval              osOK
 * @retval              osErrorISR
 * @retval              osErrorParameter
 * @author              zhaozhenge@outlook.com
 * @date                2019/04/03
 */
extern osStatus_t osMessageQueueDelete  (
    osMessageQueueId_t  mq_id   )
{
    osStatus_t  ret =   osError;

    do
    {
        if(IS_IRQ())
        {
            ret =   osErrorISR;
            break;
        }
        if(!mq_id)
        {
            ret =   osErrorParameter;
            break;
        }
        vQueueDelete((QueueHandle_t)mq_id);
        ret =   osOK;
    }while(0);

    return ret;
}
