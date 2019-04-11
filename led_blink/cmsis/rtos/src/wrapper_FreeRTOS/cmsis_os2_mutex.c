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
 * @file        cmsis_os2_mutex.c
 * @brief       CMSIS RTOS Mutex Management wrapper of FreeRTOS.
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

/**************************************************************
**  Interface
**************************************************************/

/** 
 * @brief               Create and Initialize a Mutex object.
 * @param[in]           attr            mutex attributes; NULL: default values.
 * @return              mutex ID for reference by other functions or NULL in case of error.
 * @author              zhaozhenge@outlook.com
 * @date                2019/04/02
 * @note                Currently not support this feature
 */
extern osMutexId_t osMutexNew   (
    const osMutexAttr_t*    attr)
{
    (void)attr;
    return (osMutexId_t)NULL;
}

/** 
 * @brief               Get name of a Mutex object.
 * @param[in]           mutex_id        mutex ID obtained by \ref osMutexNew.
 * @return              name as null-terminated string.
 * @author              zhaozhenge@outlook.com
 * @date                2019/04/02
 * @note                Currently not support this feature
 */
extern const char* osMutexGetName   (
    osMutexId_t mutex_id    )
{
    (void)mutex_id;
    return NULL;
}

/** 
 * @brief               Acquire a Mutex or timeout if it is locked.
 * @param[in]           mutex_id        mutex ID obtained by \ref osMutexNew.
 * @param[in]           timeout         \ref CMSIS_RTOS_TimeOutValue or 0 in case of no time-out.
 * @retval              osError
 * @author              zhaozhenge@outlook.com
 * @date                2019/04/02
 * @note                Currently not support this feature
 */
extern osStatus_t osMutexAcquire(
    osMutexId_t mutex_id,
    uint32_t    timeout )
{
    (void)mutex_id;
    (void)timeout;
    return (osError);
}

/** 
 * @brief               Release a Mutex that was acquired by \ref osMutexAcquire.
 * @param[in]           mutex_id        mutex ID obtained by \ref osMutexNew.
 * @retval              osError
 * @author              zhaozhenge@outlook.com
 * @date                2019/04/02
 * @note                Currently not support this feature
 */
extern osStatus_t osMutexRelease(
    osMutexId_t mutex_id    )
{
    (void)mutex_id;
    return (osError);
}

/** 
 * @brief               Get Thread which owns a Mutex object.
 * @param[in]           mutex_id        mutex ID obtained by \ref osMutexNew.
 * @return              thread ID of owner thread or NULL when mutex was not acquired.
 * @author              zhaozhenge@outlook.com
 * @date                2019/04/02
 * @note                Currently not support this feature
 */
extern osThreadId_t osMutexGetOwner (
    osMutexId_t mutex_id    )
{
    (void)mutex_id;
    return (osThreadId_t)NULL;
}

/** 
 * @brief               Delete a Mutex object.
 * @param[in]           mutex_id        mutex ID obtained by \ref osMutexNew.
 * @retval              osError
 * @author              zhaozhenge@outlook.com
 * @date                2019/04/02
 * @note                Currently not support this feature
 */
extern osStatus_t osMutexDelete (
    osMutexId_t mutex_id    )
{
    (void)mutex_id;
    return (osError);
}
