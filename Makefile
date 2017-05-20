CFLAGS= -I lib/
PROJECTNAME= ctlModelChecking.cpp

all: classes
	mkdir -p obj bin
	g++ ./src/$(PROJECTNAME) $(CFLAGS) -o ./bin/modelchecking ./obj/parserExpression.o ./obj/parserSM.o ./obj/operationCaller.o -Wall

classes:
	@g++ -c ./src/parserExpression.cpp $(CFLAGS) -o ./obj/parserExpression.o
	@g++ -c ./src/parserSM.cpp $(CFLAGS) -o ./obj/parserSM.o
	@g++ -c ./src/operationCaller.cpp $(CFLAGS) -o ./obj/operationCaller.o

clean:
	rm -f ./obj/* ./bin/*
	rmdir bin obj
	find -name "*~" | xargs rm -rf

memorycheck: ./bin/modelchecking
	valgrind ./bin/modelchecking

run: ./bin/modelchecking
	./bin/modelchecking < ${IN}