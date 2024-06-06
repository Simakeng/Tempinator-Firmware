/**
 * @file uart_log.c
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
 * directory of this project named "LICENSE" file.
 * 
 * https://www.gnu.org/licenses/gpl-3.0.html
 * 
 * *****************************************************************************
 * 
 */

#include "usart.h"

#include <string.h>

#include "uart_log.h"

static int32_t uart1_dev_putc(int32_t c)
{
    HAL_StatusTypeDef res = HAL_OK;
    res = HAL_UART_Transmit(&huart1, (uint8_t *)&c, 1, 0xFFFF);
    return res == HAL_OK ? c : EOF;
}

static int32_t uart1_dev_puts(const char *s)
{
    uint32_t str_len = strlen(s);
    HAL_StatusTypeDef res = HAL_OK;
    res = HAL_UART_Transmit(&huart1, (uint8_t *)s, str_len, 0xFFFF);
    return res == HAL_OK ? str_len : EOF;
}

void uart_log_init(void)
{
    dbg_low_level_io_ops_t iops = {
        .putc = uart1_dev_putc,
        .puts = uart1_dev_puts,
    };

    dbg_print_init(&iops);
}