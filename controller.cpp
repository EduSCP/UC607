// controller.cpp
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cctype>
#include <map>
#include <limits>

#include "colaborador.h"
#include "utils.h"
#include "view.h"

using namespace std;

// =========================
// Funções auxiliares
// =========================
string toLower(string s) {
    for (char &c : s) c = tolower(c);
    return s;
}

int procurarColaboradorID(const vector<Colaborador*> &colabs, int id) {
    if (id <= 0 || id > (int)colabs.size()) return -1;
    return id - 1;
}

int procurarColaboradorNome(const vector<Colaborador*> &colabs, const string &nome) {
    string alvo = toLower(nome);
    for (int i = 0; i < (int)colabs.size(); i++) {
        if (toLower(colabs[i]->nome) == alvo) return i;
    }
    return -1;
}

// =========================
// Persistência (Simples)
// =========================
string encriptar(const string &s) {
    string r = s;
    for (char &c : r) c ^= 7;
    return r;
}

void guardar(const vector<Colaborador*> &colabs) {
    ofstream f("dados.txt");
    if (!f) return;

    f << colabs.size() << "\n";
    for (auto c : colabs) {
        f << encriptar(c->nome) << "\n";
        f << encriptar(c->departamento) << "\n";

        // Marcações
        f << c->marcacoes.size() << "\n";
        for (auto &m : c->marcacoes) {
            f << m.dia << " " << m.mes << " " << m.ano << " " << m.tipo << "\n";
        }

        // Formações
        f << c->formacoes.size() << "\n";
        for (auto &f1 : c->formacoes) {
            f << encriptar(f1.nome_curso) << "\n";
            f << encriptar(f1.data_conclusao) << "\n";
        }

        // Notas
        f << c->notas.size() << "\n";
        for (auto &n : c->notas) {
            f << encriptar(n.titulo) << "\n";
            f << encriptar(n.texto) << "\n";
            f << encriptar(n.data) << "\n";
        }
    }
}

vector<Colaborador*> carregar() {
    vector<Colaborador*> c;
    ifstream f("dados.txt");
    if (!f) return c;

    int total;
    f >> total;
    f.ignore();

    for (int i = 0; i < total; i++) {
        string nome, dept;

        getline(f, nome);
        getline(f, dept);

        nome = encriptar(nome);
        dept = encriptar(dept);

        Colaborador *col = new Colaborador(nome, dept);

        // Marcações
        int nm;
        f >> nm;
        for (int j = 0; j < nm; j++) {
            Marcacao m;
            f >> m.dia >> m.mes >> m.ano >> m.tipo;
            col->marcacoes.push_back(m);
        }

        // Formações
        int nf;
        f >> nf;
        f.ignore();
        for (int j = 0; j < nf; j++) {
            Formacao fo;
            getline(f, fo.nome_curso);
            getline(f, fo.data_conclusao);
            fo.nome_curso = encriptar(fo.nome_curso);
            fo.data_conclusao = encriptar(fo.data_conclusao);
            col->formacoes.push_back(fo);
        }

        // Notas
        int nn;
        f >> nn;
        f.ignore();
        for (int j = 0; j < nn; j++) {
            Nota n;
            getline(f, n.titulo);
            getline(f, n.texto);
            getline(f, n.data);
            n.titulo = encriptar(n.titulo);
            n.texto = encriptar(n.texto);
            n.data = encriptar(n.data);
            col->notas.push_back(n);
        }

        c.push_back(col);
    }

    return c;
}

// =========================
// Gestão de Marcações
// =========================
void marcarFeriasFaltas(vector<Colaborador*> &colabs) {
    int id;
    cout << "ID do colaborador: ";
    cin >> id;

    int idx = procurarColaboradorID(colabs, id);
    if (idx == -1) {
        cout << "ID inválido!\n";
        return;
    }

    Colaborador *c = colabs[idx];

    int dia, mes, ano;
    char tipo;

    cout << "Dia: "; cin >> dia;
    cout << "Mês: "; cin >> mes;
    cout << "Ano: "; cin >> ano;

    cout << "Tipo (F = férias, X = falta, C = cancelar): ";
    cin >> tipo;

    if (tipo == 'C') {
        c->removerMarcacao(dia, mes, ano);
        cout << "Marcação removida.\n";
        guardar(colabs);
        return;
    }

    // Verificar fim de semana
    int dw = diaSemana(dia, mes, ano);
    if (dw == 0 || dw == 6) {
        cout << "Não pode marcar ao fim de semana!\n";
        return;
    }

    // Aviso de conflito
    for (auto outro : colabs) {
        if (outro->departamento == c->departamento &&
            outro != c &&
            outro->obterMarcacao(dia, mes, ano) == 'F')
        {
            cout << "⚠ AVISO: "
                 << outro->nome
                 << " já tem férias neste dia!\n";
        }
    }

    c->adicionarMarcacao(dia, mes, ano, tipo);
    cout << "Marcação adicionada!\n";

    guardar(colabs);
}

// =========================
// Gestão de Formações
// =========================
void menuFormacoes(Colaborador *c) {
    while (true) {
        cout << "\n--- FORMAÇÕES DE " << c->nome << " ---\n";
        cout << "1. Listar\n2. Adicionar\n3. Editar\n4. Remover\n0. Voltar\n> ";

        int op;
        cin >> op;
        cin.ignore();

        if (op == 0) return;

        if (op == 1) {
            cout << "\n--- Lista ---\n";
            for (int i = 0; i < (int)c->formacoes.size(); i++) {
                cout << "[" << i+1 << "] " << c->formacoes[i].nome_curso
                     << " (" << c->formacoes[i].data_conclusao << ")\n";
            }
        }
        else if (op == 2) {
            Formacao f;
            cout << "Nome do curso: ";
            getline(cin, f.nome_curso);
            cout << "Data conclusão: ";
            getline(cin, f.data_conclusao);
            c->formacoes.push_back(f);
            cout << "Adicionado!\n";
        }
        else if (op == 3) {
            int id;
            cout << "ID da formação: ";
            cin >> id; cin.ignore();
            if (id < 1 || id > (int)c->formacoes.size()) {
                cout << "Inválido.\n"; continue;
            }
            Formacao &f = c->formacoes[id-1];
            cout << "Novo nome: ";
            getline(cin, f.nome_curso);
            cout << "Nova data: ";
            getline(cin, f.data_conclusao);
            cout << "Atualizado!\n";
        }
        else if (op == 4) {
            int id;
            cout << "ID: ";
            cin >> id; cin.ignore();
            if (id < 1 || id > (int)c->formacoes.size()) {
                cout << "Inválido.\n"; continue;
            }
            c->formacoes.erase(c->formacoes.begin() + (id-1));
            cout << "Removido!\n";
        }
    }
}

// =========================
// Gestão de Notas
// =========================
void menuNotas(Colaborador *c) {
    while (true) {
        cout << "\n--- NOTAS DE " << c->nome << " ---\n";
        cout << "1. Listar\n2. Adicionar\n3. Editar\n4. Remover\n0. Voltar\n> ";

        int op;
        cin >> op;
        cin.ignore();

        if (op == 0) return;

        if (op == 1) {
            cout << "\n--- Lista ---\n";
            for (int i = 0; i < (int)c->notas.size(); i++) {
                cout << "[" << i+1 << "] "
                     << c->notas[i].titulo << " - "
                     << c->notas[i].data << "\n"
                     << c->notas[i].texto << "\n\n";
            }
        }
        else if (op == 2) {
            Nota n;
            cout << "Título: ";
            getline(cin, n.titulo);
            cout << "Texto: ";
            getline(cin, n.texto);
            cout << "Data: ";
            getline(cin, n.data);
            c->notas.push_back(n);
            cout << "Adicionado!\n";
        }
        else if (op == 3) {
            int id;
            cout << "ID da nota: ";
            cin >> id; cin.ignore();
            if (id < 1 || id > (int)c->notas.size()) {
                cout << "Inválido.\n"; continue;
            }
            Nota &n = c->notas[id-1];
            cout << "Novo título: ";
            getline(cin, n.titulo);
            cout << "Novo texto: ";
            getline(cin, n.texto);
            cout << "Nova data: ";
            getline(cin, n.data);
            cout << "Atualizado!\n";
        }
        else if (op == 4) {
            int id;
            cout << "ID: ";
            cin >> id; cin.ignore();
            if (id < 1 || id > (int)c->notas.size()) {
                cout << "Inválido.\n"; continue;
            }
            c->notas.erase(c->notas.begin() + (id-1));
            cout << "Removido!\n";
        }
    }
}

// =========================
// Relatórios Mensais
// =========================
void relatorioMensal(const vector<Colaborador*> &colabs) {
    int mes, ano;
    cout << "Mês: "; cin >> mes;
    cout << "Ano: "; cin >> ano;

    cout << "\n=== RELATÓRIO " << nomeMes(mes) << " " << ano << " ===\n";

    for (auto c : colabs) {
        int ferias = 0, faltas = 0;

        for (auto &m : c->marcacoes) {
            if (m.mes == mes && m.ano == ano) {
                if (m.tipo == 'F') ferias++;
                if (m.tipo == 'X') faltas++;
            }
        }

        cout << c->nome << " | Férias: " << ferias
             << " | Faltas: " << faltas << "\n";
    }
}

// =========================
// Estatísticas de departamento
// =========================
void estatisticasDepartamento(const vector<Colaborador*> &colabs) {
    struct Info {
        int ferias = 0;
        int faltas = 0;
    };
    map<string, Info> dep;

    for (auto c : colabs) {
        for (auto &m : c->marcacoes) {
            if (m.tipo == 'F') dep[c->departamento].ferias++;
            if (m.tipo == 'X') dep[c->departamento].faltas++;
        }
    }

    cout << "\n=== ESTATÍSTICAS ===\n\n";

    string pior;
    int piorTotal = -1;

    for (auto &p : dep) {
        int total = p.second.ferias + p.second.faltas;
        cout << p.first << ": " << total << " ausências\n";

        if (total > piorTotal) {
            piorTotal = total;
            pior = p.first;
        }
    }

    cout << "\nDepartamento com mais ausências: " << pior << "\n";
}

// =========================
// Dashboard Resumido
// =========================
void dashboard(const vector<Colaborador*> &colabs) {
    int mes, ano;
    cout << "Mês: "; cin >> mes;
    cout << "Ano: "; cin >> ano;

    cout << "\n=== DASHBOARD ===\n\n";
    cout << "Nome\tFérias\tFaltas\tDias restantes\n";

    for (auto c : colabs) {
        int f = 0, x = 0;

        for (auto &m : c->marcacoes) {
            if (m.mes == mes && m.ano == ano) {
                if (m.tipo == 'F') f++;
                if (m.tipo == 'X') x++;
            }
        }

        int restantes = 22 - f;

        cout << c->nome << "\t" << f << "\t" << x << "\t" << restantes << "\n";
    }
}

// =========================
// Procurar colaborador
// =========================
void buscarColaborador(vector<Colaborador*> &colabs) {
    cout << "1 - Procurar por ID\n";
    cout << "2 - Procurar por nome\n> ";

    int op;
    cin >> op;
    cin.ignore();

    int idx = -1;

    if (op == 1) {
        int id;
        cout << "ID: ";
        cin >> id;
        idx = procurarColaboradorID(colabs, id);
    }
    else {
        string nome;
        cout << "Nome: ";
        getline(cin, nome);
        idx = procurarColaboradorNome(colabs, nome);
    }

    if (idx == -1) {
        cout << "Colaborador não encontrado!\n";
        return;
    }

    Colaborador *c = colabs[idx];

    cout << "\nEncontrado:\n";
    cout << "Nome: " << c->nome << "\nDepartamento: "
         << c->departamento << "\n\n";

    // Mostrar calendário do mês atual (exemplo: Novembro 2025)
    mostrarCalendario(c, 11, 2025);
}

// =========================
// Exportar Relatório
// =========================
void exportarRelatorioColaborador(const Colaborador *c, int ano, const string &ficheiro) {
    ofstream f(ficheiro);
    if (!f) {
        cout << "Erro ao criar ficheiro!\n";
        return;
    }

    f << "RELATORIO DE FÉRIAS E FALTAS - " << ano << "\n";
    f << "------------------------------------------------\n";
    f << "Colaborador: " << c->nome << "\n";
    f << "Departamento: " << c->departamento << "\n";
    f << "------------------------------------------------\n";
    f << "Data       | Tipo\n";
    f << "------------------------------------------------\n";

    int totalF = 0;
    int totalX = 0;

    // Ordenar marcacoes por data seria ideal, mas vamos listar como estão
    // ou filtrar pelo ano.
    for (const auto &m : c->marcacoes) {
        if (m.ano == ano) {
            f << (m.dia < 10 ? "0" : "") << m.dia << "/"
              << (m.mes < 10 ? "0" : "") << m.mes << "/"
              << m.ano << " | ";
            
            if (m.tipo == 'F') {
                f << "Férias";
                totalF++;
            } else if (m.tipo == 'X') {
                f << "Falta";
                totalX++;
            }
            f << "\n";
        }
    }

    f << "------------------------------------------------\n";
    f << "Total Férias: " << totalF << "\n";
    f << "Total Faltas: " << totalX << "\n";
    
    cout << "Relatório exportado para " << ficheiro << " com sucesso!\n";
}

// =========================
// Sistema Principal
// =========================
void executarSistema() {
    vector<Colaborador*> colabs = carregar();

    while (true) {
        int op = mostrarMenu();

        switch (op) {
            case 1:
                listarColaboradores(colabs);
                break;

            case 2: {
                string nome, dept;
                cin.ignore();
                cout << "Nome: "; getline(cin, nome);
                cout << "Departamento: "; getline(cin, dept);
                colabs.push_back(new Colaborador(nome, dept));
                guardar(colabs);
                cout << "Colaborador adicionado!\n";
                break;
            }

            case 3:
                marcarFeriasFaltas(colabs);
                break;

            case 4: {
                int id;
                cout << "ID: ";
                cin >> id;

                int idx = procurarColaboradorID(colabs, id);
                if (idx != -1) {
                    int m, a;
                    cout << "Mês: "; cin >> m;
                    cout << "Ano: "; cin >> a;
                    mostrarCalendario(colabs[idx], m, a);
                }
                break;
            }

            case 5:
                buscarColaborador(colabs);
                break;

            case 6: {
                int id;
                cout << "ID: ";
                cin >> id;
                int idx = procurarColaboradorID(colabs, id);
                if (idx != -1) menuFormacoes(colabs[idx]);
                guardar(colabs);
                break;
            }

            case 7: {
                int id;
                cout << "ID: ";
                cin >> id;
                int idx = procurarColaboradorID(colabs, id);
                if (idx != -1) menuNotas(colabs[idx]);
                guardar(colabs);
                break;
            }

            case 8:
                relatorioMensal(colabs);
                break;

            case 9:
                estatisticasDepartamento(colabs);
                break;

            case 10:
                dashboard(colabs);
                break;

            case 11: {
                int id;
                cout << "ID do colaborador: ";
                cin >> id;
                int idx = procurarColaboradorID(colabs, id);
                if (idx != -1) {
                    int ano;
                    cout << "Ano do relatório: ";
                    cin >> ano;
                    string nomeFicheiro = "relatorio_" + to_string(id) + "_" + to_string(ano) + ".txt";
                    exportarRelatorioColaborador(colabs[idx], ano, nomeFicheiro);
                } else {
                    cout << "Colaborador não encontrado.\n";
                }
                break;
            }

            case 0:
                cout << "A sair...\n";
                guardar(colabs);
                return;

            default:
                cout << "Opção inválida!\n";
        }

        cout << "\nPressione ENTER para continuar...";
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}
