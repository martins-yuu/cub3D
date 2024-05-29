/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuuko <yuuko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 22:37:11 by yuuko             #+#    #+#             */
/*   Updated: 2024/07/15 14:07:23 by yuuko            ###   ########.fr       */
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
