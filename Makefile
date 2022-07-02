# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbesan <mbesan@student.21-school.ru>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/23 00:36:23 by mbesan            #+#    #+#              #
#    Updated: 2022/01/28 04:42:07 by mbesan           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

BONUS_NAME = so_long_bonus

SRCS =			src/so_long.c src/read_and_check_map.c src/game.c \
				src/termination.c src/dynamics.c src/exit_serv.c \
				libs/gnl/get_next_line.c libs/gnl/get_next_line_utils.c \

BONUS_SRCS =	bonus/so_long_bonus.c bonus/read_and_check_map_bonus.c \
				bonus/termination_bonus.c bonus/sprites_bonus.c \
				bonus/dynamics_bonus.c bonus/init_and_exit_serv_bonus.c \
				bonus/patrols_bonus.c bonus/game_bonus.c \
				bonus/score_bonus.c \
				libs/gnl/get_next_line.c libs/gnl/get_next_line_utils.c \

OBJ = $(SRCS:.c=.o)

BONUS_OBJS = $(BONUS_SRCS:.c=.o)

CC = gcc

%.o: %.c
	$(CC) -I./libs/mlxx -I./libs/gnl -g -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	make -C libs/mlxx
	$(CC) $(OBJ) -L libs/mlxx -lmlx -framework OpenGL -framework AppKit -o $(NAME)
	mv libs/mlxx/libmlx.dylib .

bonus: $(BONUS_OBJS)
	make -C libs/mlxx
	$(CC) $(BONUS_OBJS) -L libs/mlxx -lmlx -O2 -fstack-protector-strong -fPIE -framework OpenGL -framework AppKit -o $(BONUS_NAME)
	mv libs/mlxx/libmlx.dylib .

clean:
	make -C libs/mlxx clean
	rm -rf $(OBJ) $(BONUS_OBJS)

fclean:	clean
	rm -rf $(NAME) $(BONUS_NAME) libmlx.dylib

re:				fclean
				make all