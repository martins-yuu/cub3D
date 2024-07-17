/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:04:18 by tforster          #+#    #+#             */
/*   Updated: 2024/07/17 12:11:57 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector/angle.h"

float deg_rad(int theta)
{
	return(theta * M_PI/180.0);
}

float	fix_angle(float theta)
{
	if (theta > 359)
		theta -= 360;
	if (theta < 0)
		theta += 360;
	return (theta);
}