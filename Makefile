# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: falarm <falarm@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/02 01:47:12 by falarm            #+#    #+#              #
#    Updated: 2022/09/08 19:59:47 by falarm           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	minishell

SOURCES_DIR		=	./source/
SOURCES_LIST	=	main.c		init.c		ft_free.c	\
					env_utils.c	ft_utils.c	ft_list.c	\
					handlers.c	errors.c	executer.c

BUILDINS_DIR	=	./source/buildins/
BUILDINS_LIST	=	ft_cd.c		ft_echo.c	ft_env.c	\
					ft_exit.c	ft_export.c	ft_pwd.c	\
					ft_unset.c

OBJECTS_DIR		=	./objects/
OBJECTS_LIST	=	$(patsubst %.c, %.o, $(SOURCES_LIST))	\
					$(patsubst %.c, %.o, $(BUILDINS_LIST))
					
OBJECTS			=	$(addprefix $(OBJECTS_DIR), $(OBJECTS_LIST))

LIBRARY			=	./libft/libft.a

INCLUDE			=	./include/
HEADER_LIST		=	minishell.h
HEADER			=	$(addprefix $(INCLUDE), $(HEADER_LIST))

CC				=	gcc

FLAGS			=	-Wall -Wextra -Werror

RM				=	rm -rf

all:				$(NAME)

$(NAME):			$(OBJECTS_DIR) $(OBJECTS) $(LIBRARY)
					$(CC) $(FLAGS) $(OBJECTS) $(LIBRARY) -lreadline -o $(NAME)

$(OBJECTS_DIR):
					mkdir -p $(OBJECTS_DIR)

$(OBJECTS_DIR)%.o:	$(BUILDINS_DIR)%.c $(HEADER)
					$(CC) $(FLAGS) -c $< -o $@ -I $(INCLUDE)

$(OBJECTS_DIR)%.o:	$(SOURCES_DIR)%.c $(HEADER)
					$(CC) $(FLAGS) -c $< -o $@ -I $(INCLUDE)

$(LIBRARY):
					@$(MAKE) -sC ./libft
					@$(MAKE) -sC ./libft bonus

clean:
					@$(RM) $(OBJECTS_DIR)
					@$(MAKE) -sC ./libft/ clean

fclean:				clean
					@$(RM) $(NAME)
					@$(MAKE) -sC ./libft/ fclean

re:					fclean all

debug:
					valgrind --leak-check=full --log-file="./report.log" ./minishell

.PHONY:				all		clean	fclean		re