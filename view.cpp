// view.cpp
#include "view.h"
#include "utils.h"
#include <iostream>
#include <iomanip>

using namespace std;

int mostrarMenu() {
    cout << "\n===== Mini-Sistema RH =====\n";
    cout << "1. Adicionar colaborador\n";
    cout << "2. Listar colaboradores\n";
    cout << "3. Marcar férias\n";
    cout << "4. Marcar falta\n";
    cout << "5. Desmarcar dia\n";
    cout << "6. Ver calendário mensal\n";
    cout << "7. Guardar e sair\n";
    cout << "Escolha: ";
    int op;
    cin >> op;
    cin.ignore();
    return op;
}

void listarColaboradores(const vector<Colaborador*> &colabs) {
    cout << "\n--- Lista de Colaboradores ---\n";
    if (colabs.empty()) {
        cout << "Nenhum colaborador registado.\n";
        return;
    }
    for (size_t i = 0; i < colabs.size(); ++i)
        cout << i+1 << ") " << colabs[i]->nome << endl;
}

void mostrarCalendario(const Colaborador *c, int mes, int ano) {
    cout << "\nCalendário de " << c->nome << " - " << nomeMes(mes) << " " << ano << "\n";
    cout << "Dom Seg Ter Qua Qui Sex Sab\n";

    int primeiroDia = diaSemana(1, mes, ano);
    int dias = diasNoMes(mes, ano);

    // espaçamento inicial
    for (int i = 0; i < primeiroDia; i++)
        cout << "    ";

    for (int d = 1; d <= dias; d++) {
        int diaSem = diaSemana(d, mes, ano);
        char marca = obterMarcacao(c, d, mes, ano);

        if (marca == 'F' || marca == 'X') {
            cout << setw(2) << d << marca << " ";
        } else if (diaSem == 0 || diaSem == 6) {
            cout << setw(2) << d << "() ";
        } else {
            cout << setw(2) << d << "   ";
        }

        if (diaSem == 6) cout << "\n";
    }
    cout << "\nLegenda: (F) Férias | (X) Falta | () Fim de semana\n";
}
