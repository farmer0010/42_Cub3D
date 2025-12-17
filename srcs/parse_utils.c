/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewonki <taewonki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 13:39:03 by juyoukim          #+#    #+#             */
/*   Updated: 2025/12/17 12:09:41 by taewonki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_extension(char *file, char *ext)
{
	size_t	len;
	size_t	ext_len;

	if (!file || !ext)
		return (0);
	len = ft_strlen(file);
	ext_len = ft_strlen(ext);
	if (len < ext_len)
		return (0);
	if (ft_strncmp(file + len - ext_len, ext, ext_len) != 0)
		return (0);
	return (1);
}

int	check_file_name(char *file)
{
	return (check_extension(file, ".cub"));
}

void	init_map_info(t_game *game)
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

void	init_ray_info(t_ray *ray)
{
	ray->camera_x = 0;
	ray->ray_dir_x = 0;
	ray->ray_dir_y = 0;
	ray->map_x = 0;
	ray->map_y = 0;
	ray->side_dist_x = 0;
	ray->side_dist_y = 0;
	ray->delta_dist_x = 0;
	ray->delta_dist_y = 0;
	ray->perp_wall_dist = 0;
	ray->step_x = 0;
	ray->step_y = 0;
	ray->hit = 0;
	ray->side = 0;
	ray->line_height = 0;
	ray->draw_start = 0;
	ray->draw_end = 0;
}

int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r');
}

void	free_split(char **split)
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
