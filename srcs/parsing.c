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
}

static int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || \
			c == '\f' || c == '\r');
}

static int	get_texture(char *line, char *type)
{
	printf("🖼️ Found Texture [%s]: %s", type, line);
	return (1);
}

static int	get_color(char *line, char *type)
{
	printf("🎨 Found Color [%s]: %s", type, line);
	return (1);
}

static int	parse_line(char *line, t_game *game)
{
	int	i;

	(void)game;
	i = 0;
	while (line[i] && is_space(line[i]) && line[i] != '\n')
		i++;
	if (!line[i] || line[i] == '\n')
		return (1);
	if (!ft_strncmp(line + i, "NO", 2))
		return (get_texture(line + i + 2, "NO"));
	else if (!ft_strncmp(line + i, "SO", 2))
		return (get_texture(line + i + 2, "SO"));
	else if (!ft_strncmp(line + i, "WE", 2))
		return (get_texture(line + i + 2, "WE"));
	else if (!ft_strncmp(line + i, "EA", 2))
		return (get_texture(line + i + 2, "EA"));
	else if (!ft_strncmp(line + i, "F", 1))
		return (get_color(line + i + 1, "F"));
	else if (!ft_strncmp(line + i, "C", 1))
		return (get_color(line + i + 1, "C"));
	else if (line[i] == '1' || line[i] == '0')
	{
		printf("🗺️ Map Content Found: %s", line);
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

int	parse_map(char *file, t_game *game)
{
	if (!check_file_name(file))
		return (printf(ERR_FILE), 0);
	init_map_info(game);
	if (!read_file(file, game))
		return (printf(ERR_FILE), 0);
	printf("✅ Map Parsing Finished (Test)\n");
	return (1);
}
