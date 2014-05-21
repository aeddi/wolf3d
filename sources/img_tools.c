/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeddi <aeddi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/19 15:44:46 by aeddi             #+#    #+#             */
/*   Updated: 2014/01/17 15:00:30 by aeddi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>
#include <mlx.h>

void		init_img_edit(t_data *d)
{
	d->e.cont = mlx_get_data_addr(d->e.img, &d->e.bpp, &d->e.sizeline,
									&d->e.endian);
}

void		put_pixel_img(t_data *d, int x, int y, int color)
{
	unsigned int	pos;
	unsigned int	memcolor;

	if (x >= 0 && x <= WIDTH && y >= 0 && y <= HEIGHT)
	{
		pos = (y * d->e.sizeline) + ((d->e.bpp / 8) * x);
		memcolor = mlx_get_color_value(d->e.mlx, color);
		d->e.cont[pos + 0] = (memcolor & 0xFF);
		d->e.cont[pos + 1] = (memcolor & 0xFF00) >> 8;
		d->e.cont[pos + 2] = (memcolor & 0xFF0000) >> 16;
	}
}
