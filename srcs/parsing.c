/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juyoukim <juyoukim@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 13:24:44 by juyoukim          #+#    #+#             */
/*   Updated: 2025/12/10 14:24:48 by juyoukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
	if (!process_map(game))
		return (0);
	if (!parse_player(game))
		return (0);
	if (!validate_map(game))
		return (0);
	return (1);
}
