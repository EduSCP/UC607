// storage.cpp
#include "storage.h"
#include "utils.h"
#include <fstream>
#include <sstream>
#include <iostream>

// Função auxiliar de encriptação simples
static std::string encriptar(const std::string &s) {
    std::string r = s;
    for (char &c : r) c ^= 7;
    return r;
}

int carregarColaboradores(const std::string &ficheiro, std::vector<Colaborador*> &colabs) {
    std::ifstream ifs(ficheiro);
    if(!ifs.is_open()) return 0;

    std::string line;
    int count = 0;

    while(std::getline(ifs, line)) {
        if(line.empty()) continue;
        std::stringstream ss(line);
        
        // Formato: nome_encriptado;departamento_encriptado;marcacoes
        std::string encname, encdept;
        if(!std::getline(ss, encname, ';')) continue;
        if(!std::getline(ss, encdept, ';')) continue;
        
        std::string nome = encriptar(encname);
        std::string departamento = encriptar(encdept);
        
        Colaborador *c = new Colaborador(nome, departamento);

        std::string rest;
        if(std::getline(ss, rest)) {
            std::stringstream ss2(rest);
            std::string token;
            while(std::getline(ss2, token, ',')) {
                if(token.size()<5) continue;
                int d=0,m=0,a=0; char t='?';
                size_t colon = token.find(':');
                if(colon==std::string::npos) continue;
                std::string date = token.substr(0, colon);
                t = token[colon+1];
                sscanf(date.c_str(), "%d-%d-%d", &d,&m,&a);
                if(d>0 && m>0 && a>0 && (t=='T' || t=='X')) {
                    char tipo = (t=='T') ? 'F' : 'X';
                    c->adicionarMarcacao(d, m, a, tipo);
                }
            }
        }

        colabs.push_back(c);
        count++;
    }

    ifs.close();
    return count;
}

bool guardarColaboradores(const std::string &ficheiro, const std::vector<Colaborador*> &colabs) {
    std::ofstream ofs(ficheiro, std::ios::trunc);
    if(!ofs.is_open()) return false;

    for(auto c : colabs) {
        std::string encnome = encriptar(c->nome);
        std::string encdept = encriptar(c->departamento);
        ofs << encnome << ";" << encdept << ";";
        
        bool first = true;
        for(auto &m : c->marcacoes) {
            if(!first) ofs << ",";
            first = false;
            char tchar = (m.tipo=='F') ? 'T' : (m.tipo=='X' ? 'X' : '?');
            ofs << m.dia << "-" << m.mes << "-" << m.ano << ":" << tchar;
        }
        ofs << "\n";
    }

    ofs.close();
    return true;
}
