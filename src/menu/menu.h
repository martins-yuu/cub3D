/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 17:07:27 by tforster          #+#    #+#             */
/*   Updated: 2024/07/21 22:12:27 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MENU_H
# define MENU_H

#include "game/game.h"

typedef struct s_menu
{
	t_map		*map;
	t_player	*player;
	mlx_image_t	*menu_img;
}				t_menu;

void	draw_menu(t_menu *menu, t_map *map, t_player *plr);
void	menu_keys(mlx_key_data_t data, void *param);

#endif
