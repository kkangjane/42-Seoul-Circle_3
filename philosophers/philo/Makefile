NAME = philo
SRCS = main.c thread.c actions.c\
	utils1.c utils2.c init.c
OBJS = $(SRCS:.c=.o)
CC = cc -Wall -Wextra -Werror
%.o : %.c
	$(CC) -c $^ -o $@

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

%.o : %.c
	$(CC) -c $^ -o $@

clean : 
	rm -rf $(OBJS)

fclean :
	rm -rf $(OBJS)
	rm -rf $(NAME)

re :
	make fclean
	make all

.PHONY : all clean fclean re