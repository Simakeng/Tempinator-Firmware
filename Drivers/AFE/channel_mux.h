/**
 * @file channel_mux.h
 * @author simakeng (simakeng@outlook.com)
 * @brief This is the driver for channel multiplexer.
 * @version 0.1
 * @date 2024-05-31
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

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#ifndef __CHANNEL_MUX_H_FILE__
#define __CHANNEL_MUX_H_FILE__

int afe_channel_mux_init(void);

#endif //! #ifndef __CHANNEL_MUX_H_FILE__
