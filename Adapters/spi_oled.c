/**
 * @file spi_oled.c
 * @author simakeng (simakeng@outlook.com)
 * @brief
 * @version 0.1
 * @date 2024-06-05
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
 * directory of this project named "COPYING" file.
 *
 * https://www.gnu.org/licenses/gpl-3.0.html
 *
 * *****************************************************************************
 *
 */

/******************************************************************************/
/*                               INCLUDE FILES                                */
/******************************************************************************/

#include <main.h>

#include "spi_oled.h"

#include <debug/print.h>

/******************************************************************************/
/*                          PUBLIC DATA DEFINITIONS                           */
/******************************************************************************/

ssd1306_device_t oled;
extern SPI_HandleTypeDef hspi1;

/******************************************************************************/
/*                        PRIVATE FUNCTION DEFINITIONS                        */
/******************************************************************************/

static error_t oled_gpio_cs_set(int gpio_state);
static error_t oled_gpio_dc_set(int gpio_state);
static error_t oled_gpio_rst_set(int gpio_state);
static error_t oled_spi_send( const void *data, uint32_t size);
// static error_t oled_spi_aquire_bus(void);
// static error_t oled_spi_release_bus(void);

/******************************************************************************/
/*                      PUBLIC FUNCTION IMPLEMENTATIONS                       */
/******************************************************************************/

void spi_oled_init(ssd1306_device_t *device)
{
    ssd1306_Init_t init = {
        .devop = {
            .gpio_cs_set = oled_gpio_cs_set,
            .gpio_dc_set = oled_gpio_dc_set,
            .gpio_rst_set = oled_gpio_rst_set,
            .spi_aquire = NULL,
            .spi_release = NULL,
            // .spi_aquire = oled_spi_aquire_bus,
            // .spi_release = oled_spi_release_bus,
            .spi_write = oled_spi_send,
        },
        .lr_flip = true,
        .ud_flip = true,
    };

    // delay 10 ms to let power stablize.
    HAL_Delay(10);

    error_t ret = ssd1306_init(device, &init);
    if (FAILED(ret))
    {
        print(ERROR, "Failed to initialize OLED device");
    }
}

/******************************************************************************/
/*                     PRIVATE FUNCTION IMPLEMENTATIONS                       */
/******************************************************************************/

static error_t oled_gpio_cs_set(int gpio_state)
{
    HAL_GPIO_WritePin(DISP_CS_GPIO_Port, DISP_CS_Pin,
                      gpio_state ? GPIO_PIN_SET : GPIO_PIN_RESET);

    return ALL_OK;
}

static error_t oled_gpio_dc_set(int gpio_state)
{
    HAL_GPIO_WritePin(DISP_DC_GPIO_Port, DISP_DC_Pin,
                      gpio_state ? GPIO_PIN_SET : GPIO_PIN_RESET);

    return ALL_OK;
}

static error_t oled_gpio_rst_set(int gpio_state)
{
    HAL_GPIO_WritePin(DISP_NRST_GPIO_Port, DISP_NRST_Pin,
                      gpio_state ? GPIO_PIN_SET : GPIO_PIN_RESET);

    return ALL_OK;
}

static error_t oled_spi_send( const void *data, uint32_t size)
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
