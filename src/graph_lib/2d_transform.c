/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2d_transform.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 14:29:15 by tforster          #+#    #+#             */
/*   Updated: 2024/07/26 17:43:01 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "graph_lib/graph_func.h"

t_mat2	mat2_diagonal(float x)
{
	t_mat2	mat;

	mat = (t_mat2)
	{
		x, 0.0, 0.0,
		0.0, x, 0.0,
		0.0, 0.0, x,
	};
	return (mat);
}

t_mat2	mat2_translate(t_vec2 disp)
{
	t_mat2	mat;

	mat = (t_mat2)
	{
		1.0, 0.0, disp.x,
		0.0, 1.0, disp.y,
		0.0, 0.0, 1.0,
	};
	return (mat);
}

t_mat2	mat2_scale(t_vec2 ratio)
{
	t_mat2	mat;

	mat = (t_mat2)
	{
		ratio.x, 0.0, 0.0,
		0.0, ratio.y, 0.0,
		0.0, 0.0, 1.0,
	};
	return (mat);
}

t_mat2	mat2_rotate(float deg)
{
	float	rad;
	t_mat2	mat;

	rad = deg_rad(deg);
	mat = (t_mat2)
	{
		cosf(rad), sinf(rad), 0,
		-sinf(rad), cosf(rad), 0,
		0, 0, 1,
	};
	return (mat);
}

t_vec2	mat2_vec2_mult(t_mat2 mat, t_vec2 vec)
{
	t_vec2	new;

	new.x = mat.i00 * vec.x + mat.i01 * vec.y + mat.i02 * vec.w;
	new.y = mat.i10 * vec.x + mat.i11 * vec.y + mat.i12 * vec.w;
	new.w = mat.i20 * vec.x + mat.i21 * vec.y + mat.i22 * vec.w;
	return (new);
}

t_mat2	mat2_mat2_mult(t_mat2 a, t_mat2 b)
{
	t_mat2	new;

	new.i00 = a.i00 * b.i00 + a.i01 * b.i10 + a.i02 * b.i20;
	new.i01 = a.i00 * b.i01 + a.i01 * b.i11 + a.i02 * b.i21;
	new.i02 = a.i00 * b.i02 + a.i01 * b.i12 + a.i02 * b.i22;
	new.i10 = a.i10 * b.i00 + a.i11 * b.i10 + a.i12 * b.i20;
	new.i11 = a.i10 * b.i01 + a.i11 * b.i11 + a.i12 * b.i21;
	new.i12 = a.i10 * b.i02 + a.i11 * b.i12 + a.i12 * b.i22;
	new.i20 = a.i20 * b.i00 + a.i21 * b.i10 + a.i22 * b.i20;
	new.i21 = a.i20 * b.i01 + a.i21 * b.i11 + a.i22 * b.i21;
	new.i22 = a.i20 * b.i02 + a.i21 * b.i12 + a.i22 * b.i22;
	return (new);
}
