/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_func.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:20:57 by tforster          #+#    #+#             */
/*   Updated: 2024/07/19 17:39:26 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPH_FUNC_H
# define GRAPH_FUNC_H

#include "MLX42/MLX42.h"
#include "graph_lib/graph_types.h"

// ANGLE //
float	deg_rad(int theta);
float	fix_angle(float theta);

// VECTOR 2D //

// MATRIX 2D //
t_mat2	mat2_diagonal(float x);
t_mat2	mat2_translate(t_vec2 *disp);
t_mat2	mat2_rotate(float *ang);

// TRANSFORM //
t_vec2	mat2_vec2_mult(t_mat2 *mt, t_vec2 *fv);
t_mat2	mat2_mat2_mult(t_mat2 *a, t_mat2 *b);

// DRAW //
void	bresenham(mlx_image_t *img, t_line *line);

#endif
