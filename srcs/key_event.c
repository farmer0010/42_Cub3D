/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewonki <taewonki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 09:30:18 by taewonki          #+#    #+#             */
/*   Updated: 2025/12/19 10:25:23 by taewonki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	close_game(t_game *game)
{
	free_all_data(game);
	if (game->mlx && game->win)
	{
		mlx_destroy_window(game->mlx, game->win);
		game->win = NULL;
	}
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		game->mlx = NULL;
	}
	exit(0);
	return (0);
}

int	is_wall(t_game *g, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	if (map_x < 0 || map_x >= g->map.width || \
			map_y < 0 || map_y >= g->map.height)
		return (1);
	if (g->map.grid[map_y][map_x] == '1')
		return (1);
	return (0);
}

void	move_player(int key, t_game *g)
{
	double	m_xy[2];

	init_arr(m_xy);
	if (key == K_W || key == K_S)
	{
		m_xy[0] = g->player.dir_x * MOVE_SPEED;
		m_xy[1] = g->player.dir_y * MOVE_SPEED;
		if (key == K_S)
			m_xy[0] *= -1;
		if (key == K_S)
			m_xy[1] *= -1;
	}
	else if (key == K_A || key == K_D)
	{
		m_xy[0] = g->player.plane_x * MOVE_SPEED;
		m_xy[1] = g->player.plane_y * MOVE_SPEED;
		if (key == K_D)
			m_xy[0] *= -1;
		if (key == K_D)
			m_xy[1] *= -1;
	}
	if (!is_wall(g, g->player.pos_x + m_xy[0], g->player.pos_y))
		g->player.pos_x += m_xy[0];
	if (!is_wall(g, g->player.pos_x, g->player.pos_y + m_xy[1]))
		g->player.pos_y += m_xy[1];
}

void	rotate_player(int key, t_game *g)
{
	double	rs;
	double	old_dir_x;
	double	old_plane_x;

	if (key == K_RIGHT)
		rs = ROT_SPEED;
	else if (key == K_LEFT)
		rs = -ROT_SPEED;
	else
		return ;
	old_dir_x = g->player.dir_x;
	g->player.dir_x = g->player.dir_x * cos(rs) - g->player.dir_y * sin(rs);
	g->player.dir_y = old_dir_x * sin(rs) + g->player.dir_y * cos(rs);
	old_plane_x = g->player.plane_x;
	g->player.plane_x = g->player.plane_x * cos(rs)
		- g->player.plane_y * sin(rs);
	g->player.plane_y = old_plane_x * sin(rs) + g->player.plane_y * cos(rs);
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == K_ESC)
		close_game(game);
	if (keycode == K_W || keycode == K_S
		|| keycode == K_A || keycode == K_D)
		move_player(keycode, game);
	if (keycode == K_LEFT || keycode == K_RIGHT)
		rotate_player(keycode, game);
	return (0);
}
