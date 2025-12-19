/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juyoukim <juyoukim@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 15:38:53 by juyoukim          #+#    #+#             */
/*   Updated: 2025/12/17 12:10:00 by juyoukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	match_identifier(char *ptr, t_game *game)
{
	if (!ft_strncmp(ptr, "NO", 2) && is_space(ptr[2]))
		return (get_texture(ptr + 2, &game->map.no_path, game));
	else if (!ft_strncmp(ptr, "SO", 2) && is_space(ptr[2]))
		return (get_texture(ptr + 2, &game->map.so_path, game));
	else if (!ft_strncmp(ptr, "WE", 2) && is_space(ptr[2]))
		return (get_texture(ptr + 2, &game->map.we_path, game));
	else if (!ft_strncmp(ptr, "EA", 2) && is_space(ptr[2]))
		return (get_texture(ptr + 2, &game->map.ea_path, game));
	else if (!ft_strncmp(ptr, "F", 1) && is_space(ptr[1]))
		return (get_color(ptr + 1, &game->map.floor_color, game));
	else if (!ft_strncmp(ptr, "C", 1) && is_space(ptr[1]))
		return (get_color(ptr + 1, &game->map.ceil_color, game));
	return (-1);
}

static int	process_map_content(char *line, t_game *game)
{
	if (game->map.map_flag == 2)
		return (printf("Error\nMap is split by empty lines\n"), 0);
	game->map.map_flag = 1;
	game->map.raw_data = gnl_strjoin(game->map.raw_data, line);
	if (!game->map.raw_data)
		return (printf(ERR_MALLOC), 0);
	return (1);
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
			return (printf("Error\nTexture/Color found after map\n"), 0);
		return (res);
	}
	else if (line[i] == '1' || line[i] == '0')
		return (process_map_content(line, game));
	return (printf("Error\nUnknown identifier: %s\n", line), 0);
}
