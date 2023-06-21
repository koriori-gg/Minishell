NAME = libft.a

CC = cc
INCLUDES = -I inc
CFLAGS = -Wall -Wextra -Werror $(INCLUDES)

SRCS = $(LIBFT_SRCS) $(PRINTF_SRCS) $(GNL_SRCS)

LIBFT_SRCS = \
	src/libft/ft_atoi.c \
	src/libft/ft_bzero.c \
	src/libft/ft_calloc.c \
	src/libft/ft_isalnum.c \
	src/libft/ft_isalpha.c \
	src/libft/ft_isascii.c \
	src/libft/ft_isdigit.c \
	src/libft/ft_isprint.c \
	src/libft/ft_itoa.c \
	src/libft/ft_memchr.c \
	src/libft/ft_memcmp.c \
	src/libft/ft_memcpy.c \
	src/libft/ft_memmove.c \
	src/libft/ft_memset.c \
	src/libft/ft_putchar_fd.c \
	src/libft/ft_strchr.c \
	src/libft/ft_strdup.c \
	src/libft/ft_strjoin.c \
	src/libft/ft_strlcat.c \
	src/libft/ft_strlcpy.c \
	src/libft/ft_strlen.c \
	src/libft/ft_strncmp.c \
	src/libft/ft_strnstr.c \
	src/libft/ft_strrchr.c \
	src/libft/ft_substr.c \
	src/libft/ft_tolower.c \
	src/libft/ft_toupper.c \
	src/libft/ft_split.c \
	src/libft/ft_strtrim.c \
	src/libft/ft_strmapi.c \
	src/libft/ft_putstr_fd.c \
	src/libft/ft_putendl_fd.c \
	src/libft/ft_putnbr_fd.c \
	src/libft/ft_striteri.c \
	src/libft/ft_lstnew.c \
	src/libft/ft_lstadd_front.c \
	src/libft/ft_lstsize.c \
	src/libft/ft_lstlast.c \
	src/libft/ft_lstadd_back.c \
	src/libft/ft_lstdelone.c \
	src/libft/ft_lstclear.c \
	src/libft/ft_lstiter.c \
	src/libft/ft_lstmap.c \
	src/libft/free_double_pointer.c \
	src/libft/ft_strndup.c

PRINTF_SRCS = \
	src/ft_printf/ft_printf.c \
	src/ft_printf/ft_printf_utils1.c \
	src/ft_printf/ft_printf_utils2.c

GNL_SRCS = \
	src/get_next_line/get_next_line_utils.c \
	src/get_next_line/get_next_line.c

OBJS = $(SRCS:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar -r $(NAME) $(OBJS)

clean:
	$(RM) -r $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
