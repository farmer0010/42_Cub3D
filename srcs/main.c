/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewonki <taewonki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 12:55:24 by juyoukim          #+#    #+#             */
/*   Updated: 2025/12/19 09:47:07 by taewonki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int ac, char **av)
{
	t_game	game;

	ft_memset(&game, 0, sizeof(t_game));
	if (ac != 2)
	{
		printf(ERR_ARGS);
		return (1);
	}
	if (!parse_map(av[1], &game))
		return (1);
	game.mlx = mlx_init();
	if (!game.mlx)
		return (printf(ERR_MALLOC), 1);
	if (!init_textures(&game))
		return (1);
	game.win = mlx_new_window(game.mlx, WIN_WIDTH, WIN_HEIGHT, "cub3d");
	if (!game.win)
		return (printf(ERR_MALLOC), 1);
	init_screen_info(&game);
	mlx_loop_hook(game.mlx, &main_loop, &game);
	mlx_hook(game.win, 2, 1L << 0, key_press, &game);
	mlx_hook(game.win, 17, 0, close_game, &game);
	mlx_loop(game.mlx);
	return (0);
}
