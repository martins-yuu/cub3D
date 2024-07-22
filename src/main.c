/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 14:53:01 by yuuko             #+#    #+#             */
/*   Updated: 2024/07/21 21:59:30 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>	// DELETE THIS
#include <stdint.h>
#include <stdlib.h>
// #include <math.h>

#include "MLX42/MLX42.h"
#include "ctx/ctx.h"
#include "menu/menu.h"
#include "game/game.h"
// #include "graph_lib/graph_func.h"

int	main(int argc, char **argv)
{
	t_map		mini_map;
	t_player	player;
	t_menu		menu;

	ctx();
	init_map(&mini_map, 512, 512);

	init_player(&mini_map, &player, 512, 512);

	ctx_on_loop(movement, &player);
	draw_menu(&menu, &player);
	ctx_on_key(menu_keys, &menu);

	mlx_loop(ctx());
	mlx_terminate(ctx());
	return (EXIT_SUCCESS);
}
