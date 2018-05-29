/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmolina <nmolina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 20:21:18 by lilam             #+#    #+#             */
/*   Updated: 2018/05/28 21:34:52 by lilam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#define TEX_VARS int **arr; int xcl; int ycl; int xyc;int i[2]

void	draw_pixel(t_mlx *mlx, int x, int y, int color)
{
	int	i;

	i = x + (y * WIDTH);
	mlx->img_ptr[i] = color;
}

int		**generate_textures(void)
{
	TEX_VARS;
	if (!(arr = (int**)malloc(sizeof(int*) * 8)))
		return (NULL);
	i[0] = 0;
	while (i[0] < 8)
		arr[i[0]++] = (int*)malloc(sizeof(int) * 64 * 64);
	i[0] = -1;
	while (++i[0] < TEX_WIDTH && (i[1] = -1))
		while (++i[1] < TEX_HEIGHT)
		{
			xcl = (i[0] * 256 / TEX_WIDTH) ^ (i[1] * 256 / TEX_HEIGHT);
			ycl = i[1] * 256 / TEX_HEIGHT;
			xyc = i[1] * 128 / TEX_HEIGHT + i[0] * 128 / TEX_WIDTH;
			arr[0][TEX_WIDTH * i[1] + i[0]] = 65536 * 254 * (i[0] != i[1]
					&& i[0] != TEX_WIDTH - i[1]);
			arr[1][TEX_WIDTH * i[1] + i[0]] = xyc + 256 * xyc + 65536 * xyc;
			arr[2][TEX_WIDTH * i[1] + i[0]] = 256 * xyc + 65536 * xyc;
			arr[3][TEX_WIDTH * i[1] + i[0]] = xcl + 256 * xcl + 65536 * xcl;
			arr[4][TEX_WIDTH * i[1] + i[0]] = 256 * xcl;
			arr[5][TEX_WIDTH * i[1] + i[0]] = 65536 * 192 *
				(i[0] % 16 && i[1] % 16);
			arr[6][TEX_WIDTH * i[1] + i[0]] = 65536 * ycl;
			arr[7][TEX_WIDTH * i[1] + i[0]] = 128 + 256 * 128 + 65536 * 128;
		}
	return (arr);
}

void	put_controls(void *mlx, void *w)
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
	mlx_string_put(mlx, w, 15, 190, 0xFFFFFF, "Music");
	mlx_string_put(mlx, w, 30, 210, 0xFFFFFF, "[M]");
}

t_mlx	*init_mlx(char *str)
{
	t_mlx *tmp;

	if (!(tmp = malloc(sizeof(t_mlx))) ||
			(!(tmp->wolf = malloc(sizeof(t_wolf))))
			|| (!(tmp->map = malloc(sizeof(t_map)))))
		check_error(0, "Failed to malloc");
	tmp->mlx_ptr = mlx_init();
	tmp->win_ptr = mlx_new_window(tmp->mlx_ptr, WIDTH, HEIGHT, str);
	tmp->img = mlx_new_image(tmp->mlx_ptr, WIDTH, HEIGHT);
	tmp->img_ptr = (int *)mlx_get_data_addr(tmp->img, &tmp->bbp,
			&tmp->stride, &tmp->endian);
	tmp->bbp /= 8;
	tmp->controls = 1;
	tmp->music = 1;
	tmp->wolf->posx = 2;
	tmp->wolf->posy = 2.5;
	tmp->wolf->dirx = -1;
	tmp->wolf->diry = 0;
	tmp->wolf->planex = 0;
	tmp->wolf->planey = 0.66;
	tmp->wolf->textures = generate_textures();
	tmp->map->mw = 0;
	tmp->map->mh = 0;
	return (tmp);
}

int		main(int argc, char **argv)
{
	t_mlx	*mlx;
	int		fd;

	if (argc != 2)
		usage();
	read_file((fd = open(argv[1], O_RDONLY)),
			(mlx = init_mlx("raycaster")));
	mlx->wolf->worldMap = process_map(
			(fd = open(argv[1], O_RDONLY)), mlx);
	render_wolf(mlx);
	mlx_hook(mlx->win_ptr, 2, 0, keys, mlx);
	mlx_hook(mlx->win_ptr, 17, 0, close_wolf3d, mlx);
	signal(SIGINT, stop_music);
	system("while : ; do afplay assets/get_them.mp3 ; done &");
	mlx_loop(mlx->mlx_ptr);
	return (0);
}
