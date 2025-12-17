/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juyoukim <juyoukim@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 12:55:24 by juyoukim          #+#    #+#             */
/*   Updated: 2025/12/08 12:55:29 by juyoukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	close_game(t_game *game)
{
	if (game -> win)
		mlx_destroy_window(game -> mlx, game -> win);
	exit(0);
	return (0);
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == K_ESC)
		close_game(game);
	return (0);
}

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
	{
		printf(ERR_ARGS);
		return (1);
	}
	if (!parse_map(av[1], &game))
		return (1);
	(void)av;
	game.mlx = mlx_init();
	if (!game.mlx)
		return (printf(ERR_MALLOC), 1);
	game.win = mlx_new_window(game.mlx, WIN_WIDTH, WIN_HEIGHT, "cub3d");
	if (!game.win)
		return (printf(ERR_MALLOC), 1);
	mlx_hook(game.win, 2, 1L << 0, key_press, &game);
	mlx_hook(game.win, 17, 0, close_game, &game);
	mlx_loop(game.mlx);
	return (0);
}
