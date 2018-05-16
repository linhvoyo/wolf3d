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
	// int map_test[24][24] = {
	// 	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// 	{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	// 	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// 	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
	// 	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// 	{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// 	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// 	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// 	{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// 	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// 	{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// 	{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// 	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// 	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}};

	int map_test[mapWidth][mapHeight]={
  {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,7,7,7,7,7,7,7,7},
  {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
  {4,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
  {4,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
  {4,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
  {4,0,4,0,0,0,0,5,5,5,5,5,5,5,5,5,7,7,0,7,7,7,7,7},
  {4,0,5,0,0,0,0,5,0,5,0,5,0,5,0,5,7,0,0,0,7,7,7,1},
  {4,0,6,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
  {4,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,7,1},
  {4,0,8,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
  {4,0,0,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,7,7,7,1},
  {4,0,0,0,0,0,0,5,5,5,5,0,5,5,5,5,7,7,7,7,7,7,7,1},
  {6,6,6,6,6,6,6,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
  {8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
  {6,6,6,6,6,6,0,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
  {4,4,4,4,4,4,0,4,4,4,6,0,6,2,2,2,2,2,2,2,3,3,3,3},
  {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
  {4,0,0,0,0,0,0,0,0,0,0,0,6,2,0,0,5,0,0,2,0,0,0,2},
  {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
  {4,0,6,0,6,0,0,0,0,4,6,0,0,0,0,0,5,0,0,0,0,0,0,2},
  {4,0,0,5,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
  {4,0,6,0,6,0,0,0,0,4,6,0,6,2,0,0,5,0,0,2,0,0,0,2},
  {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
  {4,4,4,4,4,4,4,4,4,4,1,1,1,2,2,2,2,2,2,3,3,3,3,3}};

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
	tmp->last_frame = clock();
	tmp->next_frame = 0;
	if (!(tmp->wolf = malloc(sizeof(t_wolf))))
		return (NULL);
	tmp->wolf->posx = 22;
	tmp->wolf->posy = 11.5;
	tmp->wolf->dirx = -1;
	tmp->wolf->diry = 0;
	tmp->wolf->planex = 0;
	tmp->wolf->planey = 0.66;
	tmp->wolf->worldMap = map();
	return tmp;
}

int **generate_text_arr(int n)
{
	int **arr;
	arr = malloc(sizeof(int*) * 8);
	int i = 0;
	while(i < n)
		arr[i++] = malloc(sizeof(int) * texWidth * texHeight);
	return (arr);
}

void render_wolf(t_mlx *mlx)
{
	ft_bzero(mlx->img_ptr, WIDTH * HEIGHT * mlx->bbp);
	double posx = mlx->wolf->posx;
	double posy = mlx->wolf->posy;
	double dirx = mlx->wolf->dirx;
	double diry = mlx->wolf->diry;

	
	int **tex_arr;
	tex_arr = generate_text_arr(8);
	int i;
	i = 0;
	int j;


	// loadImage(tex_arr[0], texWidth , texHeight, "barrel.png");
	while (i < texWidth)
	{
		j = 0;
		while (j < texHeight)
		{
			int xorcolor = (i * 256 /texWidth) ^ (j * 256 / texHeight);
			int ycolor = j * 256 / texHeight;
			int xycolor = j * 128 / texHeight + i * 128 / texWidth;
			tex_arr[0][texWidth * j + i] = 65536 * 254 * (i != j && i != texWidth - j);
			tex_arr[1][texWidth * j + i] = xycolor + 256 * xycolor + 65536 * xycolor;
			tex_arr[2][texWidth * j + i] = 256 * xycolor + 65536 * xycolor;
			tex_arr[3][texWidth * j + i] = xorcolor + 256 * xorcolor + 65536 * xorcolor;
			tex_arr[4][texWidth * j + i] = 256 * xorcolor;
			tex_arr[5][texWidth * j + i] = 65536 * 192 * (i % 16 && j % 16);
			tex_arr[6][texWidth * j + i] = 65536 * ycolor;
			tex_arr[7][texWidth * j + i] = 128 + 256 * 128 + 65536 * 128;
			j++;
		}
		i++;
	}




	printf("posx %f poxy %f dirx %f diry %f\n", posx, posy, dirx, diry);
	double planex = mlx->wolf->planex;
	double planey = mlx->wolf->planey;

	

	int buffer[HEIGHT][WIDTH];

	//ray casting loop
	double camerax;
	double rayx;
	double rayy;
	int x = 0;
	while (x < WIDTH)
	{
		//calculate ray position and direction
		camerax = 2 * x / (double)WIDTH - 1;
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
			if (mlx->wolf->worldMap[mapx][mapy] > 0)
				hit = 1;
		}

		//Calculate distance projected on camera direction
		if (side == 0)
			perpWallDist = (mapx - posx + (1 - stepx) / 2) / rayx;
		else
			perpWallDist = (mapy - posy + (1 - stepy) / 2) / rayy;

		//Calculate height of line draw on screen
		// h = the height in pixels of the screen, to bring it to pixel coordinates.

		int lineHeight = (int)(HEIGHT / perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + HEIGHT / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + HEIGHT / 2;
		if (drawEnd >= HEIGHT)
			drawEnd = HEIGHT - 1;

		// int color;
		// // printf("wolrdMap[mapx][mapy] %d, %d, %d\n", mapx, mapy, mlx->wolf->worldMap[mapx][mapy]);
		// if (mlx->wolf->worldMap[mapx][mapy] == 1)
		// 	color = 0xFF0000; //red
		// else if (mlx->wolf->worldMap[mapx][mapy] == 2)
		// 	color = 0x00FF00; //green
		// else if (mlx->wolf->worldMap[mapx][mapy] == 3)
		// 	color = 0x0000FF; //blue
		// else if (mlx->wolf->worldMap[mapx][mapy] == 4)
		// 	color = 0xFFFFFF; //white
		// else if (mlx->wolf->worldMap[mapx][mapy] == 0)
		// 	color = 0xFFFF00; //yellow

		// if (side == 1)
		// 	color = color / 2;

		// while (drawStart < drawEnd)
		// 	draw_pixel(mlx, x , drawStart++, color);


		int texNum = mlx->wolf->worldMap[mapx][mapy] - 1;
		double wallx;
		if (side == 0)
			wallx = posy + perpWallDist * rayy;
		else
			wallx = posx + perpWallDist * rayx;
		wallx = wallx - floor((wallx));

		int texx = (int)(wallx * (double)texWidth);
		if (side == 0 && rayx > 0)
			texx = texWidth - texx - 1;
		if (side == 1 && rayy < 0)
			texx = texWidth - texx - 1;
		
		while (drawStart < drawEnd)
		{
			int d = drawStart * 256 - HEIGHT * 128 + lineHeight * 128;
			int texy = ((d * texHeight) / lineHeight) / 256;
			int color = tex_arr[texNum][texHeight * texy + texx];
			if (side == 1)
				color = (color >> 1) & 8355711;
			// buffer[drawStart++][x] = color;
			draw_pixel(mlx, x, drawStart++, color);
		}
		x++;
		}

		// oldtime = time;
		// time = clock();
		// double frameTime = (time - oldtime) / 1000;
		// printf("fps %f\n", frameTime);
		mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img, 0, 0);
}

int main()
{
	t_mlx *mlx;
	mlx = init_mlx("raycaster");

	render_wolf(mlx);
	// mlx_loop_hook(mlx->mlx_ptr, loop_hook, mlx);
	mlx_hook(mlx->win_ptr, 2, 0, keys, mlx);
	mlx_loop(mlx->mlx_ptr);
	return (0);
}
