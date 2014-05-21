/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeddi <aeddi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/19 16:06:21 by aeddi             #+#    #+#             */
/*   Updated: 2014/01/17 15:00:13 by aeddi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>
#include <mlx.h>
#include <libft.h>

static void		draw_right_h(t_data *d, int color, int img)
{
	int	x;

	x = d->l.x1;
	while (x <= d->l.x2 && img)
	{
		put_pixel_img(d, x, d->l.y1 + ((d->l.y2 - d->l.y1)
						* (x - d->l.x1)) / (d->l.x2 - d->l.x1), color);
		x++;
	}
	while (x <= d->l.x2 && !img)
	{
		mlx_pixel_put(d->e.mlx, d->e.win, x, d->l.y1 + ((d->l.y2 - d->l.y1)
						* (x - d->l.x1)) / (d->l.x2 - d->l.x1), color);
		x++;
	}
}

static void		draw_left_h(t_data *d, int color, int img)
{
	int	x;

	x = d->l.x2;
	while (x <= d->l.x1 && img)
	{
		put_pixel_img(d, x, d->l.y2 + ((d->l.y1 - d->l.y2)
						* (x - d->l.x2)) / (d->l.x1 - d->l.x2), color);
		x++;
	}
	while (x <= d->l.x1 && !img)
	{
		mlx_pixel_put(d->e.mlx, d->e.win, x, d->l.y2 + ((d->l.y1 - d->l.y2)
						* (x - d->l.x2)) / (d->l.x1 - d->l.x2), color);
		x++;
	}
}

static void		draw_up_v(t_data *d, int color, int img)
{
	int	y;

	y = d->l.y2;
	while (y <= d->l.y1 && img)
	{
		put_pixel_img(d, d->l.x2 + ((d->l.x1 - d->l.x2)
						* (y - d->l.y2)) / (d->l.y1 - d->l.y2), y, color);
		y++;
	}
	while (y <= d->l.y1 && !img)
	{
		mlx_pixel_put(d->e.mlx, d->e.win, d->l.x2 + ((d->l.x1 - d->l.x2)
						* (y - d->l.y2)) / (d->l.y1 - d->l.y2), y, color);
		y++;
	}
}

static void		draw_down_v(t_data *d, int color, int img)
{
	int	y;

	y = d->l.y1;
	while (y <= d->l.y2 && img)
	{
		put_pixel_img(d, d->l.x1 + ((d->l.x2 - d->l.x1)
						* (y - d->l.y1)) / (d->l.y2 - d->l.y1), y, color);
		y++;
	}
	while (y <= d->l.y2 && !img)
	{
		mlx_pixel_put(d->e.mlx, d->e.win, d->l.x1 + ((d->l.x2 - d->l.x1)
						* (y - d->l.y1)) / (d->l.y2 - d->l.y1), y, color);
		y++;
	}
}

void			draw_line(t_data *d, int color, int img)
{
	if (d->l.x1 <= d->l.x2 && (d->l.x2 - d->l.x1) >= ft_abs(d->l.y2 - d->l.y1))
			draw_right_h(d, color, img);
	if (d->l.x2 <= d->l.x1 && (d->l.x1 - d->l.x2) >= ft_abs(d->l.y1 - d->l.y2))
			draw_left_h(d, color, img);
	if (d->l.y2 <= d->l.y1 && (d->l.y1 - d->l.y2) >= ft_abs(d->l.x1 - d->l.x2))
			draw_up_v(d, color, img);
	if (d->l.y1 <= d->l.y2 && (d->l.y2 - d->l.y1) >= ft_abs(d->l.x2 - d->l.x1))
			draw_down_v(d, color, img);
}
