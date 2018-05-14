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
# define WIDTH 512
# define HEIGHT 384

typedef struct s_mlx
{
  void *mlx_ptr;
  void *win_ptr;
  void *img;
  int *img_ptr;
  int bbp;
  int stride;
  int endian;

}               t_mlx;

int keys(int key, t_mlx *mlx);

#endif
