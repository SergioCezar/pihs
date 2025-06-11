// hamming.h
#ifndef HAMMING_H
#define HAMMING_H

#include <stddef.h>

// Retorna a distância de Hamming entre duas strings de mesmo comprimento.
// Retorna (size_t)-1 se os comprimentos forem diferentes.
size_t hamming(const char *a, const char *b);

#endif
