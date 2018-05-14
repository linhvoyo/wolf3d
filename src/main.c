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
	if (!(tmp->wolf = malloc(sizeof(t_wolf))))
		return (NULL);
	tmp->wolf->posx = 22;
	tmp->wolf->posy = 12;
	tmp->wolf->dirx = -1;
	tmp->wolf->diry = 0;
	return tmp;
}


void wolf(t_mlx *mlx)
{
	int **worldMap;
	worldMap = map();


		//  double posx = 22;
		//  double posy = 12;
	  // //
		//  double dirx = -1;
		//  double diry = 0;

		 double posx = mlx->wolf->posx;
		 double posy = mlx->wolf->posy;
		 double dirx = mlx->wolf->dirx;
		 double diry = mlx->wolf->diry;

		 printf("posx %f poxy %f dirx %f diry %f\n", posx, posy, dirx, diry);
		 double planex = 0;
		 double planey = 0.66;
	  //
		double time = 0;
		double oldTime = 0;



		//ray casting loop
		double camerax;
		double rayx;
		double rayy;
		int x = 0;
		while (x < WIDTH)
		{
			//calculate ray position and direction
			camerax = 2 * x / (double)x - 1;
			rayx = dirx + planex * camerax;
			rayy = diry + planey * camerax;

			//which box of the map we're in
			int mapx = posx;
			int mapy = posy;

			//lenght of ray from current position to the next x or y-side
			double sideDistX;
			double sideDistY;

			// length of ray from one x to another x-side
			// length of ray from one y to another y-side
			double deltaDistX = fabs(1/ rayx);
			double deltaDistY = fabs(1/ rayy);
			double perpWallDist;

			//what direction to step in , x or y direction (either +1 or -1)
			int stepx;
			int stepy;

			int hit = 0; //was there a wall hit?
			int side; //was a NS or a EW wall hit?;

			//calculate step and initial sideDist
			if (rayx < 0)
			{
				stepx = -1;
				sideDistX = (posx - mapx) * deltaDistX;
			}
			else
			{
				stepx = 1;
				sideDistX = (mapx + 1.0 - posx) * deltaDistX;
			}
			if (rayy < 0)
			{
				stepy = -1;
				sideDistY = (posy - mapy) * deltaDistY;
			}
			else
			{
				stepy = 1;
				sideDistY = (mapy + 1.0 - posy) * deltaDistY;
			}

			//perform DDA
			while (hit == 0)
			{
				//jump to next map sqaure, or in direction of x or y
				if (sideDistX < sideDistY)
				{
					sideDistX += deltaDistX;
					mapx += stepx;
					side = 0;
				}
				else
				{
					sideDistY += deltaDistY;
					mapy += stepy;
					side = 1;
				}
				//Check if ray has hit a wall
				if (worldMap[mapx][mapy] > 0)
					hit = 1;
			}

			//Calculate distance projected on camera direction
			if (side == 0)
				perpWallDist = (mapx - posx + (1 - stepx) / 2) / rayx;
			else
				perpWallDist = (mapy - posy + (1 - stepy) / 2) / rayy;

			//Calculate height of line draw on screen
			// h = the height in pixels of the screen, to bring it to pixel coordinates.
			int h = 150;

			int lineHeight = (int)(h / perpWallDist);

			//calculate lowest and highest pixel to fill in current stripe
			int drawStart = -lineHeight / 2 + h / 2;
			if (drawStart < 0)
				drawStart = 0;
			int drawEnd = lineHeight / 2 + h / 2;
			if (drawEnd >= h)
				drawEnd = h - 1;

			int color;
			if (worldMap[mapx][mapy] == '1')
				color = 0xFF0000;
			else if (worldMap[mapx][mapy] == '2')
				color = 0x00FF00;
			else if (worldMap[mapx][mapy] == '3')
				color = 0x0000FF;
			else if (worldMap[mapx][mapy] == '4')
				color = 0xFFFFFF;

			if (side == 1)
				color = color / 2;

			int k;
			k = drawStart;
			// printf("x %d drawStart %d drawEnd %d perpWallDist %f\n",x, k, drawEnd, perpWallDist);
			while (k < drawEnd)
			{
				// printf("x %d drawStart %d drawEnd %d perpWallDist %f\n",x, k, drawEnd, perpWallDist);
				draw_pixel(mlx, x , k++, 0xFF00000);
			}
			x++;
		}

		mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img, 0, 0);
}

int main()
{
	// int **worldMap;
	//
	// worldMap = map();

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

	wolf(mlx);
  //
	// //  double posx = 22;
	// //  double posy = 12;
  // // //
	// //  double dirx = -1;
	// //  double diry = 0;
  //
	//  double posx = mlx->wolf->posx;
	//  double posy = mlx->wolf->posy;
	//  double dirx = mlx->wolf->dirx;
	//  double diry = mlx->wolf->diry;
  //
	//  printf("posx %f poxy %f dirx %f diry %f\n", posx, posy, dirx, diry);
	//  double planex = 0;
	//  double planey = 0.66;
  // //
	// double time = 0;
	// double oldTime = 0;
  //
  //
  //
	// //ray casting loop
	// double camerax;
	// double rayx;
	// double rayy;
	// int x = 0;
	// while (x < WIDTH)
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
	// 	//Calculate height of line draw on screen
	// 	// h = the height in pixels of the screen, to bring it to pixel coordinates.
	// 	int h = 150;
  //
	// 	int lineHeight = (int)(h / perpWallDist);
  //
	// 	//calculate lowest and highest pixel to fill in current stripe
	// 	int drawStart = -lineHeight / 2 + h / 2;
	// 	if (drawStart < 0)
	// 		drawStart = 0;
	// 	int drawEnd = lineHeight / 2 + h / 2;
	// 	if (drawEnd >= h)
	// 		drawEnd = h - 1;
  //
	// 	int color;
	// 	if (worldMap[mapx][mapy] == '1')
	// 		color = 0xFF0000;
	// 	else if (worldMap[mapx][mapy] == '2')
	// 		color = 0x00FF00;
	// 	else if (worldMap[mapx][mapy] == '3')
	// 		color = 0x0000FF;
	// 	else if (worldMap[mapx][mapy] == '4')
	// 		color = 0xFFFFFF;
  //
	// 	if (side == 1)
	// 		color = color / 2;
  //
	// 	int k;
	// 	k = drawStart;
	// 	// printf("x %d drawStart %d drawEnd %d perpWallDist %f\n",x, k, drawEnd, perpWallDist);
	// 	while (k < drawEnd)
	// 	{
	// 		// printf("x %d drawStart %d drawEnd %d perpWallDist %f\n",x, k, drawEnd, perpWallDist);
	// 		draw_pixel(mlx, x , k++, 0xFF00000);
	// 	}
	// 	x++;
	// }

	//
	// printf("time %d\n", time);
	// mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img, 0, 0);
	mlx_hook(mlx->win_ptr, 2, 0, keys, mlx);
	mlx_loop(mlx->mlx_ptr);
	return (0);
}
