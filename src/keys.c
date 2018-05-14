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
  }
  printf("key %d\n", key);
  wolf(mlx);
  return (0);
}
