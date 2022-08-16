# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: falarm <falarm@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/02 01:47:12 by falarm            #+#    #+#              #
#    Updated: 2022/08/16 15:04:06 by falarm           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	minishell

SOURCES_DIR		=	./source/
SOURCES_LIST	=	main.c		init.c		ft_cd.c		\
					ft_echo.c	ft_env.c	ft_exit.c	\
					ft_export.c	ft_pwd.c	ft_unset.c	\
					ft_free.c	env_utils.c	ft_utils.c

SOURCES			=	$(addprefix $(SOURCES_DIR), $(SOURCES_LIST))

OBJECTS_DIR		=	./objects/
OBJECTS_LIST	=	$(patsubst %.c, %.o, $(SOURCES_LIST))
OBJECTS			=	$(addprefix $(OBJECTS_DIR), $(OBJECTS_LIST))

LIBRARY			=	/home/fuse/libft/libft.a

INCLUDE			=	include/
HEADER_LIST		=	minishell.h
HEADER			=	$(addprefix $(INCLUDE), $(HEADER_LIST))

CC				=	gcc

FLAGS			=	-g -Wall -Wextra #-Werror

RM				=	rm -rf

all:				libft $(NAME)

libft:
					@$(MAKE) -sC /home/fuse/libft/
					@$(MAKE) -sC /home/fuse/libft/ bonus

$(NAME):			$(OBJECTS_DIR) $(OBJECTS)
					$(CC) $(FLAGS) $(OBJECTS) $(LIBRARY) -o $(NAME)

$(OBJECTS_DIR):
					mkdir -p $(OBJECTS_DIR)

$(OBJECTS_DIR)%.o:	$(SOURCES_DIR)%.c $(HEADER)
					$(CC) $(FLAGS) -c $< -o $@ -I $(INCLUDE)

clean:
					@$(RM) $(OBJECTS_DIR)
					@$(MAKE) -sC /home/fuse/libft/ clean

fclean:				clean
					@$(RM) $(NAME)
					@$(MAKE) -sC /home/fuse/libft/ fclean

re:					fclean all

debug:
					valgrind --leak-check=full --log-file="./report.log" ./minishell

.PHONY:				all		clean	fclean		re