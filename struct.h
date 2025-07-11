#ifndef STR
#define STR

//Definição de um struct para as datas:
struct data{
    int dia;
    int mes;
    int ano;
};

//Definição de um struct para compra:
struct compra{
    char nome[160];
    char email[160];
    char endereco[160];
    struct data da_compra;
    struct data envio;
};

#endif