/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilam <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 20:21:18 by lilam             #+#    #+#             */
/*   Updated: 2018/05/13 17:17:25 by linh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <stdio.h>
#include <math.h>
#define mapWidth 24
#define mapHeight 24

int 	**map()
{
	int map_test[24][24] = {
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
		{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
		{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}};

		int **map;

		map = malloc(sizeof(int*) * mapHeight);

		int i;
		i = 0;
		int j;
		while (i < mapHeight)
		{
			j = 0;
			map[i] = malloc(sizeof(int) * mapWidth);
			while (j < mapWidth)
			{
				map[i][j] = map_test[i][j];
				j++;
			}
			i++;
		}
	return map;
}


void 	draw_pixel(t_mlx *mlx, int x, int y, int color)
{
	int i;
	i = x + (y * WIDTH);
	mlx->img_ptr[i] = color;

}

t_mlx 	*init_mlx(char *str)
{
	t_mlx *tmp;

	if (!(tmp = malloc(sizeof(t_mlx))))
		return (NULL);
	tmp->mlx_ptr = mlx_init();
	tmp->win_ptr = mlx_new_window(tmp->mlx_ptr, WIDTH, HEIGHT, str);
	tmp->img = mlx_new_image(tmp->mlx_ptr, WIDTH, HEIGHT);
	tmp->img_ptr = (int *)mlx_get_data_addr(tmp->img, &tmp->bbp, &tmp->stride, &tmp->endian);
	tmp->bbp /= 8;

	return tmp;
}


int main()
{
	int **worldMap;

	worldMap = map();

	// int i = 0;
	// int j;
	// while (i < mapHeight)
	// {
	// 	j = 0;
	// 	while (j < mapWidth)
	// 	{
	// 		printf("%d", test[i][j]);
	// 		j++;
	// 	}
	// 	printf("\n");
	// 	i++;
	// }


	t_mlx *mlx;
	mlx = init_mlx("raycaster");

	int x1 = 10;
	int y1 = 10;
	int i;
	i = x1 + (y1 * WIDTH);
	mlx->img_ptr[i] = 0xFFFFFF;

	//  double posx = 22;
	//  double posy = 12;
  // //
	//  double dirx = -1;
	//  double diry = 0;
	//  double planex = 0;
	//  double planey = 0.66;
  // //
	// // double time = 0;
	// // double oldTime = 0;
  //
  //
  //
	// //ray casting loop
	// double camerax;
	// double rayx;
	// double rayy;
	// int x = 0;
	// while (x < mapWidth)
	// {
	// 	//calculate ray position and direction
	// 	camerax = 2 * x / (double)x - 1;
	// 	rayx = dirx + planex * camerax;
	// 	rayy = diry + planey * camerax;
  //
	// 	//which box of the map we're in
	// 	int mapx = posx;
	// 	int mapy = posy;
  //
	// 	//lenght of ray from current position to the next x or y-side
	// 	double sideDistX;
	// 	double sideDistY;
  //
	// 	// length of ray from one x to another x-side
	// 	// length of ray from one y to another y-side
	// 	double deltaDistX = fabs(1/ rayx);
	// 	double deltaDistY = fabs(1/ rayy);
	// 	double perpWallDist;
  //
	// 	//what direction to step in , x or y direction (either +1 or -1)
	// 	int stepx;
	// 	int stepy;
  //
	// 	int hit = 0; //was there a wall hit?
	// 	int side; //was a NS or a EW wall hit?;
  //
	// 	//calculate step and initial sideDist
	// 	if (rayx < 0)
	// 	{
	// 		stepx = -1;
	// 		sideDistX = (posx - mapx) * deltaDistX;
	// 	}
	// 	else
	// 	{
	// 		stepx = 1;
	// 		sideDistX = (mapx + 1.0 - posx) * deltaDistX;
	// 	}
	// 	if (rayy < 0)
	// 	{
	// 		stepy = -1;
	// 		sideDistY = (posy - mapy) * deltaDistY;
	// 	}
	// 	else
	// 	{
	// 		stepy = 1;
	// 		sideDistY = (mapy + 1.0 - posy) * deltaDistY;
	// 	}
  //
	// 	//perform DDA
	// 	while (hit == 0)
	// 	{
	// 		//jump to next map sqaure, or in direction of x or y
	// 		if (sideDistX < sideDistY)
	// 		{
	// 			sideDistX += deltaDistX;
	// 			mapx += stepx;
	// 			side = 0;
	// 		}
	// 		else
	// 		{
	// 			sideDistY += deltaDistY;
	// 			mapy += stepy;
	// 			side = 1;
	// 		}
	// 		//Check if ray has hit a wall
	// 		if (worldMap[mapx][mapy] > 0)
	// 			hit = 1;
	// 	}
  //
	// 	//Calculate distance projected on camera direction
	// 	if (side == 0)
	// 		perpWallDist = (mapx - posx + (1 - stepx) / 2) / rayx;
	// 	else
	// 		perpWallDist = (mapy - posy + (1 - stepy) / 2) / rayy;
  //
  //
  //
	// 	x++;
	// }

	mlx_hook(mlx->win_ptr, 2, 0, keys, mlx);
	mlx_loop(mlx->mlx_ptr);
	return (0);
}
