/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuuko <yuuko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 21:11:00 by yuuko             #+#    #+#             */
/*   Updated: 2024/07/15 14:08:33 by yuuko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "ctx/constants.h"
#include "ft_stdio.h"
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>

mlx_t	*ctx(void)
{
	static mlx_t	*instance = NULL;

	if (instance == NULL)
	{
		instance = mlx_init(WIDTH, HEIGHT, TITLE, true);
		if (!instance)
		{
			ft_putendl_fd((char *)mlx_strerror(mlx_errno), STDERR_FILENO);
			exit(EXIT_FAILURE);
		}
	}
	return (instance);
}

void	ctx_panic(void)
{
	ft_putendl_fd((char *)mlx_strerror(mlx_errno), STDERR_FILENO);
	mlx_close_window(ctx());
	exit(EXIT_FAILURE);
}
