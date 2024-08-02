/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 19:18:24 by tforster          #+#    #+#             */
/*   Updated: 2024/08/01 21:19:05 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "ctx/ctx.h"
#include "graph_lib/graph_func.h"
#include "game/game.h"

#include <stdio.h>	// DELETE THIS

static void	yaw(t_player *plr, t_mov direction);
static void	strafe(t_player *plr, t_mov direction);
static void	normal(t_player *plr, t_mov direction);

static void	resize(int32_t width, int32_t height, void* param)
{
	mlx_t *instance = ctx();
	instance->width = 512;
	instance->height = 320;
}


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

	plr->dgr = fix_angle(plr->dgr - (direction) * ANG);
	rad = deg_rad(plr->dgr);
	plr->disp.x = cosf(rad);
	plr->disp.y = -sinf(rad);
}

void	strafe(t_player *plr, t_mov direction)
{
	plr->p0.x -= (direction) * (STRF_STEP * plr->disp.y);
	plr->p0.y -= -(direction) * (STRF_STEP * plr->disp.x);
}

static void	normal(t_player *plr, t_mov direction)
{
	plr->p0.x += (direction) * (STEP * plr->disp.x);
	plr->p0.y += (direction) * (STEP * plr->disp.y);
}
