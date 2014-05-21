/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_n_moves.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeddi <aeddi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/15 17:40:42 by aeddi             #+#    #+#             */
/*   Updated: 2014/01/17 15:00:39 by aeddi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>
#include <math.h>
#include <libft.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static void	parse_map(t_data *d, int fd)
{
	int		i;
	int		h;
	int		w;
	char	*buf;

	if ((fd = open(MAP_F, O_RDONLY)) == -1)
		error_printer(NULL);
	d->map = (int **)malloc(sizeof(int **) * MAP_H);
	h = 0;
	while (h < MAP_H)
	{
		get_next_line(fd, &buf);
		i = w = 0;
		d->map[h] = (int *)malloc(sizeof(int *) * MAP_W);
		while (buf[i] != '\0')
		{
			if (ft_isdigit(buf[i]))
				d->map[h][w++] = buf[i] - '0';
			i++;
		}
		ft_strdel(&buf);
		h++;
	}
	if ((close(fd) == -1))
		error_printer(NULL);
}

void		init_map_n_player(t_data *d)
{
	parse_map(d, 0);
	d->p.x = 15 * CUBE;
	d->p.y = 6 * CUBE;
	d->p.a = SOUTH;
	d->m.up = 0;
	d->m.down = 0;
	d->m.left = 0;
	d->m.right = 0;
}

void		move_forward(t_data *d)
{
	if (d->p.a <= NORTH
		&& d->map[(d->p.y + VER_Y) / CUBE][(d->p.x - VER_X) / CUBE] != 1)
	{
		d->p.x += MOVE_X;
		d->p.y -= MOVE_Y;
	}
	else if (d->p.a <= WEST
			&& d->map[(d->p.y - VER_Y) / CUBE][(d->p.x - VER_X) / CUBE] != 1)
	{
		d->p.x -= MOVE_X;
		d->p.y -= MOVE_Y;
	}
	else if (d->p.a <= SOUTH
			&& d->map[(d->p.y + VER_Y) / CUBE][(d->p.x - VER_X) / CUBE] != 1)
	{
		d->p.x -= MOVE_X;
		d->p.y += MOVE_Y;
	}
	else if (d->p.a > SOUTH
			&& d->map[(d->p.y + VER_Y) / CUBE][(d->p.x + VER_X) / CUBE] != 1)
	{
		d->p.x += MOVE_X;
		d->p.y += MOVE_Y;
	}
}

void		move_backward(t_data *d)
{
	if (d->p.a <= NORTH
		&& d->map[(d->p.y + VER_Y) / CUBE][(d->p.x - VER_X) / CUBE] != 1)
	{
		d->p.x -= MOVE_X;
		d->p.y += MOVE_Y;
	}
	else if (d->p.a <= WEST
			&& d->map[(d->p.y + VER_Y) / CUBE][(d->p.x + VER_X) / CUBE] != 1)
	{
		d->p.x += MOVE_X;
		d->p.y += MOVE_Y;
	}
	else if (d->p.a <= SOUTH
			&& d->map[(d->p.y - VER_Y) / CUBE][(d->p.x + VER_X) / CUBE] != 1)
	{
		d->p.x += MOVE_X;
		d->p.y -= MOVE_Y;
	}
	else if (d->p.a > SOUTH
			&& d->map[(d->p.y - VER_Y) / CUBE][(d->p.x - VER_X) / CUBE] != 1)
	{
		d->p.x -= MOVE_X;
		d->p.y -= MOVE_Y;
	}
}

void		rotate_player(t_player *p, char dir)
{
	if (dir == 'l')
		p->a = (360 + (p->a + ROT_A)) % 360;
	else if (dir == 'r')
		p->a = (360 + (p->a - ROT_A)) % 360;
}
