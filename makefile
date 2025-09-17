# **************************************************************************** #
# DIRECTORIES
SRC_DIR		:= src/
INC_DIR		:= inc/
OBJ_DIR		:= obj/
LIBFT_DIR = ./libft

LIBFT_INC_DIR:= $(LIBFT_DIR)inc/

# **************************************************************************** #
# PROJECT
NAME		:= minishell
LIBFT		:= $(LIBFT_DIR)/libft.a

# **************************************************************************** #
# FILES
SRCS_FILES =	bi_cd.c \
				bi_echo.c \
				bi_exit.c \
				bi_export.c \
				bi_pwd.c \
				bi_unset.c \
				builting.c \
				cmd_exit.c \
				env.c \
				execution_utils.c \
				execution.c \
				execution2.c \
				execution3.c \
				expansion.c \
				init.c \
				is_command.c \
				lexer_utils.c \
				lexer.c \
				main_loop.c \
				main.c \
				pipex.c \
				pipex_utils.c \
				process_input.c \
				process_input2.c \
				quotes_utils.c \
				quotes.c \
				redirections.c \
				signal.c \
				syntax_validator.c \
				token_analyzer.c \
				tokens.c \
				type.c\
				utils.c \
				utils2.c \
				var_ft.c \
				bi_cd_two.c \


INC_FILES	:= minishell.h

# GENERAL FILES
# GENERAL FILES
SRCS	:= $(addprefix $(SRC_DIR), $(SRCS_FILES))
OBJS	:= $(addprefix $(OBJ_DIR), $(SRCS_FILES:.c=.o))
DEPS	:= $(OBJS:.o=.d)


# **************************************************************************** #
# COMPILER
CC		:= cc
CFLAGS	:= -Wall -Wextra -Werror -g
CFLAGS	+= -MMD -MP
IFLAGS	:= -I$(INC_DIR) -I$(LIBFT_INC_DIR)
LDFLAGS	:= -L$(LIBFT_DIR) -lft -lreadline

# DEBUG MODE
BUILD_MODE_FILE := .build_mode
DEBUG			?= 0
VALGRIND		?= 0
VALGRIND_FLAGS	:= --leak-check=full --show-leak-kinds=all \
		--track-origins=yes --trace-children=yes --track-fds=yes \
		--suppressions=doc/valgrind.supp --log-file=doc/memcheck.log #--gen-suppressions=all

ifeq ($(DEBUG),1)
	CFLAGS += -g3 -fsanitize=address
	LDFLAGS += -fsanitize=address
endif

ifeq ($(VALGRIND),1)
	CFLAGS += -g3
endif

# **************************************************************************** #
# COLOURS: BOLD RGBYW
BR	= \033[1;31m
BG	= \033[1;32m
BB	= \033[1;34m
BY	= \033[1;33m
BW	= \033[1;37m

# NO COLOR and CLEAR LINE
NC	= \033[0;39m
CL	= \033[2K

# **************************************************************************** #
# ESSENTIAL RULES
-include $(DEPS)

# Default rule to create the program
all: libft $(NAME)

# Rule to create the program
$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(IFLAGS) $^ $(LDFLAGS) -o $(NAME)
	@printf "%b" "$(CL) -> $(BW)[$(NAME)]:\t$(BG)Compilation success\t✅$(NC)\n"
	@echo "─────────────────────────────────────────────────────$(BY)"
	@echo "███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗     "
	@echo "████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║     "
	@echo "██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║     "
	@echo "██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║     "
	@echo "██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗"
	@echo "╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝"
	@echo "                  by aamaya-g and davmoren"
	@echo "$(NC)─────────────────────────────────────────────────────"


# Rule to compile object files from source files
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@printf "%b" "$(CL) -> $(BW)[$(NAME)]:\t\t$(NC)$<\r"
	@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

# Rule to make the library Libft
libft: $(LIBFT)
$(LIBFT):
	@$(MAKE) -sC $(LIBFT_DIR)

# Rule to clean generated files
clean:
	@$(MAKE) clean -sC $(LIBFT_DIR)
	@rm -rf $(OBJ_DIR) $(BUILD_MODE_FILE)
	@printf "%b" "$(CL) -> $(BW)[$(NAME)]:\t$(BG)Object files cleaned\t❎$(NC)\n"

# Rule to clean generated files and the executable
fclean:
	@$(MAKE) clean > /dev/null
	@$(MAKE) fclean -sC $(LIBFT_DIR)
	@rm -rf $(NAME) $(BONUS_NAME)
	@printf "%b" "$(CL) -> $(BW)[$(NAME)]:\t$(BG)Exe and objects cleaned\t❎$(NC)\n"

# Rule to recompile from zero
re: fclean all

# **************************************************************************** #
# NORM AND DEBUG RULES

# Rule to check if the files pass norminette
norm:
	@norminette $(SRC_DIR) $(INC_DIR)

# Rule to compile with debug flags
debug:
	@if [ ! -f $(BUILD_MODE_FILE) ] || ! grep -q "DEBUG=1" $(BUILD_MODE_FILE); then \
		$(MAKE) fclean -s; \
	fi
	@echo "DEBUG=1" > $(BUILD_MODE_FILE)
	@$(MAKE) DEBUG=1 -s
	@echo " -> $(BW)[Debug]:\t\t$(BB)Debug mode enabled\t🟦$(NC)\n"
	-@./$(NAME) $(ARGS)

# Rule to compile with valgrind debug flags
valgrind:
	@if [ ! -f $(BUILD_MODE_FILE) ] || ! grep -q "VALGRIND=1" $(BUILD_MODE_FILE); then \
		$(MAKE) fclean -s; \
	fi
	@echo "VALGRIND=1" > $(BUILD_MODE_FILE)
	@$(MAKE) VALGRIND=1 -s
	@echo " -> $(BW)[Valgrind]:\t\t$(BB)Valgrind mode enabled\t🟦$(NC)\n"
	-@valgrind $(VALGRIND_FLAGS) ./$(NAME) $(ARGS)

# **************************************************************************** #

.PHONY: all clean fclean re bonus norm debug valgrind
.DEFAULT_GOAL := all
