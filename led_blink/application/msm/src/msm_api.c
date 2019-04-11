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
**  STM32 MCU program sample thread (LED blink)
**************************************************************/
/** 
 * @file        msm_api.c
 * @brief       machine status management module external API used by other application module.
 * @author      zhaozhenge@outlook.com
 *
 * @version     00.00.01 
 *              - 2019/04/08 : zhaozhenge@outlook.com
 *                  -# New
 */

/**************************************************************
**  Include
**************************************************************/

#include <string.h>

#include "stm32l4xx_ll_bus.h"
#include "stm32l4xx_ll_gpio.h"
#include "cmsis_os2.h"

/**************************************************************
**  Interface
**************************************************************/

/** 
 * @brief               Machine status management thread
 * @param[in]           argument        User argument
 * @return              None
 * @author              zhaozhenge@outlook.com
 * @date                2019/04/08
 */
extern void msm_thread(void *argument)
{
    (void)argument;
    for(;;)
    {
        osDelay (1000);
        LL_GPIO_TogglePin(GPIOB, LL_GPIO_PIN_14);
    }
}

/** 
 * @brief               Initial machine status management module
 * @return              None
 * @author              zhaozhenge@outlook.com
 * @date                2019/04/08
 */
extern void msm_init(void)
{
    LL_GPIO_InitTypeDef GPIO_InitStruct;
    /* initial led hardware */
    memset(&GPIO_InitStruct, 0, sizeof(LL_GPIO_InitTypeDef));
    LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOB);
    LL_GPIO_StructInit(&GPIO_InitStruct);
    GPIO_InitStruct.Pin = LL_GPIO_PIN_14;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    if(SUCCESS == LL_GPIO_Init(GPIOB, &GPIO_InitStruct))
    {
        /* LED initial success */
        LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_14);
    }
}

