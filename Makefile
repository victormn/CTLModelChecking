CFLAGS= -I lib/
PROJECTNAME= ctlModelChecking.cpp

all: classes
	g++ ./src/$(PROJECTNAME) $(CFLAGS) -o ./bin/modelchecking ./obj/parserExpression.o ./obj/parserStateMachine.o ./obj/operationCaller.o -Wall

classes:
	@mkdir -p obj bin
	@g++ -c ./src/parserExpression.cpp $(CFLAGS) -o ./obj/parserExpression.o
	@g++ -c ./src/parserStateMachine.cpp $(CFLAGS) -o ./obj/parserStateMachine.o
	@g++ -c ./src/operationCaller.cpp $(CFLAGS) -o ./obj/operationCaller.o

clean:
	@rm -rf bin obj
	@find -name "*~" | xargs rm -rf

memorycheck: ./bin/modelchecking
	valgrind ./bin/modelchecking < ${IN}

run: ./bin/modelchecking
	./bin/modelchecking < ${IN}