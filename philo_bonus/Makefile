NAME=philo_bonus

SRCS = philo_bonus.c declare_all.c more_tools.c tools.c errors.c\

OBJS = $(SRCS:.c=.o)

CC = gcc
CFLAGS  = -Wall -Werror -Wextra -g

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