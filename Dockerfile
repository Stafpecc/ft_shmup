FROM gcc:latest
RUN apt-get update && apt-get install -y libncurses6-dev libncursesw6-dev
WORKDIR /app
COPY . .
RUN gcc -o ft_shmup *.c -lncurses
CMD ["./ft_shmup"]