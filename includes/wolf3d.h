/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmolina <nmolina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 20:18:32 by lilam             #+#    #+#             */
/*   Updated: 2018/05/28 20:26:07 by nmolina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H
# include "mlx.h"
# include "libft.h"
# include <math.h>
# include <time.h>
# include <fcntl.h>
# include <signal.h>
# define WIDTH 640
# define HEIGHT 480
# define TEX_WIDTH 64
# define TEX_HEIGHT 64

typedef struct	s_wolf
{
	double		dirx;
	double		diry;
	double		posy;
	double		posx;
	double		planex;
	double		planey;
	double		rayx;
	double		rayy;
	double		distx;
	double		disty;
	double		delta_distx;
	double		delta_disty;
	double		per_wall_dist;
	int			stepx;
	int			stepy;
	int			mapx;
	int			mapy;
	int			hit;
	int			side;
	int			drawStart;
	int			drawEnd;
	int			**worldMap;
	int			**textures;
}				t_wolf;

typedef struct	s_map
{
	int			mw;
	int			mh;
	int			commas;
}				t_map;

typedef struct	s_mlx
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img;
	int			*img_ptr;
	int			bbp;
	int			stride;
	int			endian;
	t_wolf		*wolf;
	t_map		*map;
	pthread_t	music_thr;
	int			controls;
	int	music;
}               t_mlx;

void			calculate_ray(t_mlx *mlx, int x);
void			calculate_step_sidedist(t_mlx *mlx, int x);
void			dda(t_mlx *mlx, int x);
void			draw_world(t_mlx *mlx, int x);
void			render_wolf(t_mlx *mlx);

int				validate_line(char *str, int map_width, int map_height);
int				**process_map(int fd, t_mlx *mlx);
void			read_file(int fd, t_mlx *mlx);
void			usage(void);
void			check_error(int err, char *msg);

void			rot_dir_plane(t_mlx *mlx, double theta);
void			move_up_down(t_mlx *mlx, int i);
int				keys(int key, t_mlx *mlx);
int				close_wolf3d(void);
void			stop_music();

void			draw_pixel(t_mlx *mlx, int x, int y, int color);
int				**generate_textures();
void			 put_controls(void *mlx, void *w);
t_mlx			*init_mlx(char *str);
void			play_music();

#endif
