/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2d_vector.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 14:56:02 by tforster          #+#    #+#             */
/*   Updated: 2024/07/18 15:29:00 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graph_lib/graph_func.h"

t_ivec2	init_ivec2(int x, int y)
{
	// const t_ivec2	ivec2 = {x, y,};
	t_ivec2	ivec2;

	ivec2 = (t_ivec2) {x, y,};

	return (ivec2);
}

t_fvec2	init_fvec2(float x, float y)
{
	const t_fvec2	ivec2 = {x, y, 1,};

	return (ivec2);
}
