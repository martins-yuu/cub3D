/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuuko <yuuko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 20:51:18 by yuuko             #+#    #+#             */
/*   Updated: 2024/06/25 19:06:25 by yuuko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_H
# define LIB_H

# include "MLX42/MLX42.h"
# include "common/types.h"
# include <stdint.h>

# define LIB lib_get

mlx_t		*lib_get(void);
void		lib_panic(void) __attribute__((noreturn));
mlx_image_t	*lib_image_new(uint32_t width, uint32_t height);
int32_t		lib_image_display(mlx_image_t *img, int32_t x, int32_t y);
void		lib_image_resize(mlx_image_t *img, uint32_t new_width,
				uint32_t new_height);
void		lib_on_loop(t_handle_func handle, void *param);

#endif
