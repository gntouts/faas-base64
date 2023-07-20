CC = gcc
CFLAGS = -Wall -Wextra
LDFLAGS = -static

build:
	@docker run --rm -v $$(pwd):/workspace docker.io/gntouts/musl-gcc:latest make docker

docker:
	@$(CC) $(CFLAGS) $(LDFLAGS) -c -o httpd.o httpd.c
	@$(CC) $(CFLAGS) $(LDFLAGS) -c -o main.o main.c
	@$(CC) $(CFLAGS) $(LDFLAGS) -o faas-base64 main.o httpd.o
	@strip faas-base64
	@rm -rf *.o
	
clean:
	@rm -rf *.o
	@rm -rf faas-base64

ping:
	curl -X 'POST' 'http://127.0.0.1:8000' -d 'hello'

live:
	curl 'http://127.0.0.1:8000/health/liveness'

ready:
	curl 'http://127.0.0.1:8000/health/readiness'
