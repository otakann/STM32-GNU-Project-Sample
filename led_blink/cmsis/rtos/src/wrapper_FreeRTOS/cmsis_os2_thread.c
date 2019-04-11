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
 * @file        cmsis_os2_thread.c
 * @brief       CMSIS RTOS Thread Management wrapper of FreeRTOS.
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
#include "task.h"

/**************************************************************
**  Global Param
**************************************************************/

static const char*  g_TskDefaultName    =   "";

/**************************************************************
**  Interface
**************************************************************/

/** 
 * @brief               Create a thread and add it to Active Threads.
 * @param[in]           func            thread function.
 * @param[in]           argument        pointer that is passed to the thread function as start argument.
 * @param[in]           attr            thread attributes; NULL: default values.
 * @return              thread ID for reference by other functions or NULL in case of error.
 * @author              zhaozhenge@outlook.com
 * @date                2019/04/01
 * @note                Thread control block and stack data should both use static memory or dynamic memory
 */
extern osThreadId_t osThreadNew (
    osThreadFunc_t          func,
    void*                   argument,
    const osThreadAttr_t*   attr)
{
    TaskHandle_t            ret             =   NULL;
    const char*             tskName         =   NULL;
    configSTACK_DEPTH_TYPE  tskStackSize    =   0;
    UBaseType_t             tskPriority     =   osPriorityNone;
    int32_t                 dynamic_cb      =   1;
    int32_t                 dynamic_st      =   1;

    do
    {
        if(IS_IRQ())
        {
            ret =   NULL;
            break;
        }
        if(!func)
        {
            ret =   NULL;
            break;
        }
        tskName         =   (attr && attr->name)?(attr->name):(g_TskDefaultName);
        tskStackSize    =   (attr && attr->stack_size)?(attr->stack_size / sizeof(StackType_t)):(configMINIMAL_STACK_SIZE);
        tskPriority     =   (attr)?(attr->priority):(osPriorityNormal);
        if ( (tskPriority < osPriorityIdle) || (tskPriority > osPriorityISR) ) 
        {
            ret =   NULL;
            break;
        }
        if(configMINIMAL_STACK_SIZE > tskStackSize)
        {
            ret =   NULL;
            break;
        }
        if( (attr) && (attr->cb_mem) && (0 < attr->cb_size) && (sizeof(StaticTask_t) > attr->cb_size) )
        {
            ret =   NULL;
            break;
        }
        /* FreeRTOS do not support join thread */
        if( attr && (osThreadJoinable == (attr->attr_bits & osThreadJoinable)) )
        {
            ret =   NULL;
            break;
        }
        if( attr && attr->cb_mem && attr->cb_size )
        {
            dynamic_cb  =   0;
        }
        if( attr && attr->stack_mem && attr->stack_size)
        {
            dynamic_st  =   0;
        }
        if( (!dynamic_cb) && (!dynamic_st) )
        {
#if( configSUPPORT_STATIC_ALLOCATION == 1 )
            /* use memory allowed by user */
            ret =   xTaskCreateStatic(func, tskName, tskStackSize, argument, tskPriority,
                                        (StackType_t*)attr->stack_mem,
                                        (StaticTask_t*)attr->cb_mem );
#else
            ret =   NULL;
#endif
        }
        else if( dynamic_cb && dynamic_st )
        {
#if( configSUPPORT_DYNAMIC_ALLOCATION == 1 )
            /* use memory alloc in heap */
            (void)xTaskCreate(func, tskName, tskStackSize, argument, tskPriority, &ret);
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

    return (osThreadId_t)ret;
}

/** 
 * @brief               Get name of a thread.
 * @param[in]           thread_id       thread ID obtained by \ref osThreadNew or \ref osThreadGetId.
 * @return              name as null-terminated string.
 * @author              zhaozhenge@outlook.com
 * @date                2019/04/01
 */
extern const char* osThreadGetName  (
    osThreadId_t    thread_id   )
{
    const char* ret =   NULL;

    do
    {
        if(IS_IRQ())
        {
            ret =   NULL;
            break;
        }
        if(!thread_id)
        {
            ret =   NULL;
            break;
        }
        ret =   pcTaskGetName ((TaskHandle_t)thread_id);
    }while(0);

    return ret;
}

/** 
 * @brief               Return the thread ID of the current running thread.
 * @return              thread ID for reference by other functions or NULL in case of error.
 * @author              zhaozhenge@outlook.com
 * @date                2019/04/01
 * @note                Cannot call in Interrupt Service Routines.
 */
extern osThreadId_t osThreadGetId (void)
{
#if ( INCLUDE_xTaskGetCurrentTaskHandle == 1 )
    TaskHandle_t    ret =   NULL;
    
    do
    {
        if(IS_IRQ())
        {
            ret =   NULL;
            break;
        }
        ret =   xTaskGetCurrentTaskHandle();
    }while(0);

    return (osThreadId_t)ret;
#else
    return (osThreadId_t)NULL;
#endif
}

/** 
 * @brief               Get current thread state of a thread.
 * @param[in]           thread_id       thread ID obtained by \ref osThreadNew or \ref osThreadGetId.
 * @retval              osThreadError
 * @retval              osThreadRunning
 * @retval              osThreadReady
 * @retval              osThreadBlocked
 * @retval              osThreadTerminated
 * @author              zhaozhenge@outlook.com
 * @date                2019/04/01
 */
extern osThreadState_t osThreadGetState (
    osThreadId_t    thread_id   )
{
#if( INCLUDE_eTaskGetState == 1 )
    osThreadState_t ret =   osThreadError;
    
    do
    {
        if(IS_IRQ())
        {
            ret =   osThreadError;
            break;
        }
        if(!thread_id)
        {
            ret =   osThreadError;
            break;
        }
        switch(eTaskGetState((TaskHandle_t)thread_id))
        {
            case eRunning:
                ret =   osThreadRunning;
                break;
            case eReady:
                ret =   osThreadReady;
                break;
            case eBlocked:
            case eSuspended:
                ret =   osThreadBlocked;
                break;
            case eDeleted:
                ret =   osThreadTerminated;
                break;
            default:
                ret =   osThreadError;
                break;
        }
    }while(0);
    
    return ret;
#else
    (void)thread_id;
    return (osThreadError);
#endif
}

/** 
 * @brief               Get stack size of a thread.
 * @param[in]           thread_id       thread ID obtained by \ref osThreadNew or \ref osThreadGetId.
 * @return              stack size in bytes.
 * @author              zhaozhenge@outlook.com
 * @date                2019/04/01
 * @note                Currently not support this feature
 */
extern uint32_t osThreadGetStackSize    (
    osThreadId_t    thread_id   )
{
    /* FreeRTOS do not support this feature */
    (void)thread_id;
    return (0);
}

/** 
 * @brief               Get available stack space of a thread based on stack watermark recording during execution.
 * @param[in]           thread_id       thread ID obtained by \ref osThreadNew or \ref osThreadGetId.
 * @return              remaining stack space in bytes.
 * @author              zhaozhenge@outlook.com
 * @date                2019/04/01
 */
extern uint32_t osThreadGetStackSpace   (
    osThreadId_t    thread_id   )
{
#if ( INCLUDE_uxTaskGetStackHighWaterMark == 1 )
    uint32_t    ret =   0;
    
    do
    {
        if(IS_IRQ())
        {
            ret =   0;
            break;
        }
        if(!thread_id)
        {
            ret =   0;
            break;
        }
        ret =   (uint32_t)uxTaskGetStackHighWaterMark((TaskHandle_t)thread_id);
    }while(0);
    
    return ret;
#else
    (void)thread_id;
    return (0);
#endif
}

/** 
 * @brief               Change priority of a thread.
 * @param[in]           thread_id       thread ID obtained by \ref osThreadNew or \ref osThreadGetId.
 * @param[in]           priority        new priority value for the thread function.
 * @retval              osOK
 * @retval              osErrorISR
 * @retval              osErrorParameter
 * @author              zhaozhenge@outlook.com
 * @date                2019/04/01
 */
extern osStatus_t osThreadSetPriority   (
    osThreadId_t    thread_id,
    osPriority_t    priority    )
{
#if ( INCLUDE_vTaskPrioritySet == 1 )
    osStatus_t  ret =   osOK;

    do
    {
        if(IS_IRQ())
        {
            ret =   osErrorISR;
            break;
        }
        if ( (!thread_id) || (priority < osPriorityIdle) || (priority > osPriorityISR) ) 
        {
            ret =   osErrorParameter;
            break;
        }
        vTaskPrioritySet((TaskHandle_t)thread_id, (UBaseType_t)priority);
        ret =   osOK;
    }while(0);

    return ret;
#else
    (void)thread_id;
    (void)priority;
    return (osError);
#endif
}

/** 
 * @brief               Get current priority of a thread.
 * @param[in]           thread_id       thread ID obtained by \ref osThreadNew or \ref osThreadGetId.
 * @return              current priority value of the specified thread.
 * @author              zhaozhenge@outlook.com
 * @date                2019/04/01
 */
extern osPriority_t osThreadGetPriority (
    osThreadId_t    thread_id   )
{
#if ( INCLUDE_uxTaskPriorityGet == 1 )
    osPriority_t    ret =   osPriorityNone;

    do
    {
        if(IS_IRQ())
        {
            ret =   osPriorityError;
            break;
        }
        if (!thread_id) 
        {
            ret =   osPriorityError;
            break;
        }
        ret =   (osPriority_t)uxTaskPriorityGet((TaskHandle_t)thread_id);
    }while(0);

    return ret;
#else
    (void)thread_id;
    return (osPriorityError);
#endif
}

/** 
 * @brief               Pass control to next thread that is in state \b READY.
 * @retval              osOK
 * @retval              osErrorISR
 * @author              zhaozhenge@outlook.com
 * @date                2019/04/01
 */
extern osStatus_t osThreadYield (void)
{
    osStatus_t  ret =   osOK;

    do
    {
        if(IS_IRQ())
        {
            ret =   osErrorISR;
            break;
        }
        taskYIELD();
        ret =   osOK;
    }while(0);

    return ret;
}

/** 
 * @brief               Suspend execution of a thread.
 * @param[in]           thread_id       thread ID obtained by \ref osThreadNew or \ref osThreadGetId.
 * @retval              osOK
 * @retval              osErrorISR
 * @retval              osErrorParameter
 * @author              zhaozhenge@outlook.com
 * @date                2019/04/01
 */
extern osStatus_t osThreadSuspend   (
    osThreadId_t    thread_id   )
{
#if ( INCLUDE_vTaskSuspend == 1 )
    osStatus_t  ret =   osOK;

    do
    {
        if(IS_IRQ())
        {
            ret =   osErrorISR;
            break;
        }
        if(!thread_id)
        {
            ret =   osErrorParameter;
            break;
        }
        vTaskSuspend((TaskHandle_t)thread_id);
        ret =   osOK;
    }while(0);

    return ret;
#else
    (void)thread_id;
    return (osError);
#endif
}

/** 
 * @brief               Resume execution of a thread.
 * @param[in]           thread_id       thread ID obtained by \ref osThreadNew or \ref osThreadGetId.
 * @retval              osOK
 * @retval              osErrorISR
 * @retval              osErrorParameter
 * @author              zhaozhenge@outlook.com
 * @date                2019/04/01
 */
extern osStatus_t osThreadResume(
    osThreadId_t    thread_id   )
{
#if ( INCLUDE_vTaskSuspend == 1 )
    osStatus_t  ret =   osOK;

    do
    {
        if(IS_IRQ())
        {
            ret =   osErrorISR;
            break;
        }
        if(!thread_id)
        {
            ret =   osErrorParameter;
            break;
        }
        vTaskResume((TaskHandle_t)thread_id);
        ret =   osOK;
    }while(0);

    return ret;
#else
    (void)thread_id;
    return (osError);
#endif
}

/** 
 * @brief               Detach a thread (thread storage can be reclaimed when thread terminates).
 * @param[in]           thread_id       thread ID obtained by \ref osThreadNew or \ref osThreadGetId.
 * @retval              osError
 * @author              zhaozhenge@outlook.com
 * @date                2019/04/01
 * @note                Currently not support this feature(all of the thread is osThreadDetached)
 */
extern osStatus_t osThreadDetach(
    osThreadId_t    thread_id   )
{
    (void)thread_id;
    return (osError);
}

/** 
 * @brief               Wait for specified thread to terminate.
 * @param[in]           thread_id       thread ID obtained by \ref osThreadNew or \ref osThreadGetId.
 * @retval              osError
 * @author              zhaozhenge@outlook.com
 * @date                2019/04/01
 * @note                Currently not support this feature(all of the thread is osThreadDetached)
 */
extern osStatus_t osThreadJoin  (
    osThreadId_t    thread_id   )
{
    (void)thread_id;
    return (osError);
}

/** 
 * @brief               Terminate execution of current running thread.
 * @return              None
 * @author              zhaozhenge@outlook.com
 * @date                2019/04/01
 */
__NO_RETURN void osThreadExit (void)
{
#if ( INCLUDE_vTaskDelete == 1 )
    vTaskDelete(NULL);
#endif
    for(;;){}
}

/** 
 * @brief               Terminate execution of a thread.
 * @param[in]           thread_id       thread ID obtained by \ref osThreadNew or \ref osThreadGetId.
 * @retval              osOK
 * @retval              osErrorISR
 * @retval              osErrorParameter
 * @retval              osErrorResource
 * @author              zhaozhenge@outlook.com
 * @date                2019/04/01
 */
extern osStatus_t osThreadTerminate (
    osThreadId_t    thread_id   )
{
#if ( INCLUDE_vTaskDelete == 1 )
    osStatus_t  ret     =   osOK;
#if ( INCLUDE_eTaskGetState == 1 )
    eTaskState  stat    =   eInvalid;
#endif
    do
    {
        if(IS_IRQ())
        {
            ret =   osErrorISR;
            break;
        }
        if(!thread_id)
        {
            ret =   osErrorParameter;
            break;
        }
#if ( INCLUDE_eTaskGetState == 1 )
        stat    =   eTaskGetState((TaskHandle_t)thread_id);
        if( (eDeleted == stat) || (eInvalid == stat) )
        {
            ret =   osErrorResource;
            break;
        }
#endif
        vTaskDelete((TaskHandle_t)thread_id);
        ret =   osOK;
    }while(0);

    return ret;
#else
    (void)thread_id;
    return (osError);
#endif
}

/** 
 * @brief               Get number of active threads.
 * @return              number of active threads.
 * @author              zhaozhenge@outlook.com
 * @date                2019/04/01
 */
extern uint32_t osThreadGetCount (void)
{
    uint32_t    ret =   0;

    do
    {
        if(IS_IRQ())
        {
            ret =   0;
            break;
        }
        ret =   (uint32_t)uxTaskGetNumberOfTasks();
    }while(0);

    return ret;
}

/** 
 * @brief               Enumerate active threads.
 * @param[out]          thread_array    pointer to array for retrieving thread IDs.
 * @param[in]           array_items     maximum number of items in array for retrieving thread IDs.
 * @return              number of enumerated threads.
 * @author              zhaozhenge@outlook.com
 * @date                2019/04/01
 */
extern uint32_t osThreadEnumerate   (
    osThreadId_t*   thread_array,
    uint32_t        array_items )
{
#if( (configSUPPORT_DYNAMIC_ALLOCATION == 1) && (configUSE_TRACE_FACILITY == 1) )
    uint32_t                ret             =   0;
    volatile UBaseType_t    tskNum          =   0;
    TaskStatus_t*           tskStatusArray  =   NULL;

    do
    {
        if(IS_IRQ())
        {
            ret =   0;
            break;
        }
        if( (!thread_array) || (!array_items) )
        {
            ret =   0;
            break;
        }
        tskNum  =   uxTaskGetNumberOfTasks();
        if(!tskNum)
        {
            ret =   0;
            break;
        }
        tskStatusArray  =   pvPortMalloc (tskNum * sizeof(TaskStatus_t));
        if(!tskStatusArray)
        {
            ret =   0;
            break;
        }
        tskNum  =   uxTaskGetSystemState (tskStatusArray, tskNum, NULL);
        for(ret = 0; (ret < tskNum) && (ret < array_items); ret++)
        {
            thread_array[ret]   =   (osThreadId_t)tskStatusArray[ret].xHandle;
        }
    }while(0);

    if(tskStatusArray)
    {
        vPortFree(tskStatusArray);
    }
    return ret;
#else
    (void)thread_array;
    (void)array_items;
    return (0);
#endif
}
