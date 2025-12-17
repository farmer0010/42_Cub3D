/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewonki <taewonki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 12:40:12 by taewonki          #+#    #+#             */
/*   Updated: 2025/12/13 13:15:35 by taewonki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
1. mlx_new_image()
2. 바닥이랑 벽이랑 지정된 색으로 먼저 싹 칠하기
3.
*/

void my_pixel_put(t_img *img, int x, int y, int color)
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

void	init_screen(t_game *g)
{
	g->screen.img = mlx_new_image(g->mlx, WIN_WIDTH, WIN_HEIGHT);
	g->screen.addr = mlx_get_data_addr(g->screen.img, &g->screen.bpp, &g->screen.line_length, &g->screen.endian);
}
