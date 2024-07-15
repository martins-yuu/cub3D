/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:51:36 by tforster          #+#    #+#             */
/*   Updated: 2024/07/15 18:05:52 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# define mapX 8		//map width
# define mapY 8		//map height
# define mapS 64	//map cube size

typedef struct	 s_map
{
	int			*grid;
	int			map_test;
	int			len_x;
	int			len_y;
	int			cube_s;
}				t_map;

void	init_map(t_map *map);

#endif
