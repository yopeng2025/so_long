NAME      := so_long
CC        := cc

# MiniLibX
MLX_DIR   := minilibx-linux
MLX       := $(MLX_DIR)/libmlx_Linux.a

# Libft
LIBFT_DIR := Libft
LIBFT     := $(LIBFT_DIR)/libft.a

CFLAGS    ?= -Wall -Wextra -Werror -g3
INC       := -Isrc -I$(MLX_DIR) -I$(LIBFT_DIR)
LDFLAGS   := -L$(MLX_DIR) -lmlx_Linux -L$(LIBFT_DIR) -lft -lXext -lX11 -lm -lz

SRCS = src/main.c \
       src/map_parse.c \
       src/map_walls.c \
       src/path.c \
       src/close_window.c \
       src/move.c \
       src/render.c \
       src/events.c \
       src/split_lines.c \
       src/read_file.c \
       src/free.c \
       src/free_extra.c \
       src/mlx_safe.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(MLX) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(MLX) $(LIBFT) $(LDFLAGS) -o $(NAME)

src/%.o: src/%.c src/so_long.h
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(MLX):
	$(MAKE) -C $(MLX_DIR)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

bonus: CFLAGS += -DBONUS
bonus: fclean all

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(MLX_DIR) clean
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all bonus clean fclean re