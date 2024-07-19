/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 14:53:01 by yuuko             #+#    #+#             */
/*   Updated: 2024/07/19 17:43:42 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>	// DELETE THIS
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

#include "MLX42/MLX42.h"
#include "ctx/ctx.h"
#include "game/game.h"
#include "graph_lib/graph_func.h"

void	basic_keys(mlx_key_data_t data, void *param)
{
	mlx_image_t	*img;

	img = param;
	if (data.key == MLX_KEY_ESCAPE && data.action == MLX_PRESS)
		mlx_close_window(ctx());
}

void	movement(void *param)
{
	t_player	*player;

	player = param;
	//  LEFT
	if (mlx_is_key_down(ctx(), MLX_KEY_A))
	{
		player->theta_dg += ANG;
		player->theta_dg = fix_angle(player->theta_dg);
		player->del.x = cosf(deg_rad (player->theta_dg));
		player->del.y = -sinf(deg_rad (player->theta_dg));
	}
	// RIGHT
	if (mlx_is_key_down(ctx(), MLX_KEY_D))
	{
		player->theta_dg -= ANG;
		player->theta_dg = fix_angle(player->theta_dg);
		player->del.x = cosf(deg_rad (player->theta_dg));
		player->del.y = -sinf(deg_rad (player->theta_dg));
	}
	// UP
	if (mlx_is_key_down(ctx(), MLX_KEY_W))
	{
		// printf("W THETA_dg %d dy[%f] dx[%f] \n", player->theta_dg, player->dy, player->dx);
		// player->img->instances[0].x += (int) (5.0 * player->del.x);
		// player->img->instances[0].y += (int) (5.0 * player->del.y);
		player->p0.x += (STEP * player->del.x);
		player->p0.y += (STEP * player->del.y);

	}
	// DOWN
	if (mlx_is_key_down(ctx(), MLX_KEY_S))
	{
		// printf("S THETA_dg %d dy[%f] dx[%f] \n", player->theta_dg, player->dy, player->dx);
		// player->img->instances[0].x -= (int) (5.0 * player->del.x);
		// player->img->instances[0].y -= (int) (5.0 * player->del.y);
		player->p0.x -= (STEP * player->del.x);
		player->p0.y -= (STEP * player->del.y);

	}
	// float dist = powf(STEP * player->del.x, 2) + pow(STEP * player->del.y, 2);
	// dist = sqrtf(dist);
	// printf("DIST [%f][%d] X[%d][%f] Y[%d][%f]\n",
	// 	dist, player->theta_dg, player->p0.x, player->del.x, player->p0.y, player->del.y);
	draw_player(player);
}

int	main(int argc __attribute__((unused)), char *argv[] __attribute__((unused)))
{
	t_map		mini_map;
	t_player	player;

	ctx();
	init_map(&mini_map, 512, 512);

	init_player(&mini_map, &player, 512, 512);
	// draw_player(&player);

	ctx_on_key(basic_keys, NULL);
	ctx_on_loop(movement, &player);

	mlx_loop(ctx());
	mlx_terminate(ctx());
	return (EXIT_SUCCESS);
}
