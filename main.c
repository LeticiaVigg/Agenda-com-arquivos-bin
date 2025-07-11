/* 
Agenda de pedidos de uma loja;
Requer: informações de cada compra (nome, email, cpf, endereço, data da compra e data do envio) e data de comparação para identificação das compras enviadas;
Assegura: cadastro, consulta e listagem das compras, arquivos com lista de pedidos completa, lista de pedidos enviados e lista de pedidos não enviados.
Autores: Danniel, Letícia, Lisiane e Murilo - 2025
*/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "struct.h"

/*
Sub-rotina para cadastrar uma compra;
Requer: nome, email, CPF e endereço do comprador e data da compra;
Assegura: entrada dos dados da compra no arquivo "lista_completa.bin".
*/
void cadastro(){
    struct compra comprador;

    char entrada[160];

    FILE *arquivo = fopen("lista_completa.bin", "ab"); 
    if(arquivo == NULL){
        perror("Erro");
        return;
    }
    
    printf("Nome: ");
    fgets(comprador.nome, sizeof comprador.nome, stdin);
    fflush(stdin);
    
    printf("Email: ");
    fgets(comprador.email, sizeof comprador.email, stdin);
    fflush(stdin);

    printf("Endereço: ");
    fgets(comprador.endereco, sizeof comprador.endereco, stdin);
    fflush(stdin);

    printf("Data da compra: ");
    fgets(entrada, sizeof entrada, stdin);
    fflush(stdin);
    sscanf(entrada, "%d %d %d", &comprador.da_compra.dia, &comprador.da_compra.mes, &comprador.da_compra.ano);

    //Verificaçâo se a data é válida
    if(comprador.da_compra.dia<31 && comprador.da_compra.mes<13 && comprador.da_compra.ano<2028 &&
        comprador.da_compra.dia>0 && comprador.da_compra.mes>0 && comprador.da_compra.ano>2020){
        if(comprador.da_compra.dia>16 && comprador.da_compra.mes!=12){
            comprador.envio.dia = 14 - (30 - comprador.da_compra.dia);
            comprador.envio.ano = comprador.da_compra.ano;
            comprador.envio.mes = (comprador.da_compra.mes + 1);

        }
        else if(comprador.da_compra.dia>16 && comprador.da_compra.mes==12){
            comprador.envio.dia = 14 - (30 - comprador.da_compra.dia);
            comprador.envio.mes = 1;
            comprador.envio.ano = (comprador.da_compra.ano + 1);
        }
            else{
                comprador.envio.dia = comprador.da_compra.dia + 14;
                comprador.envio.mes = comprador.da_compra.mes;
                comprador.envio.ano = comprador.da_compra.ano;
            }
    }

    if(comprador.da_compra.dia<31 && comprador.da_compra.mes<13 && comprador.da_compra.ano<2028 &&
        comprador.da_compra.dia>0 && comprador.da_compra.mes>0 && comprador.da_compra.ano>2020){
        
        fwrite(&comprador, sizeof comprador, 1, arquivo);
    }
    fclose(arquivo);
}

/*
Sub-rotina para buscar uma compra na "lista_completa.bin" a partir de um nome;
Requer: arquivo lista_completa.bin;
Assegura: apresentação do cadastro da compra referente ao nome buscado;
*/
void consulta_por_nome(){
    struct compra comprador;

    FILE *arquivo = fopen("lista_completa.bin", "rb"); //arquivo completo
    if(arquivo == NULL){
        perror("Erro");
        return;
    }

    printf("Digite o nome do comprador: ");
    char nome_procurado[160];
    fgets(nome_procurado, sizeof nome_procurado, stdin);
    fflush(stdin);

    bool achou = false;
    while(!achou && fread(&comprador, sizeof comprador, 1, arquivo) > 0){
        if(strcmp(comprador.nome, nome_procurado) == 0){
            achou = true;
        }
    }
    if(achou){
        printf("\n%s%s%s%02d/%02d/%04d\n%02d/%02d/%04d\n", comprador.nome, comprador.email,
                comprador.endereco, comprador.da_compra.dia, comprador.da_compra.mes, comprador.da_compra.ano,
                comprador.envio.dia, comprador.envio.mes, comprador.envio.ano);
    }
    else{
        printf("Compra não identificada");
    }

    fclose(arquivo);
}

/*
Sub-rotina para buscar uma compra na "lista_completa.bin" a partir de um e-mail;
Requer: arquivo lista_completa.bin;
Assegura: apresentação do cadastro da compra referente ao e-mail buscado;
*/
void consulta_por_email(){
    struct compra comprador;

    FILE *arquivo = fopen("lista_completa.bin", "rb"); 
    if(arquivo == NULL){
        perror("Erro");
        return;
    }

    printf("Digite o email do comprador: ");
    char email_procurado[160];
    fgets(email_procurado, sizeof email_procurado, stdin);
    fflush(stdin);

    bool achou = false;
    while(!achou && fread(&comprador, sizeof comprador, 1, arquivo) > 0){
        if(strcmp(comprador.email, email_procurado) == 0){
            achou = true;
        }
    }
    if(achou){
        printf("\n%s%s%s%02d/%02d/%04d\n%02d/%02d/%04d\n", comprador.nome, comprador.email,
                comprador.endereco, comprador.da_compra.dia, comprador.da_compra.mes, comprador.da_compra.ano,
                comprador.envio.dia, comprador.envio.mes, comprador.envio.ano);
    }
    else{
        printf("Compra não identificada");
    }

    fclose(arquivo);
}

/*
Sub-rotina para apresentar a lista completa;
Requer: arquivo "lista_completa.bin";
Assegura: apresentação da lista completa.
*/
void lista_completa(){
    struct compra comprador;

    FILE *arquivo = fopen("lista_completa.bin", "rb"); //arquivo completo
    if(arquivo == NULL){
        perror("Erro");
        return;
    }

    while(fread(&comprador, sizeof comprador, 1, arquivo) > 0){
        printf("\n%s%s%s%02d/%02d/%04d\n%02d/%02d/%04d\n", comprador.nome, comprador.email,
            comprador.endereco, comprador.da_compra.dia, comprador.da_compra.mes,
            comprador.da_compra.ano, comprador.envio.dia, comprador.envio.mes, comprador.envio.ano);
    }

    fclose(arquivo);
}

/*
Sub-rotina para separar a lista completa em duas listas: uma de pedios enviados e uma de pedidos não enviados;
Requer: data de comparação para identificação das compras enviadas e arquivo "lista_completa.bin";
Assegura: dois arquivos com listas diferentes, um com as compras enviadas e um com as compras não enviadas;
*/
void separa_lista(){
    char entrada[160];
    printf("Data a ser comparada: ");
    fgets(entrada, sizeof entrada, stdin);
    fflush(stdin);
    int dia, mes, ano;
    sscanf(entrada, "%d %d %d", &dia, &mes, &ano);
    if(dia<0 || dia>30 || mes<0 || mes>12 || ano<2020 || ano>2028){
        printf("\nData invalida\n");
        return;
    }

    struct compra comparador;

    FILE *arquivo1 = fopen("lista_completa.bin", "rb"); 
    FILE *arquivo2 = fopen("lista_enviados.bin", "wb"); 
    FILE *arquivo3 = fopen("lista_nao_enviados.bin", "wb"); 
    if(arquivo1 == NULL || arquivo2 == NULL || arquivo3 == NULL){
        perror("Erro");
        return;
    }

    while(fread(&comparador, sizeof comparador, 1, arquivo1) > 0){
        if(comparador.envio.ano < ano){
            fwrite(&comparador, sizeof comparador, 1, arquivo2);
        }
        else if(comparador.envio.ano > ano){
                fwrite(&comparador, sizeof comparador, 1, arquivo3);
        }
            else if(comparador.envio.ano == ano){
                if(comparador.envio.mes < mes){
                    fwrite(&comparador, sizeof comparador, 1, arquivo2);
                }
                else if(comparador.envio.mes > mes){
                    fwrite(&comparador, sizeof comparador, 1, arquivo3);
                }
                    else if(comparador.envio.mes == mes){
                        if(comparador.envio.dia < dia){
                            fwrite(&comparador, sizeof comparador, 1, arquivo2);
                        }
                        else if(comparador.envio.dia > dia){
                            fwrite(&comparador, sizeof comparador, 1, arquivo3);
                        }
                            else if(comparador.envio.dia == dia){
                                fwrite(&comparador, sizeof comparador, 1, arquivo2);
                            }
                    }
            }
    }

    fclose(arquivo1);
    fclose(arquivo2);
    fclose(arquivo3);
}

/*
Sub-rotina para apresentar a lista dos pedidos não enviados;
Requer: arquivo "lista_nao_enviados.bin";
Assegura: apresentação da lista de pedidos não enviados.
*/
void lista_nao_enviados(){
    struct compra comprador;

    FILE *arquivo = fopen("lista_nao_enviados.bin", "rb"); //arquivo de lista de pedidos não enviados
    if(arquivo == NULL){
        perror("Erro");
        return;
    }

    while(fread(&comprador, sizeof comprador, 1, arquivo) > 0){
        printf("\n%s%s%s%02d/%02d/%04d\n%02d/%02d/%04d\n", comprador.nome, comprador.email,
                comprador.endereco, comprador.da_compra.dia, comprador.da_compra.mes, comprador.da_compra.ano,
                comprador.envio.dia, comprador.envio.mes, comprador.envio.ano);
    }

    fclose(arquivo);
}

/*
Sub-rotina para apresentar a lista dos pedidos enviados;
Requer: arquivo "lista_enviados.bin";
Assegura: apresentação da lista de pedidos enviados.
*/
void lista_enviados(){
    struct compra comprador;

    FILE *arquivo = fopen("lista_enviados.bin", "rb"); //arquivo lista de pedidos enviados
    if(arquivo == NULL){
        perror("Erro");
        return;
    }

    while(fread(&comprador, sizeof comprador, 1, arquivo) > 0){
        printf("\n%s%s%s%02d/%02d/%04d\n%02d/%02d/%04d\n", comprador.nome, comprador.email,
                comprador.endereco, comprador.da_compra.dia, comprador.da_compra.mes, comprador.da_compra.ano,
                comprador.envio.dia, comprador.envio.mes, comprador.envio.ano);
    }

    fclose(arquivo);
}

int main(void){
    printf("Bem vinda a agenda virtual de compras");
    printf("\n---------------------------------\n");

    char opcao[40];
    do{
        printf("\nMenu da agenda:\n"
               "1 - Cadastrar uma comprar\n"
               "2 - Consultar uma compra por nome\n"
               "3 - Consultar uma compra por email\n"
               "4 - Listar a agenda completa\n"
               "5 - Listar as compras enviadas a partir de certa data\n"
               "6 - Listar as compras não enviadas a partir de certa data\n"
               "7 - Sair\n");
        fgets(opcao, sizeof opcao, stdin);
        switch(opcao[0]){
            case'1':
                cadastro();
                break;
            case '2':
                consulta_por_nome();
                break;
            case '3':
                consulta_por_email();
                break;
            case '4':
                lista_completa();
                break;
            case '5':
                separa_lista();
                lista_enviados();
                break;
            case '6':
                separa_lista();
                lista_nao_enviados();
                break;        
        }       
    }while(opcao[0] != '7');
    
    return 0;
}