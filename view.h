// view.h
#ifndef VIEW_H
#define VIEW_H

#include <vector>
#include "colaborador.h"

// Mostra o menu principal e devolve a opção escolhida
int mostrarMenu();

// Lista os colaboradores
void listarColaboradores(const std::vector<Colaborador*> &colabs);

// Mostra o calendário de um colaborador num mês e ano
void mostrarCalendario(const Colaborador *c, int mes, int ano);

#endif
