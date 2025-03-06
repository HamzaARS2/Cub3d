CFLAGS = 
MLX_FLAGS = -framework Cocoa -framework OpenGL -framework IOKit

MLX := MLX42
MLX_BUILD := $(MLX)/build
MLX_LIB = $(MLX)/build/libmlx42.a -Iinclude -lglfw -lm

LIBFT_DIR := libft
LIBFT := $(LIBFT_DIR)/libft.a

HEADERS := $(MLX)/include

MAIN_FILES = Mandatory/cub4d.c Mandatory/mapscan/mapscan.c Mandatory/mapscan/mp_reader.c Mandatory/mapscan/mp_utils.c \
Mandatory/mapscan/mp_checker.c Mandatory/mgame/game.c Mandatory/mgame/game_utils.c Mandatory/mgame/gfx_manager.c Mandatory/mgame/player.c \
Mandatory/movement/movement.c Mandatory/raycaster/raycaster.c Mandatory/raycaster/raycaster_I.c Mandatory/mgame/minimap.c \
Mandatory/world/world.c Mandatory/world/world_utils.c

BONUS_FILES := Bonus/cub4d_bonus.c Bonus/mapscan/mapscan_bonus.c Bonus/mapscan/mp_checker_bonus.c Bonus/mapscan/mp_reader_bonus.c Bonus/mapscan/mp_utils_bonus.c \
Bonus/mgame/game_bonus.c Bonus/mgame/game_utils_bonus.c Bonus/mgame/gfx_manager_bonus.c Bonus/mgame/minimap_bonus.c Bonus/mgame/player_bonus.c \
Bonus/movement/movement_bonus.c Bonus/raycaster/raycaster_bonus.c Bonus/raycaster/raycaster_I_bonus.c Bonus/world/world_bonus.c

OBJS_FILES = $(MAIN_FILES:.c=.o)
BONUS_OBJS_FILES = $(BONUS_FILES:.c=.o)

HEADER = ./Mandatory/include/game.h
BONUS_HEADER = ./Bonus/include/game_bonus.h
NAME = cub3D
BONUS_NAME = cub3D_bonus

ADS := -fsanitize=address -g

all: libmlx $(NAME)

bonus: libmlx $(BONUS_OBJS_FILES) $(LIBFT) $(BONUS_HEADER)
	$(CC) $(ADS) $(CFLAGS) $(BONUS_OBJS_FILES) $(LIBFT) $(MLX_LIB) -o $(BONUS_NAME)

libmlx:
	@cmake $(MLX) -B $(MLX_BUILD)
	@make -C $(MLX_BUILD) -j4

$(LIBFT):
	@make -C $(LIBFT_DIR) all bonus

%.o: %.c $(H)
	$(CC) $(ADS) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS_FILES) $(LIBFT) $(HEADER)
	$(CC) $(ADS) $(CFLAGS) $(OBJS_FILES) $(LIBFT) $(MLX_LIB) -o $@

clean:
	rm -rf $(OBJS_FILES)
	rm -rf $(BONUS_OBJS_FILES)
	@make -C $(LIBFT_DIR) clean

fclean: clean
	rm -rf $(NAME)
	rm -rf $(BONUS_NAME)
	rm -rf $(MLX_BUILD)
	@make -C $(LIBFT_DIR)  fclean

re: fclean all