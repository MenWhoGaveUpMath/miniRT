/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 13:17:09 by bahn              #+#    #+#             */
/*   Updated: 2022/04/20 16:47:08 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	output_scene(t_scene *scene)
{
	int			w;
	int			h;
	double		u;
	double		v;

	h = scene->canvas.height - 1;
	while (h >= 0)
	{
		w = 0;
		while (w < scene->canvas.width)
		{
			u = (double)w / (scene->canvas.width);
			v = (double)h / (scene->canvas.height);
			scene->ray = ray_primary(scene->camera->content, u, v);
			minirt_pixel_put_vector(scene->vars->img_data, w, scene->canvas.height - 1 - h, write_color(ray_color(scene)));
			w++;
		}
		h--;
	}
	mlx_put_image_to_window(scene->vars->mlx, scene->vars->win, scene->vars->img_data->img, 0, 0);
}