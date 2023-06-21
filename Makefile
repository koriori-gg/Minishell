NAME = minishell

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

RL_DIR = $(shell brew --prefix readline)

LIBS = -lreadline -L$(RL_DIR)/lib

CC = cc
INCLUDES = -I $(LIBFT_DIR)/inc -I inc -I $(RL_DIR)/include
CFLAGS = -Wall -Wextra -Werror $(INCLUDES)

SRCS = src/minishell.c \
	src/redirect/redirection.c \
	src/redirect/stash_fd.c \
	src/redirect/heredoc.c \
	src/error/error1.c \
	src/error/error2.c \
	src/error/print_error.c \
	src/error/print_error_utils1.c \
	src/error/print_error_utils2.c \
	src/parser/parser.c \
	src/parser/node_operators.c \
	src/parser/free_node.c \
	src/parser/check_operator.c \
	src/tokenizer/tokenizer.c \
	src/tokenizer/tokenizer_helpers.c \
	src/tokenizer/token_operators.c \
	src/tokenizer/tokens_to_argv.c \
	src/expansion/expansion.c \
	src/expansion/expand_variables.c \
	src/expansion/expand_quotes.c \
	src/expansion/is_variable.c \
	src/expansion/remove_quote.c \
	src/expansion/append_char.c \
	src/execute/check_path.c \
	src/execute/validate_path.c \
	src/execute/execute.c \
	src/execute/execute_command.c \
	src/execute/search_path.c \
	src/execute/validate_redirect.c \
	src/execute/pipe.c \
	src/env/init_env.c \
	src/env/delete_env.c \
	src/env/update_env.c \
	src/env/env_operators.c \
	src/env/environ.c \
	src/builtin/echo.c \
	src/builtin/exit.c \
	src/builtin/pwd.c \
	src/builtin/env.c \
	src/builtin/export.c \
	src/builtin/unset.c \
	src/builtin/cd.c \
	src/builtin/execute_builtin.c \
	src/signal/signal.c \
	src/utils/try_calloc.c \
	src/utils/try_strdup.c \
	src/utils/try_strndup.c \
	src/utils/print_debug.c \

OBJS = $(SRCS:%.c=%.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(LIBFT) $(OBJS) $(LIBS)

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	make clean -C $(LIBFT_DIR)
	$(RM) $(OBJS)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	$(RM) $(NAME)

re: fclean all

debug: $(LIBFT) $(OBJS)
	$(CC) -fsanitize=address $(CFLAGS) -o $(NAME) $(LIBFT) $(OBJS) $(LIBS)

.PONEY: all clean fclean re
