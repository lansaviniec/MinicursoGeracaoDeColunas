# Minicurso de Geração de Colunas

Material do minicurso "Implementação de geração de colunas usando CPLEX em linguagem C/C++", ministrado no Instituto de Ciências Matemáticas e de Computação da Universidade de São Paulo nos dias 01 e 02 de fevereiro de 2018.

---

### Introdução:

Geração de colunas (DESAULNIERS et al., 2005) é um método para resolver problemas de otimização que tem sido empregado com bastante sucesso na área de Pesquisa Operacional. Neste minicurso, abordaremos a técnica de geração de colunas (GC) dando enfoque na implementação do método. Mostraremos como implementar GC usando o pacote de otimização CPLEX (concert) com interface de programação na linguagem C++. O minicurso está estruturado da seguinte forma:

  1) Apresentamos uma breve revisão do método de decomposição Dantzig-Wolfe (BAZARAA et al., 2010).
  2) Propomos um framework genérico em C++ para implementação do método de GC.
  3) Mostramos como usar o framework para implementar uma GC para o problema de dimensionamento de lotes capacitado com múltiplos itens (PDL).
  4) Mostramos como usar o framework para implementar a GC para o problema de corte unidimensional (PCU).
  
  Ao final do minicurso, espera-se que o participante esteja apto a reusar o framework para implementar GC para outros problemas.

### Material:

Os seguintes arquivos estão disponíveis neste repositório:

Slides.pdf : slides do curso contendo uma revisão do método de decomposição Dantzig-Wolfe, a estrutura do framework proposto, e a formulação dos dois problemas usados como exemplo.

framework.cpp : código do framework proposto durante o curso.

pdl.zip : código da implementação de GC para o PDL utilizando o framework proposto.

pcu.zip : código da implementação de GC para o PCU utilizando o framework proposto.

### Material complementar:

Teoria : uma introdução sucinta sobre geração de colunas, origem e aplicações pode ser encontrado no tutorial "GERAÇÃO DE COLUNAS EM 17.500 CARACTERES" do Professor Doutor José Manuel Valério de Carvalho, disponível em https://goo.gl/gvrocN.

Cplex : a documentação do pacote de otimização CPLEX pode ser consultada em https://goo.gl/G5CQvY.

C++ : para programadores iniciantes e interessados em aprender a linguagem C++, recomendamos o tutorial disponível em https://goo.gl/wPMxJ7.

### Instruções:

Para compilar e executar os códigos apresentados, será necessário um computador com um compilador de C/C++ e alguma versão do software CPLEX instalada.

Os usuários de Windows, deverão usar alguma interface que faça a ligação das bibliotecas do CPLEX na compilação do código (Visual Studio, Code::Blocks, etc).

Para usuários de Linux, disponibilizamos um arquivo de compilação (makefile). Assumimos que o caminho de instalação do CPLEX é o padrão, e utilizamos a versão 12.6 do software (o que pode ser facilmente alterado como documentado no arquivo).

### Referências

1) BAZARAA, M. S.; JARVIS, J. J.; SHERALI, H. D. Linear Programming and Network Flows. 4th. ed. [S.l.]:
Wiley-Interscience, 2010. ISBN 9780470462720.

2) DESAULNIERS, G.; DESROSIERS, J.; SOLOMON, M. M. Column generation. 1st. ed. [S.l.]: Springer Science &
Business Media, 2005. v. 5.

---

### Autores:

Dr. Landir Saviniec (UFPR)

Dr. Luiz Henrique Cherri (ODM / USP) - www.odmcentral.com
