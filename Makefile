DOCKER_IMAGE = ft_shmup
DOCKER_TAG = latest

all: docker-run

docker-build:
	docker build -t $(DOCKER_IMAGE):$(DOCKER_TAG) .

docker-run: docker-build
	docker run --rm -it $(DOCKER_IMAGE):$(DOCKER_TAG)

clean:
	docker rmi -f $(DOCKER_IMAGE):$(DOCKER_TAG)

re: clean all

.PHONY: all clean docker-build docker-run