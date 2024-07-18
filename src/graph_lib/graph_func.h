/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_func.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:20:57 by tforster          #+#    #+#             */
/*   Updated: 2024/07/17 16:00:52 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPH_FUNC_H
# define GRAPH_FUNC_H

#include <math.h>
#include "graph_lib/graph_types.h"
#include "MLX42/MLX42.h"
#include "color/color.h"

t_ivec2	vec_float_to_int(t_fvec2 *fvec2);

float	deg_rad(int theta);
float	fix_angle(float theta);

// void	bresenham(mlx_image_t *img, t_fvec2 fv[2], t_color c);
void	bresenham(mlx_image_t *img, t_line *line);

#endif
