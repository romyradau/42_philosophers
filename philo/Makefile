CC = gcc
CFLAGS = -Wall -Wextra -Werror 
RM = rm -f
NAME = philo
SOURCES = 0_main.c 1_input.c 2_creation.c 3_routine.c 11_helpers.c
OBJECTS = $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME)

clean:
	$(RM) $(OBJECTS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

val:
	docker run -ti -v $(PWD):/test memory-test:0.1 bash -c "cd /test/; gcc -pthread $(SOURCES) -o main && valgrind --leak-check=full ./main 2 500 200 200 5; rm -f ./main"

test1: all
	./philo 1 800 200 200

test2: all
	./philo 5 800 200 200

test3: all
	./philo 5 800 200 200 7 | grep "eat" | wc -l

test4: all
	./philo 4 410 200 200

test5: all
	./philo 4 310 200 100

test6: all
	./philo 100 800 200 200

test7: all
	./philo 200 800 200 200

test8: test1 test2 test3 test4 test5 test6 test7 