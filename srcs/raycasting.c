/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewonki <taewonki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 15:42:45 by taewonki          #+#    #+#             */
/*   Updated: 2025/12/13 12:00:27 by taewonki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
t_game 내부 요소
t_map map => 맵의 정보 / 텍스쳐 경로 / 바닥 천장 색
t_player player => 플레이어 위치벡터(x,y), 플레이어 방향벡터(x,y), 카메라 평면 벡터(x,y)
t_ray ray
- camera_x : 현재 쏘는 광선의 시야의 양 끝중에서 어디에 위치하는지를 나타내는 비율 값
if camera_x == -1 : 카메라 평면의 가장 왼쪽
else if camera_x == 0 : 플레이어가 바라보는 정면
else if camera_x == 1 : 카메라 평면의 가장 오른쪽
- ray_dir_x, y => 광선의 방향벡터
- map_x,y => 실수 위치벡터와 비교할 실제 정수 맵의 좌표
- sidedist_x,y = 해당 방향 벡터로 갔을때 처음 x를 만나는 점과 처음 y를 만나는 점
*/
int	raycast(t_game *game)
{
	t_ray	ray;

	init_ray_info(&ray);
	while(1)
	{
		int	x;

		x = -1;
		while (++x < WIN_WIDTH)
		{
			ray.camera_x = (2 * x / (double)WIN_WIDTH) - 1;
			// 전체 화면 너비에서 내가 쏘려는 광선의 방향을 계산 -1 ~ 1
			ray.ray_dir_x = game->player.dir_x + game->player.plane_x * ray.camera_x;
			ray.ray_dir_y = game->player.dir_y + game->player.plane_y * ray.camera_x;
			// 위에서 구한 비율 정보를 바탕으로 실제 ray의 방향벡터를 구한다.
			ray.map_x = (int)game->player.pos_x;
			ray.map_y = (int)game->player.pos_y;
			// 플레이어가 현재 위치한 맵의 한 칸 정보를 저장
			ray.delta_dist_x = fabs(1 / ray.ray_dir_x);
			ray.delta_dist_y = fabs(1 / ray.ray_dir_y);
			// delta_dist_x => x가 1 증가하는 동안 벡터의 크기
			// delta_dist_y => y가 1 증가하는 동안 벡터의 크기
			ray.hit = 0;
			if (ray.ray_dir_x < 0)
			{
				ray.step_x = -1;
				ray.side_dist_x = (game->player.pos_x - ray.map_x) * ray.delta_dist_x;
			}
			else
			{
				ray.step_x = 1;
				ray.side_dist_x = (ray.map_x + 1.0 - game->player.pos_x)* ray.delta_dist_x;
			}
			if (ray.ray_dir_y < 0)
			{
				ray.step_y = -1;
				ray.side_dist_y = (game->player.pos_y - ray.map_y) * ray.delta_dist_y;
			}
			else
			{
				ray.step_y = 1;
				ray.side_dist_y = (ray.map_y + 1 - game->player.pos_y) * ray.delta_dist_y;
			}
			// side_dist + step 1,2 값 계산
			while (ray.hit == 0)
			// 벽이 아닌 경우 루프 걔속 돌리기
			{
				if (ray.side_dist_x < ray.side_dist_y)
				{
					ray.side_dist_x += ray.delta_dist_x;
					ray.map_x += ray.step_x;
					ray.side = 0;
				}
				// side_dist_x 가 y보다 짧은 경우, x를 기준으로 한칸씩 전진하면서 벽 탐색
				// 그리고 x축 방향으로(수평으로) 갔기 때문에 side = 0으로 한다
				else
				{
					ray.side_dist_y += ray.delta_dist_y;
					ray.map_y += ray.step_y;
					ray.side = 1;
				}
				// 반대의 경우 y를 기준으로 한칸씩 전진하면서 벽 탐색
				// 그리고 y축 방향으로 갔기 때문에 side = 1 로 한다
				if (game->map.grid[ray.map_y][ray.map_x] == '1')
					ray.hit = 1;
				// 위 루프 통과 후 거기가 벽인지 검사
			}
			if (ray.side == 0)
				ray.perp_wall_dist = (ray.map_x - game->player.pos_x + (1 - ray.step_x) / 2) / ray.ray_dir_x;
			else
				ray.perp_wall_dist = (ray.map_y - game->player.pos_y + (1 - ray.step_y) / 2) / ray.ray_dir_y;
			// 여기서 나누기 0 하는거 처리 해줘야함

			// 여기서부터 대충 이미지 찍어보기
			int color;
			if (ray.side == 1)
				color = 0x00FF0000; // 빨강 (Y축 벽, 약간 어둡게 처리하면 입체감 남)
			else
				color = 0x0000FF00;
		}
	}
}
