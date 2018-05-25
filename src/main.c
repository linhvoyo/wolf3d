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
#include <fcntl.h>


void 	draw_pixel(t_mlx *mlx, int x, int y, int color)
{
	int i;
	i = x + (y * WIDTH);
	mlx->img_ptr[i] = color;
}

int **generate_textures()
{
	int **arr;
	int i = 0;
	int j = 0;
	int x_color;
	int y_color;
	int xy_color;

	if (!(arr = malloc(sizeof(int*) * 8)))
		return (NULL);
	while (i < 8)
		arr[i++] = malloc(sizeof(int) * texWidth * texHeight);
	i = 0;
	while (i < texWidth)
	{
		j = 0;
		while (j < texHeight)
		{
			x_color = (i * 256 / texWidth) ^ (j * 256 / texHeight);
			y_color = j * 256 / texHeight;
			xy_color = j * 128 / texHeight + i * 128 / texWidth;
			arr[0][texWidth * j + i] = 65536 * 254 * (i != j && i != texWidth - j);
			arr[1][texWidth * j + i] = xy_color + 256 * xy_color + 65536 * xy_color;
			arr[2][texWidth * j + i] = 256 * xy_color + 65536 * xy_color;
			arr[3][texWidth * j + i] = x_color + 256 * x_color + 65536 * x_color;
			arr[4][texWidth * j + i] = 256 * x_color;
			arr[5][texWidth * j + i] = 65536 * 192 * (i % 16 && j % 16);
			arr[6][texWidth * j + i] = 65536 * y_color;
			arr[7][texWidth * j + i] = 128 + 256 * 128 + 65536 * 128;
			j++;
		}
		i++;
	}
	return arr;
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
	tmp->wolf->posy = 11.5;
	tmp->wolf->dirx = -1;
	tmp->wolf->diry = 0;
	tmp->wolf->planex = 0;
	tmp->wolf->planey = 0.66;
	tmp->wolf->textures = generate_textures();
	if (!(tmp->map = malloc(sizeof(t_map))))
		return (NULL);
	tmp->map->mw = 0;
	tmp->map->mh = 0;
	return tmp;
}

void calculate_ray(t_mlx *mlx, int x)
{
	//calculate ray position given direction vector
	double camerax;
	
	camerax = 2 * x / (double)WIDTH - 1;
	mlx->wolf->rayx = mlx->wolf->dirx + mlx->wolf->planex * camerax;
	mlx->wolf->rayy = mlx->wolf->diry + mlx->wolf->planey * camerax;
}

// void calculate_step_sidedist(t_mlx *mlx, int x)
// {

// }

void render_wolf(t_mlx *mlx)
{
	ft_bzero(mlx->img_ptr, WIDTH * HEIGHT * mlx->bbp);

	printf("posx %f poxy %f dirx %f diry %f\n", mlx->wolf->posx,
	mlx->wolf->posy, mlx->wolf->dirx, mlx->wolf->diry);


	//ray casting loop

	int x = 0;
	while (x < WIDTH)
	{
		calculate_ray(mlx, x);
		//which box of the map we're in
		mlx->wolf->mapx = mlx->wolf->posx;
		mlx->wolf->mapy = mlx->wolf->posy;

		//lenght of ray from current position to the next x or y-side
		double sideDistX;
		double sideDistY;

		// length of ray from one x to another x-side
		// length of ray from one y to another y-side
		double deltaDistX = fabs(1 / mlx->wolf->rayx);
		double deltaDistY = fabs(1 / mlx->wolf->rayy);
		double perpWallDist;

		//what direction to step in , x or y direction (either +1 or -1)
		int stepx;
		int stepy;

		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?;

		//calculate step and initial sideDist
		if (mlx->wolf->rayx < 0)
		{
			stepx = -1;
			sideDistX = (mlx->wolf->posx - mlx->wolf->mapx) * deltaDistX;
		}
		else
		{
			stepx = 1;
			sideDistX = (mlx->wolf->mapx + 1.0 - mlx->wolf->posx) * deltaDistX;
		}
		if (mlx->wolf->rayy < 0)
		{
			stepy = -1;
			sideDistY = (mlx->wolf->posy - mlx->wolf->mapy) * deltaDistY;
		}
		else
		{
			stepy = 1;
			sideDistY = (mlx->wolf->mapy + 1.0 - mlx->wolf->posy) * deltaDistY;
		}

		//perform DDA
		while (hit == 0)
		{
			//jump to next map sqaure, or in direction of x or y
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mlx->wolf->mapx += stepx;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mlx->wolf->mapy += stepy;
				side = 1;
			}
			//Check if ray has hit a wall
			if (mlx->wolf->worldMap[mlx->wolf->mapx][mlx->wolf->mapy] > 0)
				hit = 1;
		}

		//Calculate distance projected on camera direction
		if (side == 0)
			perpWallDist = (mlx->wolf->mapx - mlx->wolf->posx + (1 - stepx) / 2) / mlx->wolf->rayx;
		else
			perpWallDist = (mlx->wolf->mapy - mlx->wolf->posy + (1 - stepy) / 2) / mlx->wolf->rayy;

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

		int texNum = mlx->wolf->worldMap[mlx->wolf->mapx][mlx->wolf->mapy] - 1;
		double wallx;
		if (side == 0)
			wallx = mlx->wolf->posy + perpWallDist * mlx->wolf->rayy;
		else
			wallx = mlx->wolf->posx + perpWallDist * mlx->wolf->rayx;
		wallx = wallx - floor((wallx));

		int texx = (int)(wallx * (double)texWidth);
		if (side == 0 && mlx->wolf->rayx > 0)
			texx = texWidth - texx - 1;
		if (side == 1 && mlx->wolf->rayy < 0)
			texx = texWidth - texx - 1;

		while (drawStart < drawEnd)
		{
			int d = drawStart * 256 - HEIGHT * 128 + lineHeight * 128;
			int texy = ((d * texHeight) / lineHeight) / 256;
			int color = mlx->wolf->textures[texNum][texHeight * texy + texx];
			if (side == 1)
				color = (color >> 1) & 8355711;
			draw_pixel(mlx, x, drawStart++, color);
		}
		x++;
		}
		mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img, 0, 0);
}





int main(int argc, char **argv)
{
	t_mlx *mlx;
	int	fd;
	// int textures[8][texWidth * texHeight];

	// generate_texture(textures);
	// printf("%d", textures[1][4]);

	read_file((fd = open(argv[1], O_RDONLY)), (mlx = init_mlx("raycaster")));
	mlx->wolf->worldMap = process_map((fd = open(argv[1], O_RDONLY)), mlx);

	render_wolf(mlx);
	// // mlx_loop_hook(mlx->mlx_ptr, loop_hook, mlx);
	mlx_hook(mlx->win_ptr, 2, 0, keys, mlx);
	mlx_loop(mlx->mlx_ptr);
	return (0);
}
