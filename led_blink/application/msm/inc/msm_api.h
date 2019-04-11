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
 * @file        msm_api.h
 * @brief       machine status management module external API used by other application module.
 * @author      zhaozhenge@outlook.com
 *
 * @version     00.00.01 
 *              - 2019/04/08 : zhaozhenge@outlook.com 
 *                  -# New
 */

#ifndef _MSM_API_H_
#define _MSM_API_H_

#ifdef __cplusplus
extern "C" {
#endif

/**************************************************************
**  Interface
**************************************************************/

/** 
 * @brief               Initial machine status management module
 * @return              None
 * @author              zhaozhenge@outlook.com
 * @date                2019/04/08
 */
extern void msm_init(void);

/** 
 * @brief               Machine status management thread
 * @param[in]           argument        User argument
 * @return              None
 * @author              zhaozhenge@outlook.com
 * @date                2019/04/08
 */
extern void msm_thread  (
    void*   argument
);

#ifdef __cplusplus
}
#endif

#endif /* _MSM_API_H_ */
