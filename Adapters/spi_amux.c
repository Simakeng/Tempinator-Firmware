/**
 * @file spi_amux.c
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

#include "spi.h"

#include "spi_amux.h"

#include <debug/print.h>
#include <error_codes.h>

/******************************************************************************/
/*                          PUBLIC DATA DEFINITIONS                           */
/******************************************************************************/

afe_pull_matrix_t afe_mat;

/******************************************************************************/
/*                        PRIVATE FUNCTION DEFINITIONS                        */
/******************************************************************************/

static int mat_gpio_clear_set(int level);
static int mat_gpio_latch_set(int level);
static int mat_gpio_oe_set(int level);
static int mat_spi_write(const void *data, uint32_t size);
// static error_t oled_spi_aquire_bus(void);
// static error_t oled_spi_release_bus(void);

/******************************************************************************/
/*                      PUBLIC FUNCTION IMPLEMENTATIONS                       */
/******************************************************************************/

void spi_amux_init(afe_pull_matrix_t *device)
{
    afe_pull_matrix_hal_t hal = {
        .gpio_clear_set = mat_gpio_clear_set,
        .gpio_latch_set = mat_gpio_latch_set,
        .gpio_oe_set = mat_gpio_oe_set,
        .spi_write = mat_spi_write,
    };

    // delay 10 ms to let power stablize.
    HAL_Delay(10);

    int ret = afe_pull_matrix_init(device, &hal);
    if (ret != 0)
    {
        print(ERROR, "Failed to initialize [AFE:PullMatrix]: %d", ret);
    }
}

/******************************************************************************/
/*                     PRIVATE FUNCTION IMPLEMENTATIONS                       */
/******************************************************************************/

static int mat_spi_write(const void *data, uint32_t size);

static int mat_gpio_clear_set(int level)
{
    HAL_GPIO_WritePin(IO_NCLR_GPIO_Port, IO_NCLR_Pin,
                      level ? GPIO_PIN_SET : GPIO_PIN_RESET);
    return ALL_OK;
}

static int mat_gpio_latch_set(int level)
{
    HAL_GPIO_WritePin(IO_LATCH_GPIO_Port, IO_LATCH_Pin,
                      level ? GPIO_PIN_SET : GPIO_PIN_RESET);
    return ALL_OK;
}

static int mat_gpio_oe_set(int level)
{
    HAL_GPIO_WritePin(IO_NOE_GPIO_Port, IO_NOE_Pin,
                      level ? GPIO_PIN_SET : GPIO_PIN_RESET);
    return ALL_OK;
}

static int mat_spi_write(const void *data, uint32_t size)
{
    HAL_StatusTypeDef res = HAL_OK;
    res = HAL_SPI_Transmit(&hspi1, (uint8_t *)data, size, 0x7FFFFFF);
    switch (res)
    {
    case HAL_OK:
        return ALL_OK;
    case HAL_BUSY:
        return E_HARDWARE_RESOURCE_BUSY;
    case HAL_TIMEOUT:
        return E_HARDWARE_TIMEOUT;
    case HAL_ERROR:
    default:
        return E_HARDWARE_ERROR;
    }
}

/******************************************************************************/
/*                                 END OF FILE                                */
/******************************************************************************/
