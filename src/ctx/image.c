/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuuko <yuuko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 21:44:09 by yuuko             #+#    #+#             */
/*   Updated: 2024/07/06 13:44:35 by yuuko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "ctx/ctx.h"
#include <stdint.h>

mlx_image_t	*ctx_image_new(uint32_t width, uint32_t height)
{
	mlx_image_t	*img;

	img = mlx_new_image(ctx(), width, height);
	if (!img)
		ctx_panic();
	return (img);
}

int32_t	ctx_image_display(mlx_image_t *img, int32_t x, int32_t y)
{
	int32_t	index;

	index = mlx_image_to_window(ctx(), img, x, y);
	if (index == -1)
		ctx_panic();
	return (index);
}

void	ctx_image_resize(mlx_image_t *img, uint32_t new_width,
		uint32_t new_height)
{
	if (!mlx_resize_image(img, new_width, new_height))
		ctx_panic();
}
