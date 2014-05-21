/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeddi <aeddi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/05 09:48:43 by aeddi             #+#    #+#             */
/*   Updated: 2014/01/17 16:17:07 by aeddi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>
#include <mlx.h>
#include <libft.h>
#include <math.h>

static float	ray_caster_h(t_data *d, float ray_a)
{
	float	int_hy;
	float	int_hx;
	float	xa;
	float	ya;

	if (ray_a <= WEST)
		int_hy = (d->p.y / CUBE) * (CUBE) - 1;
	else
		int_hy = (d->p.y / CUBE) * (CUBE) + CUBE;
	int_hx = d->p.x + (d->p.y - int_hy) / TAN(ray_a);
	ya = (ray_a <= WEST) ? -CUBE : CUBE;
	xa = -ya / TAN(ray_a);
	while ((int_hx >= 0 && int_hx < CUBE * MAP_H)
			&& (int_hy >= 0 && int_hy < CUBE * MAP_H))
	{
		if (d->map[(int)(int_hy / CUBE)][(int)(int_hx / CUBE)] != 0)
			return (sqrt(pow(d->p.x - int_hx, 2) + pow(d->p.y - int_hy, 2)));
		int_hx += xa;
		int_hy += ya;
	}
	return (MAX_DS);
}

static float	ray_caster_v(t_data *d, float ray_a)
{
	float	int_vy;
	float	int_vx;
	float	xa;
	float	ya;

	if (ray_a <= NORTH || ray_a > SOUTH)
		int_vx = (d->p.x / CUBE) * (CUBE) + CUBE;
	else
		int_vx = (d->p.x / CUBE) * (CUBE) - 1;
	int_vy = d->p.y + (d->p.x - int_vx) * TAN(ray_a);
	xa = (ray_a <= NORTH || ray_a > SOUTH) ? CUBE : -CUBE;
	ya = -xa * TAN(ray_a);
	while ((int_vx >= 0 && int_vx < CUBE * MAP_H)
			&& (int_vy >= 0 && int_vy < CUBE * MAP_H))
	{
		if (d->map[(int)(int_vy / CUBE)][(int)(int_vx / CUBE)] != 0)
			return (sqrt(pow(d->p.x - int_vx, 2) + pow(d->p.y - int_vy, 2)));
		int_vx += xa;
		int_vy += ya;
	}
	return (MAX_DS);
}

static void		display_wall(t_data *d, float w_dis, int count)
{
	float	t_dis;
	float	b;
	float	p_size;

	d->l.x1 = d->l.x2 = WIDTH - 1 - count;
	d->l.y1 = 0;
	d->l.y2 = HEIGHT / 2;
	draw_line(d, SKY, 1);
	d->l.y1 = HEIGHT / 2;
	d->l.y2 = HEIGHT - 1;
	draw_line(d, FLOOR, 1);
	if (w_dis < MAX_DS)
	{
		b = fabs((FOV / 2) - (count * SUBRAY));
		t_dis = w_dis * COS(b);
		p_size = CUBE / t_dis * DISTP;
		d->l.y1 = (HEIGHT / 2) - (p_size / 2);
		d->l.y2 = p_size + d->l.y1;
		draw_line(d, d->l.color, 1);
	}
}

void			engine(t_data *d)
{
	int		count;
	float	ray_a;
	float	int_h;
	float	int_v;
	float	w_dis;

	count = 0;
	while (count != WIDTH)
	{
		ray_a = d->p.a - (FOV / 2) + ((float)count * SUBRAY);
		ray_a += (ray_a < 0) ? 360 : 0;
		ray_a -= (ray_a >= 360) ? 360 : 0;
		int_h = ray_caster_h(d, ray_a);
		int_v = ray_caster_v(d, ray_a);
		if (int_h < int_v)
			d->l.color = (ray_a <= WEST) ? BLUE : RED;
		else
			d->l.color = (ray_a <= NORTH || ray_a > SOUTH) ? GREEN : YELLOW;
		w_dis = (int_h < int_v) ? int_h : int_v;
		display_wall(d, w_dis, count);
		count++;
	}
}

int				main(void)
{
	t_data	d;

	if ((d.e.mlx = mlx_init()) == NULL)
		error_printer(NULL);
	d.e.win = mlx_new_window(d.e.mlx, WIDTH, HEIGHT, "Wolf42");
	d.e.img = mlx_new_image(d.e.mlx, WIDTH, HEIGHT);
	if (d.e.win == NULL || d.e.img == NULL)
		error_printer(NULL);
	mlx_expose_hook(d.e.win, expose_event, &d);
	mlx_do_key_autorepeatoff(d.e.mlx);
	mlx_hook(d.e.win, 2, 1, key_press_event, &d);
	mlx_hook(d.e.win, 3, 2, key_release_event, &d);
	mlx_loop_hook(d.e.mlx, loop_event, &d);
	init_map_n_player(&d);
	mlx_loop(d.e.mlx);
	return (0);
}
