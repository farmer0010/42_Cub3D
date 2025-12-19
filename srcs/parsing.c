/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewonki <taewonki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 13:24:44 by juyoukim          #+#    #+#             */
/*   Updated: 2025/12/19 10:29:00 by taewonki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	check_missing_info(t_game *game)
{
	if (!game->map.no_path || !game->map.so_path
		|| !game->map.we_path || !game->map.ea_path)
		return (printf("Error\nMissing texture path(s)\n"), 0);
	if (game->map.floor_color == -1 || game->map.ceil_color == -1)
		return (printf("Error\nMissing color(s)\n"), 0);
	return (1);
}

static void	drain_gnl(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
}

static int	read_file(char *file, t_game *game)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (0);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (!parse_line(line, game))
		{
			free(line);
			drain_gnl(fd);
			close(fd);
			return (0);
		}
		free(line);
	}
	close(fd);
	return (1);
}

void	free_all_data(t_game *game)
{
	if (game->map.no_path)
		free(game->map.no_path);
	if (game->map.so_path)
		free(game->map.so_path);
	if (game->map.we_path)
		free(game->map.we_path);
	if (game->map.ea_path)
		free(game->map.ea_path);
	if (game->map.raw_data)
		free(game->map.raw_data);
	if (game->map.grid)
		free_map_grid(game->map.grid);
}

int	parse_map(char *file, t_game *game)
{
	init_map_info(game);
	if (!check_extension(file, ".cub"))
		return (printf("Error\nInvalid extension\n"), 0);
	if (!read_file(file, game))
	{
		free_all_data(game);
		return (0);
	}
	if (!check_missing_info(game) || !process_map(game)
		|| !validate_map(game) || !parse_player(game))
	{
		free_all_data(game);
		return (0);
	}
	return (1);
}
