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
 * @file        cmsis_os2_memorypool.c
 * @brief       CMSIS RTOS Memory Pool wrapper of FreeRTOS.
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
 * @brief               Create and Initialize a Memory Pool object.
 * @param[in]           block_count     maximum number of memory blocks in memory pool.
 * @param[in]           block_size      memory block size in bytes.
 * @param[in]           attr            memory pool attributes; NULL: default values.
 * @return              memory pool ID for reference by other functions or NULL in case of error.
 * @author              zhaozhenge@outlook.com
 * @date                2019/04/02
 * @note                Currently not support this feature
 */
extern osMemoryPoolId_t osMemoryPoolNew (
    uint32_t                    block_count,
    uint32_t                    block_size,
    const osMemoryPoolAttr_t*   attr    )
{
    (void)block_count;
    (void)block_size;
    (void)attr;
    return (osMemoryPoolId_t)NULL;
}

/** 
 * @brief               Get name of a Memory Pool object.
 * @param[in]           mp_id           memory pool ID obtained by \ref osMemoryPoolNew.
 * @return              name as null-terminated string.
 * @author              zhaozhenge@outlook.com
 * @date                2019/04/02
 * @note                Currently not support this feature
 */
extern const char* osMemoryPoolGetName  (
    osMemoryPoolId_t    mp_id   )
{
    (void)mp_id;
    return NULL;
}

/** 
 * @brief               Allocate a memory block from a Memory Pool.
 * @param[in]           mp_id           memory pool ID obtained by \ref osMemoryPoolNew.
 * @param[in]           timeout         \ref CMSIS_RTOS_TimeOutValue or 0 in case of no time-out.
 * @return              address of the allocated memory block or NULL in case of no memory is available.
 * @author              zhaozhenge@outlook.com
 * @date                2019/04/02
 * @note                Currently not support this feature
 */
extern void* osMemoryPoolAlloc  (
    osMemoryPoolId_t    mp_id,
    uint32_t            timeout )
{
    (void)mp_id;
    (void)timeout;
    return NULL;
}

/** 
 * @brief               Return an allocated memory block back to a Memory Pool.
 * @param[in]           mp_id           memory pool ID obtained by \ref osMemoryPoolNew.
 * @param[in]           block           address of the allocated memory block to be returned to the memory pool.
 * @retval              osError
 * @author              zhaozhenge@outlook.com
 * @date                2019/04/02
 * @note                Currently not support this feature
 */
extern osStatus_t osMemoryPoolFree  (
    osMemoryPoolId_t    mp_id,
    void*               block   )
{
    (void)mp_id;
    (void)block;
    return (osError);
}

/** 
 * @brief               Get maximum number of memory blocks in a Memory Pool.
 * @param[in]           mp_id           memory pool ID obtained by \ref osMemoryPoolNew.
 * @return              maximum number of memory blocks.
 * @author              zhaozhenge@outlook.com
 * @date                2019/04/02
 * @note                Currently not support this feature
 */
extern uint32_t osMemoryPoolGetCapacity (
    osMemoryPoolId_t    mp_id   )
{
    (void)mp_id;
    return (0);
}

/** 
 * @brief               Get memory block size in a Memory Pool.
 * @param[in]           mp_id           memory pool ID obtained by \ref osMemoryPoolNew.
 * @return              memory block size in bytes.
 * @author              zhaozhenge@outlook.com
 * @date                2019/04/02
 * @note                Currently not support this feature
 */
extern uint32_t osMemoryPoolGetBlockSize(
    osMemoryPoolId_t    mp_id   )
{
    (void)mp_id;
    return (0);
}

/** 
 * @brief               Get number of memory blocks used in a Memory Pool.
 * @param[in]           mp_id           memory pool ID obtained by \ref osMemoryPoolNew.
 * @return              number of memory blocks used.
 * @author              zhaozhenge@outlook.com
 * @date                2019/04/02
 * @note                Currently not support this feature
 */
extern uint32_t osMemoryPoolGetCount(
    osMemoryPoolId_t    mp_id   )
{
    (void)mp_id;
    return (0);
}

/** 
 * @brief               Get number of memory blocks available in a Memory Pool.
 * @param[in]           mp_id           memory pool ID obtained by \ref osMemoryPoolNew.
 * @return              number of memory blocks available.
 * @author              zhaozhenge@outlook.com
 * @date                2019/04/02
 * @note                Currently not support this feature
 */
extern uint32_t osMemoryPoolGetSpace(
    osMemoryPoolId_t    mp_id   )
{
    (void)mp_id;
    return (0);
}

/** 
 * @brief               Delete a Memory Pool object.
 * @param[in]           mp_id           memory pool ID obtained by \ref osMemoryPoolNew.
 * @retval              osError
 * @author              zhaozhenge@outlook.com
 * @date                2019/04/02
 * @note                Currently not support this feature
 */
extern osStatus_t osMemoryPoolDelete(
    osMemoryPoolId_t    mp_id   )
{
    (void)mp_id;
    return (osError);
}
