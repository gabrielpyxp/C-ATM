/*### transaction.[c/h]
- Saque, depósito e extrato
- Atualiza `accounts.json` e `transaction_log.json`
*/

/*
int depositar(Conta *conta, double valor);
int sacar(Conta *conta, double valor);
int transferir(Conta *origem, Conta *destino, double valor);
void registrar_transacao(const char *tipo, const Conta *conta, double valor, const char *destino_id);
*/

 #include <stdio.h>
    int main(){
        int escolha = 0;
        int depositar;
        int sacar;
        int transferir;
        int extrato;
        int opcao;
    
    

        printf("\nEscolha uma opcao:\n1 - Deposito\n2 - Saque\n3 - transferencia\n4 - extrato\n5 - Sair\nOpcao: ");
        scanf("%d", &opcao);

        while(escolha < 5) {

        switch(opcao) {
            case 1:
                printf("Digite o valor a depositar: ");
                scanf("%d",depositar);
                return 0;
                
            case 2:
                printf("Digite o valor de saque.\n");
                scanf("%d",sacar);
                return 0;
                
            case 3:
                printf("Digite a instituição para realizar a transferencia.\n");
                scanf("%d",transferir);
                 return 0;

            case 4:
            printf("Extrato.\n");
            return 0;

            case 5:
            printf("Sair.\n");
            return 0;

            default:
                printf("Opcao invalida!\n");
                return 0;
        }
    
    }
    

    }

     



