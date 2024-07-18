/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:35:00 by tforster          #+#    #+#             */
/*   Updated: 2024/07/18 19:21:03 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include "graph_lib/graph_types.h"
# include "map/map.h"

# define STEP	5
# define ANG	2
# define PLAYER_SIZE	5

typedef struct s_player
{
	t_fvec2		p0;
	t_fvec2		del;
	float		theta_dg;
	int			size;
	mlx_image_t	*map;
	mlx_image_t	*view;
	int			*grid;
	t_fvec2		geometry[10];
}				t_player;

void	init_player(t_map *map, t_player *player, int x0, int y0);
void	draw_player(void *param);

#endif
