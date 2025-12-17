/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewonki <taewonki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 15:42:45 by taewonki          #+#    #+#             */
/*   Updated: 2025/12/13 13:17:42 by taewonki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	raycast(t_game *game)
{
	t_ray	ray;

	init_ray_info(&ray);
	while(1)
	{
		int	x;

		x = -1;
		while (++x < WIN_WIDTH)
		{
			dda_algo(game, &ray, x);
			// 여기서부터 대충 이미지 찍어보기
			int y = 0;
			while (y < ray.draw_start)
			{
				my_pixel_put(&game->screen, x, y, game->map.ceil_color);
				y++;
			}
			init_screen(game);
			int color;
			if (ray.side == 1)
				color = 0x00FF0000;
			else
				color = 0x0000FF00;
			// (B) 벽 그리기
			y = ray.draw_start;
			while (y < ray.draw_end)
			{
				// 헬퍼 함수를 사용해 game->screen에 색을 칠함
				my_pixel_put(&game->screen, x, y, color);
				y++;
			}

			// (C) 바닥 그리기 (배경을 미리 안 칠했다면 여기서)
			while (y < WIN_HEIGHT)
			{
				my_pixel_put(&game->screen, x, y, game->map.floor_color);
				y++;
			}
		}
	}
}
