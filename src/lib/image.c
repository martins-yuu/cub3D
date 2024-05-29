/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuuko <yuuko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 21:44:09 by yuuko             #+#    #+#             */
/*   Updated: 2024/06/11 22:29:43 by yuuko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "lib.h"
#include <stdint.h>

mlx_image_t	*lib_image_new(uint32_t width, uint32_t height)
{
	mlx_image_t	*img;

	img = mlx_new_image(lib_get(), width, height);
	if (!img)
		lib_panic();
	return (img);
}

int32_t	lib_image_display(mlx_image_t *img, int32_t x, int32_t y)
{
	int32_t	index;

	index = mlx_image_to_window(lib_get(), img, x, y);
	if (index == -1)
		lib_panic();
	return (index);
}

void	lib_image_resize(mlx_image_t *img, uint32_t new_width,
		uint32_t new_height)
{
	if (!mlx_resize_image(img, new_width, new_height))
		lib_panic();
}
