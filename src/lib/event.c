/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuuko <yuuko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 22:37:11 by yuuko             #+#    #+#             */
/*   Updated: 2024/06/25 19:08:34 by yuuko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "common/types.h"
#include "lib/lib.h"

void	lib_on_loop(t_handle_func handle, void *param)
{
	if (!mlx_loop_hook(lib_get(), handle, param))
		lib_panic();
}
