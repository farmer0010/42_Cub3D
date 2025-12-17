/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewonki <taewonki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 12:07:49 by taewonki          #+#    #+#             */
/*   Updated: 2025/12/13 12:29:55 by taewonki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	dda_algo(t_game *g, t_ray *r, int x);
void	calculate_side_dist_xy(t_game *g, t_ray *r);
void	is_hit(t_game *g, t_ray *r);

void	dda_algo(t_game *g, t_ray *r, int x)
{
	r->camera_x = (2 * x / (double)WIN_WIDTH) - 1;
	// 전체 화면 중 현재 내가 쏘는 광선이 화면 중 어느 정도(비율)에 있는지의 값을 계산
	r->ray_dir_x = g->player.dir_x + g->player.plane_x * r->camera_x;
	r->ray_dir_y = g->player.dir_y + g->player.plane_y * r->camera_x;
	// 위에서 구한 비율 정보를 바탕으로 현재 쏘는 광선의 방향벡터를 계산
	r->map_x = (int)g->player.pos_x;
	r->map_y = (int)g->player.pos_y;
	// 현재 플레이어가 있는 실수좌표를 정수 좌표값으로 변환한다 이건 나중에 벽 충돌 로직에서 사용
	r->delta_dist_x = fabs(1 / r->ray_dir_x);
	r->delta_dist_y = fabs(1 / r->ray_dir_y);
	// x, y 가 1 증가할때의 벡터크기(delta_dist)를 구한다
	r->hit = 0;
	calculate_side_dist_xy(g, r);
	is_hit(g, r);
}

void	calculate_side_dist_xy(t_game *g, t_ray *r)
{
	if (r->ray_dir_x < 0)
	{
		r->step_x = -1;
		r->side_dist_x = (g->player.pos_x - r -> map_x) * r->delta_dist_x;
	}
	// x < 0, 즉 광선이 좌측일 때
	else
	{
		r->step_x = 1;
		r->side_dist_x = (r->map_x + 1.0 - g->player.pos_x)* r->delta_dist_x;
	}
	// x < 0, 광선이 우측일 때
	if (r->ray_dir_y < 0)
	{
		r->step_y = -1;
		r->side_dist_y = (g->player.pos_y - r->map_y) * r->delta_dist_y;
	}
	// y < 0, 광선이 위로 갈때
	else
	{
		r->step_y = 1;
		r->side_dist_y = (r->map_y + 1 - g->player.pos_y) * r->delta_dist_y;
	}
	// y > 0, 광선이 아래로 갈 때
}

void	is_hit(t_game *g, t_ray *r)
{
	while (r->hit == 0)
	// 벽이 아닌 경우 루프 걔속 돌리기
	{
		if (r->side_dist_x < r->side_dist_y)
		{
			r->side_dist_x += r->delta_dist_x;
			r->map_x += r->step_x;
			r->side = 0;
		}
		// side_dist_x 가 y보다 짧은 경우, x를 기준으로 한칸씩 전진하면서 벽 탐색
		// 그리고 x축 방향으로(수평으로) 갔기 때문에 side = 0으로 한다
		else
		{
			r->side_dist_y += r->delta_dist_y;
			r->map_y += r->step_y;
			r->side = 1;
		}
		// 반대의 경우 y를 기준으로 한칸씩 전진하면서 벽 탐색
		// 그리고 y축 방향으로 갔기 때문에 side = 1 로 한다
		if (g->map.grid[r->map_y][r->map_x] == '1')
			r->hit = 1;
		// 위 루프 통과 후 거기가 벽인지 검사
	}
	if (r->side == 0)
		r->perp_wall_dist = (r->map_x - g->player.pos_x + (1 - r->step_x) / 2) \
		 / r->ray_dir_x;
	else
		r->perp_wall_dist = (r->map_y - g->player.pos_y + (1 - r->step_y) / 2) \
		 / r->ray_dir_y;
}
