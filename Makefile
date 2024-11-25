CFLAGS = 
MLX_FLAGS = -framework Cocoa -framework OpenGL -framework IOKit

MLX := ~/MLX42
MLX_BUILD := $(MLX)/build
MLX_LIB = $(MLX)/build/libmlx42.a -Iinclude -lglfw

HEADERS := $(MLX)/include

MAIN_FILES = cub4d.c

OBJS_FILES = $(MAIN_FILES:.c=.o)

NAME = cub3D

all: libmlx $(NAME)

libmlx:
	@cmake $(MLX) -B $(MLX_BUILD)
	@make -C $(MLX_BUILD) -j4

%.o: %.c
	$(CC) $(CFLAGS) -c $< 

$(NAME): $(OBJS_FILES)
	$(CC) $(CFLAGS) $(OBJS_FILES) $(MLX_LIB) -o $@

clean:
	rm -rf $(OBJS_FILES)
	rm -rf $(MLX_BUILD)

fclean: clean
	rm -rf $(NAME)

re: fclean all