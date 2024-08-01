/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 20:59:54 by tforster          #+#    #+#             */
/*   Updated: 2024/07/31 21:10:46 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "graph_lib/graph_func.h"
#include "ray_casting/ray_types.h"

t_trigo	get_trigonometric_values(const float ray_theta_drg)
{
	return ((t_trigo){
		cosf(deg_rad(ray_theta_drg)), sinf(deg_rad(ray_theta_drg)),
		sinf(deg_rad(ray_theta_drg)) / cosf(deg_rad(ray_theta_drg)),
		cosf(deg_rad(ray_theta_drg)) / sinf(deg_rad(ray_theta_drg)),
	});
}
