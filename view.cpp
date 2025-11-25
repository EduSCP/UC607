// view.cpp
#include <iostream>
#include <iomanip>
#include "view.h"
#include "utils.h"        // <-- NECESSÁRIO para nomeMes, diasNoMes
#include "colaborador.h"  // <-- NECESSÁRIO para obterMarcacao

using namespace std;

int mostrarMenu()
{
    cout << "\n=============================\n";
    cout << "        RH AVANCADO\n";
    cout << "=============================\n";
    cout << "1. Listar colaboradores\n";
    cout << "2. Adicionar colaborador\n";
    cout << "3. Marcar ferias/faltas\n";
    cout << "4. Visualizar calendario do colaborador\n";
    cout << "5. Buscar colaborador por ID ou nome\n";
    cout << "6. Gerir formacoes/cursos\n";
    cout << "7. Gerir notas/observacoes\n";
    cout << "8. Relatorios mensais\n";
    cout << "9. Estatisticas por departamento\n";
    cout << "10. Dashboard resumido\n";
    cout << "11. Exportar dados\n";
    cout << "0. Guardar e sair\n";
    cout << "-----------------------------\n";
    cout << "Escolha: ";

    int opcao;
    cin >> opcao;
    cin.ignore(); // remove newline
    return opcao;
}

void listarColaboradores(const vector<Colaborador*> &colabs)
{
    cout << "\n--- Lista de Colaboradores ---\n";
    int i = 1;
    for (auto c : colabs)
    {
        cout << i++ << ") " << c->nome << "  [" << c->departamento << "]\n";
    }
}

void mostrarCalendario(const Colaborador *c, int mes, int ano)
{
    cout << "\n=== Calendário de " << c->nome
         << " — " << nomeMes(mes) << " " << ano << " ===\n";

    int totalDias = diasNoMes(mes, ano);

    for (int d = 1; d <= totalDias; d++)
    {
        char t = c->obterMarcacao(d, mes, ano);

        if (t == 'F')
            cout << setw(2) << d << ": Férias\n";
        else if (t == 'X')
            cout << setw(2) << d << ": Falta\n";
        else
            cout << setw(2) << d << ": ( )\n";
    }
}
