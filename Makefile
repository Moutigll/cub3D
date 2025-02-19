CC = cc
CFLAGS = -g -I include -I libft/include -Wall -Wextra -Werror

# 🏗️ Names
NAME = cub3D

# 📂 Folders
SRC_DIR = src
OBJ_DIR = obj
LIBFT_PATH = libft
LIBFT = $(LIBFT_PATH)/libft.a

# MinilibX
MLX_FLAGS = -L./minilibx-linux -lmlx -lX11 -lXext -lm

# 🔍 Recover files
CUB3D_SRCS = $(filter-out $(SRC_DIR)/main.c, $(shell find $(SRC_DIR) -type f -name "*.c"))
CUB3D_OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(CUB3D_SRCS))

MAIN_SRCS = $(SRC_DIR)/main.c
MAIN_OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(MAIN_SRCS))

DEPS = $(CUB3D_OBJS:.o=.d) $(MAIN_OBJS:.o=.d)

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

# Compilation of MinilibX
minilibx:
	@printf "$(BLUE)🔧 Compiling MinilibX...$(RESET)\n"
	@$(MAKE) -C minilibx-linux

$(NAME): $(OBJ_DIR) $(LIBFT) $(CUB3D_OBJS) $(MAIN_OBJS) minilibx
	@printf "$(YELLOW)🚀 Creating $(BOLD)$(NAME)$(RESET)$(YELLOW)...$(RESET)\n"
	$(CC) $(CFLAGS) -o $(NAME) $(MAIN_OBJS) $(CUB3D_OBJS) $(LIBFT) $(MLX_FLAGS) $(LDFLAGS)
	@printf "$(GREEN)✅ Compilation success !$(RESET)\n"

# 🛠️ Progression
TOTAL_FILES := $(words $(CUB3D_SRCS) $(MAIN_SRCS))
COMPILED_FILES := 0

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(eval COMPILED_FILES := $(shell expr $(COMPILED_FILES) + 1))
	@printf "$(BLUE)📦 Compilation [$$(($(COMPILED_FILES) * 100 / $(TOTAL_FILES)))%%] -> $(BOLD)$<$(RESET)\n"
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@printf "$(RED)🧹 Deleting object files...$(RESET)\n"
	@rm -rf $(OBJ_DIR)
	@$(MAKE) clean -C $(LIBFT_PATH)
	@$(MAKE) clean -C minilibx-linux

fclean: clean
	@printf "$(RED)🗑️ Removing binaries...$(RESET)\n"
	@rm -f $(NAME)
	@$(MAKE) fclean -C $(LIBFT_PATH)
	@$(MAKE) fclean -C minilibx-linux

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re minilibx
