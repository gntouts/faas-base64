#include "base64.h"

char* base64_encode(const char* input) {
    size_t input_len = strlen(input);
    size_t output_len = 4 * ((input_len + 2) / 3); // Calculate the output buffer size
    char* encoded = (char*)malloc(output_len + 1); // Allocate memory for the encoded string

    if (encoded) {
        size_t i, j;
        for (i = 0, j = 0; i < input_len;) {
            uint32_t octet_a = i < input_len ? (unsigned char)input[i++] : 0;
            uint32_t octet_b = i < input_len ? (unsigned char)input[i++] : 0;
            uint32_t octet_c = i < input_len ? (unsigned char)input[i++] : 0;

            uint32_t triple = (octet_a << 16) + (octet_b << 8) + octet_c;

            encoded[j++] = base64_table[(triple >> 18) & 0x3F];
            encoded[j++] = base64_table[(triple >> 12) & 0x3F];
            encoded[j++] = base64_table[(triple >> 6) & 0x3F];
            encoded[j++] = base64_table[triple & 0x3F];
        }

        // Pad with '=' characters if necessary
        size_t padding = input_len % 3;
        if (padding > 0) {
            for (size_t k = 0; k < 3 - padding; k++) {
                encoded[output_len - 1 - k] = '=';
            }
        }

        encoded[output_len] = '\0';
    }

    return encoded;
}