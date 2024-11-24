.PHONY: all clean fclean re docker-build docker-run docker-clean docker

NAME = ft_shmup

CFILES = main.c \
		ft_asteroid.c \
		ft_bullet.c \
		ft_enemy.c \
		ft_move.c \
		ft_player.c \
		ft_timer.c \
		ft_menu.c \
		ft_power.c

INCLUDE = ft_shmup.h
MAKEFILE = Makefile

RM = rm -f
CC = cc
AR = ar -rcs

CFLAGS = -Wall -Wextra -Werror 

OBJS = $(CFILES:.c=.o)
DOCKER_IMAGE = ft_shmup
DOCKER_TAG = latest

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $@ $^ -lncurses -lm

%.o: %.c $(INCLUDE) $(MAKEFILE)
	$(CC) $(CFLAGS) -c $< -o $@ 

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re : fclean all

docker-build:
	docker build -t $(DOCKER_IMAGE):$(DOCKER_TAG) .

docker-run: docker-build
	docker run --rm -it $(DOCKER_IMAGE):$(DOCKER_TAG)

docker-clean:
	docker rmi -f $(DOCKER_IMAGE):$(DOCKER_TAG)

docker: docker-run