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
		free(grid[i++]);
	free(grid);
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
			if (!ft_strchr("01NSEW ", c))
				return (printf("Error\nInvalid map character: '%c'\n", c), 0);
			x++;
		}
		y++;
	}
	return (1);
}

static int	make_rectangular(t_game *game)
{
	char	**new;
	int		i;
	int		max;

	i = -1;
	max = 0;
	while (++i < game->map.height)
		if ((int)ft_strlen(game->map.grid[i]) > max)
			max = ft_strlen(game->map.grid[i]);
	game->map.width = max;
	new = ft_calloc(game->map.height + 1, sizeof(char *));
	if (!new)
		return (0);
	i = -1;
	while (++i < game->map.height)
	{
		new[i] = ft_calloc(max + 1, 1);
		if (!new[i])
			return (free_map_grid(new), 0);
		ft_memset(new[i], ' ', max);
		ft_memcpy(new[i], game->map.grid[i], ft_strlen(game->map.grid[i]));
	}
	free_map_grid(game->map.grid);
	game->map.grid = new;
	return (1);
}

static int	is_enclosed(t_game *game, int x, int y)
{
	if (x == 0 || x == game->map.width - 1 || y == 0
		|| y == game->map.height - 1)
		return (0);
	if (game->map.grid[y - 1][x] == ' ' || game->map.grid[y + 1][x] == ' '
		|| game->map.grid[y][x - 1] == ' ' || game->map.grid[y][x + 1] == ' ')
		return (0);
	return (1);
}

int	validate_map(t_game *game)
{
	int	x;
	int	y;

	if (!check_map_content(game))
		return (0);
	if (!make_rectangular(game))
		return (printf(ERR_MALLOC), 0);
	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			if (ft_strchr("0NSEW", game->map.grid[y][x]))
			{
				if (!is_enclosed(game, x, y))
					return (printf("Error\nMap not enclosed at %d,%d\n"
							, x, y), 0);
			}
			x++;
		}
		y++;
	}
	return (1);
}
