#include "wolf3d.h"
#include <stdio.h>

int keys(int key, t_mlx *mlx)
{
  (void)mlx;

  key == 53 ? exit(EXIT_SUCCESS) : 0;
  if (key == 126)
  {
      mlx->wolf->posx += mlx->wolf->dirx;
      mlx->wolf->posy += mlx->wolf->diry;
      render_wolf(mlx);
  }
  if (key == 125)
  {
      mlx->wolf->posx -= mlx->wolf->dirx;
      mlx->wolf->posy -= mlx->wolf->diry;
      render_wolf(mlx);
  }
  printf("key %d\n", key);
  // render_wolf(mlx);
  return (0);
}
