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
 * @file        cmsis_os2_kernel.c
 * @brief       CMSIS RTOS Kernel Information and Control wrapper of FreeRTOS.
 * @author      zhaozhenge@outlook.com
 *
 * @version     00.00.01 
 *              - 2019/04/03 : zhaozhenge@outlook.com 
 *                  -# New
 */

/**************************************************************
**  Include
**************************************************************/

#include <string.h>

#include "cmsis_os2_dev.h"
#include "FreeRTOS.h"
#include "task.h"

/**************************************************************
**  Symbol
**************************************************************/

#define D_KERNEL_VER_MAJOR          (10)
#define D_KERNEL_VER_MINOR          (2)
#define D_KERNEL_VER_REV            (0)

#define D_API_VER_MAJOR             (0)
#define D_API_VER_MINOR             (0)
#define D_API_VER_REV               (1)

#define KERNEL_VERSION              (((uint32_t)D_KERNEL_VER_MAJOR * 10000000UL) | \
                                       ((uint32_t)D_KERNEL_VER_MINOR * 10000UL) | \
                                       ((uint32_t)D_KERNEL_VER_REV * 1UL))

#define API_VERSION                 (((uint32_t)D_API_VER_MAJOR * 10000000UL) | \
                                       ((uint32_t)D_API_VER_MINOR * 10000UL) | \
                                       ((uint32_t)D_API_VER_REV * 1UL))

/**************************************************************
**  Global Param
**************************************************************/

static osKernelState_t      g_KernelState   =   osKernelInactive;
static const char*          g_KernalId      =   "FreeRTOSv10.2.0";
#if ( configSUPPORT_DYNAMIC_ALLOCATION == 1 )
static const HeapRegion_t   g_HeapRegions[] =   {
                                                    {   (uint8_t*)0x10000000,   configTOTAL_HEAP_SIZE },
                                                    {   NULL,                   0                     }
                                                };
#endif
#if ( configSUPPORT_STATIC_ALLOCATION == 1 )
static StaticTask_t         g_IdleTaskTCBBuffer;
static StackType_t          g_IdleTaskStackBuffer[configMINIMAL_STACK_SIZE];
static StaticTask_t         g_TimerTaskTCBBuffer;
static StackType_t          g_TimerTaskStackBuffer[configTIMER_TASK_STACK_DEPTH];
#endif

/**************************************************************
**  Interface
**************************************************************/

#if( configSUPPORT_STATIC_ALLOCATION == 1 )
/**
 * @brief               Get memory for idle task.
 * @param[out]          ppxIdleTaskTCBBuffer    pointer to buffer for for control block.
 * @param[out]          ppxIdleTaskStackBuffer  pointer to buffer for for stack.
 * @param[out]          pulIdleTaskStackSize    size of stack.
 * @return              None
 * @author              zhaozhenge@outlook.com
 * @date                2019/03/28
 */
extern void vApplicationGetIdleTaskMemory   (
    StaticTask_t**  ppxIdleTaskTCBBuffer,
    StackType_t**   ppxIdleTaskStackBuffer,
    uint32_t*       pulIdleTaskStackSize    )
{
    *ppxIdleTaskTCBBuffer   =   &g_IdleTaskTCBBuffer;
    *ppxIdleTaskStackBuffer =   (StackType_t*)g_IdleTaskStackBuffer;
    *pulIdleTaskStackSize   =   configMINIMAL_STACK_SIZE;
}

/**
 * @brief               Get memory for timer task.
 * @param[out]          ppxTimerTaskTCBBuffer   pointer to buffer for for control block.
 * @param[out]          ppxTimerTaskStackBuffer pointer to buffer for for stack.
 * @param[out]          pulTimerTaskStackSize   size of stack.
 * @return              None
 * @author              zhaozhenge@outlook.com
 * @date                2019/05/14
 */
extern void vApplicationGetTimerTaskMemory  (
    StaticTask_t**  ppxTimerTaskTCBBuffer,
    StackType_t**   ppxTimerTaskStackBuffer,
    uint32_t*       pulTimerTaskStackSize   )
{
    *ppxTimerTaskTCBBuffer  =   &g_TimerTaskTCBBuffer;
    *ppxTimerTaskStackBuffer=   (StackType_t*)g_TimerTaskStackBuffer;
    *pulTimerTaskStackSize  =   configTIMER_TASK_STACK_DEPTH;
}

#endif

/** 
 * @brief               Initialize the RTOS Kernel.
 * @retval              osOK
 * @author              zhaozhenge@outlook.com
 * @date                2019/03/28
 */
extern osStatus_t osKernelInitialize (void)
{
    osStatus_t  ret =   osOK;
    
    do
    {
        if(IS_IRQ())
        {
            ret =   osErrorISR;
            break;
        }
        if(osKernelInactive != g_KernelState)
        {
            ret =   osError;
            break;
        }
#if ( configSUPPORT_DYNAMIC_ALLOCATION == 1 )
        /* create heap */
        vPortDefineHeapRegions (g_HeapRegions);
#endif
        g_KernelState   =   osKernelReady;
    }while(0);

    return ret;
}

/** 
 * @brief               Get RTOS Kernel Information.
 * @param[out]          version         pointer to buffer for retrieving version information.
 * @param[out]          id_buf          pointer to buffer for retrieving kernel identification string.
 * @param[in]           id_size         size of buffer for kernel identification string.
 * @retval              osOK
 * @retval              osErrorNoMemory
 * @author              zhaozhenge@outlook.com
 * @date                2019/03/28
 */
extern osStatus_t osKernelGetInfo  (
    osVersion_t*    version,
    char*           id_buf,
    uint32_t        id_size )
{
    osStatus_t  ret     =   osOK;
    uint32_t    length  =   strlen(g_KernalId) + 1;

    do
    {
        if( (!id_buf) && (id_size < length) )
        {
            ret =   osErrorNoMemory;
            break;
        }
        if(version)
        {
            version->kernel =   KERNEL_VERSION;
            version->api    =   API_VERSION;
        }
        if(id_buf)
        {
            memcpy(id_buf, g_KernalId, length);
        }
    }while(0);

    return ret;
}

/** 
 * @brief               Get the current RTOS Kernel state.
 * @retval              osKernelInactive
 * @retval              osKernelSuspended
 * @retval              osKernelRunning
 * @retval              osKernelReady
 * @retval              osKernelLocked
 * @retval              osKernelError
 * @author              zhaozhenge@outlook.com
 * @date                2019/03/28
 */
extern osKernelState_t osKernelGetState (void)
{
#if ( INCLUDE_xTaskGetSchedulerState == 1 )
    osKernelState_t ret =   osKernelError;

    do
    {
        if(osKernelRunning != ret)
        {
            ret =   g_KernelState;
            break;
        }
        switch(xTaskGetSchedulerState())
        {
            case taskSCHEDULER_RUNNING:
                ret =   osKernelRunning;
                break;
            case taskSCHEDULER_NOT_STARTED:
                ret =   osKernelReady;
                break;
            case taskSCHEDULER_SUSPENDED:
                ret =   osKernelLocked;
                break;
            default:
                ret =   osKernelError;
                break;
        }
    }while(0);

    return ret;
#else
    return (osKernelError);
#endif
}

/** 
 * @brief               Start the RTOS Kernel scheduler.
 * @retval              osErrorISR
 * @retval              osError
 * @retval              osOK
 * @author              zhaozhenge@outlook.com
 * @date                2019/03/28
 */
extern osStatus_t osKernelStart (void)
{
    if(IS_IRQ())
    {
        return (osErrorISR);
    }
    if(osKernelReady != g_KernelState)
    {
        return (osError);
    }
    g_KernelState   =   osKernelRunning;
    vTaskStartScheduler();
    return (osOK);
}

/** 
 * @brief               Lock the RTOS Kernel scheduler.
 * @retval              1               previous lock state locked
 * @retval              0               previous lock state not locked
 * @retval              osErrorISR      call in Interrupt Service Routine
 * @retval              osError         unexpected error
 * @author              zhaozhenge@outlook.com
 * @date                2019/03/28
 */
extern int32_t osKernelLock (void)
{
    int32_t ret =   0;
    
    do
    {
        if(IS_IRQ())
        {
            ret =   (int32_t)osErrorISR;
            break;
        }
        switch(osKernelGetState())
        {
            case osKernelLocked:
                ret =   1;
                break;
            case osKernelRunning:
                ret =   0;
                vTaskSuspendAll();
                break;
            default:
                ret =   (int32_t)osError;
                break;
        }
    }while(0);

    return ret;
}

/** 
 * @brief               Unlock the RTOS Kernel scheduler.
 * @retval              1               previous lock state locked
 * @retval              0               previous lock state not locked
 * @retval              osErrorISR      call in Interrupt Service Routine
 * @retval              osError         unexpected error
 * @author              zhaozhenge@outlook.com
 * @date                2019/03/28
 */
extern int32_t osKernelUnlock (void)
{
    int32_t ret =   0;
    
    do
    {
        if(IS_IRQ())
        {
            ret =   (int32_t)osErrorISR;
            break;
        }
        switch(osKernelGetState())
        {
            case osKernelLocked:
                ret =   1;
                if(!xTaskResumeAll())
                {
                    taskYIELD ();
                }
                break;
            case osKernelRunning:
                ret =   0;
                break;
            default:
                ret =   (int32_t)osError;
                break;
        }
    }while(0);

    return ret;
}

/** 
 * @brief               Restore the RTOS Kernel scheduler lock state.
 * @param[in]           lock            lock state obtained by \ref osKernelLock or \ref osKernelUnlock.
 * @retval              1               new lock state locked
 * @retval              0               new lock state not locked
 * @retval              osErrorISR      call in Interrupt Service Routine
 * @retval              osError         unexpected error
 * @author              zhaozhenge@outlook.com
 * @date                2019/03/28
 */
extern int32_t osKernelRestoreLock  (
    int32_t lock    )
{
    int32_t ret =   0;
    
    do
    {
        if(IS_IRQ())
        {
            ret =   (int32_t)osErrorISR;
            break;
        }
        if(osKernelRunning != g_KernelState)
        {
            ret =   (int32_t)osError;
            break;
        }
        if(1 == lock)
        {
            vTaskSuspendAll();
            ret =   1;
        }
        else if(0 == lock)
        {
            if(!xTaskResumeAll())
            {
                taskYIELD ();
            }
            ret =   0;
        }
        else
        {
            ret =   (int32_t)osError;
        }
    }while(0);

    return ret;
}

/** 
 * @brief               Suspend the RTOS Kernel scheduler.
 * @return              time in ticks, for how long the system can sleep or power-down.
 * @author              zhaozhenge@outlook.com
 * @date                2019/03/28
 * @note                Currently not support this feature
 */
extern uint32_t osKernelSuspend (void)
{
    /* currently not support */
    return (0);
}

/** 
 * @brief               Resume the RTOS Kernel scheduler.
 * @param[in]           sleep_ticks     time in ticks for how long the system was in sleep or power-down mode.
 * @return              None
 * @author              zhaozhenge@outlook.com
 * @date                2019/03/28
 * @note                Currently not support this feature
 */
extern void osKernelResume  (
    uint32_t    sleep_ticks )
{
    /* currently not support */
    (void)sleep_ticks;
}

/** 
 * @brief               Get the RTOS kernel tick count.
 * @return              RTOS kernel current tick count
 * @author              zhaozhenge@outlook.com
 * @date                2019/03/28
 */
extern uint32_t osKernelGetTickCount (void)
{
    uint32_t    ret =   0;

    do
    {
        if(IS_IRQ())
        {
            ret =   (uint32_t)xTaskGetTickCountFromISR();
        }
        else
        {
            ret =   (uint32_t)xTaskGetTickCount();
        }
    }while(0);

    return ret;
}

/** 
 * @brief               Get the RTOS kernel tick frequency.
 * @return              frequency of the kernel tick in Hertz, i.e. kernel ticks per second
 * @author              zhaozhenge@outlook.com
 * @date                2019/03/28
 */
extern uint32_t osKernelGetTickFreq (void)
{
    return (configTICK_RATE_HZ);
}

/** 
 * @brief               Get the RTOS kernel system timer count.
 * @return              RTOS kernel current system timer count as 32-bit value.
 * @author              zhaozhenge@outlook.com
 * @date                2019/03/28
 */
extern uint32_t osKernelGetSysTimerCount (void)
{
    return osKernelGetTickCount();
}

/** 
 * @brief               Get the RTOS kernel system timer frequency.
 * @return              frequency of the system timer in hertz, i.e. timer ticks per second.
 * @author              zhaozhenge@outlook.com
 * @date                2019/03/28
 */
extern uint32_t osKernelGetSysTimerFreq (void)
{
    return osKernelGetTickFreq();
}
