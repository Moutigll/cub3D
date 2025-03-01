CC = cc
CFLAGS = -g -I include -I libft/include -Wall -Wextra -Werror -MMD -MP

NAME = cub3D
NAME_THREAD = cub3D_thread

SRC_DIR = src
OBJ_DIR = obj
LIBFT_PATH = libft
LIBFT = $(LIBFT_PATH)/libft.a

MLX_PATH = minilibx-linux
MLX = $(MLX_PATH)/libmlx.a
MLX_FLAGS = -L$(MLX_PATH) -lmlx -lX11 -lXext -lm

SRCS = \
	$(SRC_DIR)/debug/debug_print.c \
	$(SRC_DIR)/debug/debug_screen.c \
	$(SRC_DIR)/init/init_utils.c \
	$(SRC_DIR)/init/init.c \
	$(SRC_DIR)/parsing/flood_fill.c \
	$(SRC_DIR)/parsing/parse_map.c \
	$(SRC_DIR)/parsing/parse_metadata.c \
	$(SRC_DIR)/rendering/apply_texture.c \
	$(SRC_DIR)/rendering/render_frame.c \
	$(SRC_DIR)/rendering/raycast.c \
	$(SRC_DIR)/rendering/minimap.c \
	$(SRC_DIR)/hooks.c \
	$(SRC_DIR)/loop.c \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/player.c

OVERRIDE_SRCS = \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/rendering/render_frame.c

THREAD_OVERRIDES = \
	$(SRC_DIR)/threads/main.c \
	$(SRC_DIR)/threads/render_frame.c \
	$(SRC_DIR)/threads/init_threads.c

THREAD_BUILD_SRCS = $(filter-out $(OVERRIDE_SRCS), $(SRCS)) $(THREAD_OVERRIDES)

OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
DEPS = $(OBJS:.o=.d)

THREAD_OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(THREAD_BUILD_SRCS))
THREAD_DEPS = $(THREAD_OBJS:.o=.d)

GREEN  = \033[1;32m
YELLOW = \033[1;33m
BLUE   = \033[1;34m
RED    = \033[1;31m
RESET  = \033[0m
BOLD   = \033[1m

all: $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(LIBFT):
	@printf "$(BLUE)🔧 Compiling Libft...$(RESET)\n"
	@$(MAKE) -C $(LIBFT_PATH)

$(MLX):
	@printf "$(BLUE)🔧 Compiling MinilibX...$(RESET)\n"
	@$(MAKE) -C $(MLX_PATH)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	@printf "$(YELLOW)🚀 Creating $(BOLD)$(NAME)$(RESET)$(YELLOW)...$(RESET)\n"
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(MLX) $(MLX_FLAGS)
	@printf "$(GREEN)✅ Compilation success !$(RESET)\n"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@printf "$(BLUE)📦 Compiling $(BOLD)$<$(RESET)\n"
	$(CC) $(CFLAGS) -c $< -o $@ -MMD -MP -MF $(@:.o=.d)

thread: $(NAME_THREAD)

$(NAME_THREAD): $(THREAD_OBJS) $(LIBFT) $(MLX)
	@printf "$(YELLOW)🚀 Creating $(BOLD)$(NAME)_thread$(RESET)$(YELLOW)...$(RESET)\n"
	$(CC) $(CFLAGS) -pthread -o $(NAME)_thread $(THREAD_OBJS) $(LIBFT) $(MLX) $(MLX_FLAGS)
	@printf "$(GREEN)✅ Thread compilation success !$(RESET)\n"

clean:
	@printf "$(RED)🧹 Deleting object files...$(RESET)\n"
	@rm -rf $(OBJ_DIR)
	@$(MAKE) clean -C $(LIBFT_PATH)
	@$(MAKE) clean -C $(MLX_PATH)

fclean: clean
	@printf "$(RED)🗑️ Removing binaries...$(RESET)\n"
	@rm -f $(NAME) $(NAME)_thread
	@$(MAKE) fclean -C $(LIBFT_PATH)
	@$(MAKE) clean -C $(MLX_PATH)

re: fclean all

-include $(DEPS)
-include $(THREAD_DEPS)

.PHONY: all clean fclean re
