// colaborador.cpp
#include "colaborador.h"

Colaborador::Colaborador(const std::string &n) {
    nome = n;
}

void adicionarMarcacao(Colaborador *c, int dia, int mes, int ano, char tipo) {
    for (auto &m : c->marcacoes) {
        if (m.dia == dia && m.mes == mes && m.ano == ano) {
            m.tipo = tipo;
            return;
        }
    }
    Marcacao m{dia, mes, ano, tipo};
    c->marcacoes.push_back(m);
}

void removerMarcacao(Colaborador *c, int dia, int mes, int ano) {
    for (auto it = c->marcacoes.begin(); it != c->marcacoes.end(); ++it) {
        if (it->dia == dia && it->mes == mes && it->ano == ano) {
            c->marcacoes.erase(it);
            return;
        }
    }
}

char obterMarcacao(const Colaborador *c, int dia, int mes, int ano) {
    for (auto &m : c->marcacoes) {
        if (m.dia == dia && m.mes == mes && m.ano == ano) {
            return m.tipo;
        }
    }
    return ' ';
}
