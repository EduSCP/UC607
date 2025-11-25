// colaborador.cpp
#include "colaborador.h"
#include <algorithm>

int Colaborador::nextId = 1;

// -------------------------
// Construtores
// -------------------------
Colaborador::Colaborador() {
    id = nextId++;
}

Colaborador::Colaborador(const std::string &n, const std::string &dep)
    : nome(n), departamento(dep)
{
    id = nextId++;
}

// -------------------------
// Marcações (Férias/Faltas)
// -------------------------
void Colaborador::adicionarMarcacao(int dia, int mes, int ano, char tipo) {
    for (auto &m : marcacoes) {
        if (m.dia == dia && m.mes == mes && m.ano == ano) {
            m.tipo = tipo;
            return;
        }
    }
    marcacoes.push_back({dia, mes, ano, tipo});
}

void Colaborador::removerMarcacao(int dia, int mes, int ano) {
    marcacoes.erase(
        std::remove_if(marcacoes.begin(), marcacoes.end(),
            [&](const Marcacao &m) {
                return m.dia == dia && m.mes == mes && m.ano == ano;
            }),
        marcacoes.end());
}

bool Colaborador::temMarcacao(int dia, int mes, int ano) const {
    for (const auto &m : marcacoes) {
        if (m.dia == dia && m.mes == mes && m.ano == ano)
            return true;
    }
    return false;
}

char Colaborador::obterMarcacao(int dia, int mes, int ano) const {
    for (const auto &m : marcacoes) {
        if (m.dia == dia && m.mes == mes && m.ano == ano)
            return m.tipo;
    }
    return ' ';
}

int Colaborador::contarFeriasNoMes(int mes, int ano) const {
    int total = 0;
    for (const auto &m : marcacoes)
        if (m.mes == mes && m.ano == ano && m.tipo == 'F')
            total++;
    return total;
}

int Colaborador::contarFaltasNoMes(int mes, int ano) const {
    int total = 0;
    for (const auto &m : marcacoes)
        if (m.mes == mes && m.ano == ano && m.tipo == 'X')
            total++;
    return total;
}

// -------------------------
// Formações
// -------------------------
void Colaborador::adicionarFormacao(const std::string &curso, const std::string &data) {
    formacoes.push_back({curso, data});
}

void Colaborador::editarFormacao(int index, const std::string &curso, const std::string &data) {
    if (index >= 0 && index < (int)formacoes.size()) {
        formacoes[index].nome_curso = curso;
        formacoes[index].data_conclusao = data;
    }
}

void Colaborador::removerFormacao(int index) {
    if (index >= 0 && index < (int)formacoes.size())
        formacoes.erase(formacoes.begin() + index);
}

// -------------------------
// Notas
// -------------------------
void Colaborador::adicionarNota(const std::string &texto, const std::string &data) {
    notas.push_back({"", texto, data});  // titulo vazio por padrão
}

void Colaborador::editarNota(int index, const std::string &texto, const std::string &data) {
    if (index >= 0 && index < (int)notas.size()) {
        notas[index].texto = texto;
        notas[index].data = data;
    }
}

void Colaborador::removerNota(int index) {
    if (index >= 0 && index < (int)notas.size())
        notas.erase(notas.begin() + index);
}
