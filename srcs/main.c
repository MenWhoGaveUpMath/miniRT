/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 12:54:42 by bahn              #+#    #+#             */
/*   Updated: 2022/04/27 01:55:35 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	init_scene(t_scene *scene, int argc, char const *argv[])
{
	if (argc > 3)
	{
		printf("Invalid Arguments\n");
		printf("./miniRT\n");
		exit(1);
	}
	else if (argc >= 2)
	{
		if (argc == 3 && ft_strncmp((char*)argv[2], "--save", 6))
		{
			printf("Invalid Arguments\n");
			printf("./miniRT\n");
			exit(1);
		}
		scene->camera = NULL;
		scene->lights = NULL;
		scene->objects = NULL;
		parse_file(scene, argv[1]);
	}
	else
	{
		printf("Error\n");
		exit(1);
	}
	scene->vars = ft_calloc(sizeof(t_vars), 1);
	scene->vars->mlx = mlx_init();
	scene->vars->win = mlx_new_window(scene->vars->mlx, WIDTH, HEIGHT, "miniRT");
	
	scene->vars->img_data = ft_calloc(sizeof(t_img_data), 1);
	scene->vars->img_data->img = mlx_new_image(scene->vars->mlx, WIDTH, HEIGHT);
	scene->vars->img_data->addr = mlx_get_data_addr(scene->vars->img_data->img, \
												&scene->vars->img_data->bits_per_pixel, \
												&scene->vars->img_data->line_length, \
												&scene->vars->img_data->endian);

	init_canvas(scene, WIDTH, HEIGHT);
	init_camera(scene);
}

int main(int argc, char const *argv[])
{
	t_scene		scene;
	
	init_scene(&scene, argc, argv);
	
	output_scene(&scene);

	mlx_hook(scene.vars->win, 2, 1L << 0, minirt_esc, &scene);
	mlx_hook(scene.vars->win, 17, 1L << 2, minirt_close, &scene);

	mlx_key_hook(scene.vars->win, camera_move, &scene);
	mlx_mouse_hook(scene.vars->win, camera_zoom, &scene);

	mlx_loop(scene.vars->mlx);
	return 0;
}
