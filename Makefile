CC = gcc
CFLAGS = -Wall -Wextra
LDFLAGS = -static
COMMIT := $(shell git describe --dirty --long --always)

musl:
	@docker run --rm -v $$(pwd):/workspace docker.io/gntouts/musl-gcc:latest make local > /dev/null 2>&1

local:
	@$(CC) $(CFLAGS) $(LDFLAGS) -c -o httpd.o httpd.c
	@$(CC) $(CFLAGS) $(LDFLAGS) -c -o main.o main.c
	@$(CC) $(CFLAGS) $(LDFLAGS) -o faas-base64 main.o httpd.o
	@strip faas-base64
	@rm -rf *.o

image:
	docker buildx build --platform linux/arm64,linux/amd64 --push -t docker.io/gntouts/faas-base64:latest \
		-t docker.io/gntouts/faas-base64:${COMMIT} -f Dockerfile .

builder-image:
	docker buildx build --platform linux/arm64,linux/amd64 --push -t docker.io/gntouts/musl-gcc:latest -f Dockerfile.builder .

clean:
	@rm -rf *.o
	@rm -rf faas-base64

ping:
	curl -X 'POST' 'http://127.0.0.1:8000' -d 'hello'

live:
	curl 'http://127.0.0.1:8000/health/liveness'

ready:
	curl 'http://127.0.0.1:8000/health/readiness'
