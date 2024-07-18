/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2d_transform.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 14:29:15 by tforster          #+#    #+#             */
/*   Updated: 2024/07/18 19:13:27 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graph_lib/graph_func.h"

// LEGAL?
#include <stdio.h>
// LEGAL?

t_mt2	mt2_diagonal(float x)
{
	const t_mt2	mt = {
		x, 0.0, 0.0,
		0.0, x, 0.0,
		0.0, 0.0, x,
	};

	return (mt);
}

t_mt2	mt2_translate(t_fvec2 *disp)
{
	const t_mt2	mt = {
		1.0, 0.0, disp->x,
		0.0, 1.0, disp->y,
		0.0, 0.0, 1.0,
		};

	return (mt);
}

t_mt2	mt2_rotate(float deg)
{
	const t_mt2	mt = {
		cosf(deg), -sinf(deg), 0,
		sinf(deg), cosf(deg), 0,
		0, 0, 1,
	};

	return (mt);
}

t_mt2	mt2_rot_on_point(t_fvec2 *d, float deg)
{
	float	rad;
	t_mt2	mt;

	rad = deg_rad(deg);
	mt = (t_mt2) {cosf(rad), -sinf(rad), -d->x * cosf(rad) + d->y * sinf(rad) + d->x,
		sinf(rad), cos(rad), -d->x * sinf(rad) - d->y * cosf(rad) + d->y,
		0, 0, 1,
	};
	return (mt);
}

t_fvec2	mult_fvec2_mt2(t_fvec2 *fv, t_mt2 *mt)
{
	t_fvec2	new;

	new = (t_fvec2) {mt->i00 * fv->x + mt->i01 * fv->y + mt->i02 * fv->w,
		mt->i10 * fv->x + mt->i11 * fv->y + mt->i12 * fv->w,
		mt->i20 * fv->x + mt->i21 * fv->y + mt->i22 * fv->w,
	};
	return (new);
}

// t_fvec2	mt2_mult(t_mt2 *m0, t_mt2 *m1)
// {
// 	t_fvec2	new;

// 	new = (t_fvec2) {fv->x * mt->i00 + fv->y * mt->i10 + fv->w * mt->i20,
// 		fv->x * mt->i01 + fv->x * mt->i11 + fv->x * mt->i21,
// 		fv->x * mt->i02 + fv->x * mt->i12 + fv->x * mt->i22,
// 	};
// 	return (new);
// }
