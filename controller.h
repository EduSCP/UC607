// controller.h
#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <vector>
#include "colaborador.h"

// Função principal que corre o menu e as ações do sistema
void executarSistema();

void gerarRelatorioMensal(const vector<Colaborador *> &colabs);

#endif
