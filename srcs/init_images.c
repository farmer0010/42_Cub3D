/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juyoukim <juyoukim@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 09:19:23 by juyoukim          #+#    #+#             */
/*   Updated: 2025/12/18 11:00:27 by juyoukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	load_texture(t_game *game, t_img *img, char *path)
{
	img->img = mlx_xpm_file_to_image(game->mlx, path, &img->width,
			&img->height);
	if (!img->img)
	{
		printf("Error\nInvalid texture content or path: %s\n", path);
		return (0);
	}
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->line_length,
			&img->endian);
	return (1);
}

int	init_textures(t_game *game)
{
	if (!load_texture(game, &game->textures[0], game->map.no_path)
		|| !load_texture(game, &game->textures[1], game->map.so_path)
		|| !load_texture(game, &game->textures[2], game->map.we_path)
		|| !load_texture(game, &game->textures[3], game->map.ea_path))
	{
		printf("Error\nTexture loading failed\n");
		exit_game(game);
	}
	return (1);
}
