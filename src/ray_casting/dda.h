/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 19:39:06 by tforster          #+#    #+#             */
/*   Updated: 2024/08/01 21:01:29 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DDA_H
# define DDA_H

# include "game/game.h"
# include "ray_casting/ray_types.h"

t_ray	dda(t_player *plr, const float ray_theta_drg);

// DDA UTILS //
t_trigo	get_trigonometric_values(const float ray_theta_drg);
bool	check_if_in_map(const int index, const t_ivec2 dof, const int *grid);
float	distance_to_wall(const t_trigo trg, const t_vec2 p0, const t_vec2 p1);

#endif
