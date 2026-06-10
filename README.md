*Este projeto foi criado como parte do currículo da 42 por mtakiyos e osousa-d.*

# Minishell

## Descrição

O Minishell é uma implementação simplificada de um interpretador de comandos inspirado no comportamento do Bash. O objetivo do projeto é compreender conceitos fundamentais de sistemas Unix, como criação de processos, gerenciamento de descritores de arquivos, execução de comandos, redirecionamentos, pipes, variáveis de ambiente e tratamento de sinais.

O programa exibe um prompt interativo, recebe comandos do usuário, realiza o processamento necessário e executa os comandos respeitando as regras definidas pelo enunciado do projeto.

Durante o desenvolvimento foram aplicados conceitos importantes de programação em C, incluindo gerenciamento manual de memória, manipulação de listas encadeadas, controle de processos através de `fork`, execução de programas com `execve`, comunicação entre processos utilizando pipes e tratamento de sinais com a API POSIX.

## Funcionalidades

* Prompt interativo.
* Histórico de comandos utilizando Readline.
* Execução de comandos externos.
* Busca de executáveis através da variável `PATH`.
* Suporte a múltiplos pipes (`|`).
* Redirecionamentos:

  * Entrada (`<`)
  * Saída (`>`)
  * Append (`>>`)
  * Here Document (`<<`)
* Expansão de variáveis de ambiente (`$VAR`).
* Expansão do código de saída (`$?`).
* Tratamento dos sinais:

  * `Ctrl-C`
  * `Ctrl-D`
  * `Ctrl-\`
* Builtins obrigatórios:

  * `echo`
  * `cd`
  * `pwd`
  * `export`
  * `unset`
  * `env`
  * `exit`

## Instruções

### Compilação

Compile o projeto:

```bash
make
```
Outros comandos:
| Comando | Descrição |
|---------|-----------|
| make clean | Remove arquivos ".o"  |
| make fclean | Remove arquivos ".o" e arquivos executaveis. |
| make re | Recompila tudo |
| make val | Compila e executa checando vazamento de memória |

### Execução

Após a compilação (exceto o make val):

```bash
./minishell
```

Exemplos de uso:

```bash
minishell> echo Hello World
Hello World

minishell> ls -la | grep minishell

minishell> export USER_NAME=42

minishell> echo $USER_NAME
42
```
Agora é só testaaaaaaar!!!

## Estrutura do Projeto

```text
.
├── includes/
│   ├── enum.h
│   ├── shell.h
│   └── structs.h
├── libftprintf/
│   ├── img/
│   ├── project/
│   │   ├── libft/
│   │   └── src/
│   ├── LICENSE
│   └── README.md
├── sources/
│   ├── clean/
│   ├── exec/
│   │   ├── builtin/
│   │   └── redirections/
│   ├── expander/
│   ├── init/
│   ├── lexer/
│   ├── parser/
│   ├── signal/
│   ├── utils/
│   └── main.c
├── Makefile
├── readine.supp
└── README.md
```

### Organização do Projeto

- `lexer/` : responsável pela tokenização da entrada do usuário.
- `parser/` : construção e validação das estruturas de comando.
- `expander/` : expansão de variáveis de ambiente e `$?`.
- `exec/` : execução de builtins, comandos externos, pipes e redirecionamentos.
- `signal/` : tratamento de sinais do shell.
- `clean/` : liberação de memória e encerramento do programa.
- `utils/` : funções auxiliares utilizadas pelo projeto.

## Escolhas Técnicas

- ENV criada usando lista ligada e no execve foi criado uma função que converte a lista pra array.
- Tratar heredoc e redirects após o parser e não junto com o parser.
- Divisão de uma pessoa cuidar da produção do Lexer/parser e outra cuidar do Exec
- Não tratar "&&" e "||" com parênteses para prioridades e fazer coringas "*" funcionar para o diretório de trabalho atual.

### Execução

A execução dos comandos é realizada através da combinação de:

* `fork()` para criação de processos filhos;
* `execve()` para execução de programas externos;
* `pipe()` para comunicação entre processos;
* `dup2()` para redirecionamento de entrada e saída;
* `waitpid()` para sincronização e obtenção dos códigos de retorno.

### Gerenciamento de Ambiente

As variáveis de ambiente são armazenadas em estruturas próprias para facilitar operações dos builtins `export`, `unset` e `env`, além da conversão para o formato exigido pelo `execve()`.

### Tratamento de Memória

Toda memória alocada dinamicamente é liberada ao final de cada ciclo do shell e também durante o encerramento do programa, evitando vazamentos de memória e descritores de arquivos, única memória não tratada é a readline (Subject deixa especificado que não é para tratar-mos).

## Recursos

### Documentação

* Manual Pages (man):

  * `man bash`
  * `man execve`
  * `man fork`
  * `man pipe`
  * `man dup2`
  * `man waitpid`
  * `man signal`

* POSIX:

  * https://pubs.opengroup.org

* GNU Readline:

  * https://tiswww.case.edu/php/chet/readline/rltop.html

* Bash Reference Manual:

  * https://www.gnu.org/software/bash/manual/

### Uso de Inteligência Artificial

Ferramentas de IA foram utilizadas exclusivamente como apoio educacional e consulta técnica durante o desenvolvimento do projeto.

As utilizações incluíram:

* Esclarecimento de conceitos relacionados a processos, pipes e sinais.
* Revisão de lógica e arquitetura de funções.
* Auxílio na identificação de possíveis vazamentos de memória e descritores de arquivos.
* Consulta sobre boas práticas de programação em C.
* Apoio na documentação do projeto.

Nenhum código foi copiado integralmente de ferramentas de IA. Todo o código final foi implementado, adaptado e validado pelos autores do projeto.
