NAME	= cub3d
CC		= cc
CFLAGS	= -Wall -Wextra -Werror

SRCS	= src/main.c \
		  src/init.c \
		  src/freeall.c \
		  src/parser/main_parse.c \
		  src/parser/parse_config.c \
		  src/parser/map_validation.c

OBJ_DIR	= obj
OBJS	= $(addprefix $(OBJ_DIR)/,$(SRCS:.c=.o))

LIBFT	= libft/libft.a
MLX		= minilibx-linux/libmlx.a
MLX_FLAGS = -Lminilibx-linux -lmlx -lX11 -lXext -lm

all: $(NAME)

$(LIBFT):
	$(MAKE) -C libft

$(MLX):
	$(MAKE) -C minilibx-linux

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I includes -I libft -I minilibx-linux -c $< -o $@

clean:
	$(MAKE) -C libft clean
	$(MAKE) -C minilibx-linux clean
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
