#include "tokens.h"
#include <iostream>

using namespace std;

void prettyPrintToken(Token tmp, ostream& out) {
    if (tmp == 0) {
        out << "Done";
        return;
    }
    if (tmp < 256) {
        out << (char)tmp;
    } else {
        switch (tmp) {
            case AUTO:
                out << "AUTO";
                break;
            case BREAK:
                out << "BREAK";
                break;
            case CASE:
                out << "CASE";
                break;
            case CHAR:
                out << "CHAR";
                break;
            case CONST:
                out << "CONST";
                break;
            case CONTINUE:
                out << "CONTINUE";
                break;
            case DEFAULT:
                out << "DEFAULT";
                break;
            case DO:
                out << "DO";
                break;
            case DOUBLE:
                out << "DOUBLE";
                break;
            case ELSE:
                out << "ELSE";
                break;
            case ENUM:
                out << "ENUM";
                break;
            case EXTERN:
                out << "EXTERN";
                break;
            case FLOAT:
                out << "FLOAT";
                break;
            case FOR:
                out << "FOR";
                break;
            case GOTO:
                out << "GOTO";
                break;
            case IF:
                out << "IF";
                break;
            case INT:
                out << "INT";
                break;
            case LONG:
                out << "LONG";
                break;
            case REGISTER:
                out << "REGISTER";
                break;
            case RETURN:
                out << "RETURN";
                break;
            case SHORT:
                out << "SHORT";
                break;
            case SIGNED:
                out << "SIGNED";
                break;
            case SIZEOF:
                out << "SIZEOF";
                break;
            case STATIC:
                out << "STATIC";
                break;
            case STRUCT:
                out << "STRUCT";
                break;
            case SWITCH:
                out << "SWITCH";
                break;
            case TYPEDEF:
                out << "TYPEDEF";
                break;
            case UNION:
                out << "UNION";
                break;
            case UNSIGNED:
                out << "UNSIGNED";
                break;
            case VOID:
                out << "VOID";
                break;
            case VOLATILE:
                out << "VOLATILE";
                break;
            case WHILE:
                out << "WHILE";
                break;
            case OP_OR:
                out << "OP_OR";
                break;
            case OP_AND:
                out << "OP_AND";
                break;
            case OP_EQ:
                out << "OP_EQ";
                break;
            case OP_NE:
                out << "OP_NE";
                break;
            case OP_LE:
                out << "OP_LE";
                break;
            case OP_GE:
                out << "OP_GE";
                break;
            case OP_INC:
                out << "OP_INC";
                break;
            case OP_DEC:
                out << "OP_DEC";
                break;
            case OP_ARROW:
                out << "OP_ARROW";
                break;
            case STRING:
                out << "STRING";
                break;
            case CHARACTER:
                out << "CHARACTER";
                break;
            case ID:
                out << "ID";
                break;
            case NUM:
                out << "NUM";
                break;
            default:
                out << "????";
                break;
        }
    }
}