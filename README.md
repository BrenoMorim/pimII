# Projeto Integrado Multidisciplinar II

## Museu Multitemático James Gosling

Nesse repositório encontra-se o código do projeto desenvolvido para a conclusão do segundo semestre do curso de Análise e Desenvolvimento de Sistemas da Universidade Paulista. A documentação detalhada do código está presente no arquivo "documentacaoPimII.docx". O código está separado nas pastas: sistemaPrincipal, que contém as funcionalidades principais do museu e de uso voltado para vendas de ingressos e para a pesquisa de satisfação; e na pasta questionario, que contém o programa que estará nas exposições e que interage com o usuário apresentando perguntas e coletando suas respostas.

### Requisitos

- Ferramenta Git instalada
- Um compilador da linguagem C instalado
  
De compilador, o make é uma das melhores opções e pode ser instalado no Windows 10/11 de forma fácil com o seguinte comando no PowerShell:

```sh
winget install GnuWin32.Make
```

Para instalar o Git, podemos instalar através do site <https://git-scm.com/downloads>, ou também é possível rodar um simples comando no PowerShell do Windows 10/11:

```sh
winget install -e --id Git.Git
```

O Git é necessário para clonar o repositório e realizar o download, enquanto o make é fundamental para que o sistema seja compilado com instruções compatíveis com o sistema operacional da sua máquina. A compilação dos arquivos do repositório foi feita em um ambiente Linux Ubuntu, não compatível com Windows.

### Instruções para fazer o download do projeto

Via terminal, de preferência o Git Bash, os seguintes comandos podem ser usados para fazer o download:

```sh
git clone https://github.com/BrenoMorim/pimII.git museu
cd ./museu
```

Após fazer o clonagem do repositório, é possível executar o seguinte comando para abrir o editor de código Visual Studio Code na pasta do projeto, é preciso estar na pasta /museu, que contém os arquivos do projeto:

```sh
code .
```

Caso você não tenha o Visual Studio Code instalado, você pode realizar o download por esse link: <https://code.visualstudio.com/download>.

### Instruções para rodar o sistema principal

É importante ressaltar que o sistema deve ser executado na mesma pasta que os arquivos .csv que contém os dados, caso os arquivos não sejam encontrados, eles serão criados do zero.

```sh
cd ./sistemaPrincipal
make main
./main
```

### Instruções para rodar o programa dos questionários

Há 4 arquivos .txt na pasta dos questionários, cada um referente a um tema em exposição no museu. Para responder eles, basta executar o programa e indicar qual questionário deseja responder. É importante que o programa esteja na mesma pasta que os arquivos .txt para que eles sejam encontrados pelo programa.

```sh
cd ./questionario
make questionario
./questionario
```

### Extensões para melhorar sua experiência

- Rainbow CSV : Ajuda na visualização de arquivos CSV, deixando cada coluna de uma cor
- Markdown Preview Enhanced : Proporciona uma visualização formatada de arquivos MD, acionada com as teclas Ctrl + Shift + V
- C/C++ : Extensão da Microsoft com funcionalidades que facilitam o desenvolvimento em C e C++, como referências das bibliotecas e preenchimento automático
