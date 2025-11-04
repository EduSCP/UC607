// utils.cpp
#include "utils.h"

int diaSemana(int dia, int mes, int ano) {
    if (mes < 3) { mes += 12; ano--; }
    int k = ano % 100;
    int j = ano / 100;
    int h = (dia + 13*(mes + 1)/5 + k + k/4 + j/4 + 5*j) % 7;
    int d = (h + 6) % 7; // 0 = Domingo, 6 = Sábado
    return d;
}

int diasNoMes(int mes, int ano) {
    switch (mes) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12: return 31;
        case 4: case 6: case 9: case 11: return 30;
        case 2: return ((ano%4==0 && ano%100!=0) || (ano%400==0)) ? 29 : 28;
        default: return 30;
    }
}

std::string nomeMes(int mes) {
    const std::string meses[] = {
        "Janeiro","Fevereiro","Março","Abril","Maio","Junho",
        "Julho","Agosto","Setembro","Outubro","Novembro","Dezembro"
    };
    if (mes < 1 || mes > 12) return "Mês Inválido";
    return meses[mes - 1];
}

// Cifra de César simples (+3)
std::string encryptName(const std::string &nome) {
    std::string out = nome;
    for (char &c : out) {
        if (isalpha(c)) {
            char base = islower(c) ? 'a' : 'A';
            c = (c - base + 3) % 26 + base;
        }
    }
    return out;
}

// Desencripta (-3)
std::string decryptName(const std::string &enc) {
    std::string out = enc;
    for (char &c : out) {
        if (isalpha(c)) {
            char base = islower(c) ? 'a' : 'A';
            c = (c - base - 3 + 26) % 26 + base;
        }
    }
    return out;
}
