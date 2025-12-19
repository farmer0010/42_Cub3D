/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juyoukim <juyoukim@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 11:39:15 by juyoukim          #+#    #+#             */
/*   Updated: 2025/12/17 09:38:02 by juyoukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	process_map(t_game *game)
{
	int	i;
	int	len;

	if (!game->map.raw_data)
		return (printf("Error\nMap data not found\n"), 0);
	game->map.grid = ft_split(game->map.raw_data, '\n');
	if (!game->map.grid)
		return (printf(ERR_MALLOC), 0);
	i = 0;
	game->map.width = 0;
	while (game->map.grid[i])
	{
		len = ft_strlen(game->map.grid[i]);
		if (len > game->map.width)
			game->map.width = len;
		i++;
	}
	game->map.height = i;
	return (1);
}

static void	init_player_vectors(t_game *game)
{
	game->player.dir_x = 0;
	game->player.dir_y = 0;
	game->player.plane_x = 0;
	game->player.plane_y = 0;
}

static void	init_dir_plane(t_game *game, char p)
{
	init_player_vectors(game);
	if (p == 'N')
	{
		game->player.dir_y = -1;
		game->player.plane_x = 0.66;
	}
	else if (p == 'S')
	{
		game->player.dir_y = 1;
		game->player.plane_x = -0.66;
	}
	else if (p == 'E')
	{
		game->player.dir_x = 1;
		game->player.plane_y = 0.66;
	}
	else if (p == 'W')
	{
		game->player.dir_x = -1;
		game->player.plane_y = -0.66;
	}
}

static void	handle_player_pos(t_game *game, int x, int y, int *count)
{
	if (ft_strchr("NESW", game->map.grid[y][x]))
	{
		game->player.pos_x = x + 0.5;
		game->player.pos_y = y + 0.5;
		init_dir_plane(game, game->map.grid[y][x]);
		game->map.grid[y][x] = '0';
		(*count)++;
	}
}

int	parse_player(t_game *game)
{
	int	x;
	int	y;
	int	count;

	count = 0;
	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (game->map.grid[y][x])
		{
			handle_player_pos(game, x, y, &count);
			x++;
		}
		y++;
	}
	if (count != 1)
		return (printf("Error\nInvalid player count: %d\n", count), 0);
	return (1);
}
