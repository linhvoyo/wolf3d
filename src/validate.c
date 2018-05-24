#include "wolf3d.h"
#include <stdio.h>


int validate_line(char *str, int map_width, int map_height)
{
  int i;
  int count;
  i = 0;
  count = 0;
  while (str[i])
  {
    printf("%c", str[i]);
    if (map_height == 0 && str[i] == '0')
        exit(1);
    if ((i % 2 == 0) && (str[i] < '0' || str[i] > '8'))
        exit(1);
    if ((i % 2 != 0) && (str[i] != ','))
        exit(1);
    if (str[i] == ',')
      count++;
    i++;
  }
  if (i != map_width || str[0] == '0' || str[i - 1] == '0')
    exit(1);
  return count;
}

int **process_map(int fd, t_mlx *mlx)
{
  int ret;
  char *line;
  int **map;
  int i;
  int j;
  char **line_split;

  printf("width %d\n", mlx->map->mw);
  printf("height %d\n", mlx->map->mh);
  if (!(map = malloc(sizeof(int*) * mlx->map->mh)))
    exit(0);
  i = 0;
  while (i < mlx->map->mh)
     map[i++] = malloc(sizeof(int) * mlx->map->mw);
  i = 0;
  while ((ret = get_next_line(fd, &line)))
  {
    if (i == mlx->map->mh - 1)
      validate_line(line, mlx->map->mw + mlx->map->commas, 0);
    line_split = ft_strsplit(line, ',');
    j = 0;
    while (line_split[j])
    {
      map[i][j] = ft_atoi(line_split[j]);
      free(line_split[j++]);
    }
    free(line_split);
    free(line);
    i++;
  }
  close(fd);
  return (map);
}


void read_file(int fd, t_mlx *mlx)
{
  int ret;
  char *line;

  while ((ret = get_next_line(fd, &line)))
  {
    if (mlx->map->mw == 0)
      mlx->map->mw = ft_strlen(line);
    mlx->map->commas = validate_line(line, mlx->map->mw, mlx->map->mh);
    mlx->map->mh++;
    free(line);
  }
  mlx->map->mw -= mlx->map->commas;
  close(fd);
}
