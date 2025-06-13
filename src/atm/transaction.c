#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"
// FEITO POR GABRIEL DE ALMEIDA
#define ID_CONTA "D1"

double carregarSaldo(const char* id_conta) {
    FILE* file = fopen("accounts.json", "r");
    if (!file) return 0;

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);

    char* data = malloc(size + 1);
    fread(data, 1, size, file);
    data[size] = '\0';
    fclose(file);

    cJSON* contas = cJSON_Parse(data);
    free(data);

    double saldo = 0;
    cJSON* conta = NULL;
    cJSON_ArrayForEach(conta, contas) {
        cJSON* id = cJSON_GetObjectItem(conta, "id");
        if (strcmp(id->valuestring, id_conta) == 0) {
            saldo = cJSON_GetObjectItem(conta, "saldo")->valuedouble;
            break;
        }
    }

    cJSON_Delete(contas);
    return saldo;
}

void salvarSaldo(const char* id_conta, double novo_saldo) {
    FILE* file = fopen("accounts.json", "r");
    if (!file) return;

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);

    char* data = malloc(size + 1);
    fread(data, 1, size, file);
    data[size] = '\0';
    fclose(file);

    cJSON* contas = cJSON_Parse(data);
    free(data);

    cJSON* conta = NULL;
    cJSON_ArrayForEach(conta, contas) {
        cJSON* id = cJSON_GetObjectItem(conta, "id");
        if (strcmp(id->valuestring, id_conta) == 0) {
            cJSON_ReplaceItemInObject(conta, "saldo", cJSON_CreateNumber(novo_saldo));
            break;
        }
    }

    file = fopen("accounts.json", "w");
    char* novo_json = cJSON_Print(contas);
    fprintf(file, "%s", novo_json);
    fclose(file);

    cJSON_free(novo_json);
    cJSON_Delete(contas);
}

void registrarTransacao(const char* id, const char* tipo, double valor, double saldo_final) {
    FILE* file = fopen("transaction_log.json", "r");
    cJSON* transacoes = NULL;

    if (file) {
        fseek(file, 0, SEEK_END);
        long size = ftell(file);
        rewind(file);

        char* data = malloc(size + 1);
        fread(data, 1, size, file);
        data[size] = '\0';
        fclose(file);

        transacoes = cJSON_Parse(data);
        free(data);
    } else {
        transacoes = cJSON_CreateArray();
    }

    cJSON* transacao = cJSON_CreateObject();
    cJSON_AddStringToObject(transacao, "id", id);
    cJSON_AddStringToObject(transacao, "tipo", tipo);
    cJSON_AddNumberToObject(transacao, "valor", valor);
    cJSON_AddNumberToObject(transacao, "saldo_resultante", saldo_final);

    cJSON_AddItemToArray(transacoes, transacao);

    file = fopen("transaction_log.json", "w");
    char* novo_json = cJSON_Print(transacoes);
    fprintf(file, "%s", novo_json);
    fclose(file);

    cJSON_free(novo_json);
    cJSON_Delete(transacoes);
}

int main() {
    int depositar = 0;
    int sacar = 0;
    int transferir = 0;
    int opcao = 0;
    double saldo = carregarSaldo(ID_CONTA);

    while (opcao != 5) {
        printf("\nEscolha uma opcao:\n");
        printf("1 - Deposito\n");
        printf("2 - Saque\n");
        printf("3 - Transferencia\n");
        printf("4 - Extrato\n");
        printf("5 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite o valor a depositar: ");
                scanf("%d", &depositar);
                saldo += depositar;
                salvarSaldo(ID_CONTA, saldo);
                registrarTransacao(ID_CONTA, "deposito", depositar, saldo);
                printf("Deposito realizado. Saldo atual: %.2f\n", saldo);
                break;

            case 2:
                printf("Digite o valor de saque: ");
                scanf("%d", &sacar);
                if (sacar <= saldo) {
                    saldo -= sacar;
                    salvarSaldo(ID_CONTA, saldo);
                    registrarTransacao(ID_CONTA, "saque", sacar, saldo);
                    printf("Saque realizado. Saldo atual: %.2f\n", saldo);
                } else {
                    printf("Saldo insuficiente!\n");
                }
                break;

            case 3:
                printf("Digite o valor para transferencia: ");
                scanf("%d", &transferir);
                if (transferir <= saldo) {
                    saldo -= transferir;
                    salvarSaldo(ID_CONTA, saldo);
                    registrarTransacao(ID_CONTA, "transferencia", transferir, saldo);
                    printf("Transferencia realizada. Saldo atual: %.2f\n", saldo);
                } else {
                    printf("Saldo insuficiente para transferencia!\n");
                }
                break;

            case 4:
                printf("Extrato atual: Saldo = %.2f\n", saldo);
                break;

            case 5:
                printf("Saindo...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }
    }

    return 0;
}
