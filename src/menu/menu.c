/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 17:05:06 by tforster          #+#    #+#             */
/*   Updated: 2024/07/22 20:44:38 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "color/color.h"
#include "ft_string.h"
#include "ctx/ctx.h"
#include "menu/menu.h"
#include "game/game.h"
#include <stdbool.h>

void	draw_menu(t_menu *menu, t_map *map, t_player *plr)
{
	mlx_image_t	*text_img[5];
	int width = 400;
	int height = 100;

	menu->mini_map = map;
	menu->player = plr;
	menu->menu_img = ctx_img_new(width, height);
	ctx_img_display(menu->menu_img, 70, 100);
	menu->menu_img->instances->z = 3;
	ft_memset(menu->menu_img->pixels, 0x64, width * height * 4);
	text_img[0] = mlx_put_string(ctx(), "PRESS <M> FOR MENU", 75, 100);
	text_img[1] = mlx_put_string(ctx(), "PRESS <C> TO SHOW MINI MAP", 75, 120);
	text_img[2] = mlx_put_string(ctx(), "PRESS <X> TO SHOW XY AXIS ON  MINI MAP", 75, 140);
	text_img[3] = mlx_put_string(ctx(), "PRESS <V> TO SHOW RAYS ON  MINI MAP", 75, 160);
	text_img[4] = mlx_put_string(ctx(), "PRESS <ESC> TO QUIT", 75, 180);
}

void	menu_keys(mlx_key_data_t data, void *param)
{
	t_menu		*menu;
	t_player	*plr;
	mlx_image_t	*mini_map;

	menu = param;
	plr = menu->player;
	mini_map = menu->mini_map->img;
	// t_player *plr = param;
	if (data.key == MLX_KEY_ESCAPE && data.action == MLX_PRESS)
		mlx_close_window(ctx());
	if (data.key == MLX_KEY_X && data.action == MLX_PRESS)
		plr->to_draw.xy_axis = (plr->to_draw.xy_axis == false);
	if (data.key == MLX_KEY_C && data.action == MLX_PRESS)
	{
		plr->map->instances->enabled = (plr->map->instances->enabled == false);
		mini_map->instances->enabled = plr->map->instances->enabled;
	}
	if (data.key == MLX_KEY_V && data.action == MLX_PRESS)
		plr->to_draw.rays = (plr->to_draw.rays == false);

}
