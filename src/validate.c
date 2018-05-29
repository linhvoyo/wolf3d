/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilam <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 18:01:54 by lilam             #+#    #+#             */
/*   Updated: 2018/05/28 18:13:10 by lilam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#define MAP_VARS int ret;char *line;int **map;int iters[2];char **line_split

int		validate_line(char *str, int map_width, int map_height)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (map_height == 0 && str[i] == '0')
			check_error(0, "all map edges must be a wall");
		if ((i % 2 == 0) && (str[i] < '0' || str[i] > '8'))
			check_error(0, "map must only consist of chars '0' - '8' or ','");
		if ((i % 2 != 0) && (str[i] != ','))
			check_error(0, "map tiles must be comma separated");
		if (str[i] == ',')
			count++;
		i++;
	}
	if (i != map_width || str[0] == '0' || str[i - 1] == '0' ||
			str[i - 1] == ',')
		check_error(0, "invalid map");
	return (count);
}

int		**process_map(int fd, t_mlx *mlx)
{
	MAP_VARS;
	if (!(map = malloc(sizeof(int*) * mlx->map->mh)))
		check_error(0, "failed to malloc map");
	iters[0] = 0;
	while (iters[0] < mlx->map->mh)
		map[iters[0]++] = malloc(sizeof(int) * mlx->map->mw);
	iters[0] = 0;
	while ((ret = get_next_line(fd, &line)))
	{
		if (iters[0] == mlx->map->mh - 1)
			validate_line(line, mlx->map->mw + mlx->map->commas, 0);
		line_split = ft_strsplit(line, ',');
		iters[1] = 0;
		while (line_split[iters[1]])
		{
			map[iters[0]][iters[1]] = ft_atoi(line_split[iters[1]]);
			free(line_split[iters[1]++]);
		}
		free(line_split);
		free(line);
		iters[0]++;
	}
	close(fd);
	return (map);
}

void	read_file(int fd, t_mlx *mlx)
{
	int		ret;
	char	*line;

	check_error(fd, "failed to open file. (check filepath)");
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

void	usage(void)
{
	ft_putstr("usage: ./wolf3d <MAP_FILE>\n");
	exit(EXIT_SUCCESS);
}

void	check_error(int err, char *msg)
{
	if (err < 1)
	{
		ft_putstr("- ERROR: ");
		ft_putstr(msg);
		ft_putstr("\n");
		exit(1);
	}
}
