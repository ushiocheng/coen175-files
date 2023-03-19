CXX		= g++
CXXFLAGS	= -g -Wall -std=c++11
EXTRAS		= lexer.cpp
LEX		= flex
OBJS		= lexer.o tokens.o SCCParser.o string.o exceptions/SCCError.o semantic-classes/SCCScope.o semantic-classes/SCCSymbol.o semantic-classes/SCCType.o ast-classes/SCCAST.o ast-classes/SCCASTAssign.o ast-classes/SCCASTFunction.o ast-classes/SCCASTStmtBlock.o ast-classes/SCCASTStatement.o ast-classes/expr-tree-classes/ExprTreeUnaryNode.o ast-classes/expr-tree-classes/ExprTreeBinaryNode.o ast-classes/expr-tree-classes/ExprTreeTermNode.o semantic-classes/SCCTypeChecker.o code-generation-classes/data-classes/SCCData.o code-generation-classes/data-classes/SCCDataArguments.o code-generation-classes/data-classes/SCCDataNumericLiteral.o code-generation-classes/data-classes/SCCDataStackVariable.o code-generation-classes/data-classes/SCCDataStaticVariable.o code-generation-classes/data-classes/SCCDataStringLiteral.o code-generation-classes/data-classes/SCCDataTempValue.o code-generation-classes/data-location-classes/SCCDataLocation.o code-generation-classes/instruction-helper/X86InstructionHelper.o code-generation-classes/label-classes/SCCLabelHelper.o code-generation-classes/label-classes/SCCStringLiteralHelper.o code-generation-classes/register-classes/SCCRegisterManager.o code-generation-classes/register-classes/SCCVirtualRegister.o code-generation-classes/register-classes/SCCX86Register.o code-generation-classes/register-classes/X86RegisterNames.o code-generation-classes/stack-classes/SCCStackManager.o
PROG		= scc


all:		$(PROG)

$(PROG):	$(EXTRAS) $(OBJS)
		$(CXX) -o $(PROG) $(OBJS)

clean:;		$(RM) $(EXTRAS) $(PROG) core *.o **/*.o

lexer.cpp:	lexer.l
		$(LEX) $(LFLAGS) -t lexer.l > lexer.cpp
