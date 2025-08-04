NAME = so_long
CC = cc
MLX_DIR = minilibx-linux
MLX = $(MLX_DIR)/libmlx_Linux.a

CFLAGS = -Wall -Wextra -Werror -Isrc -Iminilibx-linux
LDFLAGS = -L$(MLX_DIR) -lmlx_Linux -lXext -lX11 -lm -lz

SRCS = src/main.c src/map.c src/utils.c src/render.c src/events.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C $(MLX_DIR)
	$(CC) $(CFLAGS) $(OBJS) $(MLX) $(LDFLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

bonus: CFLAGS += -DBONUS
bonus: fclean all

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
