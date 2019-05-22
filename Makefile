# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tnicolas <tnicolas@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/08 10:53:49 by tnicolas          #+#    #+#              #
#    Updated: 2019/05/22 19:23:42 by tnicolas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = scop
PROJECT_NAME = $(shell echo $(NAME) | tr a-z A-Z)  # name in MAJUSCULE

ARGS =

FILES = main.c \
		parser.c \
		init.c \
		callbacks.c \
		transform.c \
		draw.c \
		loop.c \
		parse_type1.c

HFILES = libft/includes/libft.h \
		 includes/scop.h \
		 includes/scop_struct.h \
		 lib/glfw_src/include/GLFW/glfw3.h

LIBFT_DIR = libft/
LIBFT = $(LIBFT_DIR)libft.a
LIBFT_LIB = -L $(LIBFT_DIR) -lft

LIBS_DIR = lib/
LIBS_LIB = -L $(LIBS_DIR)/glfw/src -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo


CC = gcc
CFLAGS = -Wall -Wno-deprecated -Wextra -g3 #-fsanitize=address # -Werror

OBJS_DIR = objs/
SRCS_DIR = srcs/

INC_DIR =	includes/ \
			$(LIBFT_DIR)includes/ \
			lib/glfw_src/include/ \

INC := $(addprefix -I , $(INC_DIR))
SRCS := $(addprefix $(SRCS_DIR), $(FILES))
OBJS := $(addprefix $(OBJS_DIR), $(FILES:.c=.o))

NORMAL = "\x1B[0m"
RED = "\x1B[31m"
GREEN = "\x1B[32m"
YELLOW = "\x1B[33m"
BLUE = "\x1B[34m"
MAGENTA = "\x1B[35m"
CYAN = "\x1B[36m"
WHITE = "\x1B[37m"
BOLD = "\e[1m"
LIGHT = "\e[2m"
ITALIC = "\e[3m"
ULINE = "\e[4m"

START = @printf $(GREEN)$(BOLD)"$(PROJECT_NAME)\n--------------------\n"$(NORMAL)
END = @printf $(GREEN)$(BOLD)"--------------------\n"$(NORMAL)

all:
	@make -C $(LIBS_DIR)
	@make -C $(LIBFT_DIR)
	$(START)
	@make $(NAME)
	$(END)

$(NAME): $(OBJS_DIR) $(OBJS) $(LIBFT)
	@printf $(CYAN)"-> create program : $(NAME)\n"$(NORMAL)
	@$(CC) -o $(NAME) $(OBJS) $(OBJS_COM) $(INC) $(CFLAGS) $(LIBFT_LIB) $(LIBS_LIB)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c $(HFILES)
	@printf $(YELLOW)"-> $<\n"$(NORMAL)
	@$(CC) -c $(INC) $< -o $@ $(CFLAGS)

$(OBJS_DIR):
	@mkdir -p $(dir $(OBJS))

clean:
	@make -C $(LIBS_DIR) clean
	@make -C $(LIBFT_DIR) clean
	$(START)
	@printf $(RED)"-x remove .o files\n"$(NORMAL)
	@rm -rf $(OBJS_DIR)
	$(END)

fclean: clean
	@make -C $(LIBS_DIR) cleanlib
	@make -C $(LIBFT_DIR) cleanlib
	$(START)
	@printf $(RED)"-x remove $(NAME)\n"$(NORMAL)
	@rm -f $(NAME)
	$(END)

re: fclean
	@make

exec:
	@clear
	@make
	@printf $(MAGENTA)$(BOLD)"EXEC $(PROJECT_NAME)\n--------------------\n"$(NORMAL)
	@./$(NAME) $(ARGS)
	@printf $(MAGENTA)$(BOLD)"--------------------\n"$(NORMAL)

.PHONY: all clean fclean re exec
