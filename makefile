# ==============================================
# MAKEFILE
#   Configuração de execução do CPLEX (concert) com a linguagem C/C++
#
#   Autores: Luiz Henrique Cherri e Landir Saviniec
# ========================================================

# ---------------------------------------------------------------------
# Variaveis relacionadas ao sistema onde o software foi instalado
#   -- Voce pode mudar estas variáveis de acordo com a instalação no seu sistema
# ---------------------------------------------------------------------
SYSTEM     = x86-64_linux
LIBFORMAT  = static_pic
CPLEXDIR      = /opt/ibm/ILOG/CPLEX_Studio126/cplex
CONCERTDIR    = /opt/ibm/ILOG/CPLEX_Studio126/concert


# ---------------------------------------------------------------------
# Compilador e opcoes. Nao recomendamos alteracoes neste trecho
# ---------------------------------------------------------------------

CC = g++
CCOPT = -m64 -O3 -fPIC -fexceptions -DNDEBUG -DIL_STD


# ---------------------------------------------------------------------
# Flags: Nesta parte, sao definidos conjuntos de flags. Nao recomendamos alteracoes neste trecho
# ---------------------------------------------------------------------

CPLEXLIBDIR   = $(CPLEXDIR)/lib/$(SYSTEM)/$(LIBFORMAT)
CONCERTLIBDIR = $(CONCERTDIR)/lib/$(SYSTEM)/$(LIBFORMAT)
CCLNFLAGS = -L$(CPLEXLIBDIR) -lilocplex -lcplex -L$(CONCERTLIBDIR) -lconcert -m64 -lm -lpthread
CLNFLAGS  = -L$(CPLEXLIBDIR) -lcplex -m64 -lm -lpthread
CONCERTINCDIR = $(CONCERTDIR)/include
CPLEXINCDIR   = $(CPLEXDIR)/include
CCFLAGS = $(CCOPT) -I$(CPLEXINCDIR) -I$(CONCERTINCDIR) -std=c++11


# ---------------------------------------------------------------------
# Compilacao. A palavra "main" DEVE ser substituida pelo nome de seu arquivo .cpp
# ---------------------------------------------------------------------

main : main.o
	${CC} ${CCFLAGS} main.o $(CCLNFLAGS) -o main 

main.o : main.cpp
	${CC} ${CCFLAGS} -c main.cpp

clean :
	rm *.o main *~



