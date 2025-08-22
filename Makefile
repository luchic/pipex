# Makefile for the ft_printf project
NAME = pipex
# folder with src code
SRC = src

## Push_swap  
CORE = $(SRC)/core/ft_open_files.c \
	   $(SRC)/core/ft_run_child.c \
	   $(SRC)/core/ft_run_proccess.c 
UTILS = $(SRC)/utils/ft_free.c \
		$(SRC)/utils/ft_pipes.c 
VALIDATE = 	$(SRC)/validate/ft_validate_cmd.c \
			$(SRC)/validate/ft_validate_file.c 
ERROR = $(SRC)/error/ft_errormsg.c

PARSE =		$(SRC)/parse
APARSE = 	$(PARSE)/args/ft_copy_arg.c \
			$(PARSE)/args/ft_parse_args.c \
			$(PARSE)/args/ft_update_args.c \
			$(PARSE)/args/ft_split_args.c 
EPARSE =	$(PARSE)/env/ft_default.c \
			$(PARSE)/env/ft_parse_env.c

SRC_FILES = $(CORE)
SRC_FILES +=$(UTILS)
SRC_FILES +=$(VALIDATE) 
SRC_FILES +=$(ERROR)
SRC_FILES +=$(APARSE)
SRC_FILES +=$(EPARSE)
SRC_FILES += $(SRC)/main.c

OBJ_FILES = $(SRC_FILES:.c=.o)

# Header
HEADER = includes

# Libft
DLIBFT = libft
LIBFT = $(DLIBFT)/libft.a
FT = ft

# For tests
TOUT = a.out

# Compiler and flags
CFLAGS = -Wall -Wextra -Werror -I$(HEADER)
CDEBUG = -g -I$(HEADER) -fsanitize=address,undefined
CC = cc

all : $(NAME)

$(NAME) : $(OBJ_FILES) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ_FILES) -L$(DLIBFT) -l$(FT)

bonus : all

debug : $(SRC_FILES) $(LIBFT)
	$(CC) $(CDEBUG) -o $(NAME) $(SRC_FILES) -L$(DLIBFT) -l$(FT)	

$(LIBFT) :
	make -C $(DLIBFT) all

re : fclean all

fclean : clean
	rm -f $(NAME)
	make -C $(DLIBFT) fclean

clean : 
	rm -f $(OBJ_FILES)
	make -C $(DLIBFT) clean

.PHONY: all clean fclean re #debug debug_bonus

