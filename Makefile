# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/06 15:43:27 by agiraude          #+#    #+#              #
#    Updated: 2022/02/05 15:32:51 by agiraude         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
NAME			=	philo

INC_DIR			=	-I includes/ 

DEP				=	-pthread

SRCS_FILE		=	forkmaster.c \
					main.c \
					philo.c \
					room.c \
					utils.c

SRCS_DIR		=	srcs/

SRCS			=	$(addprefix $(SRCS_DIR), $(SRCS_FILE))

OBJS			=	$(SRCS:.c=.o)

CFLAGS			=	-Wall -Wextra -g $(INC_DIR)

CC				=	clang

%.o:			%.s
				$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME):		$(OBJS)
				$(CC) $(CFLAGS) $(OBJS) $(DEP) -o $(NAME)

all:			$(NAME)

clean:
				rm -f $(OBJS)

fclean:			clean
				rm -f $(NAME)

re:				fclean all

.PHONY:			all clean flcean re
