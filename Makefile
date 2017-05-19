CFLAGS= -I lib/
PROJECTNAME= parserExpression.cpp

all:
	g++ ./src/$(PROJECTNAME) $(CFLAGS) -o ./bin/modelchecking

clean:
	rm -f ./obj/* ./bin/*
	find -name "*~" | xargs rm -rf

memorycheck: ./bin/modelchecking
	valgrind ./bin/modelchecking

run: ./bin/modelchecking
	./bin/modelchecking ${IN}