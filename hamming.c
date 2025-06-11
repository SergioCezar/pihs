#include "hamming.h"
#include <string.h>

size_t hamming(const char *a, const char *b) {
    
    size_t len_a = strlen(a);
    size_t len_b = strlen(b);

    if (len_a != len_b) {
        return (size_t)-1; // Erro: strings de tamanho diferente
    }

    size_t dist = 0;
    for (size_t i = 0; i < len_a; i++) {
        if (a[i] != b[i]) dist++;
    }

    return dist;
}
