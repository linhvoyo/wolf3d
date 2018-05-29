/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmolina <nmolina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 20:21:18 by lilam             #+#    #+#             */
/*   Updated: 2018/05/28 20:34:59 by nmolina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <stdio.h>

void 	draw_pixel(t_mlx *mlx, int x, int y, int color)
{
	int i;
	i = x + (y * WIDTH);
	mlx->img_ptr[i] = color;
}

int **generate_textures()
{
	int **arr;
	int i;
	int j;
	int x_color;
	int y_color;
	int xy_color;

	if (!(arr = (int**)malloc(sizeof(int*) * 8)))
		return (NULL);
	i = 0;
	while (i < 8)
	{
		arr[i] = (int*)malloc(sizeof(int) * 64 * 64);
		i++;
	}
	i = 0;
	while (i < TEX_WIDTH)
	{
		j = 0;
		while (j < TEX_HEIGHT)
		{
			x_color = (i * 256 / TEX_WIDTH) ^ (j * 256 / TEX_HEIGHT);
			y_color = j * 256 / TEX_HEIGHT;
			xy_color = j * 128 / TEX_HEIGHT + i * 128 / TEX_WIDTH;
			arr[0][TEX_WIDTH * j + i] = 65536 * 254 * (i != j && i != TEX_WIDTH - j);
			arr[1][TEX_WIDTH * j + i] = xy_color + 256 * xy_color + 65536 * xy_color;
			arr[2][TEX_WIDTH * j + i] = 256 * xy_color + 65536 * xy_color;
			arr[3][TEX_WIDTH * j + i] = x_color + 256 * x_color + 65536 * x_color;
			arr[4][TEX_WIDTH * j + i] = 256 * x_color;
			arr[5][TEX_WIDTH * j + i] = 65536 * 192 * (i % 16 && j % 16);
			arr[6][TEX_WIDTH * j + i] = 65536 * y_color;
			arr[7][TEX_WIDTH * j + i] = 128 + 256 * 128 + 65536 * 128;
			j++;
		}
		i++;
	}
	return arr;
}

void    put_controls(void *mlx, void *w)
{
    mlx_string_put(mlx, w, 10, 20, 0xFFFFFF, "--------------");
    mlx_string_put(mlx, w, 20, 35, 0xFFFFFF, "CONTROLS");
    mlx_string_put(mlx, w, 10, 50, 0xFFFFFF, "--------------");
    mlx_string_put(mlx, w, 15, 70, 0xFFFFFF, "Movement");
    mlx_string_put(mlx, w, 30, 90, 0xFFFFFF, "[UP] & [DOWN]");
    mlx_string_put(mlx, w, 15, 110, 0xFFFFFF, "Rotation");
    mlx_string_put(mlx, w, 30, 130, 0xFFFFFF, "[LEFT] & [RIGHT]");
    mlx_string_put(mlx, w, 15, 150, 0xFFFFFF, "Controls");
    mlx_string_put(mlx, w, 30, 170, 0xFFFFFF, "[C]");
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
	tmp->controls = 1;
	if (!(tmp->wolf = malloc(sizeof(t_wolf))))
		return (NULL);
	tmp->wolf->posx = 2;
	tmp->wolf->posy = 2.5;
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

void	play_music()
{
	system("while : ; do afplay assets/get_them.mp3 ; done &");
}

int main(int argc, char **argv)
{
	t_mlx	*mlx;
	int		fd;

	if (argc != 2)
		usage();
	read_file((fd = open(argv[1], O_RDONLY)), (mlx = init_mlx("raycaster")));
	mlx->wolf->worldMap = process_map((fd = open(argv[1], O_RDONLY)), mlx);
	render_wolf(mlx);
	mlx_hook(mlx->win_ptr, 2, 0, keys, mlx);
	mlx_hook(mlx->win_ptr, 17, 0, close_wolf3d, mlx);
	signal(SIGINT, stop_music);
	play_music();
	mlx_loop(mlx->mlx_ptr);
	return (0);
}
