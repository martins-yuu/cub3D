/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuuko <yuuko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 21:11:00 by yuuko             #+#    #+#             */
/*   Updated: 2024/07/16 01:07:06 by yuuko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "ft_stdio.h"
#include "window_internal.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

void	window_init(int32_t width, int32_t height, const char *title,
		bool resize)
{
	mlx_t	**instance;

	instance = window_get_handle();
	*instance = mlx_init(width, height, title, resize);
	if (!*instance)
	{
		ft_putendl_fd((char *)mlx_strerror(mlx_errno), STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
}

void	window_panic(void)
{
	ft_putendl_fd((char *)mlx_strerror(mlx_errno), STDERR_FILENO);
	mlx_close_window(*(mlx_t **)window_get_handle());
	exit(EXIT_FAILURE);
}

void	*window_get_handle(void)
{
	static mlx_t	*instance = NULL;

	return (&instance);
}
