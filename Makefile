# **************************************************************************** #
#                                CUB3D MAKEFILE                                #
# **************************************************************************** #

NAME        := cub3d
CC          := cc
CFLAGS      := -Wall -Wextra -Werror -g
RM          := rm -rf

# Valgrind rules
VALGRIND       = valgrind
VALGRIND_FLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes

valgrind: $(NAME)
	$(VALGRIND) $(VALGRIND_FLAGS) ./$(NAME) maps/test.cub

valgrind-full: $(NAME)
	$(VALGRIND) $(VALGRIND_FLAGS) ./$(NAME) maps/test.cub

SRC_DIRS    := src src/parser src/3d_engine src/2d_engine src/player
OBJ_DIR     := obj
LIBFT_DIR   := libft
MLX_DIR     := minilibx-linux
INCLUDE_DIR := includes

LIBFT       := $(LIBFT_DIR)/libft.a
MLX         := $(MLX_DIR)/libmlx.a
HEADERS     := -I$(INCLUDE_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)
MLX_FLAGS   := -L$(MLX_DIR) -lmlx -lX11 -lXext -lm

SRC         := $(foreach dir, $(SRC_DIRS), $(wildcard $(dir)/*.c))
OBJ         := $(patsubst %.c, $(OBJ_DIR)/%.o, $(notdir $(SRC)))
SRC_TO_OBJ_MAP = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.c=.o)))

all: $(OBJ_DIR) $(LIBFT) $(MLX) $(NAME)

$(NAME): $(SRC_TO_OBJ_MAP) $(LIBFT) $(MLX)
	@echo "Linking $(NAME)..."
	@$(CC) $(CFLAGS) $(SRC_TO_OBJ_MAP) -L$(LIBFT_DIR) -lft $(MLX_FLAGS) -o $(NAME)

$(OBJ_DIR):
	@mkdir -p $@

define MAKE_OBJ_RULE
$(OBJ_DIR)/$(notdir $(1:.c=.o)): $(1) | $(OBJ_DIR)
	@echo "Compiling $(1)..."
	@$(CC) $(CFLAGS) $(HEADERS) -c $$< -o $$@
endef

$(foreach src, $(SRC), $(eval $(call MAKE_OBJ_RULE,$(src))))

$(LIBFT):
	@echo "Building libft..."
	@$(MAKE) -s -C $(LIBFT_DIR)

$(MLX):
	@echo "Building minilibx..."
	@$(MAKE) -s -C $(MLX_DIR)

clean:
	@echo "Cleaning cub3d objects..."
	@$(RM) $(OBJ_DIR)
	@$(MAKE) -s -C $(LIBFT_DIR) clean
	@$(MAKE) -s -C $(MLX_DIR) clean

fclean: clean
	@echo "Removing $(NAME)..."
	@$(RM) $(NAME)
	@$(MAKE) -s -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re valgrind valgrind-full
