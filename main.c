#include "pocketpy/pocketpy.h"
#include "levenshtein.h"
#include "hamming.h"
#include <stdio.h>
#include <stdlib.h>

// Função auxiliar exposta ao Python para cálculo de Levenshtein
bool py_calc_levenshtein(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_str);
    PY_CHECK_ARG_TYPE(1, tp_str);

    const char *str1 = py_tostr(py_arg(0));
    const char *str2 = py_tostr(py_arg(1));

    size_t dist = levenshtein(str1, str2);
    py_newint(py_retval(), dist);

    return true;
}

// Função auxiliar exposta ao Python para cálculo de Hamming
bool py_calc_hamming(int argc, py_Ref argv) {
    PY_CHECK_ARGC(2);
    PY_CHECK_ARG_TYPE(0, tp_str);
    PY_CHECK_ARG_TYPE(1, tp_str);

    const char *str1 = py_tostr(py_arg(0));
    const char *str2 = py_tostr(py_arg(1));

    size_t dist = hamming(str1, str2);

    if (dist == (size_t)-1) {
        py_newstr(py_retval(), "Erro: tamanhos incompatíveis");
    } else {
        py_newint(py_retval(), dist);
    }

    return true;
}

// Função para carregar conteúdo de um arquivo em memória
char* carregar_script(const char *nome_arquivo) {
    FILE *arq = fopen(nome_arquivo, "r");
    if (!arq) {
        perror("Falha ao abrir o arquivo do script");
        return NULL;
    }

    fseek(arq, 0, SEEK_END);
    long tamanho = ftell(arq);
    rewind(arq);

    char *conteudo = malloc(tamanho + 1);
    if (!conteudo) {
        perror("Falha de alocação de memória");
        fclose(arq);
        return NULL;
    }

    fread(conteudo, 1, tamanho, arq);
    conteudo[tamanho] = '\0';
    fclose(arq);

    return conteudo;
}

int main() {
    py_initialize();

    py_GlobalRef py_main = py_getmodule("__main__");

    py_bindfunc(py_main, "dist_levenshtein", py_calc_levenshtein);
    py_bindfunc(py_main, "dist_hamming", py_calc_hamming);

    char *codigo = carregar_script("script.py");
    if (!codigo) {
        py_finalize();
        return EXIT_FAILURE;
    }

    if (!py_exec(codigo, "exec_script", EXEC_MODE, NULL)) {
        fprintf(stderr, "Erro ao executar o script.\n");
    }

    free(codigo);
    py_finalize();

    return EXIT_SUCCESS;
}
