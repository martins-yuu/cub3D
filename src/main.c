/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 14:53:01 by yuuko             #+#    #+#             */
/*   Updated: 2024/07/26 17:40:51 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>	// DELETE THIS
#include <stddef.h>	// DELETE THIS
#include <stdalign.h> 	// DELETE THIS

#include <stdint.h>
#include <stdlib.h>
// #include <math.h>

// #include "MLX42/MLX42.h"
#include "ctx/ctx.h"
#include "graph_lib/graph_types.h"
#include "menu/menu.h"
#include "game/game.h"
// #include "graph_lib/graph_func.h"

int	main(int argc, char **argv)
{
	t_map		mini_map;
	t_player	player;
	t_menu		menu;


	ctx();
	map_ctx();
	// printf(">>>>>>>> START WIDHT[%d] HEIGHT[%d]\n", instance->width, instance->height);
	// printf(">>>>>>>> NB RAYS [%d][%d]\n", instance->width / 4, instance->width % 4);


	init_map(&mini_map);
	init_player(&player, &mini_map);

	draw_menu(&menu, &mini_map, &player);
	ctx_on_loop(movement, &player);
	ctx_on_key(menu_keys, &menu);

	// printf("MINI_MAP[%d] MAP[%d] VIEW[%d] MENE[%d]\n",
	// 	mini_map.img->instances->z, player.map->instances->z, player.view->instances->z, menu.menu_img->instances->z);

	mlx_loop(ctx());
	mlx_terminate(ctx());
	return (EXIT_SUCCESS);
}
