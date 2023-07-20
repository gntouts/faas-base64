#ifndef _BASE64_H___
#define _BASE64_H___

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

const char base64_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

char* base64_encode(const char* input);
#endif
