/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuuko <yuuko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 20:51:18 by yuuko             #+#    #+#             */
/*   Updated: 2024/07/16 00:4 by yuuko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_H
# define WINDOW_H

# include "MLX42/MLX42.h"
# include "window/types.h"
# include <stdint.h>

void		window_init(int32_t width, int32_t height, const char *title,
				bool resize);
void		window_panic(void) __attribute__((noreturn));
mlx_image_t	*ctx_image_new(uint32_t width, uint32_t height);
int32_t		ctx_image_display(mlx_image_t *img, int32_t x, int32_t y);
void		ctx_image_resize(mlx_image_t *img, uint32_t new_width,
				uint32_t new_height);
void		ctx_on_loop(t_handle_func handle, void *param);

#endif
