CFLAGS = 
MLX_FLAGS = -framework Cocoa -framework OpenGL -framework IOKit

MLX := ~/MLX42
MLX_BUILD := $(MLX)/build
MLX_LIB = $(MLX)/build/libmlx42.a -Iinclude -lglfw

LIBFT_DIR := ./libft
LIBFT := $(LIBFT_DIR)/libft.a

HEADERS := $(MLX)/include

GNL_FILES := gnl/get_next_line.c gnl/get_next_line_utils.c

UTILS := utils/clear_array.c

MAIN_FILES = $(GNL_FILES) $(UTILS) cub4d.c mapscan/mapscan.c mapscan/mp_reader.c mapscan/mp_utils.c \
mapscan/mp_checker.c


OBJS_FILES = $(MAIN_FILES:.c=.o)

NAME = cub3D

# ADS := -fsanitize=address -g

all: libmlx $(NAME)

libmlx:
	@cmake $(MLX) -B $(MLX_BUILD)
	@make -C $(MLX_BUILD) -j4

$(LIBFT):
	@make -C $(LIBFT_DIR) all bonus

%.o: %.c
	$(CC) $(ADS) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS_FILES) $(LIBFT)
	$(CC) $(ADS) $(CFLAGS) $(OBJS_FILES) $(LIBFT) $(MLX_LIB) -o $@

clean:
	rm -rf $(OBJS_FILES)
#	rm -rf $(MLX_BUILD)
	@make -C $(LIBFT_DIR) clean

fclean: clean
	rm -rf $(NAME)
	@make -C $(LIBFT_DIR)  fclean

re: fclean all