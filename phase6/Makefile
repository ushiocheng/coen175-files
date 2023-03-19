CXX		= g++
CXXFLAGS	= -g -Wall -std=c++11
EXTRAS		= lexer.cpp
LEX		= flex
OBJS		= lexer.o tokens.o SCCParser.o string.o exceptions/SCCError.o semantic-classes/SCCScope.o semantic-classes/SCCSymbol.o semantic-classes/SCCType.o ast-classes/SCCAST.o ast-classes/SCCASTAssign.o ast-classes/SCCASTFunction.o ast-classes/SCCASTStmtBlock.o ast-classes/SCCASTStatement.o ast-classes/expr-tree-classes/ExprTreeUnaryNode.cpp ast-classes/expr-tree-classes/ExprTreeBinaryNode.cpp ast-classes/expr-tree-classes/ExprTreeTermNode.cpp semantic-classes/SCCTypeChecker.cpp code-generation-classes/data-classes/SCCData.cpp code-generation-classes/data-classes/SCCDataNumericLiteral.cpp code-generation-classes/data-classes/SCCDataStackVariable.cpp code-generation-classes/data-classes/SCCDataStaticVariable.cpp code-generation-classes/data-classes/SCCDataStringLiteral.cpp code-generation-classes/data-classes/SCCDataTempValue.cpp code-generation-classes/data-location-classes/SCCDataLocation.cpp code-generation-classes/instruction-helper/X86InstructionHelper.cpp code-generation-classes/label-classes/SCCLabelHelper.cpp code-generation-classes/label-classes/SCCStringLiteralHelper.cpp code-generation-classes/register-classes/SCCRegisterManager.cpp code-generation-classes/register-classes/SCCVirtualRegister.cpp code-generation-classes/register-classes/SCCX86Register.cpp code-generation-classes/register-classes/X86RegisterNames.cpp code-generation-classes/stack-classes/SCCStackManager.cpp
PROG		= scc


all:		$(PROG)

$(PROG):	$(EXTRAS) $(OBJS)
		$(CXX) -o $(PROG) $(OBJS)

clean:;		$(RM) $(EXTRAS) $(PROG) core *.o **/*.o

lexer.cpp:	lexer.l
		$(LEX) $(LFLAGS) -t lexer.l > lexer.cpp
