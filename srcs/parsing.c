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

static int check_file_name(char *file)
{
	size_t	len;

	len = ft_strlen(file);
	if (len < 4)
		return (0);
	if(ft_strncmp(file + len - 4, ".cub", 4))
		return (0);
	return (1);
}

static void	init_map_info(t_game *game)
{
	game -> map.so_path = NULL;
	game -> map.no_path = NULL;
	game -> map.ea_path = NULL;
	game -> map.we_path = NULL;
	game -> map.ceil_color = -1;
	game -> map.floor_color = -1;
	game -> map.grid = NULL;
	game -> map.width = 0;
	game -> map.height = 0;
}

static int	parse_line(char *line, t_game *game)
{
	(void)game;
	printf("Read Line: %s", line);
	return (1);
}

static int	read_file(char *file, t_game *game)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		if(!parse_line(line, game))
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
	if(!check_file_name(file))
		return (printf(ERR_FILE), 0);
	init_map_info(game);
	if (!read_file(file, game))
		return (printf(ERR_FILE), 0);
	return (1);
}
