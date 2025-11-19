// controller.cpp
#include "controller.h"
#include "view.h"
#include "utils.h"
#include "storage.h"
#include <iostream>

using namespace std;

void executarSistema()
{
    vector<Colaborador *> colabs;

    // Tenta carregar colaboradores do ficheiro
    int lidos = carregarColaboradores("data.txt", colabs);
    cout << "Foram carregados " << lidos << " colaboradores do ficheiro.\n";

    bool sair = false;

    while (!sair)
    {
        int op = mostrarMenu();

        switch (op)
        {

        case 1:
        { // Listar colaboradores
            listarColaboradores(colabs);
            break;
        }

        case 2:
        { // Adicionar colaborador
            cout << "Nome do colaborador: ";
            string nome;
            getline(cin, nome);

            bool existe = false;
            for (auto c : colabs)
                if (c->nome == nome)
                    existe = true;

            if (existe)
            {
                cout << "Já existe um colaborador com esse nome!\n";
            }
            else
            {
                colabs.push_back(new Colaborador(nome));
                cout << "Colaborador adicionado com sucesso.\n";
            }
            break;
        }

        case 3:
        { // Marcar férias/faltas → submenu
            // vamos criar esta função mais tarde
            cout << ">>> Marcação de férias/faltas (a implementar)\n";
            break;
        }

        case 4:
        { // Visualizar calendário
            listarColaboradores(colabs);
            if (colabs.empty())
                break;

            cout << "Escolha o número do colaborador: ";
            int n;
            cin >> n;
            cin.ignore();

            if (n < 1 || n > (int)colabs.size())
            {
                cout << "Número inválido.\n";
                break;
            }

            int mes, ano;
            cout << "Mês e ano (ex: 11 2025): ";
            cin >> mes >> ano;
            cin.ignore();

            mostrarCalendario(colabs[n - 1], mes, ano);
            break;
        }

        case 5:
        {
            cout << ">>> Buscar colaborador por nome/ID (a implementar)\n";
            break;
        }

        case 6:
        {
            cout << ">>> Gestão de formações/cursos (a implementar)\n";
            break;
        }

        case 7:
        {
            cout << ">>> Gestão de notas/observações (a implementar)\n";
            break;
        }

        case 8:
        { // Relatórios mensais
            gerarRelatorioMensal(colabs);
            break;
        }

        case 9:
        {
            cout << ">>> Estatísticas por departamento (a implementar)\n";
            break;
        }

        case 10:
        {
            cout << ">>> Dashboard resumido (a implementar)\n";
            break;
        }

        case 0:
        {
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

        // Libertar memória
        for (auto c : colabs)
            delete c;

        cout << "Programa terminado.\n";
    }

    void gerarRelatorioMensal(const vector<Colaborador *> &colabs)
    {
        if (colabs.empty())
        {
            cout << "Nenhum colaborador registado.\n";
            return;
        }

        int mes, ano;
        cout << "Gerar relatório de que mês e ano? (ex: 11 2025): ";
        cin >> mes >> ano;
        cin.ignore();

        cout << "\n===== RELATÓRIO MENSAL =====\n";
        cout << nomeMes(mes) << " de " << ano << "\n";
        cout << "------------------------------\n";

        for (auto c : colabs)
        {
            int ferias = 0;
            int faltas = 0;

            int dias = diasNoMes(mes, ano);

            // percorre todos os dias do mês
            for (int d = 1; d <= dias; d++)
            {
                char m = obterMarcacao(c, d, mes, ano);
                if (m == 'F')
                    ferias++;
                if (m == 'X')
                    faltas++;
            }

            cout << c->nome
                 << "  |  Férias: " << ferias
                 << "  |  Faltas: " << faltas << "\n";
        }

        cout << "------------------------------\n";
    }
