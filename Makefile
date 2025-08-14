# Makefile for the ft_printf project
NAME = pipex
# folder with src code
SRC = src

## Push_swap  
CORE = $(SRC)/core
UTILS = $(SRC)/utils
VALIDATE = $(SRC)/validate
PARSE = $(SRC)/parse

SRC_FILES = $(wildcard $(CORE)/*.c) 
SRC_FILES +=$(wildcard $(UTILS)/*.c)
SRC_FILES +=$(wildcard $(VALIDATE)/*.c) 
SRC_FILES +=$(wildcard $(PARSE)/*.c)
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
CDEBUG = -g -I$(HEADER) -o	$(TOUT) -fsanitize=address,undefined
CC = cc

all : $(NAME)

$(NAME) : $(OBJ_FILES) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ_FILES) -L$(DLIBFT) -l$(FT)

debug : $(SRC_FILES) $(LIBFT)
	$(CC) $(CDEBUG) -o $(NAME) $(SRC_FILES) -L$(DLIBFT) -l$(FT)	

$(LIBFT) :
	make -C $(DLIBFT) all

re : fclean all

fclean : clean
	rm -f $(NAME)
	make -C $(DLIBFT) fclean

clean : 
	rm -f $(STACK_OBJ)
	rm -f $(COMMON_OBJ)
	rm -f $(OBJ_FILES)
	rm -f $(TOUT)
	make -C $(DLIBFT) fclean

.PHONY: all clean fclean re #debug debug_bonus

