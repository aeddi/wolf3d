# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aeddi <aeddi@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/01/01 11:54:59 by aeddi             #+#    #+#              #
#    Updated: 2014/01/16 11:12:39 by aeddi            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 			=	wolf3d
CC 				=	gcc
GDB				?=	0
ifeq ($(GDB), 1)
	CFLAGS		=	-Wall -Wextra -Werror -g3 -I$(INCS_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)
else
	CFLAGS		=	-Wall -Wextra -Werror -O3 -I$(INCS_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)
endif
LFLAGS			=	-L$(LIBFT_DIR) -lft -L$(X11_DIR) -lXext -lX11 -L$(MLX_DIR) -lmlx -lm
X11_DIR			=	/usr/X11/lib
MLX_DIR			=	./minilibx
LIBFT_DIR		=	./libft
INCS_DIR		=	./includes
OBJS_DIR		=	./objects
SRCS_DIR		=	./sources
OBJS			=	$(patsubst %.c, $(OBJS_DIR)/%.o, $(SRCS))
SRCS			=	wolf3d.c		\
					img_tools.c		\
					draw_line.c		\
					error_printer.c	\
					map_n_moves.c	\
					events.c


all				:	$(NAME)

$(NAME)			:	$(OBJS_DIR) $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(LFLAGS) 

$(OBJS_DIR)/%.o	:	$(addprefix $(SRCS_DIR)/, %.c)
	$(CC) $(CFLAGS) -o $@ -c $^

$(OBJS_DIR)		:	make_lib
	@mkdir -p $(OBJS_DIR)

make_lib		:
	@$(MAKE) -C $(LIBFT_DIR)
	@$(MAKE) -C $(MLX_DIR)

fclean			:	clean
	rm -f $(NAME)

clean			:
	rm -rf $(OBJS_DIR)

re				:	fclean all

.PHONY: clean all re fclean
