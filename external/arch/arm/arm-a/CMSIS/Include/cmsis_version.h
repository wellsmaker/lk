/**************************************************************************//**
 * @file     cmsis_version.h
 * @brief    CMSIS Core Version definitions
 * @version  V6.0.0
 * @date     2. July 2023
 ******************************************************************************/
/*
 * Copyright (c) 2009-2023 ARM Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#if   defined ( __ICCARM__ )
  #pragma system_include         /* treat file as system include file for MISRA check */
#elif defined (__clang__)
  #pragma clang system_header   /* treat file as system include file */
#endif

#ifndef __CMSIS_VERSION_H
#define __CMSIS_VERSION_H

/*  CMSIS Version definitions */
#define __CMSIS_VERSION_MAIN    ( 6U)                                     /*!< \brief [31:16] CMSIS-Core(A/R/M) main version */
#define __CMSIS_VERSION_SUB     ( 0U)                                     /*!< \brief [15:0]  CMSIS-Core(A/R/M) sub version */
#define __CMSIS_VERSION         ((__CMSIS_VERSION_MAIN << 16U) | \
                                  _CMSIS_VERSION_SUB           )          /*!< \brief CMSIS-Core(A/R/M) version number */

#define __CA_CMSIS_VERSION_MAIN (6U)                                      /*!< \brief [31:16] CMSIS-Core(A) main version   */
#define __CA_CMSIS_VERSION_SUB  (0U)                                      /*!< \brief [15:0]  CMSIS-Core(A) sub version    */
#define __CA_CMSIS_VERSION      ((__CA_CMSIS_VERSION_MAIN << 16U) | \
                                  __CA_CMSIS_VERSION_SUB          )       /*!< \brief CMSIS-Core(A) version number         */

#define __CR_CMSIS_VERSION_MAIN (6U)                                      /*!< \brief [31:16] CMSIS-Core(R) main version   */
#define __CR_CMSIS_VERSION_SUB  (0U)                                      /*!< \brief [15:0]  CMSIS-Core(R) sub version    */
#define __CR_CMSIS_VERSION      ((__CR_CMSIS_VERSION_MAIN << 16U) | \
                                  __CR_CMSIS_VERSION_SUB          )       /*!< \brief CMSIS-Core(R) version number         */

#define __CM_CMSIS_VERSION_MAIN ( 6U)                                     /*!< \brief [31:16] CMSIS-Core(M) main version */
#define __CM_CMSIS_VERSION_SUB  ( 0U)                                     /*!< \brief [15:0]  CMSIS-Core(M) sub version */
#define __CM_CMSIS_VERSION      ((__CM_CMSIS_VERSION_MAIN << 16U) | \
                                  __CM_CMSIS_VERSION_SUB           )      /*!< \brief CMSIS-Core(M) version number */

#endif