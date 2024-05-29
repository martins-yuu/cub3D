/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuuko <yuuko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 05:14:23 by yuuko             #+#    #+#             */
/*   Updated: 2024/06/25 19:06:11 by yuuko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color/color.h"
#include <stdint.h>
#include <stdlib.h>

t_color	color(uint32_t v)
{
	return ((t_color){.value = v});
}

t_color	color_from_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	return ((t_color){
		.red = r,
		.green = g,
		.blue = b,
		.alpha = a,
	});
}

t_color	color_opacity(t_color c, double opacity)
{
	return ((t_color){
		.red = c.red,
		.green = c.green,
		.blue = c.blue,
		.alpha = c.alpha * opacity,
	});
}

t_color	color_grayscale(t_color c)
{
	uint8_t	gray;

	gray = (c.red + c.green + c.blue) / 3;
	return ((t_color){
		.red = gray,
		.green = gray,
		.blue = gray,
		.alpha = c.alpha,
	});
}

t_color	color_lerp(t_color a, t_color b, double t)
{
	return ((t_color){
		.red = a.red + (b.red - a.red) * t,
		.green = a.green + (b.green - a.green) * t,
		.blue = a.blue + (b.blue - a.blue) * t,
		.alpha = a.alpha + (b.alpha - a.alpha) * t,
	});
}

t_color	color_random(void)
{
	return ((t_color){
		.red = rand() % 0xFF,
		.green = rand() % 0xFF,
		.blue = rand() % 0xFF,
		.alpha = rand() % 0xFF,
	});
}
