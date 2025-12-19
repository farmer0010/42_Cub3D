/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewonki <taewonki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 13:01:15 by juyoukim          #+#    #+#             */
/*   Updated: 2025/12/19 10:57:21 by taewonki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_map_grid(char **grid)
{
	int	i;

	if (!grid)
		return ;
	i = 0;
	while (grid[i])
	{
		free(grid[i]);
		i++;
	}
	free(grid);
}

static char	**copy_map(t_game *game)
{
	char	**new_map;
	int		i;
	int		j;

	new_map = (char **)ft_calloc(game->map.height + 1, sizeof(char *));
	if (! new_map)
		return (NULL);
	i = -1;
	while (++i < game->map.height)
	{
		j = -1;
		new_map[i] = ft_strdup(game->map.grid[i]);
		if (!new_map[i])
		{
			free_map_grid(new_map);
			return (NULL);
		}
		while (new_map[i][++j])
		{
			if (is_space(new_map[i][j]))
				new_map[i][j] = '1';
		}
	}
	new_map[i] = NULL;
	return (new_map);
}

static int	flood_fill(char **map, int x, int y, t_game *game)
{
	if (y < 0 || y >= game->map.height || x < 0)
		return (0);
	if (x >= (int)ft_strlen(map[y]))
		return (0);
	if (map[y][x] == ' ' || map[y][x] == '\0')
		return (0);
	if (map[y][x] == '1' || map[y][x] == 'V')
		return (1);
	map[y][x] = 'V';
	if (!flood_fill(map, x + 1, y, game)
		|| !flood_fill(map, x - 1, y, game)
		|| !flood_fill(map, x, y + 1, game)
		|| !flood_fill(map, x, y - 1, game))
		return (0);
	return (1);
}

static int	check_map_content(t_game *game)
{
	int		x;
	int		y;
	char	c;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (game->map.grid[y][x])
		{
			c = game->map.grid[y][x];
			if (!ft_strchr("01NESW ", c))
				return (printf("Error\nInvalid character in map: '%c'\n", c), 0);
			x++;
		}
		y++;
	}
	return (1);
}

int	validate_map(t_game *game)
{
	char	**map_copy;
	int		p_x;
	int		p_y;

	if (! check_map_content(game))
		return (0);
	map_copy = copy_map(game);
	if (!map_copy)
		return (printf(ERR_MALLOC), 0);
	p_x = (int)game->player.pos_x;
	p_y = (int)game->player.pos_y;
	if (!flood_fill(map_copy, p_x, p_y, game))
	{
		free_map_grid(map_copy);
		return (printf("Error\nMap is not enclosed by walls\n"), 0);
	}
	free_map_grid(map_copy);
	return (1);
}
