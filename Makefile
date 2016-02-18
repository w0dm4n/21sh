# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: frmarinh <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/17 08:34:59 by frmarinh          #+#    #+#              #
#    Updated: 2016/02/18 01:35:59 by frmarinh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21sh

SRCS_NAME = main.c read_user_entry.c utils.c cursor_movement.c cursor_movement_ext.c cursor_movement_ext_2.c refresh_stdout.c cmd_logs.c handle_array.c handle_array_ext.c check_chars.c check_chars_ext.c utils_ext.c handle_keys.c handle_keys_suite.c handle_keys_suite_2.c handle_all_cmds.c handle_cmd.c do_cmd.c check_cmd.c chdir_command.c chdir_command_ext.c env_v.c check_execve.c get_path.c check_access_folder.c setenv_command.c unsetenv_command.c

LIB_FOLDER = libft/

O_NAME = $(SRCS_NAME:.c=.o)

FLAGS = -Wall -Wextra -Werror -ggdb

INCLUDE_FOLDER = libft/includes/

all: $(NAME)

$(NAME):
	@make -C libft/ fclean
	@make -C libft/
	@gcc $(FLAGS) -I $(INCLUDE_FOLDER) -c $(SRCS_NAME)
	@gcc -o $(NAME) $(O_NAME) -L $(LIB_FOLDER) -lft -ltermcap

clean:
	@rm -rf $(O_NAME)

fclean: clean
	@rm -rf $(NAME)

re:		fclean all

.PHONY: all clean fclean re
