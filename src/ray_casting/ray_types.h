/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_types.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 17:23:31 by tforster          #+#    #+#             */
/*   Updated: 2024/07/31 19:11:02 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_TYPES_H
# define RAY_TYPES_H

# include "graph_lib/graph_types.h"

typedef struct s_ray
{
	t_vec2	dir;
	t_vec2	step;
	int		dof;
	float	dist;
}				t_ray;

typedef struct s_trigo
{
	float	cos;
	float	sin;
	float	tan;
	float	inv_tan;
}				t_trigo;

#endif
