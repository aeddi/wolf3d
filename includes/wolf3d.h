/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeddi <aeddi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/04 13:32:03 by aeddi             #+#    #+#             */
/*   Updated: 2014/01/17 16:09:51 by aeddi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

/*
** Keys defines
*/
# define ECHAP	65307
# define LEFT	65361
# define UP		65362
# define RIGHT	65363
# define DOWN	65364

/*
** Colors defines
*/
# define SKY	0xB8E9F0
# define FLOOR	0x5E5E5E
# define RED	0xFF0000
# define GREEN	0x00FF00
# define BLUE	0x0000FF
# define YELLOW	0xFFE100

/*
** Cardinal define
*/
# define NORTH	90
# define SOUTH	270
# define EAST	0
# define WEST	180

/*
** Map define
*/
# define MAP_W	20
# define MAP_H	20
# define MAP_F	"sources/map"
# define CUBE	10240

/*
** Player define
*/
# define FOV	60
# define ROT_A	1
# define MOVE_X	fabs(COS(d->p.a) * (CUBE / 26))
# define MOVE_Y	fabs(SIN(d->p.a) * (CUBE / 26))
# define VER_X	(int)(fabs(COS(d->p.a) * (CUBE / 13)))
# define VER_Y	(int)(fabs(SIN(d->p.a) * (CUBE / 13)))

/*
** Projection define
*/
# define WIDTH	1280
# define HEIGHT	720
# define DISTP	(WIDTH / 2) / TAN(FOV / 2)
# define SUBRAY	FOV / WIDTH

/*
** Formulate define
*/
# define PI		3.14159265359
# define TAN(x)	tan(x * PI / 180.0)
# define COS(x) cos(x * PI / 180.0)
# define SIN(x) sin(x * PI / 180.0)
# define MAX_DS CUBE * (MAP_H + MAP_W)

typedef struct	s_env
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*cont;
	int			bpp;
	int			sizeline;
	int			endian;
}				t_env;

typedef struct	s_line
{
	int			x1;
	int			y1;
	int			x2;
	int			y2;
	int			color;
}				t_line;

typedef struct	s_player
{
	int			x;
	int			y;
	int			a;
}				t_player;

typedef struct	s_move
{
	int			up;
	int			down;
	int			left;
	int			right;
}				t_move;

typedef struct	s_data
{
	t_env		e;
	t_line		l;
	t_player	p;
	t_move		m;
	int			**map;
}				t_data;

/*
** Events functions
*/
int		expose_event(t_data *d);
int		key_press_event(int key, t_data *d);
int		key_release_event(int key, t_data *d);
int		loop_event(t_data *d);

/*
** Displaying functions
*/
void	put_pixel_img(t_data *d, int x, int y, int color);
void	init_img_edit(t_data *d);
void	draw_line(t_data *d, int color, int img);
void	engine(t_data *d);

/*
** Misc functions
*/
void	error_printer(char *cause);
void	move_forward(t_data *d);
void	move_backward(t_data *d);
void	rotate_player(t_player *p, char dir);
void	init_map_n_player(t_data *d);

#endif /* !WOLF3D_H */
