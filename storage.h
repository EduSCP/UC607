// storage.h
#ifndef STORAGE_H
#define STORAGE_H

#include <vector>
#include <string>
#include "colaborador.h"

// Carrega colaboradores do ficheiro (retorna número de colaboradores carregados)
int carregarColaboradores(const std::string &ficheiro, std::vector<Colaborador*> &colabs);

// Guarda todos os colaboradores no ficheiro
bool guardarColaboradores(const std::string &ficheiro, const std::vector<Colaborador*> &colabs);

#endif
