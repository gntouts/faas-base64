#include "httpd.h"
#include "base64.c"
#include <sys/stat.h>

#define CHUNK_SIZE 1024 // read 1024 bytes at a time

int main(int argc, char **argv)
{
  char *port = argc == 1 ? "8000" : argv[1];
  serve_forever(port);
  return 0;
}

void route()
{
  ROUTE_START()

  GET("/")
  {
    HTTP_200;
    printf("Hello! You are using %s.\n", request_header("User-Agent"));
  }

  GET("/health/liveness")
  {
    HTTP_200;
    printf("{\"ok\":true}\n");
  }

  GET("/health/readiness")
  {
    HTTP_200;
    printf("{\"ok\":true}\n");
  }

  POST("/")
  {
    HTTP_201;
    char *inputString = payload;
    char *encoded_string = base64_encode(inputString);
    printf("%s", encoded_string);
    free(encoded_string); // Remember to free the allocated memory after use
  }

  GET(uri)
  {
    HTTP_200;
    printf("%s", uri);
  }

  ROUTE_END()
}
