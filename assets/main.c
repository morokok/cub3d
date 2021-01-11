/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarzouk <mmarzouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 07:27:16 by mmarzouk          #+#    #+#             */
/*   Updated: 2020/12/22 20:38:59 by mmarzouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	ta_sir(char *s)
{
	write(1, "Error \n", 7);
	ft_putstr_fd(s, 1);
	write(1, "\n", 1);
	exit(0);
}

int		end(int x, void *s)
{
	mlx_destroy_window(g_ptr, g_win);
	exit(0);
}

int		try(int x, void *s)
{
	int i;

	if (x == W)
	{
		g_map.nppy = g_map.ppy + sin(g_map.pdrct) * STP;
		g_map.nppx = g_map.ppx + cos(g_map.pdrct) * STP;
	}
	if (x == A)
	{
		g_map.nppy = g_map.ppy - sin(g_map.pdrct + M_PI / 2) * STP;
		g_map.nppx = g_map.ppx - cos(g_map.pdrct + M_PI / 2) * STP;
	}
	if (x == S)
	{
		g_map.nppy = g_map.ppy - sin(g_map.pdrct) * STP;
		g_map.nppx = g_map.ppx - cos(g_map.pdrct) * STP;
	}
	if (x == D)
	{
		g_map.nppy = g_map.ppy + sin(g_map.pdrct + M_PI / 2) * STP;
		g_map.nppx = g_map.ppx + cos(g_map.pdrct + M_PI / 2) * STP;
	}
	if (x == 53)
		end(x, s);
	if (x == 124)
		g_map.pdrct += M_PI / 12;
	if (x == 123)
		g_map.pdrct -= M_PI / 12;
	mlx_destroy_image(g_ptr, g_image);
	g_image = mlx_new_image(g_ptr, g_tool.xa, g_tool.ya);
	g_screen = (int *)mlx_get_data_addr(g_image, &i, &i, &i);
	correcting_angle();
	wall();
	floor_ceiling();
	updis();
	ft_fov();
	render_sprite();
	mlx_put_image_to_window(g_ptr, g_win, g_image, 0, 0);
	return (0);
}

void	looping(void)
{
	int i;
	int j;
	int k;

	g_win = mlx_new_window(g_ptr, g_tool.xa, g_tool.ya, "image");
	g_image = mlx_new_image(g_ptr, g_tool.xa, g_tool.ya);
	if (g_image == NULL)
		ta_sir("couldn't make an image");
	g_screen = (int *)mlx_get_data_addr(g_image, &i, &j, &k);
	mlx_hook(g_win, 2, 1, try, NULL);
	mlx_hook(g_win, 17, 0, end, NULL);
	render();
	mlx_loop(g_ptr);
}

int		main(int argc, char **argv)
{
	int fd;
	if (argc != 2 && argc != 3)
		ta_sir("wrong number of arguments");
	fd = chk_file(argv[1]);
	init();
	ft_gnl(fd);
	handling_errors();
	spalloc();
	init_sprites();
	if(argc == 3)
	{
		
		save_flag(argv[2]);
	}
	looping();
	return (0);
}