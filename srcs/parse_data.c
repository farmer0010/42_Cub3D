/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juyoukim <juyoukim@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 15:38:53 by juyoukim          #+#    #+#             */
/*   Updated: 2025/12/10 19:10:00 by juyoukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	get_texture(char *line, char **target, t_game *game)
{
	char	*path;
	int		i;
	int		len;
	int		fd;

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
	if (! check_extension(path, ".xpm"))
	{
		free(path);
		return (printf("Error\nInvalid texture extension (must be .xpm)\n"), 0);
	}
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		free(path);
		return (printf("Error\nTexture file not found or cannot open: %s\n", line), 0);
	}
	close(fd);
	*target = path;
	return (1);
}

static int	check_comma(char *line)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	while (line[i])
	{
		if (line[i] = ',')
			cnt++;
		i++;
	}
	if (cnt != 2)
		return (0);
	return (1);
}

static int	convert_rgb(char **colors, int *rgb)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		rgb[i] = ft_atoi(colors[i]);
		if (rgb[i] < 0 || rgb[i] > 255)
			return (0);
		i++;
	}
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
	if (!check_comma(line))
		return (printf("Error\nInvalid color format (Check commas)\n"), 0);
	colors = ft_split(line, ',');
	if (!colors)
		return (printf(ERR_MALLOC), 0);
	i = 0;
	while (colors[i])
		i++;
	if (i != 3 || !convert_rgb(colors, rgb))
	{
		free_split(colors);
		if (i != 3)
			return (printf(ERR_RGB), 0);
		return (printf("Error\nColor value out of range (0-255)\n"), 0);
	}
	free_split(colors);
	*target = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
	return (1);
}

static int	match_identifier(char *ptr, t_game *game)
{
	if (!ft_strncmp(ptr, "NO", 2))
		return (get_texture(ptr + 2, &game->map.no_path, game));
	else if (!ft_strncmp(ptr, "SO", 2))
		return (get_texture(ptr + 2, &game->map.so_path, game));
	else if (!ft_strncmp(ptr, "WE", 2))
		return (get_texture(ptr + 2, &game->map.we_path, game));
	else if (!ft_strncmp(ptr, "EA", 2))
		return (get_texture(ptr + 2, &game->map.ea_path, game));
	else if (!ft_strncmp(ptr, "F", 1))
		return (get_color(ptr + 1, &game->map.floor_color, game));
	else if (!ft_strncmp(ptr, "C", 1))
		return (get_color(ptr + 1, &game->map.ceil_color, game));
	return (-1);
}

int	parse_line(char *line, t_game *game)
{
	int	i;
	int	res;

	i = 0;
	while (line[i] && is_space(line[i]) && line[i] != '\n')
		i++;
	if (!line[i] || line[i] == '\n')
	{
		if (game->map.map_flag == 1)
			game->map.map_flag = 2;
		return (1);
	}
	res = match_identifier(line + i, game);
	if (res != -1)
	{
		if (game->map.map_flag >= 1)
			return (printf("Error\nTexture/Color found after map start\n"), 0);
		return (res);
	}
	else if (line[i] == '1' || line[i] == '0')
	{
		if (game->map.map_flag == 2)
			return (printf("Error\nMap is split by empty lines\n"), 0);
		game->map.map_flag = 1;
		game->map.raw_data = gnl_strjoin(game->map.raw_data, line);
		if (!game->map.raw_data)
			return (printf(ERR_MALLOC), 0);
		return (1);
	}
	return (printf("Error\nUnknown identifier: %s\n", line), 0);
}
