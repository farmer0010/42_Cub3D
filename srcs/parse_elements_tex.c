/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements_tex.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juyoukim <juyoukim@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 08:49:55 by juyoukim          #+#    #+#             */
/*   Updated: 2025/12/18 10:52:56 by juyoukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	validate_texture(char *path)
{
	int	fd;

	if (!check_extension(path, ".xpm"))
		return (printf("Error\nInvalid extension (must be .xpm)\n"), 0);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (printf("Error\nTexture not found: %s\n", path), 0);
	close(fd);
	return (1);
}

int	get_texture(char *line, char **target, t_game *game)
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
	if (!validate_texture(path))
	{
		free(path);
		return (0);
	}
	*target = path;
	return (1);
}
