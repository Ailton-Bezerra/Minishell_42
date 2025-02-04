/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_minisshell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <ailbezer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:10:03 by ailbezer          #+#    #+#             */
/*   Updated: 2025/02/04 11:19:26 by ailbezer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// tests/test_minishell.c
#include "includes/minishell.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define TEST_ASSERT(cond, msg) do { \
    if (!(cond)) { \
        printf("❌ ERRO: %s\n", msg); \
        return 1; \
    } else { \
        printf("✅ SUCESSO: %s\n", msg); \
    } \
} while(0)

// Teste 1: Verificar o prompt
int test_get_prompt() {
    char *expected = "MINISHEL > ";
    char *actual = get_prompt();
    TEST_ASSERT(actual != NULL, "Prompt não é NULL");
    TEST_ASSERT(strcmp(actual, expected) == 0, "Prompt está correto");
    return 0;
}

// Teste 2: Verificar comportamento de saída (Ctrl+D)
int test_exit_behavior() {
    int pipefd[2];
    if (pipe(pipefd) == -1) return 1;

    pid_t pid = fork();
    if (pid == 0) {
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        exit(0); // Simula o comportamento de saída
    } else {
        close(pipefd[1]);
        char buffer[1024];
        read(pipefd[0], buffer, sizeof(buffer));
        close(pipefd[0]);
        TEST_ASSERT(strstr(buffer, "exiting") != NULL, "Mensagem de saída correta");
    }
    return 0;
}

int main() {
    printf("\n🛠️  Rodando testes...\n\n");
    int failed = 0;
    
    failed += test_get_prompt();
    failed += test_exit_behavior();
    
    printf("\n");
    if (failed == 0)
        printf("✅ Todos os testes passaram!\n");
    else
        printf("❌ %d teste(s) falharam!\n", failed);
    
    return (failed != 0);
}
