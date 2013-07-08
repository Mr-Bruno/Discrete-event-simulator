## Modulo:  Makefile
## Fecha:   02/02/12

.SUFFIXES: .o .c .cc


CCOMPILER = g++
CFLAGS   = -g  -Wall
CXXFLAGS = "-O3"
LIBS = -lm
SRCS = usuario.cc colas.cc simulador.cc varaleat.cc principal.cc 
OBJECTS = usuario.o colas.o simulador.o varaleat.o principal.o Promedio.o
EXEC = practica3


all: $(EXEC)

$(EXEC): $(OBJECTS)
	@echo [Creando ejecutable]
	$(CCOMPILER) $(CFLAGS) $(CXXFLAGS) -o $(EXEC) $(OBJECTS) $(LIBS)
	@chmod 755 $(EXEC)

.cc.o:
	@echo Compilando $<
	@$(CCOMPILER) $(CFLAGS) $(INCLUDE_PATH) -c $<
	@echo Hecho!!

clean:
	@echo [Haciendo limpieza]
	@rm -f *~ $(OBJECTS) core
	@rm -f $(EXEC) $(GENERADOS)



#end Makefile


             

