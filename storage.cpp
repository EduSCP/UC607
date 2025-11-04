// storage.cpp
#include "storage.h"
#include "utils.h"
#include <fstream>
#include <sstream>
#include <iostream>

int carregarColaboradores(const std::string &ficheiro, std::vector<Colaborador*> &colabs) {
    std::ifstream ifs(ficheiro);
    if(!ifs.is_open()) return 0;

    std::string line;
    int count = 0;

    while(std::getline(ifs, line)) {
        if(line.empty()) continue;
        std::stringstream ss(line);
        std::string encname;
        if(!std::getline(ss, encname, ';')) continue;
        std::string nome = decryptName(encname);
        Colaborador *c = new Colaborador(nome);

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
                    adicionarMarcacao(c, d, m, a, tipo);
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
        std::string enc = encryptName(c->nome);
        ofs << enc << ";";
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
