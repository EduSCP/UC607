// colaborador.h
#ifndef COLABORADOR_H
#define COLABORADOR_H

#include <string>
#include <vector>

struct Marcacao {
    int dia;
    int mes;
    int ano;
    char tipo; // 'F' = Férias, 'X' = Falta
};

struct Colaborador {
    std::string nome;
    std::vector<Marcacao> marcacoes;

    // Construtor simples
    Colaborador(const std::string &n);
};

// Funções associadas ao colaborador
void adicionarMarcacao(Colaborador *c, int dia, int mes, int ano, char tipo);
void removerMarcacao(Colaborador *c, int dia, int mes, int ano);
char obterMarcacao(const Colaborador *c, int dia, int mes, int ano);

#endif
