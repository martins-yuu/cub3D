/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2d_transform.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 14:29:15 by tforster          #+#    #+#             */
/*   Updated: 2024/08/05 17:32:12 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "graph_lib/graph_func.h"
#include "graph_lib/graph_types.h"

t_mat2	mat2_diagonal(const float x)
{
	return ((t_mat2)
		{
			x, 0.0, 0.0,
			0.0, x, 0.0,
			0.0, 0.0, x,
		}
	);
}

t_mat2	mat2_translate(const t_vec2 disp)
{
	return ((t_mat2)
		{
			1.0, 0.0, disp.x,
			0.0, 1.0, disp.y,
			0.0, 0.0, 1.0,
		}
	);
}

t_mat2	mat2_scale(const t_vec2 ratio)
{
	return ((t_mat2)
		{
			ratio.x, 0.0, 0.0,
			0.0, ratio.y, 0.0,
			0.0, 0.0, 1.0,
		}
	);
}

t_mat2	mat2_rotate(const float deg)
{
	const float	rad = deg_rad(deg);

	return ((t_mat2)
		{
			cosf(rad), sinf(rad), 0,
			-sinf(rad), cosf(rad), 0,
			0, 0, 1,
		}
	);
}

t_vec2	mat2_vec2_mult(const t_mat2 mat, const t_vec2 vec)
{
	return ((t_vec2)
		{
			mat.i00 * vec.x + mat.i01 * vec.y + mat.i02 * vec.w,
			mat.i10 * vec.x + mat.i11 * vec.y + mat.i12 * vec.w,
			mat.i20 * vec.x + mat.i21 * vec.y + mat.i22 * vec.w,
		}
	);
}

t_mat2	mat2_mat2_mult(const t_mat2 a, const t_mat2 b)
{
	return ((t_mat2)
		{
			a.i00 * b.i00 + a.i01 * b.i10 + a.i02 * b.i20,
			a.i00 * b.i01 + a.i01 * b.i11 + a.i02 * b.i21,
			a.i00 * b.i02 + a.i01 * b.i12 + a.i02 * b.i22,
			a.i10 * b.i00 + a.i11 * b.i10 + a.i12 * b.i20,
			a.i10 * b.i01 + a.i11 * b.i11 + a.i12 * b.i21,
			a.i10 * b.i02 + a.i11 * b.i12 + a.i12 * b.i22,
			a.i20 * b.i00 + a.i21 * b.i10 + a.i22 * b.i20,
			a.i20 * b.i01 + a.i21 * b.i11 + a.i22 * b.i21,
			a.i20 * b.i02 + a.i21 * b.i12 + a.i22 * b.i22,
		}
	);
}
