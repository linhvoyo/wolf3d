#include "wolf3d.h"
#include <stdio.h>

int keys(int key, t_mlx *mlx)
{
  (void)mlx;

  key == 53 ? exit(EXIT_SUCCESS) : 0;
  if (key == 126)
  {
    if (!(mlx->wolf->worldMap[(int)(mlx->wolf->posx + mlx->wolf->dirx * 0.15)][(int)(mlx->wolf->posy)]))
        mlx->wolf->posx += mlx->wolf->dirx * 0.15;
    if (!(mlx->wolf->worldMap[(int)(mlx->wolf->posx)][(int)(mlx->wolf->posy + mlx->wolf->diry * 0.15)]))
        mlx->wolf->posy += mlx->wolf->diry * 0.15;
    render_wolf(mlx);
  }
  if (key == 125)
  {
    if (!(mlx->wolf->worldMap[(int)(mlx->wolf->posx - mlx->wolf->dirx * 0.15)][(int)(mlx->wolf->posy)]))
        mlx->wolf->posx -= mlx->wolf->dirx * 0.15;
    if (!(mlx->wolf->worldMap[(int)(mlx->wolf->posx)][(int)(mlx->wolf->posy - mlx->wolf->diry * 0.15)]))      mlx->wolf->posy -= mlx->wolf->diry * 0.15;
    render_wolf(mlx);
  }
  if (key == 124)
  {
      double olddirx = mlx->wolf->dirx;
      mlx->wolf->dirx = mlx->wolf->dirx * cos(-0.045) - mlx->wolf->diry * sin(-0.045);
      mlx->wolf->diry = olddirx * sin(-0.045) + mlx->wolf->diry * cos(-0.045);
      double oldplanex = mlx->wolf->planex;
      mlx->wolf->planex = mlx->wolf->planex * cos(-0.045) - mlx->wolf->planey * sin(-0.045);
      mlx->wolf->planey = mlx->wolf->planex * sin(-0.045) + mlx->wolf->planey * cos(-0.045);
      render_wolf(mlx);
  }
  if (key == 123)
  {
      double olddirx = mlx->wolf->dirx;
      mlx->wolf->dirx = mlx->wolf->dirx * cos(0.045) - mlx->wolf->diry * sin(0.045);
      mlx->wolf->diry = olddirx * sin(0.045) + mlx->wolf->diry * cos(0.045);
      double oldplanex = mlx->wolf->planex;
      mlx->wolf->planex = mlx->wolf->planex * cos(0.045) - mlx->wolf->planey * sin(0.045);
      mlx->wolf->planey = mlx->wolf->planex * sin(0.045) + mlx->wolf->planey * cos(0.045);
      render_wolf(mlx);
  }
  printf("key %d\n", key);
  // render_wolf(mlx);
  return (0);
}

int loop_hook(t_mlx *mlx)
{

    // printf("current_frame fps %lu\n", mlx->last_frame - mlx->next_frame);
    // mlx->next_frame = mlx->last_frame;
    mlx->last_frame = clock();
    if (mlx->next_frame > mlx->last_frame)
        return (0);
    // printf("current_frame fps %lu\n", mlx->next_frame - mlx->last_frame);
    mlx->next_frame = mlx->last_frame + (CLOCKS_PER_SEC / 1000);
    // printf("next_frame fps %lu\n", mlx->next_frame);
    // printf("last_frame fps %lu\n", mlx->last_frame);
    printf("current_frame fps %lu\n", mlx->next_frame - mlx->last_frame);
    // mlx->next_frame = mlx->last_frame + (CLOCKS_PER_SEC / 100000);
    // render_wolf(mlx);
    return (0);
}