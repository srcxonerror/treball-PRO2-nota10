OPCIONS = -D_JUDGE_ -D_GLIBCXX_DEBUG -O2 -Wall -Wextra -Werror -Wno-sign-compare -std=c++11
#
G++ = g++ #esto solo es necesario en la FIB, ya que su g++ es muy antiguo
#
program.exe: ProcessosPendents.o Cluster.o Proc.o processador.o program.o
	$(G++) -o program.exe ProcessosPendents.o Cluster.o Proc.o processador.o program.o
#
ProcessosPendents.o: ProcessosPendents.cc ProcessosPendents.hh
	$(G++) -c ProcessosPendents.cc $(OPCIONS)
#
Cluster.o: Cluster.cc Cluster.hh
	$(G++) -c Cluster.cc $(OPCIONS)
#
processador.o: processador.cc processador.hh
	$(G++) -c processador.cc $(OPCIONS)
#
Proc.o: Proc.cc Proc.hh
	$(G++) -c Proc.cc $(OPCIONS)
#
program.o: program.cc Proc.hh processador.hh ProcessosPendents.hh Cluster.hh
	$(G++) -c program.cc $(OPCIONS)
#
practica.tar: program.cc ProcessosPendents.cc Cluster.cc processador.cc Proc.cc BinTree.hh ProcessosPendents.hh Cluster.hh processador.hh Proc.hh
	tar cvf practica.tar program.cc ProcessosPendents.cc Cluster.cc processador.cc Proc.cc BinTree.hh ProcessosPendents.hh Cluster.hh processador.hh Proc.hh Makefile html.zip
#
clean:
	rm -f *.o
	rm -f *.exe
