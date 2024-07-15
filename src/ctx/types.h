/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 22:23:56 by yuuko             #+#    #+#             */
/*   Updated: 2024/07/15 20:08:11 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

typedef void	(*t_handle_func)(void *param);
typedef void	(*t_key_func)(mlx_key_data_t, void *param);

typedef	struct	s_player
{
	int			x0;
	int			y0;
	float		dx;
	float		dy;
	int		theta;
	mlx_image_t	*img;
}				t_player;

#endif
