/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:35:03 by tforster          #+#    #+#             */
/*   Updated: 2024/07/19 17:43:46 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>	// DELETE THIS
#include <math.h>

#include "ft_string.h"
#include "ctx/ctx.h"
#include "graph_lib/graph_func.h"
#include "game/game.h"

// static void	orientation_vec(t_player *player, int del);

t_line	org_arrow(t_vec2 *ivec, t_vec2 *idel, int org);
t_line	sub_arrow(t_vec2 *ivec, t_vec2 *sub, t_vec2 *idel, int org);
t_line	sub_arrowS(t_vec2 *ivec, t_vec2 *sub, t_vec2 *idel, int org);

void	perp(t_player *plr, int del);

static void	draw_2drays(t_player *player);

static void	player_geometry(t_vec2 geometry[6]);

void	init_player(t_map *map, t_player *player, int x0, int y0)
{
	// mlx_image_t	*img;

	player->p0.x = (float) (map->cube_s * map->player_pos0.x + map->cube_s / 2);
	player->p0.y = (float) (map->cube_s * map->player_pos0.y + map->cube_s / 2);
	player->theta_dg = 90;
	player->del.x = cosf(deg_rad(player->theta_dg));
	player->del.y = -sinf(deg_rad(player->theta_dg));
	player->size = PLAYER_SIZE;
	player->map = ctx_img_new(x0, y0);
	player->grid = map->grid;
	player_geometry(player->geometry);
	ctx_img_display(player->map, 0, 0);
	player->view = ctx_img_new(x0, 320);
	ctx_img_display(player->view, x0, 0);
}

static void	player_geometry(t_vec2 *geometry)
{
	geometry[0] = (t_vec2) { 0.0,   3.0, 1.0};
	geometry[1] = (t_vec2) { 2.0,   2.0, 1.0};
	geometry[2] = (t_vec2) { 3.0,   1.0, 1.0};
	geometry[3] = (t_vec2) { 3.0,  -3.0, 1.0};
	geometry[4] = (t_vec2) { 2.0, -10.0, 1.0};
	geometry[5] = (t_vec2) { 0.0, -20.0, 1.0};
	geometry[6] = (t_vec2) {-2.0, -10.0, 1.0};
	geometry[7] = (t_vec2) {-3.0,  -3.0, 1.0};
	geometry[8] = (t_vec2) {-3.0,   1.0, 1.0};
	geometry[9] = (t_vec2) {-2.0,   2.0, 1.0};
}

void	draw_player(void *param)
{
	uint32_t	i;
	uint32_t	size;
	t_color		c;
	t_player	*player;

	player = param;
	i = 0;
	ft_memset(player->map->pixels, 0,
		player->map->width * player->map->height * 4);
	size = player->size * player->size;

	int p = 0;
	float	obj_deg = player->theta_dg - 90;
	t_mat2	rot = mat2_rotate(&obj_deg);
	t_color	white = color(0xFFFFFFFF);
	t_mat2	transl = mat2_translate(&player->p0);
	t_mat2	mat = mat2_mat2_mult(&transl, &rot);

	t_line	line_h = {{player->p0.x, 60},{player->p0.x, 500}, white, white};
	t_line	line_v = {{60, player->p0.y},{500, player->p0.y}, white, white};
	bresenham(player->map, &line_h);
	bresenham(player->map, &line_v);

	printf("[%.f][%.f][%.f]\n[%.f][%.f][%.f]\n[%.f][%.f][%.f]\n\n",
		rot.i00, rot.i01, rot.i02,
		rot.i10, rot.i11, rot.i12,
		rot.i20, rot.i21, rot.i22);

	printf("[%.f][%.f][%.f]\n[%.f][%.f][%.f]\n[%.f][%.f][%.f]\n\n",
		transl.i00, transl.i01, transl.i02,
		transl.i10, transl.i11, transl.i12,
		transl.i20, transl.i21, transl.i22);

	t_vec2	new_p[2];
	t_ivec2	int_p[2];
	t_line	plr_line;
	t_color plr_c = color(0xFFFF00FF);
	// printf(">> BF [%.f][%.f] [%.f][%.f]\n", player->geometry[5].x, player->geometry[5].y,
	// 	player->geometry[0].x, player->geometry[0].y);
	while (p < 10)
	{
		// new_p[0] = mat2_vec2_mult(&transl, &player->geometry[p % 10]);
		// new_p[1] = mat2_vec2_mult(&transl, &player->geometry[(p + 1) % 10]);
		new_p[0] = mat2_vec2_mult(&mat, &player->geometry[p % 10]);
		new_p[1] = mat2_vec2_mult(&mat, &player->geometry[(p + 1) % 10]);
		int_p[0] = (t_ivec2) {(int) new_p[0].x, (int) new_p[0].y};
		int_p[1] = (t_ivec2) {(int) new_p[1].x, (int) new_p[1].y};
		plr_line = (t_line) {int_p[0], int_p[1], plr_c, plr_c};
		// printf("{%d}[%.f][%.f] ", p, new_p[0].x, new_p[0].y);
		bresenham(player->map, &plr_line);
		p++;
	}
	// printf("\n>> AF [%.f][%.f] [%.f][%.f]\n", new_p[0].x, new_p[0].y, new_p[1].x, new_p[1].y);



	ft_memset(player->view->pixels, 0,
		player->view->width * player->view->height * 4);
	// draw_2drays(player);

	// t_line	line = org_arrow(&player->p0, &player->del, player->size / 2);
	// bresenham(player->map, &line);

	// float	rad = deg_rad(player->theta_dg);

	// t_vec2	subL = {cosf(M_PI_2 - rad), sinf(M_PI_2 - rad)};
	// t_line	sub_lineL = sub_arrow(&player->p0, &subL, &player->del, player->size / 2);
	// bresenham(player->map, &sub_lineL);
	// t_vec2	subR = {-cosf(M_PI_2 - rad), -sinf(M_PI_2 - rad)};
	// t_line	sub_lineR = sub_arrow(&player->p0, &subR, &player->del, player->size / 2);
	// bresenham(player->map, &sub_lineR);

	// t_vec2	subLS = {cosf(M_PI_2 - rad), sinf(M_PI_2 - rad)};
	// t_line	sub_lineLS = sub_arrowS(&player->p0, &subLS, &player->del, player->size / 2);
	// bresenham(player->map, &sub_lineLS);
	// t_vec2	subRS = {-cosf(M_PI_2 - rad), -sinf(M_PI_2 - rad)};
	// t_line	sub_lineRS = sub_arrowS(&player->p0, &subRS, &player->del, player->size / 2);
	// bresenham(player->map, &sub_lineRS);

		// orientation_vec(player, player->size / 2);

	// perp(player, player->size / 2);
}

static void	draw_2drays(t_player *player)
{
	int		ray_nb;
	// t_ivec2	ivec;
	int		mx;
	int		my;
	int		mp;
	int		dof;
	// int		side;
	// t_vec2	f_rays;
	float	rx;
	float	ry;
	float	vx;
	float	vy;
	float	ray_theta_deg;
	float	ray_theta_rad;
	float	xo;
	float	yo;

	float	dist_v;
	float	dist_h;

	// ray_theta_rad = fix_angle(player->theta_dg + 30);
	// ray_theta_rad = deg_rad(player->theta_dg);
	// float	degree = player->theta_dg;
	ray_theta_deg = fix_angle(player->theta_dg + 30);
	// ray_theta_rad = fix_angle(player->theta_dg);
	// ray_theta_rad = player->theta_dg;

	ray_nb = 0;
	while (ray_nb < 61)
	{
		ray_theta_rad = deg_rad(ray_theta_deg);
		// VERTICAL
		dof = 0;
		float tg = tanf(ray_theta_rad);
		dist_v = 100000;
		if (cos(ray_theta_rad) > 0.001)
		{
			rx = (((int) player->p0.x >> 6) << 6) + 64;
			ry = (player->p0.x - rx) * tg + player->p0.y;
			xo = 64;
			yo = -xo * tg;
		} // LEFT
		else if (cos(ray_theta_rad) < -0.001)
		{
			rx = (((int) player->p0.x >> 6) << 6) - 0.0001;
			ry = (player->p0.x - rx) * tg + player->p0.y;
			xo = -64;
			yo = -xo * tg;
		} // RIGHT
		else
		{
			rx = player->p0.x;
			ry = player->p0.y;
			dof = 8;
		} // looking straight up or down
		while (dof < 8)
		{
			mx = (int)(rx) >> 6;
			my = (int)(ry) >> 6;

			mp = my * 8 + mx;
			if (mp > 0 && mp < (8 * 8) && player->grid[mp] == 1)
			{
				dof = 8;
				dist_v = cosf(ray_theta_rad) * (rx - player->p0.x) - sinf(ray_theta_rad) * (ry - player->p0.y);
			} // HIT
			else
			{
				rx += xo;
				ry += yo;
				dof +=1;
			} // CHECK NEXT HORIZONTAL
		}
		vx = rx;
		vy = ry;

		// HORIZONTAL
		dof = 0;
		float inv_tg = 1.0 / tg;
		dist_h = 100000;
		if (sinf(ray_theta_rad) > 0.001)
		{
			ry = (((int) player->p0.y >> 6) << 6) - 0.0001;
			rx = (player->p0.y - ry) * inv_tg + player->p0.x;
			yo = -64;
			xo = -yo*inv_tg;
		} // UP
		else if (sinf(ray_theta_rad) < -0.001)
		{
			ry = (((int) player->p0.y >> 6) << 6) + 64;
			rx = (player->p0.y - ry) * inv_tg + player->p0.x;
			yo = 64;
			xo = -yo*inv_tg;
		} // DOWN
		else
		{
			rx = player->p0.x;
			ry = player->p0.y;
			dof = 8;
		} // looking straight left or right
		while (dof < 8)
		{
			mx = (int)(rx) >> 6;
			my = (int)(ry) >> 6;

			mp = my * 8 + mx;
			if (mp > 0 && mp < (8 * 8) && player->grid[mp] == 1)
			{
				dof = 8;
				dist_h = cosf(ray_theta_rad) * (rx - player->p0.x) - sinf(ray_theta_rad) * (ry - player->p0.y);

			} // HIT
			else
			{
				rx += xo;
				ry += yo;
				dof +=1;
			} // CHECK NEXT HORIZONTAL
		}
		if (dist_v < dist_h)
		{
			rx = vx;
			ry = vy;
			dist_h = dist_v;
		}

		t_ivec2 ivec[2];
		ivec[0].x =  (player->p0.x + player->size / 2);
		ivec[0].y =  (player->p0.y + player->size / 2);

		ivec[1].x =  rx;
		ivec[1].y =  ry;
		t_color	c0 = color(0xFF0000FF);
		t_color	c1 = color(0xFF0000FF);
		t_line	line = {ivec[0], ivec[1], c0, c1};
		bresenham(player->map, &line); // DRAW 2D RAYS

		// DRAW VIEW
		// printf("[%d]DIST_H[%.2f]", ray_nb, dist_h);
		float view_theta = fix_angle(( player->theta_dg - ray_theta_deg));
		dist_h = dist_h * cosf(deg_rad(view_theta));
		// dist_h = dist_h * cosf(deg_rad(ray_theta_deg));
		// printf("ANGs[%.2f][%.2f][%.2f]NEW[%.2f]\n",  player->theta_dg, ray_theta_deg, view_theta, dist_h);
		// dist_h = dist_h * cosf(view_theta);
		int line_h = (64 * 320) / (dist_h);
		if (line_h > 320)
		{
			line_h = 320;
		}
		int	line_off = 160 - (line_h / 2);

		// int	line_with = 8;
		int	j = 0;
		while (j < line_h)
		{
			int	i = 0;
			while (i < 8)
			{
				mlx_put_pixel(player->view, ray_nb * 8 + i, line_off + j, c0.value);
				i++;
			}
			j++;
		}
		ray_theta_deg = fix_angle(ray_theta_deg - 1);
		// ray_theta_deg--;
		ray_nb++;
	}
	// printf("ANG[%f][%f]\n", player->theta_dg, ray_theta_rad);
}

// void	orientation_vec(t_player *plr, int org)
// {
// 	const t_ivec2	ivec0 = {(int) plr->p0.x + org , (int) plr->p0.y + org};
// 	const t_color	c0 = color(0xFFFF00FF);
// 	const t_ivec2	ivec1 = {(int) (plr->p0.x + org + 50 * plr->del.x),
// 		(int) (plr->p0.y + org + 50 * plr->del.y)};
// 	const t_color	c1 = color(0xFFFF00FF);
// 	const t_line	line = {(t_ivec2 *) &ivec0, (t_color *) &c0,
// 		(t_ivec2 *) &ivec1, (t_color *) &c1};
// 	bresenham(plr->img, (t_line *) &line);
// }

t_line	org_arrow(t_vec2 *ivec, t_vec2 *idel, int org)
{
	const t_ivec2	ivec0 = {(int) ivec->x + org, (int) ivec->y + org};
	const t_color	c0 = color(0xFFFF00FF);

	const t_ivec2	ivec1 = {(int) (ivec->x + org + 20 * idel->x), (int) (ivec->y + org + 20 * idel->y)};
	const t_color	c1 = color(0xFFFF00FF);

	const t_line	line = {(t_ivec2) ivec0, (t_ivec2) ivec1, (t_color) c0, (t_color) c1};
	return ((t_line) line);
}

t_line	sub_arrow(t_vec2 *ivec, t_vec2 *sub, t_vec2 *idel, int org)
{
	const t_ivec2	ivec0 = {(int) (ivec->x + org + 2 * sub->x), (int) (ivec->y + org + 2 * sub->y)};
	const t_color	c0 = color(0xFFFF00FF);

	const t_ivec2	ivec1 = {(int) (ivec->x + org + 20 * idel->x), (int) (ivec->y + org + 20 * idel->y)};
	const t_color	c1 = color(0xFFFF00FF);

	const t_line	line = {(t_ivec2) ivec0, (t_ivec2) ivec1, (t_color) c0, (t_color) c1};
	return ((t_line) line);
}

t_line	sub_arrowS(t_vec2 *ivec, t_vec2 *sub, t_vec2 *idel, int org)
{
	const t_ivec2	ivec0 = {(int) (ivec->x + org + 1 * sub->x), (int) (ivec->y + org + 1 * sub->y)};
	const t_color	c0 = color(0xFFFF00FF);

	const t_ivec2	ivec1 = {(int) (ivec->x + org + 20 * idel->x), (int) (ivec->y + org + 20 * idel->y)};
	const t_color	c1 = color(0xFFFF00FF);

	const t_line	line = {(t_ivec2) ivec0, (t_ivec2) ivec1, (t_color) c0, (t_color) c1};
	return ((t_line) line);
}
