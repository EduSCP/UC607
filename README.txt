# README.md — Mini-Sistema de RH (Calendário de Férias/Faltas)

## Descrição

O **Mini-Sistema RH** é uma aplicação de consola em C++ que permite:

* Gerir colaboradores (adicionar, listar)
* Marcar/desmarcar **férias (F)** e **faltas (X)**
* Visualizar o **calendário mensal** com marcações e fins de semana
* Guardar e carregar dados de forma persistente num ficheiro (`data.txt`)
* Aplicar uma **cifra simples de encriptação** aos nomes dos colaboradores para proteger a privacidade

O programa segue uma estrutura modular (inspirada no padrão **MVC**) e usa **ponteiros** e **ficheiros separados (.h / .cpp)**.

---

## Estrutura do Projeto

```
MiniRH/
 ├── main.cpp
 ├── controller.cpp / controller.h   → Lógica principal e ligação entre módulos
 ├── view.cpp / view.h               → Interface de consola (menus, calendários)
 ├── colaborador.cpp / colaborador.h → Estrutura e funções de colaboradores
 ├── storage.cpp / storage.h         → Leitura/escrita de ficheiros + cifra
 ├── utils.cpp / utils.h             → Funções auxiliares (Zeller, meses, etc.)
 └── data.txt                        → Ficheiro de dados (gerado automaticamente)
```

---

## Instruções de Compilação

1. Abre o terminal na pasta onde estão os ficheiros.

2. Compila todos os `.cpp` com:

   ```bash
   g++ -std=c++17 main.cpp controller.cpp view.cpp colaborador.cpp storage.cpp utils.cpp -o minirh
   ```

3. Executa o programa:

   ```bash
   ./minirh
   ```

4. Ao sair, os dados são guardados no ficheiro `data.txt`.
   Quando o programa é iniciado novamente, esse ficheiro é automaticamente lido e desencriptado.

---

## Funcionalidades Principais

| Opção | Função                |
| ----- | --------------------- |
| 1     | Adicionar colaborador |
| 2     | Listar colaboradores  |
| 3     | Marcar férias         |
| 4     | Marcar falta          |
| 5     | Desmarcar dia         |
| 6     | Ver calendário mensal |
| 7     | Guardar e sair        |

O calendário mostra:

* `F` → Férias
* `X` → Falta
* `()` → Fim de semana

Não é possível marcar férias/faltas ao fim de semana.

---

## Encriptação / Desencriptação

Para proteger os nomes dos colaboradores guardados em ficheiro, é usada uma **cifra pedagógica simples**, semelhante a uma **Cifra de César**.

### Exemplo:

```text
Original:  Ana
Cifrado:   Dqd
```

### Algoritmo:

Cada letra é deslocada **3 posições à frente** no alfabeto.

* ‘A’ → ‘D’, ‘B’ → ‘E’, …, ‘Z’ → ‘C’
* Minúsculas e maiúsculas são tratadas separadamente.
* Números e outros caracteres não são alterados.

A **função de cifra** e a **de descifra** são inversas uma da outra.

### Código Simplificado:

```cpp
std::string cifra(const std::string &texto, int chave = 3) {
    std::string res = texto;
    for (char &c : res) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            c = base + (c - base + chave) % 26;
        }
    }
    return res;
}

std::string decifra(const std::string &texto, int chave = 3) {
    return cifra(texto, 26 - chave);
}
```

---

## Cálculo do Dia da Semana — Fórmula de Zeller

O sistema usa a **congruência de Zeller** para determinar o dia da semana de qualquer data.

```cpp
int diaSemana(int dia, int mes, int ano) {
    if (mes < 3) { mes += 12; ano--; }
    int k = ano % 100;
    int j = ano / 100;
    int h = (dia + 13*(mes+1)/5 + k + k/4 + j/4 + 5*j) % 7;
    int d = (h + 6) % 7; // 0 = Domingo, 6 = Sábado
    return d;
}
```

* 0 → Domingo
* 6 → Sábado
  Esta função é usada para evitar marcações ao fim de semana e desenhar o calendário corretamente.

---

## Funções Auxiliares

**Dias no mês (com tratamento de anos bissextos):**

```cpp
int diasNoMes(int mes, int ano) {
    switch(mes){
        case 1: case 3: case 5: case 7: case 8: case 10: case 12: return 31;
        case 4: case 6: case 9: case 11: return 30;
        case 2: return ((ano%4==0 && ano%100!=0) || (ano%400==0)) ? 29 : 28;
        default: return 30;
    }
}
```

**Nome do mês:**

```cpp
std::string nomeMes(int mes) {
    const std::string meses[] = {"Janeiro","Fevereiro","Março","Abril","Maio","Junho",
                                 "Julho","Agosto","Setembro","Outubro","Novembro","Dezembro"};
    return meses[mes-1];
}
```

---

## Conceitos Trabalhados

* Estrutura **MVC** simplificada (Model, View, Controller)
* Uso de **ponteiros** e **std::vector**
* Manipulação de **ficheiros texto (I/O)**
* **Validação de datas** e tratamento de anos bissextos
* **Encriptação e desencriptação** de dados
* **Cálculo do dia da semana (Zeller)**
* Modularização e boas práticas em C++

---

## Autor

Eduardo Pires
Trabalho prático de C++ — Mini-Sistema RH
Curso de Programação / Estruturas de Dados
Ano letivo: **2025**
