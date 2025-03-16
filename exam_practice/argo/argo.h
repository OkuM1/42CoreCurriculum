#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <malloc.h>

typedef struct json {
    enum {
      MAP,
      INTEGER,
      STRING
    } type;
    union {
        struct {
                struct pair *data;
                size_t      size;
        } map;
        int   integer;
        char  *string;
    };
} json;

typedef struct pair {
    char *key;
    json value;
} pair;

void free_json(json j);

int argo(json *dst, FILE *stream);
