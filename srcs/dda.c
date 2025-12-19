/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewonki <taewonki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 12:07:49 by taewonki          #+#    #+#             */
/*   Updated: 2025/12/19 09:48:02 by taewonki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	dda_algo(t_game *g, t_ray *r, int x);
void	calculate_side_dist_xy(t_game *g, t_ray *r);
void	is_hit(t_game *g, t_ray *r);

void	dda_algo(t_game *g, t_ray *r, int x)
{
	r->camera_x = (2 * x / (double)WIN_WIDTH) - 1;
	r->ray_dir_x = g->player.dir_x + g->player.plane_x * r->camera_x;
	r->ray_dir_y = g->player.dir_y + g->player.plane_y * r->camera_x;
	r->map_x = (int)g->player.pos_x;
	r->map_y = (int)g->player.pos_y;
	r->delta_dist_x = fabs(1 / r->ray_dir_x);
	r->delta_dist_y = fabs(1 / r->ray_dir_y);
	r->hit = 0;
	calculate_side_dist_xy(g, r);
	is_hit(g, r);
}

void	calculate_side_dist_xy(t_game *g, t_ray *r)
{
	if (r->ray_dir_x < 0)
	{
		r->step_x = -1;
		r->side_dist_x = (g->player.pos_x - r -> map_x) * r->delta_dist_x;
	}
	else
	{
		r->step_x = 1;
		r->side_dist_x = (r->map_x + 1.0 - g->player.pos_x) * r->delta_dist_x;
	}
	if (r->ray_dir_y < 0)
	{
		r->step_y = -1;
		r->side_dist_y = (g->player.pos_y - r->map_y) * r->delta_dist_y;
	}
	else
	{
		r->step_y = 1;
		r->side_dist_y = (r->map_y + 1 - g->player.pos_y) * r->delta_dist_y;
	}
}

void	is_hit(t_game *g, t_ray *r)
{
	while (r->hit == 0)
	{
		if (r->side_dist_x < r->side_dist_y)
		{
			r->side_dist_x += r->delta_dist_x;
			r->map_x += r->step_x;
			r->side = 0;
		}
		else
		{
			r->side_dist_y += r->delta_dist_y;
			r->map_y += r->step_y;
			r->side = 1;
		}
		if (g->map.grid[r->map_y][r->map_x] == '1')
			r->hit = 1;
	}
	if (r->side == 0)
		r->perp_wall_dist = (r->map_x - g->player.pos_x + (1 - r->step_x) / 2) \
		/ r->ray_dir_x;
	else
		r->perp_wall_dist = (r->map_y - g->player.pos_y + (1 - r->step_y) / 2) \
		/ r->ray_dir_y;
}
