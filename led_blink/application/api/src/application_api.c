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
 * @file        application_api.c
 * @brief       application external API used by system low layer.
 * @author      zhaozhenge@outlook.com
 *
 * @version     00.00.01 
 *              - 2019/03/28 : zhaozhenge@outlook.com 
 *                  -# New
 */

/**************************************************************
**  Include
**************************************************************/

#include "cmsis_os2.h"
#include "wrapper_api.h"
#include "msm_api.h"

/**************************************************************
**  Structure
**************************************************************/

static uint8_t msm_stack[1024];
static uint8_t msm_cb[sizeof(THREAD_CB)];

/**
 * @brief      Machine status Management thread attribute
 * @author     zhaozhenge@outlook.com
 * @date       2019/04/08
 */
static const osThreadAttr_t msm_attr = 
{
    "MSM",                  /*!< name of the thread */
    osThreadDetached,       /*!< attribute bits */
    (void*)msm_cb,          /*!< memory for control block */
    sizeof(msm_cb),         /*!< size of provided memory for control block */
    (void*)msm_stack,       /*!< memory for stack */
    sizeof(msm_stack),      /*!< size of stack */
    osPriorityNormal,       /*!< initial thread priority */
    0,                      /*!< TrustZone module identifier(not used) */
    0                       /*!< reserved(not used) */
};

/**************************************************************
**  Interface
**************************************************************/

/** 
 * @brief               application run
 * @return              error code
 * @author              zhaozhenge@outlook.com
 * @date                2019/03/28
 */
extern int Application_run (void)
{
    /* Initialize RTOS kernel */
    if(osOK != osKernelInitialize())
    {
        return (-1);
    }
    /* Initialize each application module */
    msm_init();
    /* Create each application thread / task */
    if(NULL == osThreadNew(msm_thread, NULL, &msm_attr))
    {
        return (-1);
    }
    /* RTOS kernel start to schedule */
    if(osOK != osKernelStart())
    {
        return (-1);
    }
    /* Should never reach here  */
    return (0);
}
