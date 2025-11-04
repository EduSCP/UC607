// controller.cpp
#include "controller.h"
#include "view.h"
#include "utils.h"
#include "storage.h"
#include <iostream>

using namespace std;

void executarSistema() {
    vector<Colaborador*> colabs;

    // Tenta carregar colaboradores do ficheiro
    int lidos = carregarColaboradores("data.txt", colabs);
    cout << "Foram carregados " << lidos << " colaboradores do ficheiro.\n";

    bool sair = false;

    while (!sair) {
        int op = mostrarMenu();

        switch (op) {
            case 1: { // Adicionar colaborador
                cout << "Nome do colaborador: ";
                string nome;
                getline(cin, nome);

                bool existe = false;
                for (auto c : colabs)
                    if (c->nome == nome) existe = true;

                if (existe) {
                    cout << "Já existe um colaborador com esse nome!\n";
                } else {
                    colabs.push_back(new Colaborador(nome));
                    cout << "Colaborador adicionado com sucesso.\n";
                }
                break;
            }

            case 2: { // Listar
                listarColaboradores(colabs);
                break;
            }

            case 3: // Marcar férias
            case 4: { // Marcar falta
                listarColaboradores(colabs);
                if (colabs.empty()) break;
                cout << "Escolha o número do colaborador: ";
                int n;
                cin >> n;
                cin.ignore();
                if (n < 1 || n > (int)colabs.size()) {
                    cout << "Número inválido.\n";
                    break;
                }

                int dia, mes, ano;
                cout << "Data (dia mes ano): ";
                cin >> dia >> mes >> ano;
                cin.ignore();

                int dw = diaSemana(dia, mes, ano);
                if (dw == 0 || dw == 6) {
                    cout << "Não é permitido marcar ao fim de semana!\n";
                    break;
                }

                if (dia < 1 || dia > diasNoMes(mes, ano)) {
                    cout << "Dia inválido para esse mês!\n";
                    break;
                }

                char tipo = (op == 3) ? 'F' : 'X';
                adicionarMarcacao(colabs[n-1], dia, mes, ano, tipo);
                cout << ((op == 3) ? "Férias" : "Falta") << " marcada.\n";
                break;
            }

            case 5: { // Desmarcar
                listarColaboradores(colabs);
                if (colabs.empty()) break;
                cout << "Escolha o número do colaborador: ";
                int n;
                cin >> n;
                cin.ignore();
                if (n < 1 || n > (int)colabs.size()) {
                    cout << "Número inválido.\n";
                    break;
                }

                int dia, mes, ano;
                cout << "Data (dia mes ano): ";
                cin >> dia >> mes >> ano;
                cin.ignore();

                removerMarcacao(colabs[n-1], dia, mes, ano);
                cout << "Dia desmarcado.\n";
                break;
            }

            case 6: { // Ver calendário
                listarColaboradores(colabs);
                if (colabs.empty()) break;
                cout << "Escolha o número do colaborador: ";
                int n;
                cin >> n;
                cin.ignore();
                if (n < 1 || n > (int)colabs.size()) {
                    cout << "Número inválido.\n";
                    break;
                }

                int mes, ano;
                cout << "Mês e ano (ex: 11 2025): ";
                cin >> mes >> ano;
                cin.ignore();
                mostrarCalendario(colabs[n-1], mes, ano);
                break;
            }

            case 7: { // Guardar e sair
                if (guardarColaboradores("data.txt", colabs))
                    cout << "Dados guardados com sucesso!\n";
                else
                    cout << "Erro ao guardar ficheiro!\n";
                sair = true;
                break;
            }

            default:
                cout << "Opção inválida!\n";
        }
    }

    // Libertar memória
    for (auto c : colabs)
        delete c;

    cout << "Programa terminado.\n";
}
