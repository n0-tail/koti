# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkivipur <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/10 14:45:40 by mkivipur          #+#    #+#              #
#    Updated: 2020/01/14 14:30:31 by mkivipur         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

SRCS = ./src/main.c ./src/fractal.c

OBJS = ./*.o

MLX_LNK	= -L /usr/local/lib -lmlx -I /usr/local/X11/include -L/usr/X11/lib -lX11 -lXext -framework OpenGL -framework AppKit

HDR = ./src/ 

LIBFT = libft/

FLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME):
	make -C $(LIBFT)
	gcc $(FLAGS) -o $(NAME) $(MLX_LNK) $(SRCS) -I $(HDR) -L. libft/libft.a
clean:
	/bin/rm -f $(OBJ)
	make -C $(LIBFT) clean
fclean: clean
	/bin/rm -f $(NAME)
	make -C $(LIBFT) fclean
re: fclean all
