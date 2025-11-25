// colaborador.h
#pragma once
#include <string>
#include <vector>

struct Formacao {
    std::string nome_curso;
    std::string data_conclusao;
};

struct Nota {
    std::string titulo;
    std::string texto;
    std::string data;
};

struct Marcacao {
    int dia = 0;
    int mes = 0;
    int ano = 0;
    char tipo = ' '; // 'F' férias | 'X' falta
};

class Colaborador {
private:
    int id;
    static int nextId;

public:
    std::string nome;
    std::string departamento;

    std::vector<Formacao> formacoes;
    std::vector<Nota> notas;
    std::vector<Marcacao> marcacoes;

    // ---- Construtores ----
    Colaborador();
    Colaborador(const std::string &n, const std::string &dep);

    // ---- Acesso ao ID ----
    int getId() const { return id; }

    // ---- Marcações ----
    void adicionarMarcacao(int dia, int mes, int ano, char tipo);
    void removerMarcacao(int dia, int mes, int ano);
    bool temMarcacao(int dia, int mes, int ano) const;
    char obterMarcacao(int dia, int mes, int ano) const;

    int contarFeriasNoMes(int mes, int ano) const;
    int contarFaltasNoMes(int mes, int ano) const;

    // ---- Formações ----
    void adicionarFormacao(const std::string &curso, const std::string &data);
    void editarFormacao(int index, const std::string &curso, const std::string &data);
    void removerFormacao(int index);

    // ---- Notas ----
    void adicionarNota(const std::string &texto, const std::string &data);
    void editarNota(int index, const std::string &texto, const std::string &data);
    void removerNota(int index);
};
