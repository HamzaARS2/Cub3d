CFLAGS = 
MLX_FLAGS = -framework Cocoa -framework OpenGL -framework IOKit

MLX := MLX42
MLX_BUILD := $(MLX)/build
MLX_LIB = $(MLX)/build/libmlx42.a -L'/Users/nhimad/.brew/opt/glfw/lib/' -Iinclude -lglfw -lm

LIBFT_DIR := libft
LIBFT := $(LIBFT_DIR)/libft.a

HEADERS := $(MLX)/include

MAIN_FILES = Mandatory/cub4d.c Mandatory/mapscan/mapscan.c Mandatory/mapscan/mp_reader.c Mandatory/mapscan/mp_utils.c \
Mandatory/mapscan/mp_checker.c Mandatory/mgame/game.c Mandatory/mgame/game_utils.c Mandatory/mgame/gfx_manager.c Mandatory/mgame/player.c \
Mandatory/movement/movement.c Mandatory/raycaster/raycaster.c Mandatory/raycaster/raycaster_I.c Mandatory/mgame/minimap.c

BONUS_FILES := Bonus/cub4d_bonus.c Bonus/mapscan/mapscan_bonus.c Bonus/mapscan/mp_checker_bonus.c Bonus/mapscan/mp_reader_bonus.c Bonus/mapscan/mp_utils_bonus.c \
Bonus/mgame/game_bonus.c Bonus/mgame/game_utils_bonus.c Bonus/mgame/gfx_manager_bonus.c Bonus/mgame/minimap_bonus.c Bonus/mgame/player_bonus.c \
Bonus/movement/movement_bonus.c Bonus/raycaster/raycaster_bonus.c Bonus/raycaster/raycaster_I_bonus.c

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