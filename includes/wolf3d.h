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


typedef struct s_mlx
{
  void *mlx_ptr;
  void *win_ptr;
}               t_mlx;

int keys(int key, t_mlx *mlx);

#endif
