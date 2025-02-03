NAME		:= fdf
# NAME_BONUS	:= fdf_bonus

CC      := cc
CFLAGS  := -g -Wextra -Wall -Werror -Wunreachable-code -Ofast -O0

LIBFT   := ./libs/libft
HEADERS := -I ./include -I $(LIBFT)/include
LIBS    := $(LIBFT)/libft.a -ldl -lglfw -pthread -lm

SRCS_DIR := mandatory/
SRCS     := $(addprefix $(SRCS_DIR), main.c errors_and_free.c map.c init.c \
			parse.c render.c render_utils.c draw_line_utils.c parse_utils.c \
			colors.c)
# SRCS_DIR_BONUS := bonus/
# SRCS_BONUS     := $(addprefix $(SRCS_DIR_BONUS), main_bonus.c errors_and_free_bonus.c map_bonus.c init_bonus.c \
# 			parse_bonus.c render_bonus.c render_utils_bonus.c draw_line_utils_bonus.c parse_utils_bonus.c \
# 			colors_bonus.c keyboard_command_utils_bonus.c rotation_bonus.c)

DIR_OBJ			:= .objs
# DIR_OBJ_BONUS	:= .objs_bonus
OBJS		:= $(SRCS:$(SRCS_DIR)%.c=$(DIR_OBJ)/%.o)
# OBJS_BONUS	:= $(SRCS_BONUS:$(SRCS_DIR_BONUS)%.c=$(DIR_OBJ_BONUS)/%.o)

# --show-leak-kinds=all
VALGRIND	:= valgrind --leak-check=full --track-origins=yes
NO_PRINT	:= --no-print-directory
CYAN		:= \033[1;36m
GREEN		:= \033[1;32m
END 		:= \033[0m

all: libft $(NAME)

libft:
	@make -s -C $(LIBFT) $(NO_PRINT)

# bonus: libft $(NAME_BONUS)

$(DIR_OBJ)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@ $(HEADERS)

# $(DIR_OBJ_BONUS)/%.o: $(SRCS_DIR_BONUS)/%.c
# 	@mkdir -p $(dir $@)
# 	@$(CC) $(CFLAGS) -c $< -o $@ $(HEADERS)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)
	@echo "$(GREEN)Done!$(END)"

# $(NAME_BONUS): $(OBJS_BONUS)
# 	@$(CC) $(OBJS_BONUS) $(LIBS) $(HEADERS) -o $(NAME_BONUS)
# 	@echo "$(GREEN)Bonus done!$(END)"

clean:
# @rm -rf $(LIBMLX)/build
	@make -C $(LIBFT) clean $(NO_PRINT)
	@rm -rf $(DIR_OBJ) $(DIR_OBJ_BONUS)
	@echo -n "$(GREEN)Cleaned$(END)"

fclean: clean
	@rm -rf $(NAME)
	@rm -f trace.txt
	@make -C $(LIBFT) fclean $(NO_PRINT)
	@echo "$(GREEN) all!$(END)"
	
re: fclean all

# test:
# 	./fdf maps/test_maps/42.fdf > trace.txt 2>&1

# test_bonus:
# 	./fdf_bonus maps/test_maps/elem-col.fdf >> trace.txt 2>&1

norm:
	@echo "\n$(CYAN)=======$(END) $(GREEN)LIBFT$(END) $(CYAN)=======$(END)"
	@norminette libs/libft | sed 's/OK/\x1b[1;32m&\x1b[0m/g' | sed 's/libft/\x1b[1;31m&\x1b[0m/g'
	@echo "\n$(CYAN)=======$(END) $(GREEN)MANDATORY$(END) $(CYAN)=======$(END)"
	@norminette mandatory | sed 's/OK/\x1b[1;32m&\x1b[0m/g' | sed 's/mandatory/\x1b[1;33m&\x1b[0m/g'
	@echo "\n$(CYAN)=======$(END) $(GREEN)BONUS$(END) $(CYAN)=======$(END)"
	@norminette bonus | sed 's/OK/\x1b[1;32m&\x1b[0m/g' | sed 's/bonus/\x1b[1;35m&\x1b[0m/g'
	@echo "\n$(CYAN)=======$(END) $(GREEN)INCLUDES$(END) $(CYAN)=======$(END)"
	@norminette includes | sed 's/OK/\x1b[1;32m&\x1b[0m/g' | sed 's/includes/\x1b[1;36m&\x1b[0m/g'

.PHONY: all clean fclean re libft test bonus test_bonus norm
