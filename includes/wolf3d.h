/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilam <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 20:18:32 by lilam             #+#    #+#             */
/*   Updated: 2018/05/03 20:20:37 by lilam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H
# include "mlx.h"
# include "libft.h"
# include <math.h>
# include <time.h>
# define WIDTH 640
# define HEIGHT 480
# define texWidth 64
# define texHeight 64

typedef struct s_wolf
{
    double dirx;
    double diry;
    double posy;
    double posx;
    double planex;
    double planey;
    double rayx;
    double rayy;
    int mapx;
    int mapy;
    int **worldMap;
    int **textures;
}               t_wolf;

typedef struct s_map
{
  int mw;
  int mh;
  int commas;
}             t_map;

typedef struct s_mlx
{
  void *mlx_ptr;
  void *win_ptr;
  void *img;
  int *img_ptr;
  int bbp;
  int stride;
  int endian;
  t_wolf   *wolf;
  t_map     *map;
  // clock_t last_frame;
  // clock_t next_frame;

}               t_mlx;

int keys(int key, t_mlx *mlx);
void render_wolf(t_mlx *mlx);
void read_file(int fd, t_mlx *mlx);
int **process_map(int fd, t_mlx *mlx);
// int loop_hook(t_mlx *mlx);

#endif
