// controller.h
#pragma once
#include "colaborador.h"
#include <vector>

Colaborador* procurarColaborador(const std::vector<Colaborador*> &colabs, const std::string &nomeOuId);
void executarSistema();

// Funções auxiliares do sistema
void gerarRelatorioMensal(const std::vector<Colaborador*> &colabs);
void buscarColaborador(const std::vector<Colaborador*> &colabs);
void mostrarEstatisticasColaborador(const std::vector<Colaborador*> &colabs);
void exportarRelatorioColaborador(const Colaborador *c, int ano, const std::string &ficheiro);
