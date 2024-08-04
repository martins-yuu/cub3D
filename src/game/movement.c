/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 19:18:24 by tforster          #+#    #+#             */
/*   Updated: 2024/08/04 20:45:32 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include <stdlib.h>

#include "ctx/ctx.h"
#include "graph_lib/graph_func.h"
#include "game/game.h"
#include "graph_lib/graph_types.h"

#include <stdint.h>
#include <stdio.h>	// DELETE THIS

static void	yaw(t_player *plr, t_mov direction);
static void	strafe(t_player *plr, t_mov direction);
static void	normal(t_player *plr, t_mov direction);

// static void	resize(int32_t width, int32_t height, void* param)
// {
// 	mlx_t *instance = ctx();
// 	instance->width = 512;
// 	instance->height = 320;
// }

void	movement(void *param)
{
	t_player	*plr;

	plr = param;
	if (mlx_is_key_down(ctx(), MLX_KEY_Q))
		yaw(plr, LEFT);
	if (mlx_is_key_down(ctx(), MLX_KEY_E))
		yaw(plr, RIGHT);
	if (mlx_is_key_down(ctx(), MLX_KEY_A))
		strafe(plr, LEFT);
	if (mlx_is_key_down(ctx(), MLX_KEY_D))
		strafe(plr, RIGHT);
	if (mlx_is_key_down(ctx(), MLX_KEY_W))
		normal(plr, UP);
	if (mlx_is_key_down(ctx(), MLX_KEY_S))
		normal(plr, DOWN);
	draw_player(plr);
}

void	yaw(t_player *plr, t_mov direction)
{
	float	rad;

	plr->dgr = fix_angle(plr->dgr - (direction) * 125 * ctx()->delta_time);
	rad = deg_rad(plr->dgr);
	plr->disp.x = cosf(rad);
	plr->disp.y = -sinf(rad);
}

void	strafe(t_player *plr, t_mov direction)
{
	const t_ivec2	grid_pos = (t_ivec2){(int) plr->p0.x, (int) plr->p0.y};
	const t_vec2	offset = (t_vec2)
	{
		(plr->disp.x < 0) * (-0.2) + (plr->disp.x > 0) * 0.2,
		(plr->disp.y < 0) * (-0.2) + (plr->disp.y > 0) * 0.2,
	};
	const t_ivec2	delta = (t_ivec2)
	{
		plr->p0.x - (direction) * offset.y,
		plr->p0.y + (direction) * offset.x
	};

	if (plr->grid[grid_pos.y * plr->dof.x + delta.x] == 0 && plr->grid[delta.y * plr->dof.x + grid_pos.x] == 0)
	{
		plr->p0.x -= (direction) * (1.5625 * ctx()->delta_time * plr->disp.y);
		plr->p0.y -= -(direction) * (1.5625 * ctx()->delta_time * plr->disp.x);
	}
}

static void	normal(t_player *plr, t_mov direction)
{
	const t_ivec2	grid_pos = (t_ivec2){(int) plr->p0.x, (int) plr->p0.y};
	const t_vec2	offset = (t_vec2){
		(plr->disp.x <= 0) * (-0.2) + (plr->disp.x > 0) * 0.2,
		(plr->disp.y <= 0) * (-0.2) + (plr->disp.y > 0) * 0.2,
	};
	const t_ivec2	delta = (t_ivec2)
	{
		plr->p0.x + (direction) * offset.x,
		plr->p0.y + (direction) * offset.y
	};

	if (plr->grid[grid_pos.y * plr->dof.x + delta.x] == 0)
		plr->p0.x += (direction) * (3.125 * ctx()->delta_time * plr->disp.x);
	if (plr->grid[delta.y * plr->dof.x + grid_pos.x] == 0)
		plr->p0.y += (direction) * (3.125 * ctx()->delta_time * plr->disp.y);
}
