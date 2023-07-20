#include "httpd.h"
#include "base64.c"
#include <sys/stat.h>

#define CHUNK_SIZE 1024 // read 1024 bytes at a time



int main(int c, char **v) {
  char *port = c == 1 ? "8000" : v[1];
  serve_forever(port);
  return 0;
}

int file_exists(const char *file_name) {
  struct stat buffer;
  int exists;

  exists = (stat(file_name, &buffer) == 0);

  return exists;
}

int read_file(const char *file_name) {
  char buf[CHUNK_SIZE];
  FILE *file;
  size_t nread;
  int err = 1;

  file = fopen(file_name, "r");

  if (file) {
    while ((nread = fread(buf, 1, sizeof buf, file)) > 0)
      fwrite(buf, 1, nread, stdout);

    err = ferror(file);
    fclose(file);
  }
  return err;
}

void route() {
  ROUTE_START()

  GET("/") {
    HTTP_200;
    printf("Hello! You are using %s.\n", request_header("User-Agent"));
  }

  GET("/health/liveness") {
    HTTP_200;
    printf("OK");
  }

  GET("/health/readiness") {
    HTTP_200;
    printf("OK");
  }

  POST("/") {
    HTTP_201;
    char *inputString = payload;
    char* encoded_string = base64_encode(inputString);
    printf("%s", encoded_string);
    free(encoded_string); // Remember to free the allocated memory after use
  }

  ROUTE_END()
}
