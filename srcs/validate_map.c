/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juyoukim <juyoukim@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 13:01:15 by juyoukim          #+#    #+#             */
/*   Updated: 2025/12/10 13:01:18 by juyoukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_map_grid(char **grid)
{
	int	i;

	if (!grid)
		return ;
	i = 0;
	while(grid[i])
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

	new_map = (char **)malloc(sizeof(char *) * (game->map.height + 1));
	if(! new_map)
		return (NULL);
	i = 0;
	while (i < game->map.height)
	{
		new_map[i] = ft_strdup(game->map.grid[i]);
		if (!new_map[i])
		{
			free_map_grid(new_map);
			return (NULL);
		}
		i++;
	}
	new_map[i] = NULL;
	return (new_map);
}

static int	flood_fill(t_game *game, int x, int y, char **map)
{
	if (x < 0 || y < 0 || y > game->map.height || \
		x >= (int)ft_strlen(map[y]))
		return (0);
	if (map[y][x] == '1' || map[y][x] == 'V')
		return (1);
	if (map[y][x] == ' ')
		return (0);
	map[y][x] = 'V';
	if (!flood_fill(game, x + 1, y, map) || \
		!flood_fill(game, x - 1, y, map) || \
		!flood_fill(game, x, y + 1, map) || \
		!flood_fill(game, x, y - 1, map))
		return (0);
	return (1);
}

int	validate_map(t_game *game)
{
	char	**map_copy;
	int		p_x;
	int		p_y;

	map_copy = copy_map(game);
	if (!map_copy)
		return (printf(ERR_MALLOC), 0);
	p_x = (int)game->player.pos_x;
	p_y = (int)game->player.pos_y;
	if (!flood_fill(game, p_x, p_y, map_copy))
	{
		free_map_grid(map_copy);
		return (printf("Error\nMap is not enclosed by walls\n"), 0);
	}

	printf("✅ Map Validation Success! (Map is closed)\n");
	free_map_grid(map_copy);
	return (1);
}
