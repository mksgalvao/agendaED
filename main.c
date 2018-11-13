#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Agenda
{
    char name[30];
    int cel;
    char email[20];
    int idade;
    char dn[10];

    struct Agenda *prox;
} contato;

int tam;

void inicia(contato *LISTA);
int menu();
void opcao(contato *LISTA, int op);
contato *aloca();
void insereFim(contato *LISTA);
void insereInicio(contato *LISTA);
void exibe(contato *LISTA);
void libera(contato *LISTA);
void insere (contato *LISTA);
void retiraInicio(contato *LISTA);
void retiraFim(contato *LISTA);
void retira(contato *LISTA);
void pesquisa(contato * LISTA);


int main()
{
    contato *LISTA = (contato *) malloc(sizeof(contato));
    if(!LISTA)
    {
        printf("Sem memoria disponivel!\n");
        exit(1);
    }
    else
    {
        inicia(LISTA);
        int opt;
        do
        {
            opt=menu();
            opcao(LISTA,opt);
        }
        while(opt);
        free(LISTA);
    }
}

int menu()
{
    int opt;
    printf("\n---- # \t Menu agenda \t # ----\n\n");
    printf("1. Adicionar um novo contato ao inicio da agenda\n");
    printf("2. Adicionar um novo contato ao final da agenda\n");
    printf("3. Escolher onde inserir um novo contato na agenda\n");
    printf("4. Excluir um contato do inicio da agenda\n");
    printf("5. Excluir um cotato do fim da agenda\n");
    printf("6. Escolher de onde excluir um contato da agenda\n");
    printf("7. Apagar toda a agenda\n");
    printf("8. Exibir toda a agenda\n");
    printf("9. Pesquisar contato na lista\n");
    printf("0. Sair\n");
    printf("Opcao: ");
    scanf("%d", &opt);
    return opt;

}

void opcao(contato *LISTA, int op)
{
    switch(op)
    {
    case 0:
        libera(LISTA);
        break;
    case 1:
        insereInicio(LISTA);
        break;
    case 2:
        insereFim(LISTA);
        break;
    case 3:
        insere(LISTA);
        break;
    case 4:
        insereFim(LISTA);
        break;
    case 5:
        retiraInicio(LISTA);
        break;
    case 6:
        retiraFim(LISTA);
        libera(LISTA);
        inicia(LISTA);
        break;
    case 7:
        retira(LISTA);;
        break;
    case 8:
        exibe(LISTA);
        break;
    case 9:
        pesquisa(LISTA);
    default:
        printf("Comando invalido\n\n");
    }
}

void inicia(contato *LISTA)
{
    LISTA->prox = NULL;
    tam=0;
}

int vazia(contato *LISTA)
{
    if(LISTA->prox == NULL)
        return 1;
    else
        return 0;
}

contato *aloca()
{
    contato *novo=(contato *) malloc(sizeof(contato));
    if(!novo)
    {
        printf("Sem memoria disponivel!\n");
        exit(1);
    }
    else
    {
        system("cls");
        printf("Nome do Contato: \n");
        scanf("%s",&novo->name);
        printf("Telefone do contato: \n");
        scanf("%d", &novo->cel);
        printf("Email do contato:\n");
        scanf("%s", &novo->email);
        printf("Idade do contato: \n");
        scanf("%d", &novo->idade);
        printf("Data de nascimento do contato: \n");
        scanf("%s", &novo->dn);

        return novo;
    }
}


void insereFim(contato *LISTA)
{
    contato *novo = aloca();
    novo->prox = NULL;
    if(vazia(LISTA))
        LISTA->prox = novo;
    else
    {
        contato *tmp = LISTA->prox;
        while(tmp->prox != NULL)
            tmp = tmp->prox;
        tmp->prox = novo;
    }
    tam++;
}

void insereInicio(contato *LISTA)
{
    contato *novo = aloca();
    contato *oldInic = LISTA->prox;
    LISTA->prox = novo;
    novo->prox = oldInic;
    tam++;
}

void exibe(contato *LISTA)
{
    system("cls");
    if(vazia(LISTA))
    {
        printf("Lista vazia\n\n");
        return ;
    }
    contato *tmp;
    tmp = LISTA->prox;
    printf("Agenda Zica:\n\n");
    while( tmp != NULL)
    {
        printf("##Contato##\n\n");
        printf("Nome:");
        puts(tmp->name);
        printf("Telefone: %d\n", tmp->cel);
        printf("Email:");
        puts(tmp->email);
        printf("idade: %d\n", tmp->idade);
        printf("Data de nascimento:");
        puts(tmp->dn);
        printf("-------##------------\n");
        tmp = tmp->prox;

    }

    printf("\n\n");
}

void libera(contato *LISTA)
{
    if(!vazia(LISTA))
    {
        contato *proximo,
                *atual;
        atual = LISTA->prox;
        while(atual != NULL)
        {
            proximo = atual->prox;
            free(atual);
            atual = proximo;
        }
    }
}

void insere(contato *LISTA)
{
    int pos,count;
    printf("Em que posicao, [de 1 ate %d] voce deseja inserir um contato: ", tam);
    scanf("%d",&pos);
    if(pos>0 && pos <= tam)
    {
        if(pos==1)
            insereInicio(LISTA);
        else
        {
            contato *atual = LISTA->prox,
                     *anterior = LISTA;
            contato *novo=aloca();
            for(count=1 ; count < pos ; count++)
            {
                anterior=atual;
                atual=atual->prox;
            }
            anterior->prox = novo;
            novo->prox = atual;
            tam++;
        }

    }
    else
        printf("Elemento invalido\n\n");
}

void retiraInicio(contato *LISTA)
{
    if(LISTA->prox == NULL)
    {
        printf("Lista vazia\n");
    }
    else
    {
        contato *tmp = LISTA->prox;
        LISTA->prox = tmp->prox;
        tam--;
    }

}

void retiraFim(contato *LISTA)
{
    if(LISTA->prox == NULL)
    {
        printf("Lista vazia\n\n");
    }
    else
    {
        contato *ultimo = LISTA->prox,
                 *penultimo = LISTA;

        while(ultimo->prox != NULL)
        {
            penultimo = ultimo;
            ultimo = ultimo->prox;
        }
        penultimo->prox = NULL;
        tam--;
    }
}

void retira(contato *LISTA)
{
    int opt,count;
    printf("Que posicao, [de 1 ate %d] voce deseja excluir o contato: ", tam);
    scanf("%d", &opt);
    if(opt>0 && opt <= tam)
    {
        if(opt==1)
            return retiraInicio(LISTA);
        else
        {
            contato *atual = LISTA->prox,
                     *anterior = LISTA;

            for(count=1 ; count < opt ; count++)
            {
                anterior=atual;
                atual=atual->prox;
            }

            anterior->prox=atual->prox;
            tam--;
        }
    }
    else
    {
        printf("Elemento invalido\n\n");
    }
}

void pesquisa(contato * LISTA)
{

    system("cls");
    char busca[30];
    printf("Digite o NOME do contato que deseja buscar\n");
    scanf("%s", &busca);

    if(vazia(LISTA))
    {
        printf("Lista vazia, contato nao encontrado!\n\n");
        return ;
    }
    contato *tmp;
    tmp = LISTA->prox;

   do
    {

        if(stricmp(tmp->name,busca) == 0)
        {
            printf("\n\n \t\t - >  Contato encontrado! < - \t\t\n\n");
            printf("##Contato##\n\n");
            printf("Nome:");
            puts(tmp->name);
            printf("Telefone: %d\n", tmp->cel);
            printf("Email:");
            puts(tmp->email);
            printf("idade: %d\n", tmp->idade);
            printf("Data de nascimento:");
            puts(tmp->dn);
            printf("-------##------------\n");
            break;
        }
        else if(stricmp(tmp->name,busca) == 1){
            printf(" \n Contato nao encontrado!\n");
            break;
        }
        tmp = tmp->prox;
    }
    while( tmp != NULL);


}


