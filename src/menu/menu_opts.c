/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_opts.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 15:16:46 by tforster          #+#    #+#             */
/*   Updated: 2024/08/06 12:54:17 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "game/game.h"

void	minimap_opts(const mlx_key_data_t data, t_player *plr)
{
	if (data.key == MLX_KEY_X && data.action == MLX_PRESS)
		if (map_ctx().img->enabled)
			plr->to_draw.xy_axis = (plr->to_draw.xy_axis == false);
	if (data.key == MLX_KEY_C && data.action == MLX_PRESS)
	{
		plr->shape->enabled = (plr->shape->enabled == false);
		map_ctx().img->enabled = plr->shape->enabled;
	}
	if (data.key == MLX_KEY_V && data.action == MLX_PRESS)
		if (map_ctx().img->enabled)
			plr->to_draw.rays = (plr->to_draw.rays == false);
}
