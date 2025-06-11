// levenshtein.c - Levenshtein distance
// MIT licensed.
// Base em código de Titus Wormer <tituswormer@gmail.com>
// Fonte: https://en.wikipedia.org/wiki/Levenshtein_distance

#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include "levenshtein.h"

// Função auxiliar que calcula a distância de Levenshtein entre `a` e `b`,
// dados seus comprimentos (evita chamadas repetidas a strlen).
size_t levenshtein_n(const char *a, const size_t length, const char *b, const size_t bLength) {
    if (a == b) return 0;
    if (length == 0) return bLength;
    if (bLength == 0) return length;

    size_t *cache = calloc(length, sizeof(size_t));
    if (!cache) return (size_t)-1; // erro de alocação

    size_t index = 0;
    while (index < length) {
        cache[index] = index + 1;
        index++;
    }

    size_t bIndex = 0;
    size_t distance, bDistance, result;
    char code;

    while (bIndex < bLength) {
        code = b[bIndex];
        result = distance = bIndex++;
        index = SIZE_MAX;

        while (++index < length) {
            bDistance = (code == a[index]) ? distance : (distance + 1);
            distance = cache[index];
            cache[index] = result =
                (distance > result)
                    ? (bDistance > result ? result + 1 : bDistance)
                    : (bDistance > distance ? distance + 1 : bDistance);
        }
    }

    free(cache);
    return result;
}

// Interface principal: calcula a distância de Levenshtein entre duas strings.
size_t levenshtein(const char *a, const char *b) {
    return levenshtein_n(a, strlen(a), b, strlen(b));
}
