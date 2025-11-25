// utils.cpp
#include "utils.h"

std::string nomeMes(int mes)
{
    static const char* nomes[] =
    {
        "Inválido",
        "Janeiro","Fevereiro","Março","Abril","Maio","Junho",
        "Julho","Agosto","Setembro","Outubro","Novembro","Dezembro"
    };

    if (mes < 1 || mes > 12) return "Inválido";
    return nomes[mes];
}

int diasNoMes(int mes, int ano)
{
    if (mes == 2)
    {
        bool bissexto = (ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0);
        return bissexto ? 29 : 28;
    }

    if (mes==4 || mes==6 || mes==9 || mes==11) return 30;

    return 31;
}

// Retorna o dia da semana: 0=Domingo, 1=Segunda, ..., 6=Sábado
int diaSemana(int dia, int mes, int ano)
{
    // Algoritmo de Zeller
    if (mes < 3) {
        mes += 12;
        ano--;
    }
    
    int q = dia;
    int m = mes;
    int k = ano % 100;
    int j = ano / 100;
    
    int h = (q + ((13 * (m + 1)) / 5) + k + (k / 4) + (j / 4) - (2 * j)) % 7;
    
    // Converter para formato: 0=Domingo, 1=Segunda, ..., 6=Sábado
    return (h + 6) % 7;
}
