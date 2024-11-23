.PHONY: all clean fclean re

NAME = ft_shmup.a

CFILES = *.c

INCLUDE = ft_shmup.h
MAKEFILE = Makefile

RM = rm -f
CC = cc
AR = ar -rcs

CFLAGS = -Wall -Wextra -Werror 

OBJS = $(CFILES:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $@ $^ -lncurses

%.o: %.c $(INCLUDE) $(MAKEFILE)
	$(CC) $(CFLAGS) -c $< -o $@ 

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re : fclean all
