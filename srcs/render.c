/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewonki <taewonki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 12:40:12 by taewonki          #+#    #+#             */
/*   Updated: 2025/12/22 12:00:53 by taewonki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	my_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

int	init_screen_info(t_game *g)
{
	g->screen.img = mlx_new_image(g->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!g->screen.img)
	{
		free_all_data(g);
		return (0);
	}
	g->screen.addr = mlx_get_data_addr(g->screen.img, &g->screen.bpp,
			&g->screen.line_length, &g->screen.endian);
	return (1);
}

t_img	*choice_img(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->ray_dir_x > 0)
			return (&game->textures[0]);
		else
			return (&game->textures[1]);
	}
	else
	{
		if (ray->ray_dir_y > 0)
			return (&game->textures[2]);
		else
			return (&game->textures[3]);
	}
}

int	get_tex_x(t_game *game, t_ray *ray)
{
	double	wall_x;
	int		tex_x;

	if (ray->side == 0)
		wall_x = game->player.pos_y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		wall_x = game->player.pos_x + ray->perp_wall_dist * ray->ray_dir_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)TEX_WIDTH);
	if (ray->side == 0 && ray->ray_dir_x > 0)
		tex_x = TEX_WIDTH - tex_x - 1;
	if (ray->side == 1 && ray->ray_dir_y < 0)
		tex_x = TEX_WIDTH - tex_x - 1;
	return (tex_x);
}

void	draw_vertical_line(t_game *game, t_ray *ray, int x)
{
	t_img	*tex;
	double	step;
	double	tex_pos;
	int		y;
	int		tex_x;

	tex = choice_img(game, ray);
	tex_x = get_tex_x(game, ray);
	step = 1.0 * TEX_HEIGHT / ray->line_height;
	tex_pos = (ray->draw_start - WIN_HEIGHT / 2 + ray->line_height / 2) * step;
	y = -1;
	while (++y < ray->draw_start)
		my_pixel_put(&game->screen, x, y, game->map.ceil_color);
	while (y < ray->draw_end)
	{
		my_pixel_put(&game->screen, x, y, *(unsigned int *)(tex->addr
				+ (((int)tex_pos & (TEX_HEIGHT - 1)) * tex->line_length
					+ tex_x * (tex->bpp / 8))));
		tex_pos += step;
		y++;
	}
	while (y < WIN_HEIGHT)
		my_pixel_put(&game->screen, x, y++, game->map.floor_color);
}
