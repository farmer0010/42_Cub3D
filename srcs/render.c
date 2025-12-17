/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewonki <taewonki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 12:40:12 by taewonki          #+#    #+#             */
/*   Updated: 2025/12/17 13:18:07 by taewonki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
1. mlx_new_image()
2. 바닥이랑 벽이랑 지정된 색으로 먼저 싹 칠하기
3.
*/

void	my_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

// 방어 코드: 화면 밖 좌표는 무시 (선택 사항이지만 권장)
	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return;
	// 이미지 데이터의 시작 주소(addr)에서 정확한 오프셋만큼 이동하여 색상 값을 씀
	// y * line_length: y번째 줄의 시작점
	// x * (bpp / 8): x번째 픽셀의 위치 (bits_per_pixel을 8로 나눠 바이트 단위로 변환)
	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int*)dst = color;
}

int	init_screen_info(t_game *g)
{
	g->screen.img = mlx_new_image(g->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!g->screen.img)
		return (0);
	g->screen.addr = mlx_get_data_addr(g->screen.img, &g->screen.bpp, &g->screen.line_length, &g->screen.endian);
	return (1);
}

void draw_vertical_line(t_game *game, t_ray *ray, int x)
{
    int y;
    int wall_color;

    // 1. 벽 색상 결정 (테스트용: 단색)
    // side == 0 (X축 벽): 빨간색
    // side == 1 (Y축 벽): 초록색 (또는 그림자 효과를 위해 더 어두운 색)
    if (ray->side == 0)
        wall_color = 0x00FF0000; // Red
    else
        wall_color = 0x0000FF00; // Green

    // 2. 그리기 시작 (y = 0 부터 맨 아래까지)
    y = 0;

    // (A) 천장 그리기 (0 ~ draw_start 전까지)
    while (y < ray->draw_start)
    {
        my_pixel_put(&game->screen, x, y, game->map.ceil_color);
        y++;
    }

    // (B) 벽 그리기 (draw_start ~ draw_end 전까지)
    while (y < ray->draw_end)
    {
        my_pixel_put(&game->screen, x, y, wall_color);
        y++;
    }

    // (C) 바닥 그리기 (draw_end ~ 화면 끝까지)
    while (y < WIN_HEIGHT)
    {
        my_pixel_put(&game->screen, x, y, game->map.floor_color);
        y++;
    }
}
