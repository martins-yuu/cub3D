/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:04:18 by tforster          #+#    #+#             */
/*   Updated: 2024/08/06 17:11:59 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "graph_lib/graph_func.h"

float	deg_rad(const float drg)
{
	return (drg * M_PI / 180.0);
}

float	fix_angle(float drg)
{
	if (drg > 359)
		drg -= 360;
	if (drg < 0)
		drg += 360;
	return (drg);
}
