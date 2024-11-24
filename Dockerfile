FROM gcc:latest
RUN apt-get update && apt-get install -y libncurses5-dev libncursesw5-dev make
WORKDIR /app
COPY . .
RUN make
CMD ["./ft_shmup"]