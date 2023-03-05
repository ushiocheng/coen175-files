#include "tokens.h"
#include <iostream>

using namespace std;

void prettyPrintToken(Token tmp) {
    if (tmp == 0) {
        cout << "Done";
        return;
    }
    if (tmp < 256) {
        cout << (char)tmp;
    } else {
        switch (tmp) {
            case AUTO:
                cout << "AUTO";
                break;
            case BREAK:
                cout << "BREAK";
                break;
            case CASE:
                cout << "CASE";
                break;
            case CHAR:
                cout << "CHAR";
                break;
            case CONST:
                cout << "CONST";
                break;
            case CONTINUE:
                cout << "CONTINUE";
                break;
            case DEFAULT:
                cout << "DEFAULT";
                break;
            case DO:
                cout << "DO";
                break;
            case DOUBLE:
                cout << "DOUBLE";
                break;
            case ELSE:
                cout << "ELSE";
                break;
            case ENUM:
                cout << "ENUM";
                break;
            case EXTERN:
                cout << "EXTERN";
                break;
            case FLOAT:
                cout << "FLOAT";
                break;
            case FOR:
                cout << "FOR";
                break;
            case GOTO:
                cout << "GOTO";
                break;
            case IF:
                cout << "IF";
                break;
            case INT:
                cout << "INT";
                break;
            case LONG:
                cout << "LONG";
                break;
            case REGISTER:
                cout << "REGISTER";
                break;
            case RETURN:
                cout << "RETURN";
                break;
            case SHORT:
                cout << "SHORT";
                break;
            case SIGNED:
                cout << "SIGNED";
                break;
            case SIZEOF:
                cout << "SIZEOF";
                break;
            case STATIC:
                cout << "STATIC";
                break;
            case STRUCT:
                cout << "STRUCT";
                break;
            case SWITCH:
                cout << "SWITCH";
                break;
            case TYPEDEF:
                cout << "TYPEDEF";
                break;
            case UNION:
                cout << "UNION";
                break;
            case UNSIGNED:
                cout << "UNSIGNED";
                break;
            case VOID:
                cout << "VOID";
                break;
            case VOLATILE:
                cout << "VOLATILE";
                break;
            case WHILE:
                cout << "WHILE";
                break;
            case OP_OR:
                cout << "OP_OR";
                break;
            case OP_AND:
                cout << "OP_AND";
                break;
            case OP_EQ:
                cout << "OP_EQ";
                break;
            case OP_NE:
                cout << "OP_NE";
                break;
            case OP_LE:
                cout << "OP_LE";
                break;
            case OP_GE:
                cout << "OP_GE";
                break;
            case OP_INC:
                cout << "OP_INC";
                break;
            case OP_DEC:
                cout << "OP_DEC";
                break;
            case OP_ARROW:
                cout << "OP_ARROW";
                break;
            case STRING:
                cout << "STRING";
                break;
            case CHARACTER:
                cout << "CHARACTER";
                break;
            case ID:
                cout << "ID";
                break;
            case NUM:
                cout << "NUM";
                break;
            default:
                cout << "????";
                break;
        }
    }
}