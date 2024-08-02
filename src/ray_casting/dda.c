/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 19:38:11 by tforster          #+#    #+#             */
/*   Updated: 2024/08/01 21:54:19 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_casting/dda.h"
#include "color/color.h"

static t_ray	vertical_ray(t_player *plr, t_trigo trg);
static t_ray	get_vertical_dist(t_player *plr, t_ray ray, t_trigo trg);
static t_ray	horizontal_ray(t_player *plr, t_trigo trg);
static t_ray	get_horizontal_dist(t_player *plr, t_ray ray, t_trigo trg);

t_ray	dda(t_player *plr, const float ray_theta_drg)
{
	t_trigo	trg;
	t_ray	ray_v;
	t_ray	ray_h;

	trg = get_trigonometric_values(ray_theta_drg);
	ray_v = vertical_ray(plr, trg);
	ray_h = horizontal_ray(plr, trg);
	if (ray_v.dist < ray_h.dist)
	{
		ray_h.dir.x = ray_v.dir.x;
		ray_h.dir.y = ray_v.dir.y;
		ray_h.dist = ray_v.dist;
		ray_h.color = color_hex_alpha(RED, A100);
	}
	else
		ray_h.color = color_hex_alpha(D_RED, A100);
	return (ray_h);
}

static t_ray	vertical_ray(t_player *plr, t_trigo trg)
{
	t_ray	ray;

	ray.dof = 0;
	if (trg.cos > 0.001)
	{
		ray.dir.x = (int) plr->p0.x + 1;
		ray.dir.y = (plr->p0.x - ray.dir.x) * trg.tan + plr->p0.y;
		ray.step = (t_vec2){1, -trg.tan};
	} // LEFT
	else if (trg.cos < -0.001)
	{
		ray.dir.x = (int) plr->p0.x - 0.0001;
		ray.dir.y = (plr->p0.x - ray.dir.x) * trg.tan + plr->p0.y;
		ray.step = (t_vec2){-1, trg.tan};
	} // RIGHT
	else
	{
		ray.dir = (t_vec2){plr->p0.x, plr->p0.y};
		ray.dof = plr->dof.x;
	} // looking straight up or down
	return (get_vertical_dist(plr, ray, trg));
}

static t_ray	get_vertical_dist(t_player *plr, t_ray ray, t_trigo trg)
{
	int		index;

	ray.dist = 10000;
	while (ray.dof < plr->dof.x)
	{
		index = ((int) ray.dir.y) * plr->dof.x + (int) ray.dir.x;
		if (check_if_in_map(index, plr->dof, plr->grid))
		{
			ray.dof = plr->dof.x;
			ray.dist = distance_to_wall(trg, plr->p0, ray.dir);
		} // HIT
		else
		{
			ray.dir = (t_vec2){ray.dir.x + ray.step.x, ray.dir.y + ray.step.y};
			ray.dof +=1;
		} // CHECK NEXT VERTICAL
	}
	return (ray);
}

static t_ray	horizontal_ray(t_player *plr, t_trigo trg)
{
	t_ray	ray;

	ray.dof = 0;
	if (trg.sin > 0.001)
	{
		ray.dir.y = (int) plr->p0.y - 0.0001;
		ray.dir.x = (plr->p0.y - ray.dir.y) * trg.inv_tan + plr->p0.x;
		ray.step = (t_vec2){trg.inv_tan, -1};
	} // UP
	else if (trg.sin < -0.001)
	{
		ray.dir.y = (int) plr->p0.y + 1;
		ray.dir.x = (plr->p0.y - ray.dir.y) * trg.inv_tan + plr->p0.x;
		ray.step = (t_vec2){-trg.inv_tan, 1};
	} // DOWN
	else
	{
		ray.dir = (t_vec2){plr->p0.x, plr->p0.y};
		ray.dof = plr->dof.y;
	} // looking straight left or right
	return (get_horizontal_dist(plr, ray, trg));
}

static t_ray	get_horizontal_dist(t_player *plr, t_ray ray, t_trigo trg)
{
	int		index;

	ray.dist = 10000;
	while (ray.dof < plr->dof.y)
	{
		index = ((int) ray.dir.y) * plr->dof.x + (int) ray.dir.x;
		if (check_if_in_map(index, plr->dof, plr->grid))
		{
			ray.dof = plr->dof.y;
			ray.dist = distance_to_wall(trg, plr->p0, ray.dir);
		} // HIT
		else
		{
			ray.dir = (t_vec2){ray.dir.x + ray.step.x, ray.dir.y + ray.step.y};
			ray.dof += 1;
		} // CHECK NEXT HORIZONTAL
	}
	return (ray);
}
