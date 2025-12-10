/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juyoukim <juyoukim@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 13:38:53 by juyoukim          #+#    #+#             */
/*   Updated: 2025/12/10 13:38:55 by juyoukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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

int	parse_line(char *line, t_game *game)
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
