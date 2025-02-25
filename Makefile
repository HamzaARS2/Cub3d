CFLAGS = 
MLX_FLAGS = -framework Cocoa -framework OpenGL -framework IOKit

MLX := MLX42
MLX_BUILD := $(MLX)/build
MLX_LIB = $(MLX)/build/libmlx42.a -L'/Users/nhimad/.brew/opt/glfw/lib/' -Iinclude -lglfw -lm

LIBFT_DIR := ./Mandatory/libft
LIBFT := $(LIBFT_DIR)/libft.a

HEADERS := $(MLX)/include

GNL_FILES := Mandatory/gnl/get_next_line.c Mandatory/gnl/get_next_line_utils.c

MAIN_FILES = $(GNL_FILES) Mandatory/cub4d.c Mandatory/mapscan/mapscan.c Mandatory/mapscan/mp_reader.c Mandatory/mapscan/mp_utils.c \
Mandatory/mapscan/mp_checker.c Mandatory/mgame/game.c Mandatory/mgame/game_utils.c Mandatory/mgame/gfx_manager.c Mandatory/mgame/object.c \
Mandatory/renderer/renderer.c Mandatory/renderer/renderer_utils.c Mandatory/movement/movement.c Mandatory/raycaster/raycaster.c Mandatory/raycaster/raycaster_I.c


OBJS_FILES = $(MAIN_FILES:.c=.o)

H = ./Mandatory/include/game.h
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