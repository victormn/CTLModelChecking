CFLAGS= -I lib/
PROJECTNAME= ctlModelChecking.cpp

all: classes
	g++ ./src/$(PROJECTNAME) $(CFLAGS) -o ./bin/modelchecking ./obj/parserExpression.o ./obj/parserStateMachine.o ./obj/operationCaller.o -Wall

classes:
	@mkdir -p obj bin
	@g++ -c ./src/parserExpression.cpp $(CFLAGS) -o ./obj/parserExpression.o -Wall
	@g++ -c ./src/parserStateMachine.cpp $(CFLAGS) -o ./obj/parserStateMachine.o -Wall
	@g++ -c ./src/operationCaller.cpp $(CFLAGS) -o ./obj/operationCaller.o -Wall

clean:
	@rm -rf bin obj
	@find -name "*~" | xargs rm -rf

run: ./bin/modelchecking
	./bin/modelchecking < ${IN}