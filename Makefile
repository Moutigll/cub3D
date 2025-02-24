CC = cc
CFLAGS = -g -I include -I libft/include -Wall -Wextra -Werror -MMD -MP

# 🏗️ Names
NAME = cub3D

# 📂 Folders
SRC_DIR = src
OBJ_DIR = obj
LIBFT_PATH = libft
LIBFT = $(LIBFT_PATH)/libft.a

# MinilibX
MLX_PATH = minilibx-linux
MLX = $(MLX_PATH)/libmlx.a
MLX_FLAGS = -L$(MLX_PATH) -lmlx -lX11 -lXext -lm

# 🔍 Recover files
SRCS = $(SRC_DIR)/debug/debug_print.c \
       $(SRC_DIR)/debug/debug_screen.c \
       $(SRC_DIR)/parsing/parse_map.c \
       $(SRC_DIR)/rendering/render_frame.c \
       $(SRC_DIR)/rendering/raycast.c \
       $(SRC_DIR)/rendering/apply_texture.c \
       $(SRC_DIR)/hooks.c \
       $(SRC_DIR)/init.c \
       $(SRC_DIR)/loop.c \
       $(SRC_DIR)/main.c \
       $(SRC_DIR)/player.c

OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
DEPS = $(OBJS:.o=.d)

# 🎨 ANSI colors
GREEN  = \033[1;32m
YELLOW = \033[1;33m
BLUE   = \033[1;34m
RED    = \033[1;31m
RESET  = \033[0m
BOLD   = \033[1m

# 🏗️ Compilation
all: $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(LIBFT):
	@printf "$(BLUE)🔧 Compiling Libft...$(RESET)\n"
	@$(MAKE) -C $(LIBFT_PATH)

# ✅ MinilibX compilation
$(MLX): 
	@printf "$(BLUE)🔧 Compiling MinilibX...$(RESET)\n"
	@$(MAKE) -C $(MLX_PATH)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	@printf "$(YELLOW)🚀 Creating $(BOLD)$(NAME)$(RESET)$(YELLOW)...$(RESET)\n"
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(MLX) $(MLX_FLAGS)
	@printf "$(GREEN)✅ Compilation success !$(RESET)\n"

# 🛠️ Compilation of obj files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)  # Création récursive des dossiers
	@printf "$(BLUE)📦 Compiling $(BOLD)$<$(RESET)\n"
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@printf "$(RED)🧹 Deleting object files...$(RESET)\n"
	@rm -rf $(OBJ_DIR)
	@$(MAKE) clean -C $(LIBFT_PATH)
	@$(MAKE) clean -C $(MLX_PATH)

fclean: clean
	@printf "$(RED)🗑️ Removing binaries...$(RESET)\n"
	@rm -f $(NAME)
	@$(MAKE) fclean -C $(LIBFT_PATH)
	@$(MAKE) clean -C $(MLX_PATH)

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re $(NAME)
