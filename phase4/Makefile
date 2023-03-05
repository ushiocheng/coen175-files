CXX		= g++
CXXFLAGS	= -g -Wall -std=c++11
EXTRAS		= lexer.cpp
LEX		= flex
OBJS		= lexer.o tokens.o SCCParser.o string.o exceptions/SCCError.o semantic-classes/SCCScope.o semantic-classes/SCCSymbol.o semantic-classes/SCCType.o ast-classes/SCCAST.o ast-classes/SCCASTAssign.o ast-classes/SCCASTFunction.o ast-classes/SCCASTStmtBlock.o ast-classes/SCCASTStatement.o ast-classes/expr-tree-classes/ExprTreeUnaryNode.cpp ast-classes/expr-tree-classes/ExprTreeBinaryNode.cpp semantic-classes/SCCTypeChecker.cpp
PROG		= scc


all:		$(PROG)

$(PROG):	$(EXTRAS) $(OBJS)
		$(CXX) -o $(PROG) $(OBJS)

clean:;		$(RM) $(EXTRAS) $(PROG) core *.o **/*.o

lexer.cpp:	lexer.l
		$(LEX) $(LFLAGS) -t lexer.l > lexer.cpp
