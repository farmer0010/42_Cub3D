/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements_color.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juyoukim <juyoukim@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 09:51:24 by juyoukim          #+#    #+#             */
/*   Updated: 2025/12/18 10:51:26 by juyoukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
	return (cnt == 2);
}

static int	is_pure_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i] && is_space(str[i]))
		i++;
	if (!str[i])
		return (0);
	while (str[i] && ft_isdigit(str[i]))
		i++;
	while (str[i] && is_space(str[i]))
		i++;
	if (str[i] != '\0')
		return (0);
	return (1);
}

static int	convert_rgb(char **colors, int *rgb)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (!colors[i] || !is_pure_digit(colors[i]))
			return (0);
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

	(void)game;
	if (*target != -1)
		return (printf("Error\nDuplicate color defined\n"), 0);
	if (!check_comma(line))
		return (printf("Error\nInvalid color format (Commas)\n"), 0);
	colors = ft_split(line, ',');
	if (!colors)
		return (printf(ERR_MALLOC), 0);
	if (!colors[0] || !colors[1] || !colors[2] || colors[3]
		|| !convert_rgb(colors, rgb))
	{
		free_split(colors);
		return (printf("Error\nInvalid RGB value or format\n"), 0);
	}
	free_split(colors);
	*target = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
	return (1);
}
