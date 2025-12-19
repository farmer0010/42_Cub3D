/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewonki <taewonki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 15:42:45 by taewonki          #+#    #+#             */
/*   Updated: 2025/12/19 10:21:56 by taewonki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_arr(double *arr)
{
	arr[0] = 0;
	arr[1] = 0;
}

void	calculate_draw_point(t_ray *ray)
{
	ray->line_height = (int)(WIN_HEIGHT / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + WIN_HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + WIN_HEIGHT / 2;
	if (ray->draw_end >= WIN_HEIGHT)
		ray->draw_end = WIN_HEIGHT - 1;
}

void	raycast(t_game *game)
{
	t_ray	ray;
	int		x;

	init_ray_info(&ray);
	x = -1;
	while (++x < WIN_WIDTH)
	{
		dda_algo(game, &ray, x);
		calculate_draw_point(&ray);
		draw_vertical_line(game, &ray, x);
	}
}
