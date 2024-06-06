/**
 * @file pull_mat.h
 * @author simakeng (simakeng@outlook.com)
 * @brief This is the driver for pull down resistor matrix.
 * @version 0.1
 * @date 2024-05-29
 *
 * *****************************************************************************
 * @copyright Copyright (C) E15 Studio 2024
 *
 * This program is FREE software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License version 3 as published by the
 * Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
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

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#ifndef CONFIG_PULL_MATRIX_CHANNEL_COUNT
#define CONFIG_PULL_MATRIX_CHANNEL_COUNT 16
#endif

#ifndef __AMUX_H_FILE__
#define __AMUX_H_FILE__

/**
 * @brief Enumeration of the pull down resistor values.
 */
typedef enum
{
    AMUX_NO_PULL = 0,
    AMUX_PULL_1K,
    AMUX_PULL_10K,
    AMUX_PULL_100K,
    AMUX_PULL_1M
} afe_pull_e;

/**
 * @brief Structure to hold the HAL functions for the pull down resistor matrix.
 */
typedef struct
{
    /**
     * @brief Function to aquire the SPI bus.
     * @note this field can be NULL if the SPI bus is dedicated to this module.
     */
    int (*spi_aquire)(void);

    /**
     * @brief Function to release the SPI bus.
     * @note this field can be NULL if the SPI bus is dedicated to this module.
     */
    int (*spi_release)(void);

    /**
     * @brief Set the output enable pin level.
     * @param level The level to set the output enable pin to.
     */
    int (*gpio_oe_set)(int level);

    /**
     * @brief Set the clear/set pin level.
     * @param level The level to set the clear/set pin to.
     * @note in case of 74HC595, depending on the vendor, this pin may be called
     * MR (Master Reset) or SRCLR (Shift Register Clear).
     */
    int (*gpio_clear_set)(int level);

    /**
     * @brief Set the latch pin level.
     * @param level The level to set the latch pin to.
     * @note in case of 74HC595, depending on the vendor, this pin may be called
     * STCP (Storage Register Clock Pulse).
     */
    int (*gpio_latch_set)(int level);

    /**
     * @brief Write data to the SPI bus.
     * @param data The data to write.
     * @param len The length of the data to write.
     */
    int (*spi_write)(void *data, uint32_t len);
} afe_pull_matrix_hal_t;

/**
 * @brief Instance of the pull down resistor matrix.
 */
typedef struct
{
    afe_pull_matrix_hal_t hal;
    afe_pull_e pull_status[CONFIG_PULL_MATRIX_CHANNEL_COUNT];
    uint8_t io_buffer[CONFIG_PULL_MATRIX_CHANNEL_COUNT / 2];
} afe_pull_matrix_t;

/**
 * @brief Initialize the pull down resistor matrix.
 *
 * @param matrix the matrix instance.
 * @param hal the HAL functions.
 * @return int <0 on error, 0 on success.
 */
int afe_pull_matrix_init(afe_pull_matrix_t *matrix, afe_pull_matrix_hal_t *hal);

/**
 * @brief Get the pull down resistor value for a channel.
 * 
 * @param matrix the matrix instance.
 * @param channel the channel to get the pull down resistor value for.
 * @param pull the pull down resistor value.
 * @return int <0 on error, 0 on success.
 */
int afe_pull_matrix_get(afe_pull_matrix_t *matrix, uint8_t channel,
                        afe_pull_e *pull);

/**
 * @brief Set the pull down resistor value for a channel.
 * 
 * @param matrix the matrix instance.
 * @param channel the channel to set the pull down resistor value for.
 * @param pull the pull down resistor value.
 * @return int <0 on error, 0 on success.
 */
int afe_pull_matrix_set(afe_pull_matrix_t *matrix, uint8_t channel,
                        afe_pull_e pull);

/**
 * @brief Clear the pull down resistor value for all channels.
 * 
 * @param matrix the matrix instance.
 * @return int <0 on error, 0 on success.
 */
int afe_pull_matrix_clear(afe_pull_matrix_t *matrix);

/**
 * @brief Apply the pull down resistor values to the matrix.
 * 
 * @param matrix the matrix instance.
 * @return int <0 on error, 0 on success.
 */
int afe_pull_matrix_apply(afe_pull_matrix_t *matrix);

#endif // !#ifndef __AMUX_H_FILE__
