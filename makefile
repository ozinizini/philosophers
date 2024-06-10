
CLANG = clang
FLAGS = -Wall -Wextra -Werror -pthread -g #-fsanitize=address -fno-omit-frame-pointer #-fsanitize=thread -g
SRCS = end_meal.c\
		monitor.c\
		mutexes_1.c\
		mutexes_2.c\
		mutexes_3.c\
		philosophers_actions.c\
		philosophers.c\
		start_meal.c\
		struct_handling_functions.c\
		time_functions.c\
		utils.c\
		validation_functions.c
OBJS = $(SRCS:.c=.o)
NAME = philosophers

OBJECTS = $(SOURCES:.c=.o)

# ANSI escape codes for bold colors
BOLD_RED = \033[1;31m
BOLD_GREEN = \033[1;32m
BOLD_YELLOW = \033[1;33m
BOLD_BLUE = \033[1;34m
BOLD_MAGENTA = \033[1;35m
BOLD_CYAN = \033[1;36m
BOLD_WHITE = \033[1;37m
NC = \033[0m # No Color

all: $(NAME)

$(NAME): $(OBJS)
	@$(CLANG) $(FLAGS) $(OBJS) -o $(NAME)
	@echo "$(BOLD_GREEN)philosophers executable compiled and ready to be used!$(NC)"

%.o: %.c
	@$(CLANG) $(FLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "Cleaning object files"
	@rm -f $(OBJS)

fclean: clean
	@echo "Cleaning philosophers program"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re