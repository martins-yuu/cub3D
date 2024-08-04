/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 14:53:01 by yuuko             #+#    #+#             */
/*   Updated: 2024/08/04 16:16:20 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>	// DELETE THIS
#include <stddef.h>	// DELETE THIS
#include <stdalign.h> 	// DELETE THIS

#include <stdint.h>
#include <stdlib.h>
// #include <math.h>

// #include "MLX42/MLX42.h"
#include "MLX42/MLX42.h"
#include "ctx/ctx.h"
#include "graph_lib/graph_types.h"
#include "menu/menu.h"
#include "game/game.h"
// #include "graph_lib/graph_func.h"

static void img_test();

int	main(int argc, char **argv)
{
	t_map		mini_map;
	t_player	player;
	t_menu		menu;

	ctx();

	img_test();

	map_ctx();

	init_map(&mini_map);
	init_player(&player, &mini_map);

	draw_menu(&menu, &mini_map, &player);

	mlx_resize_hook(ctx(), menu_position, &menu);
	ctx_on_loop(movement, &player);
	ctx_on_key(menu_keys, &menu);

	mlx_loop(ctx());
	mlx_terminate(ctx());
	return (EXIT_SUCCESS);
}

static void img_test()
{
	mlx_texture_t	*texture;
	texture = mlx_load_png("texture/eagle.png");
	printf("WIDTH[%d] HEIGHT[%d] BYTES PER PIXEL[%d] SIZE [%zu]\n\n",
		texture->width, texture->height, texture->bytes_per_pixel, sizeof(texture->pixels));

	mlx_image_t		*eagle;
	eagle = mlx_texture_to_image(ctx(), texture);
	printf("WIDTH[%d] HEIGHT[%d] SIZE[%zu]\n\n",
		eagle->width, eagle->height,  sizeof(eagle->pixels));


	mlx_image_t		*copy;
	copy = mlx_new_image(ctx(), 64, 64);
	int i = 0;
	// while (i < 4 * 64 * 64)
	// {
	// 	copy->pixels[i] = eagle->pixels[i];
	// 	i++;
	// }

	copy->pixels = texture->pixels;
	// i = 12*64;
	// while (i < 13*64)
	// {
	// 	printf("[%d][%d][%d][%d][%d]\n", i, texture->pixels[4*i], texture->pixels[4*i + 1], texture->pixels[4*i + 2], texture->pixels[4*i + 3]);
	// 	printf("[%d][%d][%d][%d][%d]\n", i, eagle->pixels[4*i], eagle->pixels[4*i + 1], eagle->pixels[4*i + 2], eagle->pixels[4*i + 3]);
	// 	printf("\n");
	// 	i++;
	// };

	mlx_resize_image(eagle, 248, 248);
	mlx_image_to_window(ctx(), eagle, 100, 100);
	mlx_image_to_window(ctx(), copy, 400, 400);

}
