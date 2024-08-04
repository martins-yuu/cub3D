/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 17:07:27 by tforster          #+#    #+#             */
/*   Updated: 2024/08/04 15:09:41 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MENU_H
# define MENU_H

# include "game/game.h"

# define MENU_OPTS	5
# define PRESS_M	"PRESS <M> FOR MENU"
# define PRESS_C	"PRESS <C> TO SHOW MINI MAP"
# define PRESS_X	"PRESS <X> TO SHOW XY AXIS ON  MINI MAP"
# define PRESS_V	"PRESS <V> TO SHOW RAYS ON  MINI MAP"
# define PRESS_ESC	"PRESS <ESC> TO QUIT"

typedef struct s_menu
{
	t_map		*mini_map;
	t_player	*player;
	mlx_image_t	*menu_img;
	mlx_image_t	*opts[5];
}				t_menu;

void	draw_menu(t_menu *menu, t_map *map, t_player *plr);
void	menu_position(int width, int height, void *menu);
void	menu_keys(mlx_key_data_t data, void *param);

#endif
