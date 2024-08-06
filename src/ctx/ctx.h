/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctx.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 20:51:18 by yuuko             #+#    #+#             */
/*   Updated: 2024/08/06 17:09:58 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CTX_H
# define CTX_H

# include "MLX42/MLX42.h"
# include "ctx/types.h"
# include <stdint.h>

mlx_t		*ctx(void);
void		ctx_panic(void) __attribute__((noreturn));
mlx_image_t	*ctx_img_new(uint32_t width, uint32_t height);
int32_t		ctx_img_display(mlx_image_t *img, int32_t x, int32_t y);
void		ctx_img_rsz(mlx_image_t *img, uint32_t n_width, uint32_t n_height);
void		ctx_on_loop(t_handle_func handle, void *param);
void		ctx_on_key(t_key_func key, void *param);

#endif
