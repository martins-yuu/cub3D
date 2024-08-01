/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 19:39:06 by tforster          #+#    #+#             */
/*   Updated: 2024/07/31 21:11:06 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DDA_H
# define DDA_H

#include "game/game.h"
#include "ray_casting/ray_types.h"

t_ray	dda(t_player *plr, const float ray_theta_drg);
t_trigo	get_trigonometric_values(const float ray_theta_drg);

#endif
