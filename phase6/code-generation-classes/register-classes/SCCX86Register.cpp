#include "SCCX86Register.hpp"

#include <cassert>

#include "../../GlobalConfig.hpp"
#include "X86RegisterNames.hpp"

SCCX86Register::SCCX86Register(SizeIndependentRegCode regCode,
                               unsigned char size) {
    if (regCode >= RSP) {
        assert(size == 8);
        switch (regCode) {
            case RSP:
                this->_actualRegCode = X86Reg::RSP;
                return;
            case RFP:
                this->_actualRegCode = X86Reg::RFP;
                return;
            case RIP:
                this->_actualRegCode = X86Reg::RIP;
                return;
            default:
                assert(false);
                this->_actualRegCode = X86Reg::RSP;
                return;
        }
    }
    if (size == 1) {
        this->_actualRegCode = regCode << 2 + 3;
    } else if (size == 2) {
        this->_actualRegCode = regCode << 2 + 2;
    } else if (size == 2) {
        this->_actualRegCode = regCode << 2 + 1;
    } else {
        assert(size == 8);
        this->_actualRegCode = regCode << 2;
    }
}

bool SCCX86Register::conflictsWith(SCCX86Register that) {
    if (this->_actualRegCode >= X86Reg::RSP) {
        return this->_actualRegCode == that._actualRegCode;
    }
    return (this->_actualRegCode >> 2) == (that._actualRegCode >> 2);
}

inline const char* SCCX86Register::getName() {
    return X86Reg::nameOf(((X86Reg::Reg)this->_actualRegCode));
}

unsigned char SCCX86Register::getSize() {
    if (_actualRegCode >= X86Reg::RSP) {
        return 8;
    }
    switch (this->_actualRegCode & 0x3) {
        case 1:
            return 4;
        case 2:
            return 2;
        case 3:
            return 1;
        default:  // case 0
            return 8;
    }
}

SCCX86Register::~SCCX86Register() {}