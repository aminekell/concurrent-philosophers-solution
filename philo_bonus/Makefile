SRC = philo_bonus.c check_args_bonus.c is_numeric.c process.c set_info.c  creat_philo.c routine.c helper.c init_philo.c creat_philo_list.c
OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -Werror

NAME = philo_bonus

all : $(NAME)

$(NAME) : $(OBJ)
	cc $(CFLAGS) $(OBJ) -o $(NAME) 

%.o : %.c philo_bonus.h
	cc $(CFLAGS) -c $< -o $@

clean :
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME)

re : fclean all