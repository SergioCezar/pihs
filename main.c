#include "pocketpy/pocketpy.h"
#include "levenshtein.h"
#include "hamming.h"
#include <stdio.h>
#include <stdlib.h>

// Função Levenshtein exposta ao Python
bool py_levenshtein(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_str);
    PY_CHECK_ARG_TYPE(1, tp_str);

    const char* str1 = py_tostr(py_arg(0));
    const char* str2 = py_tostr(py_arg(1));

    unsigned int resultado = levenshtein(str1, str2);
    py_newint(py_retval(), resultado);

    return true;
}

// Função Hamming exposta ao Python
bool py_hamming(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_str);
    PY_CHECK_ARG_TYPE(1, tp_str);

    const char* str1 = py_tostr(py_arg(0));
    const char* str2 = py_tostr(py_arg(1));

    size_t resultado = hamming(str1, str2);

    if (resultado == (size_t)-1) {
        py_newstr(py_retval(), "Erro: strings com comprimentos diferentes!");
    } else {
        py_newint(py_retval(), resultado);
    }

    return true;
}

// Leitura de arquivo para carregar o script Python
char* read_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Erro ao abrir o script Python");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long tamanho = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* buffer = malloc(tamanho + 1);
    if (!buffer) {
        perror("Erro de alocação de memória");
        fclose(file);
        return NULL;
    }

    fread(buffer, 1, tamanho, file);
    buffer[tamanho] = '\0';
    fclose(file);

    return buffer;
}

int main() {
    py_initialize();

    py_GlobalRef modulo_main = py_getmodule("__main__");

    py_bindfunc(modulo_main, "levenshtein_em_python", py_levenshtein);
    py_bindfunc(modulo_main, "hamming_em_python", py_hamming);

    char* script = read_file("script.py");
    if (!script) {
        py_finalize();
        return 1;
    }

    if (!py_exec(script, "print_levenshtein", EXEC_MODE, NULL)) {
        printf("Erro de execução do script.\n");
    }

    free(script);
    py_finalize();

    return 0;
}
