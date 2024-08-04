/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 22:37:11 by yuuko             #+#    #+#             */
/*   Updated: 2024/08/03 17:28:41 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "ctx/ctx.h"
#include "ctx/types.h"

void	ctx_on_loop(t_handle_func handle, void *param)
{
	if (!mlx_loop_hook(ctx(), handle, param))
		ctx_panic();
}

void	ctx_on_key(t_key_func key, void *param)
{
	mlx_key_hook(ctx(), key, param);
}
