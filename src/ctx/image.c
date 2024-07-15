/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 21:44:09 by yuuko             #+#    #+#             */
/*   Updated: 2024/07/15 15:32:16 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "ctx/ctx.h"
#include <stdint.h>

mlx_image_t	*ctx_img_new(uint32_t width, uint32_t height)
{
	mlx_image_t	*img;

	img = mlx_new_image(ctx(), width, height);
	if (!img)
		ctx_panic();
	return (img);
}

int32_t	ctx_img_display(mlx_image_t *img, int32_t x, int32_t y)
{
	int32_t	index;

	index = mlx_image_to_window(ctx(), img, x, y);
	if (index == -1)
		ctx_panic();
	return (index);
}

void	ctx_img_rsz(mlx_image_t *img, uint32_t n_width, uint32_t n_height)
{
	if (!mlx_resize_image(img, n_width, n_height))
		ctx_panic();
}
