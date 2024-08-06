/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_func.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:20:57 by tforster          #+#    #+#             */
/*   Updated: 2024/08/06 17:15:20 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPH_FUNC_H
# define GRAPH_FUNC_H

# include "MLX42/MLX42.h"
# include "graph_lib/graph_types.h"

// ANGLE //
float	deg_rad(const float drg);
float	fix_angle(float drg);

// VECTOR 2D //

// MATRIX 2D //
t_mat2	mat2_diagonal(const float x);
t_mat2	mat2_translate(const t_vec2 disp);
t_mat2	mat2_scale(const t_vec2 ratio);
t_mat2	mat2_rotate(const float ang);

// TRANSFORM //
t_vec2	mat2_vec2_mult(const t_mat2 mat, const t_vec2 vec);
t_mat2	mat2_mat2_mult(const t_mat2 a, const t_mat2 b);

// DRAW //
void	bresenham(mlx_image_t *img, t_line *line);

#endif
