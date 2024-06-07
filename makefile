
CLANG = clang
FLAGS = -Wall -Wextra -Werror -pthread
SRCS = end_meal.c\
		monitor.c\
		mutexes.c\
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

all: $(NAME)

$(NAME): $(OBJS)
	$(CLANG) $(FLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re