/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 14:54:22 by bahn              #+#    #+#             */
/*   Updated: 2022/04/21 16:33:27 by bahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_light	*light_init(t_point3 light_origin, t_color3 light_color, double bright_ratio)
{
	t_light	*light;

	light = ft_calloc(sizeof(t_light), 1);
	if (light == NULL)
		return (NULL);
	light->orig = light_origin;
	light->light_color = light_color;
	light->bright_ratio = bright_ratio;
	return (light);
}

t_color3	phong_lighting(t_scene *scene)
{
	t_color3	light_color; // 빛의 양, 정도를 저장하기 위한 변수

	scene->ambient.color = vmul_t(scene->ambient.ratio, vmul_t(1.0 / 255.0, scene->ambient.color));
	light_color = color_init(0, 0, 0); // 광원이 없을 경우, 빛의 양은 0
	light_color = get_point_light(scene); // diffuse, specular 계산

	// printf("Albedo : %f, %f, %f\n", scene->rec.albedo.x, scene->rec.albedo.y, scene->rec.albedo.z);
	// printf("Ambient Color : %f, %f, %f\n", scene->ambient.color.x, scene->ambient.color.y, scene->ambient.color.z);
	// printf("Light Color : %f, %f, %f\n", light_color.x, light_color.y, light_color.z);

	light_color = vsum(light_color, scene->ambient.color);

	
	// printf("%f, %f, %f\n", vmul(scene->rec.albedo, light_color).x, vmul(scene->rec.albedo, light_color).y, vmul(scene->rec.albedo, light_color).z);
	// sleep(1);
	return (vmin(vmul(scene->rec.albedo, light_color), color_init(1, 1, 1)));
}