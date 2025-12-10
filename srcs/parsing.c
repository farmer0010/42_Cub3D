/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juyoukim <juyoukim@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 13:24:44 by juyoukim          #+#    #+#             */
/*   Updated: 2025/12/08 13:24:48 by juyoukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	check_file_name(char *file)
{
	size_t	len;

	len = ft_strlen(file);
	if (len < 4)
		return (0);
	if (ft_strncmp(file + len - 4, ".cub", 4) != 0)
		return (0);
	return (1);
}

static void	init_map_info(t_game *game)
{
	game->map.so_path = NULL;
	game->map.no_path = NULL;
	game->map.ea_path = NULL;
	game->map.we_path = NULL;
	game->map.ceil_color = -1;
	game->map.floor_color = -1;
	game->map.grid = NULL;
	game->map.width = 0;
	game->map.height = 0;
	game->map.raw_data = NULL;
}

static int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r');
}

static void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

static int	get_texture(char *line, char **target, t_game *game)
{
	char	*path;
	int		i;
	int		len;

	(void)game;
	if (*target != NULL)
		return (printf("Error\nDuplicate texture found\n"), 0);
	i = 0;
	while (line[i] && is_space(line[i]))
		i++;
	path = ft_strdup(line + i);
	if (!path)
		return (printf(ERR_MALLOC), 0);
	len = ft_strlen(path);
	if (len > 0 && path[len - 1] == '\n')
		path[len - 1] = '\0';
	*target = path;
	return (1);
}

static int	get_color(char *line, int *target, t_game *game)
{
	char	**colors;
	int		rgb[3];
	int		i;

	(void)game;
	if (*target != -1)
		return (printf("Error\nDuplicate color defined\n"), 0);
	colors = ft_split(line, ',');
	if (!colors)
		return (printf(ERR_MALLOC), 0);
	i = 0;
	while (colors[i])
		i++;
	if (i != 3)
	{
		free_split(colors);
		return (printf(ERR_RGB), 0);
	}
	i = 0;
	while (i < 3)
	{
		rgb[i] = ft_atoi(colors[i]);
		if (rgb[i] < 0 || rgb[i] > 255)
		{
			free_split(colors);
			return (printf("Error\nColor value out of range (0-255)\n"), 0);
		}
		i++;
	}
	free_split(colors);
	*target = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
	return (1);
}

static int	parse_line(char *line, t_game *game)
{
	int	i;

	i = 0;
	while (line[i] && is_space(line[i]) && line[i] != '\n')
		i++;
	if (!line[i] || line[i] == '\n')
		return (1);
	if (!ft_strncmp(line + i, "NO", 2))
		return (get_texture(line + i + 2, &game->map.no_path, game));
	else if (!ft_strncmp(line + i, "SO", 2))
		return (get_texture(line + i + 2, &game->map.so_path, game));
	else if (!ft_strncmp(line + i, "WE", 2))
		return (get_texture(line + i + 2, &game->map.we_path, game));
	else if (!ft_strncmp(line + i, "EA", 2))
		return (get_texture(line + i + 2, &game->map.ea_path, game));
	else if (!ft_strncmp(line + i, "F", 1))
		return (get_color(line + i + 1, &game->map.floor_color, game));
	else if (!ft_strncmp(line + i, "C", 1))
		return (get_color(line + i + 1, &game->map.ceil_color, game));
	else if (line[i] == '1' || line[i] == '0')
	{
		game->map.raw_data = gnl_strjoin(game->map.raw_data, line);
		if (!game->map.raw_data)
			return (printf(ERR_MALLOC), 0);
		return (1);
	}
	return (printf("Error\nUnknown identifier: %s\n", line), 0);
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
			close(fd);
			return (0);
		}
		free(line);
	}
	close(fd);
	return (1);
}

static int	process_map(t_game *game)
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

static void	init_dir_plane(t_game *game, char p)
{
	if (p == 'N')
	{
		game->player.dir_x = 0;
		game->player.dir_y = -1;
		game->player.plane_x = 0.66;
		game->player.plane_y = 0;
	}
	else if (p == 'S')
	{
		game->player.dir_x = 0;
		game->player.dir_y = 1;
		game->player.plane_x = -0.66;
		game->player.plane_y = 0;
	}
	else if (p == 'W')
	{
		game->player.dir_x = -1;
		game->player.dir_y = 0;
		game->player.plane_x = 0;
		game->player.plane_y = -0.66;
	}
	else if (p == 'E')
	{
		game->player.dir_x = 1;
		game->player.dir_y = 0;
		game->player.plane_x = 0;
		game->player.plane_y = 0.66;
	}
}

static int	parse_player(t_game *game)
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
			if (ft_strchr("NESW", game->map.grid[y][x]))
			{
				game->player.pos_x = x + 0.5;
				game->player.pos_y = y + 0.5;
				init_dir_plane(game, game->map.grid[y][x]);
				game->map.grid[y][x] = '0';
				count++;
			}
			x++;
		}
		y++;
	}
	if (count != 1)
		return (printf("Error\nInvalid player count: %d\n", count), 0);
	return (1);
}

int	parse_map(char *file, t_game *game)
{
	if (!check_file_name(file))
		return (printf(ERR_FILE), 0);
	init_map_info(game);
	if (!read_file(file, game))
		return (printf(ERR_FILE), 0);
	if (!process_map(game))
		return (0);
	if (!parse_player(game))
		return (0);
	if (!validate_map(game))
        return (0);

	printf("\n=== Parsing Result Check ===\n");
	printf("NO: [%s]\n", game->map.no_path);
	printf("SO: [%s]\n", game->map.so_path);
	printf("WE: [%s]\n", game->map.we_path);
	printf("EA: [%s]\n", game->map.ea_path);
	printf("Floor Color: %d (Hex: %X)\n", game->map.floor_color, game->map.floor_color);
	printf("Ceil Color:  %d (Hex: %X)\n", game->map.ceil_color, game->map.ceil_color);
	printf("--- Raw Map Data ---\n%s\n--------------------\n", game->map.raw_data);
	printf("===============================\n");
	printf("\n=== Map & Player Processed ===\n");
	printf("Map Size: %d x %d\n", game->map.width, game->map.height);
	printf("Player Pos: (%.2f, %.2f)\n", game->player.pos_x, game->player.pos_y);
	printf("Player Dir: (%.2f, %.2f)\n", game->player.dir_x, game->player.dir_y);
	printf("===============================\n");

	return (1);
}

