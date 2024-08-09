/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 14:53:01 by yuuko             #+#    #+#             */
/*   Updated: 2024/08/08 16:40:32 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>	// DELETE THIS
#include <stdlib.h>
#include "ctx/ctx.h"
#include "menu/menu.h"
#include "game/game.h"

static mlx_texture_t	*load_texture(void);

int	main(int argc, char **argv)
{
	t_texture	texture;
	t_player	player;
	t_menu		menu;

	argc = 0;
	argv = NULL;
	ctx();
	texture.north = load_texture();
	// INDEX[768]R[31]G[31]B[31]ALPHA[255]
	// int i = 768;
	// printf("INDEX[%d]R[%d]G[%d]B[%d]ALPHA[%d]\n", i, texture.north->pixels[4*i], texture.north->pixels[4*i + 1], texture.north->pixels[4*i + 2], texture.north->pixels[4*i + 3]);
	// INDEX[780]R[223]G[223]B[223]ALPHA[255]
	// int i = 0;
	// while (i < 64)
	// {
	// 	// printf("INDEX[%d]R[%d]G[%d]B[%d]ALPHA[%d]\n", i,
	// 	// 	texture.north->pixels[64*i],
	// 	// 	texture.north->pixels[64*i + 1],
	// 	// 	texture.north->pixels[64*i + 2],
	// 	// 	texture.north->pixels[64*i + 3]);

	// 	printf("INDEX[%d]R[%d]G[%d]B[%d]ALPHA[%d]\n", i,
	// 		texture.north->pixels[0 + 4*i],
	// 		texture.north->pixels[1 + 4*i],
	// 		texture.north->pixels[2 + 4*i],
	// 		texture.north->pixels[3 + 4*i]);
	// 	i++;
	// }

	map_ctx();
	init_map();
	init_player(&player);

	player.texture = &texture;

	draw_menu(&menu, &player);
	mlx_resize_hook(ctx(), menu_position, &menu);
	ctx_on_loop(movement, &player);
	ctx_on_key(menu_keys, &menu);
	mlx_loop(ctx());
	mlx_terminate(ctx());
	return (EXIT_SUCCESS);
}

static mlx_texture_t	*load_texture(void)
{
	mlx_texture_t	*texture;

	texture = mlx_load_png("texture/greystone.png");
	printf("WIDTH[%d] HEIGHT[%d] BYTES PER PIXEL[%d] SIZE [%d]\n\n",
		texture->width, texture->height, texture->bytes_per_pixel,
		texture->width * texture->height * texture->bytes_per_pixel);

	// mlx_image_t		*eagle;
	// eagle = mlx_texture_to_image(ctx(), texture);
	// printf("WIDTH[%d] HEIGHT[%d] SIZE[%zu]\n\n",
	// 	eagle->width, eagle->height,  sizeof(eagle->pixels));

	mlx_image_t		*copy;
	copy = mlx_new_image(ctx(), 64, 64);
	copy->pixels = texture->pixels;
	int i = 0;
	// while (i < 4 * 64 * 64)
	// {
	// 	copy->pixels[i] = eagle->pixels[i];
	// 	i++;
	// }

	// i = 12*64;
	// while (i < 13*64)
	// {
	// 	printf("INDEX[%d]R[%d]G[%d]B[%d]ALPHA[%d]\n", i, texture->pixels[4*i], texture->pixels[4*i + 1], texture->pixels[4*i + 2], texture->pixels[4*i + 3]);
	// 	// printf("[%d][%d][%d][%d][%d]\n", i, eagle->pixels[4*i], eagle->pixels[4*i + 1], eagle->pixels[4*i + 2], eagle->pixels[4*i + 3]);
	// 	i++;
	// };
	// printf("\n");

	// mlx_resize_image(eagle, 248, 248);
	// mlx_image_to_window(ctx(), eagle, 100, 100);
	mlx_image_to_window(ctx(), copy, 400, 400);
	return (texture);
}
