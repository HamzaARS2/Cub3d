CC = cc
#CFLAGS = -Wall -Wextra -Werror
SRC_FILES = ft_isalnum.c ft_isdigit.c ft_memmove.c ft_strlcat.c ft_tolower.c \
             ft_isalpha.c ft_isprint.c ft_memset.c ft_strlcpy.c ft_toupper.c \
             ft_bzero.c ft_isascii.c ft_memcpy.c ft_strchr.c ft_strlen.c ft_strrchr.c \
			 ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c \
			 ft_strncmp.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c \
			 ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
			 ft_putnbr_fd.c get_next_line_utils.c get_next_line.c $(ADDONS)

BONUS_FILES = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c \
			  ft_lstclear.c ft_lstiter.c ft_lstmap.c

ADDONS = ft_iswhitespace.c ft_clear_array.c ft_charcount.c get_rgba.c ft_lstcontent_max.c free_array.c

OBJ_FILES = $(SRC_FILES:.c=.o)
BONUS_OBJ = $(BONUS_FILES:.c=.o)
NAME = libft.a

all: $(NAME)

bonus: $(BONUS_OBJ)
	ar rcs $(NAME) $^

$(NAME): $(OBJ_FILES)
	ar rcs $@ $^

%.o: %.c libft.h
	@$(CC) -c $(CFLAGS) $< -o $@

clean:
	@rm -f $(OBJ_FILES) $(BONUS_OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all 

.PHONY: clean


