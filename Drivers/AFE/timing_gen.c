/**
 * @file timing_gen.c
 * @author simakeng (simakeng@outlook.com)
 * @brief
 * @version 0.1
 * @date 2024-06-25
 *
 * *****************************************************************************
 * @copyright Copyright (C) E15 Studio 2024
 *
 * This program is FREE software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License version 3 as published by the
 * Free Software Foundation.
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc.,
 * 675 Mass Ave, Cambridge, MA 02139, USA. Or you can visit the link below to
 * read the license online, or you can find a copy of the license in the root
 * directory of this project named "LICENSE" file.
 *
 * https://www.gnu.org/licenses/gpl-3.0.html
 *
 * *****************************************************************************
 *
 */

/******************************************************************************/
/*                               INCLUDE FILES                                */
/******************************************************************************/

#include "timing_gen.h"

#include <main.h>
#include <tim.h>

#include <hardware/devop.h>
#include <error_codes.h>

/******************************************************************************/
/*                            CONSTANT DEFINITIONS                            */
/******************************************************************************/

/******************************************************************************/
/*                              MACRO DEFINITIONS                             */
/******************************************************************************/

/******************************************************************************/
/*                              TYPE DEFINITIONS                              */
/******************************************************************************/

/******************************************************************************/
/*                            CONSTANT DEFINITIONS                            */
/******************************************************************************/

/******************************************************************************/
/*                          PUBLIC DATA DEFINITIONS                           */
/******************************************************************************/

/******************************************************************************/
/*                          PRIVATE DATA DEFINITIONS                          */
/******************************************************************************/

/******************************************************************************/
/*                        PRIVATE FUNCTION DEFINITIONS                        */
/******************************************************************************/

/******************************************************************************/
/*                      PUBLIC FUNCTION IMPLEMENTATIONS                       */
/******************************************************************************/

int afe_timing_gen_init(void)
{
    return afe_timing_gen_reset();
}

int afe_timing_gen_start(void)
{
    // TIM3 is a slave timer to TIM1, so dont need to start it manually.
    // HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);

    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4); 
}

int afe_timing_gen_stop(void)
{
    HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
    HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_4);
    HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_1);

    HAL_TIM_Base_Stop(&htim1);
    HAL_TIM_Base_Stop(&htim3);
}

int afe_timing_gen_reset(void)
{
    int res = afe_timing_gen_stop();
    if (FAILED(res))
        return res;

    // Part of the timer initialization code is in the tim.c file
    // see void MX_TIM1_Init(void) and void MX_TIM3_Init(void) for more
    // detailed configuration.

    // Delay the reset pulse by 10us.
    TIM3->CNT = 40000 - 10 * 4;
    TIM1->CNT = 0;

    // No need to update timer CC here, it is done in MX_TIMX_Init.

    return ALL_OK;
}
/******************************************************************************/
/*                     PRIVATE FUNCTION IMPLEMENTATIONS                       */
/******************************************************************************/

/******************************************************************************/
/*                                 END OF FILE                                */
/******************************************************************************/
