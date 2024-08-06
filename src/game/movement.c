/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 19:18:24 by tforster          #+#    #+#             */
/*   Updated: 2024/08/06 13:04:02 by tforster         ###   ########.fr       */
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

static void		yaw(t_player *plr, const t_mov direction);
static void		strafe(t_player *plr, const t_mov direction);
static void		normal(t_player *plr, const t_mov direction);
static bool		v_coll(const t_ivec2 grid_p, const t_ivec2 del);
static bool		h_coll(const t_ivec2 grid_p, const t_ivec2 del);
static t_vec2	get_wall_offset(const t_vec2 disp);

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

void	yaw(t_player *plr, const t_mov direction)
{
	float	rad;

	plr->dgr = fix_angle(plr->dgr - (direction) * 125 * ctx()->delta_time);
	rad = deg_rad(plr->dgr);
	plr->disp.x = cosf(rad);
	plr->disp.y = -sinf(rad);
}

void	strafe(t_player *plr, const t_mov drctn)
{
	const t_ivec2	grid_pos = (t_ivec2){(int) plr->p0.x, (int) plr->p0.y};
	const t_vec2	wall_offset = get_wall_offset(plr->disp);
	const t_ivec2	delta = (t_ivec2)
	{
		plr->p0.x - (drctn) * wall_offset.y,
		plr->p0.y + (drctn) * wall_offset.x
	};

	if (v_coll(grid_pos, delta))
		plr->p0.x -= (drctn) * (1.5625 * ctx()->delta_time * plr->disp.y);
	if (h_coll(grid_pos, delta))
		plr->p0.y -= -(drctn) * (1.5625 * ctx()->delta_time * plr->disp.x);
}

static void	normal(t_player *plr, const t_mov drctn)
{
	const t_ivec2	grid_pos = (t_ivec2){(int) plr->p0.x, (int) plr->p0.y};
	const t_vec2	wall_offset = get_wall_offset(plr->disp);
	const t_ivec2	delta = (t_ivec2)
	{
		plr->p0.x + (drctn) * wall_offset.x,
		plr->p0.y + (drctn) * wall_offset.y
	};

	if (v_coll(grid_pos, delta))
		plr->p0.x += (drctn) * (3.125 * ctx()->delta_time * plr->disp.x);
	if (h_coll(grid_pos, delta))
		plr->p0.y += (drctn) * (3.125 * ctx()->delta_time * plr->disp.y);
}

static t_vec2	get_wall_offset(const t_vec2 disp)
{
	return ((t_vec2)
		{
			(disp.x <= 0) * (-WALL_OFFSET) + (disp.x > 0) * WALL_OFFSET,
			(disp.y <= 0) * (-WALL_OFFSET) + (disp.y > 0) * WALL_OFFSET,
			1,
		}
	);
}

static bool	v_coll(const t_ivec2 grid_p, const t_ivec2 del)
{
	const int		*grid = map_ctx().grid;
	const t_ivec2	dim = map_ctx().grid_dim;

	return (grid[grid_p.y * dim.x + del.x] == 0);
}

static bool	h_coll(const t_ivec2 grid_p, const t_ivec2 del)
{
	const int		*grid = map_ctx().grid;
	const t_ivec2	dim = map_ctx().grid_dim;

	return (grid[del.y * dim.x + grid_p.x] == 0);
}
