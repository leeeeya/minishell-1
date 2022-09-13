NAME			=	minishell_parser

SOURSES_DIR		=	./parser/
SOURSES_LIST	=	env.c	errors.c	get_args.c		\
					main.c	quotes.c	search_path.c	\
					utils.c	input_utils.c	input_delete.c

OBJECTS_DIR		=	./objects/
OBJECTS_LIST	=	$(patsubst %.c, %.o, $(SOURSES_LIST))
OBJECTS			=	$(addprefix $(OBJECTS_DIR), $(OBJECTS_LIST))

LIBRARY			=	./parser/libft/libft.a

HEADERS_DIR		=	./parser/
HEADERS_LIST	=	parser.h
INCLUDE			=	$(addprefix $(HEADERS_DIR), $(HEADERS_LIST))

CC				=	gcc 
FLAGS			=	-Wall -Wextra -Werror
RM				=	rm -rf

all:				libft $(NAME)

libft:
					@$(MAKE) -sC ./parser/libft

$(NAME):			$(OBJECTS_DIR) $(OBJECTS)
					$(CC) $(FLAGS) $(OBJECTS) $(LIBRARY) -lreadline -o $(NAME)

$(OBJECTS_DIR):
					mkdir -p $(OBJECTS_DIR)

$(OBJECTS_DIR)%.o:	$(SOURSES_DIR)%.c $(INCLUDE)
					$(CC) $(FLAGS) -c $< -o $@ -I $(HEADERS_DIR)

clean:
					@$(RM) $(OBJECTS_DIR)
					@$(MAKE) -sC ./parser/libft clean

fclean:				clean
					@$(RM) $(NAME)
					@$(MAKE) -sC ./parser/libft fclean
				
re:					fclean all

.PHONY:				all clean fclean re
