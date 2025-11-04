// utils.h
#ifndef UTILS_H
#define UTILS_H

#include <string>

// Cálculo do dia da semana (Zeller)
// Retorna: 0 = Domingo, 6 = Sábado
int diaSemana(int dia, int mes, int ano);

// Devolve o número de dias de um determinado mês/ano
int diasNoMes(int mes, int ano);

// Nome textual do mês
std::string nomeMes(int mes);

// Encriptação e desencriptação de nomes (Cifra de César +3 / -3)
std::string encryptName(const std::string &nome);
std::string decryptName(const std::string &enc);

#endif
