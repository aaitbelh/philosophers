NAME=philo

SRCS = main.c exit.c declarations.c needs.c\

OBJS = $(SRCS:.c=.o)

CC = gcc
CFLAGS  = -Wall -Werror -Wextra -pthread -g

all : $(NAME)

$(NAME) : $(OBJS)

	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o : %.c 
	$(CC) $(CFLAGS) -c $<

clean : 
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all