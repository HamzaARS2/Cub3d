CFLAGS = 
MLX_FLAGS = -framework Cocoa -framework OpenGL -framework IOKit

MLX := MLX42
MLX_BUILD := $(MLX)/build
MLX_LIB = $(MLX)/build/libmlx42.a -L'/Users/nhimad/.brew/opt/glfw/lib/' -Iinclude -lglfw

LIBFT_DIR := ./libft
LIBFT := $(LIBFT_DIR)/libft.a

HEADERS := $(MLX)/include

GNL_FILES := gnl/get_next_line.c gnl/get_next_line_utils.c

MAIN_FILES = $(GNL_FILES) cub4d.c mapscan/mapscan.c mapscan/mp_reader.c mapscan/mp_utils.c \
mapscan/mp_checker.c mgame/game.c mgame/game_utils.c mgame/gfx_manager.c mgame/object.c renderer/renderer.c \
renderer/renderer_utils.c movement/movement.c raycaster/raycaster.c raycaster/raycaster_I.c


OBJS_FILES = $(MAIN_FILES:.c=.o)

H = ./include/game.h
NAME = cub3D

ADS := -fsanitize=address -g

all: libmlx $(NAME)

libmlx:
	@cmake $(MLX) -B $(MLX_BUILD)
	@make -C $(MLX_BUILD) -j4

$(LIBFT):
	@make -C $(LIBFT_DIR) all bonus

%.o: %.c $(H)
	$(CC) $(ADS) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS_FILES) $(LIBFT) $(H)
	$(CC) $(ADS) $(CFLAGS) $(OBJS_FILES) $(LIBFT) $(MLX_LIB) -o $@

clean:
	rm -rf $(OBJS_FILES)
	@make -C $(LIBFT_DIR) clean

fclean: clean
	rm -rf $(NAME)
	rm -rf $(MLX_BUILD)
	@make -C $(LIBFT_DIR)  fclean

re: fclean all