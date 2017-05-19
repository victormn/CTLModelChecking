CFLAGS= -I lib/
PROJECTNAME= parserExpression.cpp

all:
	mkdir obj bin
	g++ ./src/$(PROJECTNAME) $(CFLAGS) -o ./bin/modelchecking

clean:
	rm -f ./obj/* ./bin/*
	rmdir bin obj
	find -name "*~" | xargs rm -rf

memorycheck: ./bin/modelchecking
	valgrind ./bin/modelchecking

run: ./bin/modelchecking
	./bin/modelchecking ${IN}