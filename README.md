# Projeto Integrado Multidisciplinar II

## Museu Multitemático James Gosling

Nesse repositório encontra-se o código do projeto desenvolvido para a conclusão do segundo semestre do curso de Análise e Desenvolvimento de Sistemas da Universidade Paulista.

### Requisitos

- Ferramenta Git instalada
- Comando make - Compilador da linguagem C instalado

O Git é necessário para clonar o repositório e realizar o download, enquanto o make é fundamental para que o sistema seja compilado com instruções compatíveis com o sistema operacional da sua máquina. A compilação dos arquivos do repositório foi feita em um ambiente Linux Ubuntu, não compatível com Windows.

### Instruções para fazer o download do projeto

Via terminal, de preferência o Git Bash, os seguintes comandos podem ser usados para fazer o download:

```sh
git clone https://github.com/BrenoMorim/pimII.git museu
cd ./museu
```

### Instruções para rodar o sistema principal

```sh
cd ./sistemaPrincipal
make main
./main
```

### Instruções para rodar o programa dos questionários

Há 4 arquivos .txt na pasta dos questionários, cada um referente a um tema em exposição no museu. Para alterar o tema, basta renomear o arquivo que é chamado "questionario.txt" para um outro nome e trocar o nome do arquivo com o questionário que deseja para "questionario.txt".

```sh
cd ./questionario
make questionario
./questionario
```
