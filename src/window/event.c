/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuuko <yuuko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 22:37:11 by yuuko             #+#    #+#             */
/*   Updated: 2024/07/16 00:58:20 by yuuko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "window/types.h"
#include "window/window.h"
#include "window/window_internal.h"

void	ctx_on_loop(t_handle_func handle, void *param)
{
	if (!mlx_loop_hook(*(mlx_t **)window_get_handle(), handle, param))
		window_panic();
}
