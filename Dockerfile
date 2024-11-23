FROM gcc:latest
RUN apt-get update && apt-get install -y libncurses5-dev libncursesw5-dev
WORKDIR /app
COPY .  .
RUN gcc -o ft_shmup *.c -lncurses
CMD ["./ft_shmup"]
