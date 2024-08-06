/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:35:03 by tforster          #+#    #+#             */
/*   Updated: 2024/07/21 15:45:09 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdbool.h>
#include "ctx/ctx.h"
#include "ctx/constants.h"
#include "graph_lib/graph_func.h"
#include "game/game.h"

#include "graph_lib/graph_types.h"

#include <stdio.h>	// DELETE THIS

static void	player_coordinates(t_player *plr);
static void	to_draw_elements(t_player *plr);

void	init_player(t_player *plr)
{
	player_coordinates(plr);
	plr->shape = ctx_img_new(MINI_MAP_S, MINI_MAP_S);
	ctx_img_display(plr->shape, 0, 0);
	plr->shape->instances->z = Z_MINI_PLAYER;
	to_draw_elements(plr);
	plr->view = ctx_img_new(MAX_WIDTH, MAX_HEIGHT);
	ctx_img_display(plr->view, 0, 0);
	plr->view->instances->z = Z_VIEW;
	plr->pixel = 1;
	plr->fov = 60.0;
}

static void	player_coordinates(t_player *plr)
{
	plr->p0 = (t_vec2){map_ctx().grid_p0.x + 0.5, map_ctx().grid_p0.y + 0.5, 1};
	plr->dgr = map_ctx().orientation;
	plr->disp.x = cosf(deg_rad(plr->dgr));
	plr->disp.y = -sinf(deg_rad(plr->dgr));
}

void	player_shape(t_vec2 *geometry)
{
	geometry[0] = (t_vec2){0.0, 3.0, 1.0};
	geometry[1] = (t_vec2){2.0, 2.0, 1.0};
	geometry[2] = (t_vec2){3.0, 1.0, 1.0};
	geometry[3] = (t_vec2){3.0, -2.0, 1.0};
	geometry[4] = (t_vec2){2.0, -8.0, 1.0};
	geometry[5] = (t_vec2){0.0, -20.0, 1.0};
	geometry[6] = (t_vec2){-2.0, -8.0, 1.0};
	geometry[7] = (t_vec2){-3.0, -2.0, 1.0};
	geometry[8] = (t_vec2){-3.0, 1.0, 1.0};
	geometry[9] = (t_vec2){-2.0, 2.0, 1.0};
}

static void	to_draw_elements(t_player *plr)
{
	plr->to_draw.rays = false;
	plr->to_draw.xy_axis = false;
	plr->shape->enabled = false;
}
