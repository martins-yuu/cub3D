/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuuko <yuuko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 04:51:38 by yuuko             #+#    #+#             */
/*   Updated: 2024/07/06 14:08:31 by yuuko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# include <stdint.h>

typedef union u_color
{
	uint32_t	value;
	struct
	{
		uint8_t	alpha;
		uint8_t	blue;
		uint8_t	green;
		uint8_t	red;
	};
}				t_color;

t_color			color(uint32_t v);
t_color			color_from_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
t_color			color_opacity(t_color c, double opacity);
t_color			color_grayscale(t_color c);
t_color			color_lerp(t_color a, t_color b, double t);
t_color			color_random(void);

#endif
