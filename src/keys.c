/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilam <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 17:44:49 by lilam             #+#    #+#             */
/*   Updated: 2018/05/28 18:00:53 by lilam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	rot_dir_plane(t_mlx *mlx, double theta)
{
	double olddirx;
	double oldplanex;

	olddirx = mlx->wolf->dirx;
	mlx->wolf->dirx = mlx->wolf->dirx * cos(theta) -
		mlx->wolf->diry * sin(theta);
	mlx->wolf->diry = olddirx * sin(theta) + mlx->wolf->diry * cos(theta);
	oldplanex = mlx->wolf->planex;
	mlx->wolf->planex = oldplanex * cos(theta) - mlx->wolf->planey * sin(theta);
	mlx->wolf->planey = mlx->wolf->planex * sin(theta) +
		mlx->wolf->planey * cos(theta);
}

void	move_up_down(t_mlx *mlx, int i)
{
	if (i == 1)
	{
		if (!(mlx->wolf->worldMap[(int)(mlx->wolf->posx + mlx->wolf->dirx *
						0.15)][(int)(mlx->wolf->posy)]))
			mlx->wolf->posx += mlx->wolf->dirx * 0.15;
		if (!(mlx->wolf->worldMap[(int)(mlx->wolf->posx)][(int)(mlx->wolf->posy
						+ mlx->wolf->diry * 0.15)]))
			mlx->wolf->posy += mlx->wolf->diry * 0.15;
	}
	else if (i == 2)
	{
		if (!(mlx->wolf->worldMap[(int)(mlx->wolf->posx - mlx->wolf->dirx *
						0.15)][(int)(mlx->wolf->posy)]))
			mlx->wolf->posx -= mlx->wolf->dirx * 0.15;
		if (!(mlx->wolf->worldMap[(int)(mlx->wolf->posx)][(int)(mlx->wolf->posy
						- mlx->wolf->diry * 0.15)]))
			mlx->wolf->posy -= mlx->wolf->diry * 0.15;
	}
}

int		keys(int key, t_mlx *mlx)
{
	(void)mlx;
	key == 53 ? close_wolf3d() : 0;
	if (key == 126)
		move_up_down(mlx, 1);
	else if (key == 125)
		move_up_down(mlx, 2);
	else if (key == 124)
		rot_dir_plane(mlx, -0.045);
	else if (key == 123)
		rot_dir_plane(mlx, 0.045);
	else if (key == 8)
		mlx->controls *= -1;
	else
		return (0);
	render_wolf(mlx);
	return (0);
}

int		close_wolf3d(void)
{
	system("pkill sh afplay > /dev/null 2>&1");
	exit(EXIT_SUCCESS);
	return (0);
}
