/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmolina <nmolina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 18:13:24 by lilam             #+#    #+#             */
/*   Updated: 2018/05/28 21:46:46 by nmolina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#define WORLD_VARS int lineHeight; double wallx; int texx; int texy; int color;

void	calculate_ray(t_mlx *mlx, int x)
{
	double camerax;

	camerax = 2 * x / (double)WIDTH - 1;
	mlx->wolf->rayx = mlx->wolf->dirx + mlx->wolf->planex * camerax;
	mlx->wolf->rayy = mlx->wolf->diry + mlx->wolf->planey * camerax;
}

void	calculate_step_sidedist(t_mlx *mlx, int x)
{
	(void)x;
	mlx->wolf->mapx = mlx->wolf->posx;
	mlx->wolf->mapy = mlx->wolf->posy;
	mlx->wolf->delta_distx = fabs(1 / mlx->wolf->rayx);
	mlx->wolf->delta_disty = fabs(1 / mlx->wolf->rayy);
	mlx->wolf->hit = 0;
	if (mlx->wolf->rayx < 0 && (mlx->wolf->stepx = -1))
		mlx->wolf->distx = (mlx->wolf->posx - mlx->wolf->mapx)
			* mlx->wolf->delta_distx;
	else if ((mlx->wolf->stepx = 1))
		mlx->wolf->distx = (mlx->wolf->mapx + 1.0 - mlx->wolf->posx)
			* mlx->wolf->delta_distx;
	if (mlx->wolf->rayy < 0 && (mlx->wolf->stepy = -1))
		mlx->wolf->disty = (mlx->wolf->posy - mlx->wolf->mapy)
			* mlx->wolf->delta_disty;
	else if ((mlx->wolf->stepy = 1))
		mlx->wolf->disty = (mlx->wolf->mapy + 1.0 - mlx->wolf->posy)
			* mlx->wolf->delta_disty;
}

void	dda(t_mlx *mlx, int x)
{
	(void)x;
	while (mlx->wolf->hit == 0)
	{
		if (mlx->wolf->distx < mlx->wolf->disty)
		{
			mlx->wolf->distx += mlx->wolf->delta_distx;
			mlx->wolf->mapx += mlx->wolf->stepx;
			mlx->wolf->side = 0;
		}
		else
		{
			mlx->wolf->disty += mlx->wolf->delta_disty;
			mlx->wolf->mapy += mlx->wolf->stepy;
			mlx->wolf->side = 1;
		}
		if (mlx->wolf->world_map[mlx->wolf->mapx][mlx->wolf->mapy] > 0)
			mlx->wolf->hit = 1;
	}
	if (mlx->wolf->side == 0)
		mlx->wolf->per_wall_dist = (mlx->wolf->mapx - mlx->wolf->posx +
				(1 - mlx->wolf->stepx) / 2) / mlx->wolf->rayx;
	else
		mlx->wolf->per_wall_dist = (mlx->wolf->mapy - mlx->wolf->posy +
				(1 - mlx->wolf->stepy) / 2) / mlx->wolf->rayy;
}

void	draw_world(t_mlx *mlx, int x)
{
	WORLD_VARS;
	lineHeight = (int)(HEIGHT / mlx->wolf->per_wall_dist);
	mlx->wolf->draw_start = -lineHeight / 2 + HEIGHT / 2;
	mlx->wolf->draw_end = lineHeight / 2 + HEIGHT / 2;
	(mlx->wolf->draw_start < 0) ? mlx->wolf->draw_start = 0 : 0;
	(mlx->wolf->draw_end >= HEIGHT) ? (mlx->wolf->draw_end = HEIGHT - 1) : 0;
	if (mlx->wolf->side == 0)
		wallx = mlx->wolf->posy + mlx->wolf->per_wall_dist * mlx->wolf->rayy;
	else
		wallx = mlx->wolf->posx + mlx->wolf->per_wall_dist * mlx->wolf->rayx;
	wallx = wallx - floor((wallx));
	texx = (int)(wallx * (double)TEX_WIDTH);
	if (mlx->wolf->side == 0 && mlx->wolf->rayx > 0)
		texx = TEX_WIDTH - texx - 1;
	if (mlx->wolf->side == 1 && mlx->wolf->rayy < 0)
		texx = TEX_WIDTH - texx - 1;
	while (mlx->wolf->draw_start < mlx->wolf->draw_end)
	{
		texy = (((mlx->wolf->draw_start * 256 - HEIGHT * 128 + lineHeight * 128)
					* TEX_HEIGHT) / lineHeight) / 256;
		color = mlx->wolf->textures[mlx->wolf->world_map[mlx->wolf->mapx]
			[mlx->wolf->mapy] - 1][TEX_HEIGHT * texy + texx];
		(mlx->wolf->side == 1) ? (color = (color >> 1) & 8355711) : 0;
		draw_pixel(mlx, x, mlx->wolf->draw_start++, color);
	}
}

void	render_wolf(t_mlx *mlx)
{
	int x;

	ft_bzero(mlx->img_ptr, WIDTH * HEIGHT * mlx->bbp);
	x = 0;
	while (x < WIDTH)
	{
		calculate_ray(mlx, x);
		calculate_step_sidedist(mlx, x);
		dda(mlx, x);
		draw_world(mlx, x);
		x++;
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img, 0, 0);
	mlx->controls == 1 ? put_controls(mlx->mlx_ptr, mlx->win_ptr) : 0;
}
