NAME		:= minishell
# NAME_BONUS	:= fdf_bonus

CC      := cc
CFLAGS  := -g -Wextra -Wall -Werror -lreadline

LIBFT   := ./libs/libft
HEADERS := -I ./include -I $(LIBFT)/include
LIBS    := $(LIBFT)/libft.a -ldl -lglfw -pthread -lm

SRCS_DIR := mandatory/
SRCS     := $(addprefix $(SRCS_DIR), main.c errors_and_free.c map.c init.c \
			parse.c render.c render_utils.c draw_line_utils.c parse_utils.c \
			colors.c)

DIR_OBJ			:= .objs
OBJS		:= $(SRCS:$(SRCS_DIR)%.c=$(DIR_OBJ)/%.o)

# --show-leak-kinds=all
VALGRIND	:= valgrind --leak-check=full --track-origins=yes --suppressions=.readline_supression
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
	@rm -f trace.txt
	@make -C $(LIBFT) fclean $(NO_PRINT)
	@echo "$(GREEN) all!$(END)"
	
re: fclean all

norm:
	@echo "\n$(CYAN)=======$(END) $(GREEN)LIBFT$(END) $(CYAN)=======$(END)"
	@norminette libs/libft | sed 's/OK/\x1b[1;32m&\x1b[0m/g' | sed 's/libft/\x1b[1;31m&\x1b[0m/g'
	@echo "\n$(CYAN)=======$(END) $(GREEN)MANDATORY$(END) $(CYAN)=======$(END)"
	@norminette mandatory | sed 's/OK/\x1b[1;32m&\x1b[0m/g' | sed 's/mandatory/\x1b[1;33m&\x1b[0m/g'
	@echo "\n$(CYAN)=======$(END) $(GREEN)BONUS$(END) $(CYAN)=======$(END)"
	@norminette bonus | sed 's/OK/\x1b[1;32m&\x1b[0m/g' | sed 's/bonus/\x1b[1;35m&\x1b[0m/g'
	@echo "\n$(CYAN)=======$(END) $(GREEN)INCLUDES$(END) $(CYAN)=======$(END)"
	@norminette includes | sed 's/OK/\x1b[1;32m&\x1b[0m/g' | sed 's/includes/\x1b[1;36m&\x1b[0m/g'

.PHONY: all clean fclean re libft norm
