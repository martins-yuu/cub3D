/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 20:59:54 by tforster          #+#    #+#             */
/*   Updated: 2024/08/06 15:12:39 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdbool.h>
#include "graph_lib/graph_func.h"
#include "graph_lib/graph_types.h"
#include "ray_casting/ray_types.h"

t_trigo	get_trigonometric_values(const float ray_theta_drg)
{
	return ((t_trigo){
		cosf(deg_rad(ray_theta_drg)), sinf(deg_rad(ray_theta_drg)),
		sinf(deg_rad(ray_theta_drg)) / cosf(deg_rad(ray_theta_drg)),
		cosf(deg_rad(ray_theta_drg)) / sinf(deg_rad(ray_theta_drg)),
	});
}

bool	check_if_in_map(const int index, const t_ivec2 dof, const int *grid)
{
	return (index > 0 && index < (dof.x * dof.y) && grid[index] == 1);
}

float	distance_to_wall(const t_trigo trg, const t_vec2 p0, const t_vec2 p1)
{
	return (trg.cos * (p1.x - p0.x) - trg.sin * (p1.y - p0.y));
}
