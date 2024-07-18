/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_func.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:20:57 by tforster          #+#    #+#             */
/*   Updated: 2024/07/18 16:35:28 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPH_FUNC_H
# define GRAPH_FUNC_H

#include <math.h>
#include "graph_lib/graph_types.h"
#include "MLX42/MLX42.h"
#include "color/color.h"

// t_ivec2	vec_float_to_int(t_fvec2 *fvec2);

float	deg_rad(int theta);
float	fix_angle(float theta);

// VECTOR 2D //

// MATRIX 2D //
t_mt2	mt2_diagonal(float x);
t_mt2	mt2_translate(t_fvec2 *disp);
t_mt2	mt2_rotate(float ang);
t_mt2	mt2_rot_on_point(t_fvec2 *d, float ang);

// TRANSFORM //
t_fvec2	mult_fvec2_mt2(t_fvec2 *fv, t_mt2 *mt);



// void	bresenham(mlx_image_t *img, t_fvec2 fv[2], t_color c);
void	bresenham(mlx_image_t *img, t_line *line);

#endif
