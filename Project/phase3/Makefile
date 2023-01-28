CPP=g++
FLEX=flex
BISON=bison

splc:
	$(FLEX) src/lex.l
	mv lex.yy.c src/lex.yy.c
	$(BISON) -t -d src/syntax.y
	mv syntax.tab.h src/syntax.tab.h
	mv syntax.tab.c src/syntax.tab.c
	$(CPP) src/syntax.tab.c src/node.cpp src/symbol.cpp src/semantic.cpp src/translate.cpp -lfl -o bin/splc
clean:
	@rm -f bin/splc src/lex.yy.c src/syntax.tab.*