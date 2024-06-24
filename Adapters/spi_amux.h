/**
 * @file spi_amux.h
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

#ifndef __SPI_AMUX_H__
#define __SPI_AMUX_H__

/******************************************************************************/
/*                               INCLUDE FILES                                */
/******************************************************************************/

#include <AFE/pull_mat.h>

/******************************************************************************/
/*                           PUBLIC DATA DEFINITIONS                          */
/******************************************************************************/
#ifdef __cplusplus
extern "C"
{
#endif //! #ifdef __cplusplus

    extern afe_pull_matrix_t afe_mat;

#ifdef __cplusplus
}
#endif //! #ifdef __cplusplus

/******************************************************************************/
/*                         PUBLIC FUNCTION DEFINITIONS                        */
/******************************************************************************/
#ifdef __cplusplus
extern "C"
{
#endif //! #ifdef __cplusplus

    void spi_amux_init(afe_pull_matrix_t *device);

#ifdef __cplusplus
}
#endif //! #ifdef __cplusplus
/******************************************************************************/
/*                                 END OF FILE                                */
/******************************************************************************/

#endif // ! #ifndef __SPI_AMUX_H__