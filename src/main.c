/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 14:53:01 by yuuko             #+#    #+#             */
/*   Updated: 2024/07/16 20:11:38 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "color/color.h"
#include "ctx/constants.h"
#include "ctx/ctx.h"
#include "player/player.h"
#include "vector/angle.h"
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
		player->theta += ANG;
		player->del.x = cosf(deg_rad (player->theta));
		player->del.y = -sinf(deg_rad (player->theta));
	}
	// RIGHT
	if (mlx_is_key_down(ctx(), MLX_KEY_D))
	{
		player->theta -= ANG;
		player->del.x = cosf(deg_rad (player->theta));
		player->del.y = -sinf(deg_rad (player->theta));
	}
	// UP
	if (mlx_is_key_down(ctx(), MLX_KEY_W))
	{
		// printf("W THETA %d dy[%f] dx[%f] \n", player->theta, player->dy, player->dx);
		// player->img->instances[0].x += (int) (5.0 * player->del.x);
		// player->img->instances[0].y += (int) (5.0 * player->del.y);
		player->p0.x += (int) (STEP * player->del.x);
		player->p0.y += (int) (STEP * player->del.y);

	}
	// DOWN
	if (mlx_is_key_down(ctx(), MLX_KEY_S))
	{
		// printf("S THETA %d dy[%f] dx[%f] \n", player->theta, player->dy, player->dx);
		// player->img->instances[0].x -= (int) (5.0 * player->del.x);
		// player->img->instances[0].y -= (int) (5.0 * player->del.y);
		player->p0.x -= (int) (STEP * player->del.x);
		player->p0.y -= (int) (STEP * player->del.y);

	}
	// float dist = powf(STEP * player->del.x, 2) + pow(STEP * player->del.y, 2);
	// dist = sqrtf(dist);
	// printf("DIST [%f][%d] X[%d][%f] Y[%d][%f]\n",
	// 	dist, player->theta, player->p0.x, player->del.x, player->p0.y, player->del.y);
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
