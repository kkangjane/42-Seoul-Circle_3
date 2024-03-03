NAME = minishell
SRCS = main.c print_error.c utils.c utils2.c\
	environ/control_env.c environ/find_env.c\
	heredoc/heredoc.c heredoc/heredoc_utils.c\
	parsing/arr_func.c parsing/attr_func.c parsing/buf_struct_func.c\
	parsing/cmd_struct_func.c parsing/env_parsing.c parsing/parsing_error.c\
	parsing/file_lst_func.c parsing/token_struct_func.c parsing/parser.c\
	process/process.c process/do_it.c process/process_error.c\
	process/open_files.c process/pipe.c process/finish_cmdline.c\
	builtin/builtin.c builtin/builtin_utils.c builtin/ft_echo.c\
	builtin/ft_env.c builtin/ft_exit.c builtin/ft_pwd.c\
	builtin/ft_unset.c builtin/ft_cd.c builtin/ft_export.c\
	signal/set_signal.c signal/signal_utils.c
OBJS = $(SRCS:.c=.o)
LIBFT = ./libft/libft.a
LIBFT_DIR = ./libft
CC = cc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lreadline -lft -L${LIBFT_DIR} \
	-L/${HOME}/.brew/Cellar/readline/8.2.7/lib \
	-I/${HOME}/.brew/Cellar/readline/8.2.7/include \

%.o : %.c
	$(CC) -c $^ -o $@ $(CFLAGS)

all : $(NAME)

$(LIBFT) :
	$(MAKE) -C $(LIBFT_DIR)

$(NAME) : $(OBJS) $(LIBFT)
	$(CC) $(OBJS) $(LIBFT) $(CFLAGS) $(LDFLAGS) -o $(NAME)

clean :
	$(MAKE) clean -C $(LIBFT_DIR)
	rm -rf $(OBJS)

fclean :
	make clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re