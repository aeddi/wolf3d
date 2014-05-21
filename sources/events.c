/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeddi <aeddi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/30 13:23:25 by aeddi             #+#    #+#             */
/*   Updated: 2014/01/17 15:00:09 by aeddi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>
#include <mlx.h>
#include <stdlib.h>

int		expose_event(t_data *d)
{
	init_img_edit(d);
	engine(d);
	mlx_put_image_to_window(d->e.mlx, d->e.win, d->e.img, 0, 0);
	return (0);
}

int		key_press_event(int key, t_data *d)
{
	if (key == UP)
		d->m.up = 1;
	if (key == DOWN)
		d->m.down = 1;
	if (key == LEFT)
		d->m.left = 1;
	if (key == RIGHT)
		d->m.right = 1;
	if (key == ECHAP)
	{
		mlx_do_key_autorepeaton(d->e.mlx);
		exit(0);
	}
	return (0);
}

int		key_release_event(int key, t_data *d)
{
	if (key == UP)
		d->m.up = 0;
	if (key == DOWN)
		d->m.down = 0;
	if (key == LEFT)
		d->m.left = 0;
	if (key == RIGHT)
		d->m.right = 0;
	return (0);
}

int		loop_event(t_data *d)
{
	if (d->m.up)
		move_forward(d);
	if (d->m.down)
		move_backward(d);
	if (d->m.left)
		rotate_player(&d->p, 'l');
	if (d->m.right)
		rotate_player(&d->p, 'r');
	expose_event(d);
	return (0);
}
