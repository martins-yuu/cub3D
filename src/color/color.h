/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 04:51:38 by yuuko             #+#    #+#             */
/*   Updated: 2024/07/19 17:28:51 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# include <stdint.h>

# define WHITE	0xFFFFFFFF
# define S_WHT	0xF0F0F0FF
# define L_GREY	0xC8C8C8FF
# define GREY	0x7F7F7FFF
# define D_GREY 0x646464FF
# define S_BLK	0x272727FF
# define BLACK	0x000000FF

# define BLUE	0x0000FFFF
# define CYAN	0x00FFFFFF
# define GREEN	0x00FF00FF
# define YELLOW	0xFFFF00FF
# define RED	0xFF0000FF
# define MAGENT	0xFF0000FF

# define PURPLE 0x91199EFF
# define ORANGE 0xFF7F00FF
# define BROWN	0x8C5311FF

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
t_color			color_opacity(t_color c, float opacity);
t_color			color_grayscale(t_color c);
t_color			color_lerp(t_color a, t_color b, float t);
t_color			color_random(void);

#endif
