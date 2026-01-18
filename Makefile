NAME        = minishell
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g3
INCLUDES    = -I./includes -I./libft

READLINE    = -lreadline

LIBFT_DIR   = ./libft
LIBFT       = $(LIBFT_DIR)/libft.a

SRC_DIR     = src
OBJ_DIR     = obj

# All source files
SRCS        = $(SRC_DIR)/main.c \
              $(SRC_DIR)/setup/ms_init.c \
              $(SRC_DIR)/setup/ms_env.c \
              $(SRC_DIR)/setup/utils.c \
              $(SRC_DIR)/signals/ms_signals.c \
              $(SRC_DIR)/lexer/lexer.c \
              $(SRC_DIR)/lexer/token_utils.c \
              $(SRC_DIR)/lexer/char_utils.c \
              $(SRC_DIR)/lexer/extract_utils.c \
              $(SRC_DIR)/lexer/quote_utils.c \
              $(SRC_DIR)/parser/parser.c \
              $(SRC_DIR)/parser/syntax_check.c \
              $(SRC_DIR)/parser/parser_utils.c \
              $(SRC_DIR)/parser/build_command.c \
              $(SRC_DIR)/expander/ms_expand_vars.c \
              $(SRC_DIR)/expander/ms_remove_quotes.c \
                $(SRC_DIR)/executor/ms_execute_cmd.c \
                $(SRC_DIR)/executor/ms_execute.c \
                $(SRC_DIR)/executor/ms_path.c \
                $(SRC_DIR)/executor/ms_pipes.c \
                $(SRC_DIR)/io_redir/ms_heredoc.c \
                $(SRC_DIR)/io_redir/ms_redir_setup.c \
                $(SRC_DIR)/Built-ins/ms_builtin_simple.c \
                $(SRC_DIR)/Built-ins/ms_builtin_complex.c \
                $(SRC_DIR)/Built-ins/ms_builtin_exit.c \
                

# Object files in obj/ directory
OBJS        = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

GREEN       = \033[0;32m
YELLOW      = \033[0;33m
RED         = \033[0;31m
RESET       = \033[0m

all: $(LIBFT) $(NAME)

$(LIBFT):
	@echo "$(YELLOW)Compiling libft...$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory
	@echo "$(GREEN)✅ Libft ready!$(RESET)"

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(READLINE) -o $(NAME)
	@echo "$(GREEN)✅ Minishell compiled successfully!$(RESET)"

# Create obj directory structure and compile
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo "$(GREEN)🔨 Compiled: $<$(RESET)"

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory
	@echo "$(YELLOW)🧹 Object files cleaned!$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory
	@echo "$(RED)🧹 Executable removed!$(RESET)"

re: fclean all

.PHONY: all clean fclean re