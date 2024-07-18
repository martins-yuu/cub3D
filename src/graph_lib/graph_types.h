/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_types.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:09:59 by tforster          #+#    #+#             */
/*   Updated: 2024/07/17 18:30:18 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPH_TYPES_H
# define GRAPH_TYPES_H

# include "color/color.h"

typedef struct	s_ivec2
{
	int	x;
	int	y;
}				t_ivec2;

typedef struct	s_fvec2
{
	float	x;
	float	y;
}				t_fvec2;

typedef struct s_line
{
	t_ivec2		ivec0;
	t_color		c0;
	t_ivec2		ivec1;
	t_color		c1;
}				t_line;

typedef struct s_bresenham
{
	int		dx;
	int		sx;
	int		dy;
	int		sy;
	int		err;
	int		e2;
	float	dist;
	float	step;
}			t_ctrl;

#endif
