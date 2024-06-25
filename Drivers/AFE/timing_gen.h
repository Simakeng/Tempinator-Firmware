/**
 * @file timing_gen.h
 * @author simakeng (simakeng@outlook.com)
 * @brief This is the driver timing generator.
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

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

/******************************************************************************/
/*                              MACRO DEFINITIONS                             */
/******************************************************************************/

#ifndef __TIMING_GEN_H_FILE__
#define __TIMING_GEN_H_FILE__

/******************************************************************************/
/*                         PUBLIC FUNCTION DEFINITIONS                        */
/******************************************************************************/
#ifdef __cplusplus
extern "C"
{
#endif //! #ifdef __cplusplus

    /**
     * @brief Initialize the timing generator.
     *
     * @return int
     */
    int afe_timing_gen_init(void);

    /**
     * @brief Start the timing generator.
     *
     * @return int
     */
    int afe_timing_gen_start(void);

    /**
     * @brief Stop the timing generator.
     *
     * @return int
     */
    int afe_timing_gen_stop(void);

    /**
     * @brief Reset the timing generator to its default state.
     *
     * @return int
     */
    int afe_timing_gen_reset(void);

#ifdef __cplusplus
}
#endif //! #ifdef __cplusplus
/******************************************************************************/
/*                                 END OF FILE                                */
/******************************************************************************/

#endif //! #ifndef __TIMING_GEN_H_FILE__
