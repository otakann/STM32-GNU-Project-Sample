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
**  STM32 MCU program entry (STM32L4)
**************************************************************/
/** 
 * @file        main.c
 * @brief       A Sample of STM32 MCU program entry.
 * @author      zhaozhenge@outlook.com
 *
 * @version     00.00.01 
 *              - 2019/03/28 : zhaozhenge@outlook.com 
 *                  -# New
 */

/**************************************************************
**  Include
**************************************************************/

#include "stm32l4xx_ll_rcc.h"
#include "stm32l4xx_ll_system.h"
#include "stm32l4xx_ll_utils.h"

#include "application_api.h"

/**************************************************************
**  Function
**************************************************************/

/** 
 * @brief               System Clock Configuration
 *                      The system Clock is configured as follows :
 *                      System Clock source            = PLL (MSI)
 *                      SYSCLK(Hz)                     = 80000000
 *                      HCLK(Hz)                       = 80000000
 *                      AHB Prescaler                  = 1
 *                      APB1 Prescaler                 = 1
 *                      APB2 Prescaler                 = 1
 *                      MSI Frequency(Hz)              = 4000000
 *                      PLL_M                          = 1
 *                      PLL_N                          = 40
 *                      PLL_R                          = 2
 *                      Flash Latency(WS)              = 4
 * @return              None
 * @author              zhaozhenge@outlook.com
 * @date                2019/03/28
 */
static void SystemClock_Config(void)
{
    /* MSI configuration and activation */
    LL_FLASH_SetLatency(LL_FLASH_LATENCY_4);
    LL_RCC_MSI_Enable();
    while(1 != LL_RCC_MSI_IsReady()) {};
    /* Main PLL configuration and activation */
    LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_MSI, LL_RCC_PLLM_DIV_1, 40, LL_RCC_PLLR_DIV_2);
    LL_RCC_PLL_Enable();
    LL_RCC_PLL_EnableDomain_SYS();
    while(1 != LL_RCC_PLL_IsReady()) {};
    /* Sysclk activation on the main PLL */
    LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
    LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);
    while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL) {};
    /* Set APB1 & APB2 prescaler*/
    LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
    LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_1);
    /* Set systick to 1ms in using frequency set to 80MHz */
    /* This frequency can be calculated through LL RCC macro */
    /* ex: __LL_RCC_CALC_PLLCLK_FREQ(__LL_RCC_CALC_MSI_FREQ(LL_RCC_MSIRANGESEL_RUN, LL_RCC_MSIRANGE_6), 
                                  LL_RCC_PLLM_DIV_1, 40, LL_RCC_PLLR_DIV_2)*/
    LL_Init1msTick(80000000);
    /* Update CMSIS variable (which can be updated also through SystemCoreClockUpdate function) */
    LL_SetSystemCoreClock(80000000);
    return;
}

/** 
 * @brief               main function
 * @author              zhaozhenge@outlook.com
 * @date                2019/03/28
 */
int main(void)
{
    /* Configure the system clock to 80 MHz */
    SystemClock_Config();
    /* application code here */
    return Application_run();
}
