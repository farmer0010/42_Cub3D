/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juyoukim <juyoukim@student.42gyeongsa>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 11:48:12 by juyoukim          #+#    #+#             */
/*   Updated: 2025/12/08 11:48:16 by juyoukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"
# include "get_next_line.h"

# define WIN_WIDTH 1280
# define WIN_HEIGHT 720
# define TEX_WIDTH 64
# define TEX_HEIGHT 64

# define K_ESC 65307
# define K_W 119
# define K_A 97
# define K_S 115
# define K_D 100
# define K_LEFT 65361
# define K_RIGHT 65363

# define ERR_MALLOC "Error\nMemory allocation failed\n"
# define ERR_ARGS "Error\nInvalid number of arguments\n"
# define ERR_FILE "Error\nCannot open file\n"
# define ERR_MAP "Error\nInvalid map configuration\n"
# define ERR_TEX "Error\nInvalid texture path\n"
# define ERR_RGB "Error\nInvalid color format\n"

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	int		floor_color;
	int		ceil_color;
	char	*raw_data;
	int		map_flag;
}	t_map;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_ray
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
}	t_ray;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_map		map;
	t_player	player;
	t_ray		ray;
	t_img		screen;
	t_img		textures[4];
}	t_game;

/* main.c */
int		close_game(t_game *game);

/* parsing.c */
int		parse_map(char *file, t_game *game);

/* parse_utils.c */
int		check_extension(char *file, char *ext);
int		check_file_name(char *file);
void	init_map_info(t_game *game);
int		is_space(char c);
void	free_split(char **split);

/* parse_data.c */
int		parse_line(char *line, t_game *game);

/* parse_elements.c */
int		get_texture(char *line, char **target, t_game *game);
int		get_color(char *line, int *target, t_game *game);

/* parse_map.c */
int		process_map(t_game *game);
int		parse_player(t_game *game);

/* validate_map.c */
int		validate_map(t_game *game);

#endif
