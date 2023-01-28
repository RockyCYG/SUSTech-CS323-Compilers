CPP=g++
FLEX=flex
BISON=bison

splc:
	@mkdir bin
	touch bin/splc
	@chmod +x bin/splc
	$(FLEX) src/lex.l
	mv lex.yy.c src/lex.yy.c
	$(BISON) -t -d src/syntax.y
	mv syntax.tab.h src/syntax.tab.h
	mv syntax.tab.c src/syntax.tab.c
	$(CPP) src/syntax.tab.c -lfl -o bin/splc
clean:
	@rm -rf bin/
	@rm -f src/lex.yy.c src/syntax.tab.* *.out