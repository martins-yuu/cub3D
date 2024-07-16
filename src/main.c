/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuuko <yuuko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 14:53:01 by yuuko             #+#    #+#             */
/*   Updated: 2024/07/16 01:04:43 by yuuko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "common/constants.h"
#include "window/window.h"
#include <stdint.h>
#include <stdlib.h>

// static void	draw_background(void *param)
// {
// 	uint32_t	i;
// 	uint32_t	size;
// 	t_color		a;
// 	t_color		c;
// 	mlx_image_t	*bg;

// 	bg = param;
// 	ctx_image_resize(bg, window_init()->width, window_init()->height);
// 	i = 0;
// 	size = bg->width * bg->height;
// 	while (i < size)
// 	{
// 		a = color_opacity(color_grayscale(color_random()), .2);
// 		c = color_lerp(a, color(0x000000FF), (double)i / size);
// 		mlx_put_pixel(bg, i % bg->width, i / bg->width, c.value);
// 		i++;
// 	}
// }

// static void	draw_movable(void *param)
// {
// 	uint32_t	i;
// 	uint32_t	size;
// 	t_color		c;
// 	mlx_image_t	*img;

// 	img = param;
// 	i = 0;
// 	size = img->width * img->height;
// 	while (i < size)
// 	{
// 		c = color_lerp(color(0x000000FF), color(0xFF00FFFF), (double)i / size);
// 		mlx_put_pixel(img, i % img->width, i / img->width, c.value);
// 		i++;
// 	}
// }

// void	handle_movement(void *param)
// {
// 	mlx_image_t	*img;

// 	img = param;
// 	if (mlx_is_key_down(window_init(), MLX_KEY_ESCAPE))
// 		mlx_close_window(window_init());
// 	if (mlx_is_key_down(window_init(), MLX_KEY_K))
// 		img->instances[0].y -= 10;
// 	if (mlx_is_key_down(window_init(), MLX_KEY_J))
// 		img->instances[0].y += 10;
// 	if (mlx_is_key_down(window_init(), MLX_KEY_H))
// 		img->instances[0].x -= 10;
// 	if (mlx_is_key_down(window_init(), MLX_KEY_L))
// 		img->instances[0].x += 10;
// }

int	main(int argc __attribute__((unused)), char *argv[] __attribute__((unused)))
{
	// mlx_image_t	*bg;
	// mlx_image_t	*ent;

	window_init(WIDTH, HEIGHT, TITLE, true);
	// bg = ctx_image_new(WIDTH, HEIGHT);
	// ent = ctx_image_new(32, 32);
	// ctx_image_display(bg, 0, 0);
	// ctx_image_display(ent, 0, 0);
	// ctx_on_loop(draw_background, bg);
	// ctx_on_loop(draw_movable, ent);
	// ctx_on_loop(handle_movement, ent);
	// mlx_loop(window_init());
	// mlx_terminate(window_init());
	return (EXIT_SUCCESS);
}
