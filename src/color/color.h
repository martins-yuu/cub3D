/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 04:51:38 by yuuko             #+#    #+#             */
/*   Updated: 2024/08/01 21:52:02 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# include <stdint.h>

// # define WHITE	0xFFFFFFFF
// # define S_WHT	0xF0F0F0FF
// # define L_GREY	0xC8C8C8FF
// # define GREY	0x7F7F7FFF
// # define D_GREY 0x646464FF
// # define S_BLK	0x272727FF
// # define BLACK	0x000000FF

// # define BLUE	0x0000FFFF
// # define CYAN	0x00FFFFFF
// # define GREEN	0x00FF00FF
// # define YELLOW	0xFFFF00FF
// # define RED	0xFF0000FF
// # define MAGENT	0xFF0000FF

// # define PURPLE 0x91199EFF
// # define ORANGE 0xFF7F00FF
// # define BROWN	0x8C5311FF

// # define ALPHA_00	00

typedef enum e_rgb
{
	WHITE = 0xFFFFFF00,
	S_WHT = 0xF0F0F000,
	L_GREY = 0xC8C8C800,
	GREY = 0x7F7F7F00,
	D_GREY = 0x64646400,
	S_BLK = 0x27272700,
	BLACK = 0x00000000,
	BLUE = 0x0000FF00,
	CYAN = 0x00FFFF00,
	GREEN = 0x00FF0000,
	YELLOW = 0xFFFF0000,
	RED = 0xFF000000,
	D_RED = 0xBF000000,
	MAGENT = 0xFF000000,
	PURPLE = 0x91199E00,
	ORANGE = 0xFF7F0000,
	BROWN = 0x8C531100,
}			t_rgb;

typedef enum e_alpha
{
	A000 = 0x00,
	A025 = 0x3F,
	A050 = 0x7F,
	A075 = 0xBF,
	A100 = 0xFF,
}	t_alpha;

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

t_color	color_hex_alpha(t_rgb hex, t_alpha alpha);
t_color	color(uint32_t v);
t_color	color_from_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
t_color	color_opacity(t_color c, float opacity);
t_color	color_grayscale(t_color c);
t_color	color_lerp(t_color a, t_color b, float t);
t_color	color_random(void);

#endif
