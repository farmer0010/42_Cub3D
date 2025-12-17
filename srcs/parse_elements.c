/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewonki <taewonki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 07:45:39 by juyoukim          #+#    #+#             */
/*   Updated: 2025/12/17 13:29:46 by taewonki         ###   ########.fr       */
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

static int	check_comma(char *line)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	while (line[i])
	{
		if (line[i] == ',')
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

int	get_color(char *line, int *target, t_game *game)
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
		return (printf("Error\nColor value invalid (0-255)\n"), 0);
	}
	free_split(colors);
	*target = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
	return (1);
}
