/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 14:53:01 by yuuko             #+#    #+#             */
/*   Updated: 2024/07/18 17:58:31 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "color/color.h"
#include "ctx/constants.h"
#include "ctx/ctx.h"
#include "player/player.h"
#include "graph_lib/graph_func.h"
#include <stdint.h>
#include <stdlib.h>

// LEGAL?
#include <stdio.h>
// LEGAL?

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

	t_fvec2 p0 = {1.0, 1.0, 1.0};
	t_fvec2 p1 = {2.0, 1.0, 1.0};
	t_fvec2 p2 = {2.0, 2.0, 1.0};
	t_fvec2 p3 = {1.0, 2.0, 1.0};
	t_fvec2 disp = {2.0, 1.0, 1.0};

	t_fvec2 points[4] = {p0, p1, p2, p3};
	t_fvec2	new[4];

	t_mt2	mat = mt2_rot_on_point(&disp, 45);
	printf("[%.2f][%.2f][%.2f]\n", sqrt(2.0)/2.0, -sqrt(2.0)/2.0, 2.0 - sqrt(2.0) / 2.0);
	printf("[%.2f][%.2f][%.2f]\n\n", mat.i00, mat.i01, mat.i02);

	printf("[%.2f][%.2f][%.2f]\n", sqrt(2.0)/2.0, sqrt(2.0)/2.0, -3.0 * sqrt(2.0) / 2.0 + 1.0);
	printf("[%.2f][%.2f][%.2f]\n\n", mat.i10, mat.i11, mat.i12);

	printf("[%.2f][%.2f][%.2f]\n", 0.0, 0.0, 1.0);
	printf("[%.2f][%.2f][%.2f]\n\n", mat.i20, mat.i21, mat.i22);

	// printf("[%.2f][%.2f][%.2f]\n\n", mat.i20, mat.i21, mat.i22);

	int i = 0;
	while (i < 4)
	{
		new[i] = mult_fvec2_mt2(&points[i], &mat);
		printf("[%.2f][%.2f][%.2f]\n", new[i].x, new[i].y, new[i].w);
		i++;
	}

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
