/**
 * @file pull_mat.c
 * @author simakeng (simakeng@outlook.com)
 * @brief
 * @version 0.1
 * @date 2024-06-24
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

#include "pull_mat.h"

#include <stdlib.h>
#include <string.h>

#include <error_codes.h>
#include <hardware/devop.h>

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

static inline uint32_t translate_channel(uint32_t ch);
static inline bool is_at_high_half(uint32_t ch);

/******************************************************************************/
/*                      PUBLIC FUNCTION IMPLEMENTATIONS                       */
/******************************************************************************/

int afe_pull_matrix_init(afe_pull_matrix_t *matrix, afe_pull_matrix_hal_t *hal)
{
    PARAM_NOT_NULL(matrix);
    PARAM_NOT_NULL(hal);

    PARAM_NOT_NULL(hal->gpio_clear_set);
    PARAM_NOT_NULL(hal->gpio_latch_set);
    PARAM_NOT_NULL(hal->gpio_oe_set);
    PARAM_NOT_NULL(hal->spi_write);

    // memset the matrix
    memset(matrix, 0, sizeof(afe_pull_matrix_t));

    // copy the HAL functions
    matrix->hal = *hal;

    // init gpio status
    CALL_WITH_ERROR_RETURN(matrix->hal.gpio_clear_set, 0);
    CALL_WITH_ERROR_RETURN(matrix->hal.gpio_latch_set, 0);
    CALL_WITH_ERROR_RETURN(matrix->hal.gpio_oe_set, 1);

    // release the reset pin
    CALL_WITH_ERROR_RETURN(matrix->hal.gpio_clear_set, 1);

    // disable the output
    CALL_WITH_ERROR_RETURN(matrix->hal.gpio_oe_set, 1);

    // send the initial state to the matrix
    CALL_WITH_ERROR_RETURN(afe_pull_matrix_apply, matrix);

    // move the data from shift register to storage register
    CALL_WITH_ERROR_RETURN(matrix->hal.gpio_latch_set, 1);
    // maybe some delay here ;-)
    CALL_WITH_ERROR_RETURN(matrix->hal.gpio_latch_set, 0);

    return 0;
}

int afe_pull_matrix_get(afe_pull_matrix_t *matrix, uint8_t channel,
                        afe_pull_e *pull)
{
    PARAM_NOT_NULL(matrix);
    PARAM_NOT_NULL(pull);

    if (channel >= CONFIG_PULL_MATRIX_CHANNEL_COUNT)
    {
        return E_INVALID_ARGUMENT;
    }
    uint32_t index = translate_channel(channel) / 2;

    uint32_t pull_value = AMUX_NO_PULL;

    if (is_at_high_half(channel))
        pull_value = matrix->pulls[index].hi;
    else
        pull_value = matrix->pulls[index].lo;

    *pull = (afe_pull_e)pull_value;

    return ALL_OK;
}

int afe_pull_matrix_set(afe_pull_matrix_t *matrix, uint8_t channel,
                        afe_pull_e pull)
{
    PARAM_NOT_NULL(matrix);

    if (channel >= CONFIG_PULL_MATRIX_CHANNEL_COUNT)
    {
        return E_INVALID_ARGUMENT;
    }

    uint32_t index = translate_channel(channel) / 2;

    if (is_at_high_half(channel))
        matrix->pulls[index].hi = pull;
    else
        matrix->pulls[index].lo = pull;

    return ALL_OK;
}

int afe_pull_matrix_clear(afe_pull_matrix_t *matrix)
{
    PARAM_NOT_NULL(matrix);

    memset(matrix->pulls, 0, sizeof(matrix->pulls));

    return ALL_OK;
}

int afe_pull_matrix_enable(afe_pull_matrix_t *matrix)
{
    PARAM_NOT_NULL(matrix);

    CALL_WITH_ERROR_RETURN(matrix->hal.gpio_oe_set, 0);

    return ALL_OK;
}

int afe_pull_matrix_disable(afe_pull_matrix_t *matrix)
{
    PARAM_NOT_NULL(matrix);

    CALL_WITH_ERROR_RETURN(matrix->hal.gpio_oe_set, 1);

    return ALL_OK;
}

int afe_pull_matrix_set_all(afe_pull_matrix_t *matrix, afe_pull_e pull)
{
    PARAM_NOT_NULL(matrix);

    uint32_t data = (pull << 4) | pull;

    memset(matrix->pulls, data, sizeof(matrix->pulls));

    return ALL_OK;
}

int afe_pull_matrix_apply(afe_pull_matrix_t *matrix)
{
    PARAM_NOT_NULL(matrix);

    CALL_NULLABLE_WITH_ERROR(matrix->hal.spi_aquire);

    CALL_WITH_ERROR_RETURN(matrix->hal.spi_write, matrix->pulls,
                           sizeof(matrix->pulls));

    CALL_WITH_ERROR_RETURN(matrix->hal.gpio_latch_set, 1);
    CALL_WITH_ERROR_RETURN(matrix->hal.gpio_latch_set, 0);

    CALL_NULLABLE_WITH_ERROR(matrix->hal.spi_release);

    return ALL_OK;
}

/******************************************************************************/
/*                     PRIVATE FUNCTION IMPLEMENTATIONS                       */
/******************************************************************************/
static inline uint32_t translate_channel(uint32_t ch)
{
    if (ch > CONFIG_PULL_MATRIX_CHANNEL_COUNT)
        ch %= CONFIG_PULL_MATRIX_CHANNEL_COUNT;

    return CONFIG_PULL_MATRIX_CHANNEL_COUNT - 1 - ch;
}

static inline bool is_at_high_half(uint32_t ch)
{
    return (ch % 2) == 1;
}
/******************************************************************************/
/*                                 END OF FILE                                */
/******************************************************************************/
