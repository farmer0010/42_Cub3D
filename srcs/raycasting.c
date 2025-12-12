/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewonki <taewonki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 15:42:45 by taewonki          #+#    #+#             */
/*   Updated: 2025/12/12 15:43:01 by taewonki         ###   ########.fr       */
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
	init_ray_info(game);
	while(1)
	{
		double	x;

		while (x < WIN_WIDTH)
		{
			game->ray.camera_x = (2 * x / (double)WIN_WIDTH) - 1;
			// 전체 화면 너비에서 내가 쏘려는 광선의 방향을 계산 -1 ~ 1
			game->ray.ray_dir_x = game->player.dir_x + game->player.plane_x * game->ray.camera_x;
			game->ray.ray_dir_y = game->player.dir_y + game->player.plane_y * game->ray.camera_x;
			// 위에서 구한 비율 정보를 바탕으로 실제 ray의 방향벡터를 구한다.
			game->ray.map_x = (int)game->player.pos_x;
			game->ray.map_y = (int)game->player.pos_y;
			// 플레이어가 현재 위치한 맵의 한 칸 정보를 저장
			game->ray.delta_dist_x = fabs(1 / game->ray.ray_dir_x);
			game->ray.delta_dist_y = fabs(1 / game->ray.ray_dir_y);
			// delta_dist_x => x가 1 증가하는 동안 벡터의 크기
			// delta_dist_y => y가 1 증가하는 동안 벡터의 크기
			game->ray.hit = 0;
			if (game->ray.ray_dir_x < 0)
			{
				game->ray.step_x = -1;
				game->ray.side_dist_x = (game->player.pos_x - game->ray.map_x) * game->ray.delta_dist_x;
			}
			else
			{
				game->ray.step_x = 1;
				game->ray.side_dist_x = (game->ray.map_x + 1.0 - game->player.pos_x)* game->ray.delta_dist_x;
			}
			if (game->ray.ray_dir_y < 0)
			{
				game->ray.step_y = -1;
				game->ray.side_dist_y = (game->player.pos_y - game->ray.map_y) * game->ray.delta_dist_y;
			}
			else
			{
				game->ray.step_y = 1;
				game->ray.side_dist_y = (game->ray.map_y + 1 - game->player.pos_y) * game->ray.delta_dist_y;
			}
			// side_dist + step 1,2 값 계산
			while (game->ray.hit == 0)
			// 벽이 아닌 경우 루프 걔속 돌리기
			{
				if (game->ray.side_dist_x < game->ray.side_dist_y)
				{
					game->ray.side_dist_x += game->ray.delta_dist_x;
					game->ray.map_x += game->ray.step_x;
					game->ray.side = 0;
				}
				// side_dist_x 가 y보다 짧은 경우, x를 기준으로 한칸씩 전진하면서 벽 탐색
				// 그리고 x축 방향으로(수평으로) 갔기 때문에 side = 0으로 한다
				else
				{
					game->ray.side_dist_y += game->ray.delta_dist_y;
					game->ray.map_y += game->ray.step_y;
					game->ray.side = 1;
				}
				// 반대의 경우 y를 기준으로 한칸씩 전진하면서 벽 탐색
				// 그리고 y축 방향으로 갔기 때문에 side = 1 로 한다
				if (game->map.grid[game->ray.map_y][game->ray.map_x] == '1')
					game->ray.hit = 1;
				// 위 루프 통과 후 거기가 벽인지 검사
			}
			if (game->ray.side == 0)
				game->ray.perp_wall_dist = (game->ray.map_x - game->player.pos_x + (1 - game->ray.step_x) / 2) / game->ray.ray_dir_x;
			else
				game->ray.perp_wall_dist = (game->ray.map_y - game->player.pos_y + (1 - game->ray.step_y) / 2) / game->ray.ray_dir_y;
			// 여기서 나누기 0 하는거 처리 해줘야함
		}
	}
}
