NAME		:= minishell

CC      := cc
CFLAGS  := -g -Wextra -Wall -Werror #-lreadline

LIBFT   := ./libraries/libft
HEADERS := -I ./include -I $(LIBFT)/include
LIBS    := $(LIBFT)/libft.a -lreadline

SRCS_DIR := src/
SRCS     := $(addprefix $(SRCS_DIR), main.c)
			
DIR_OBJ			:= .objs
OBJS		:= $(SRCS:$(SRCS_DIR)%.c=$(DIR_OBJ)/%.o)

VALGRIND	:= valgrind --leak-check=full --track-origins=yes \
			--show-leak-kinds=all --suppressions=.readline_supression
NO_PRINT	:= --no-print-directory
CYAN		:= \033[1;36m
GREEN		:= \033[1;32m
END 		:= \033[0m

all: libft $(NAME)

libft:
	@make -s -C $(LIBFT) $(NO_PRINT)

$(DIR_OBJ)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@ $(HEADERS)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)
	@echo "$(GREEN)Done!$(END)"

clean:
	@make -C $(LIBFT) clean $(NO_PRINT)
	@rm -rf $(DIR_OBJ) $(DIR_OBJ_BONUS)
	@echo -n "$(GREEN)Cleaned$(END)"

fclean: clean
	@rm -rf $(NAME)
	@make -C $(LIBFT) fclean $(NO_PRINT)
	@echo "$(GREEN) all!$(END)"
	
re: fclean all

val: libft $(NAME)
	$(VALGRIND) ./minishell
norm:
	@echo "\n$(CYAN)=======$(END) $(GREEN)LIBFT$(END) $(CYAN)=======$(END)"
	@norminette libraries/libft | sed 's/OK/\x1b[1;32m&\x1b[0m/g' | sed 's/libft/\x1b[1;31m&\x1b[0m/g'
	@echo "\n$(CYAN)=======$(END) $(GREEN)MANDATORY$(END) $(CYAN)=======$(END)"
	@norminette src | sed 's/OK/\x1b[1;32m&\x1b[0m/g' | sed 's/src/\x1b[1;33m&\x1b[0m/g'
	@echo "\n$(CYAN)=======$(END) $(GREEN)INCLUDES$(END) $(CYAN)=======$(END)"
	@norminette includes | sed 's/OK/\x1b[1;32m&\x1b[0m/g' | sed 's/includes/\x1b[1;36m&\x1b[0m/g'

.PHONY: all clean fclean re libft norm val