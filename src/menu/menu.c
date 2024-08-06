/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 17:05:06 by tforster          #+#    #+#             */
/*   Updated: 2024/08/06 12:54:04 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdint.h>
// #include <stdint.h>
#include <stdint.h>
#include <stdio.h>
// #include "MLX42/MLX42.h"
// #include "color/color.h"
#include <stdbool.h>
// #include "MLX42/MLX42.h"
#include "ft_string.h"
#include "ctx/ctx.h"
#include "ctx/constants.h"
#include "menu/menu.h"
// #include "game/game.h"
// #include "graph_lib/graph_types.h"

static void	assign_text(mlx_image_t *opts[MENU_OPTS]);

void	draw_menu(t_menu *menu, t_player *plr)
{
	menu->player = plr;
	menu->menu_img = ctx_img_new(MENU_WIDTH, MENU_HEIGHT);
	menu->menu_img->enabled = false;
	ctx_img_display(menu->menu_img, 0, 0);
	menu->menu_img->instances->z = Z_MENU;
	ft_memset(menu->menu_img->pixels, A050, MENU_WIDTH * MENU_HEIGHT * 4);
	assign_text(menu->opts);
	menu_position(ctx()->width, ctx()->height, menu);
}

static void	assign_text(mlx_image_t *opts[MENU_OPTS])
{
	int			i;
	const char	*str[MENU_OPTS] = {
		PRESS_M, PRESS_C, PRESS_X, PRESS_V, PRESS_ESC};

	i = 0;
	while (i < MENU_OPTS)
	{
		opts[i] = mlx_put_string(ctx(), str[i], 0, 0);
		opts[i]->enabled = false;
		i++;
	}
}

void	menu_position(const int width, const int height, void *param)
{
	int				i;
	const t_menu	*menu = param;
	const t_ivec2	pos = (t_ivec2)
	{
		(width - MENU_WIDTH) / 2,
		(height - MENU_HEIGHT) / 2
	};

	menu->menu_img->instances->x = pos.x;
	menu->menu_img->instances->y = pos.y;
	i = 0;
	while (i < MENU_OPTS)
	{
		menu->opts[i]->instances->x = pos.x;
		menu->opts[i]->instances->y = pos.y + i * 20;
		i++;
	}
}

void	menu_keys(const mlx_key_data_t data, void *param)
{
	int				i;
	const t_menu	*menu = param;

	if (data.key == MLX_KEY_ESCAPE && data.action == MLX_PRESS)
		mlx_close_window(ctx());
	if (data.key == MLX_KEY_M && data.action == MLX_PRESS)
	{
		menu->menu_img->enabled = (menu->menu_img->enabled == false);
		i = 0;
		while (i < MENU_OPTS)
			menu->opts[i++]->enabled = menu->menu_img->enabled;
	}
	minimap_opts(data, menu->player);
}
