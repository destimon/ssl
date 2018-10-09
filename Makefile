# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dcherend <dcherend@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/17 15:19:05 by dcherend          #+#    #+#              #
#    Updated: 2018/09/27 18:13:54 by dcherend         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 			= ft_ssl

LIBFT 			= $(LIBFT_DIR)libft.a
LIBFT_DIR 		= $(LIB_DIR)libft/
LIBFT_FLAGS 	= -lft -L $(LIBFT_DIR)
LIBFT_DIR 		= ./lib/libft/
LIBFT_HDR_DIR 	= ./lib/libft/
OBJ_DIR 		= ./obj/
SRC_DIR 		= ./src/

CC 				= gcc
CFLAGS 			= -I$(HDR_DIR) -I$(LIBFT_HDR_DIR) -Wall -Werror -Wextra \

SRC 			= main.c md5_algo.c core.c encrypting.c sha256_algo.c output.c
OBJ 			= $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

LIB_BIN 		= $(LIBFT_DIR)libft.a
LIB_FLAGS 		= -lft -L$(LIBFT_DIR)
LIB 			= $(MAKE) -C $(LIBFT_DIR)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(OBJ) $(LIBFT_FLAGS) -o $(NAME)

$(OBJ): | $(OBJ_DIR)

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c inc/$(HEAD)
	$(CC) -c $< -o $@ $(HEADERS_FLAGS) $(CFLAGS)

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	rm -f $(OBJ)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	rm -rf $(OBJ_DIR)
	make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re
