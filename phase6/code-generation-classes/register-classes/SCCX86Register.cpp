#include "SCCX86Register.hpp"

#include <cassert>

#include "../../GlobalConfig.hpp"
#include "X86RegisterNames.hpp"
#include "../data-location-classes/SCCDataLocation.hpp"

SCCX86Register::SCCX86Register(SizeIndependentRegCode regCode,
                               unsigned char size) {
    if (regCode >= RSP) {
        assert(size == 8);
        switch (regCode) {
            case RSP:
                this->_actualRegCode = X86Reg::RSP;
                return;
            case RBP:
                this->_actualRegCode = X86Reg::RBP;
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



int SCCX86Register::actualRegCode() const { return _actualRegCode; }
SizeIndependentRegCode SCCX86Register::siRegCode() const {
    if (_actualRegCode < X86Reg::RSP) return _actualRegCode<<2;
    switch (_actualRegCode)
    {
    case X86Reg::RSP: return SizeIndependentRegCode::RSP;
    case X86Reg::RBP: return SizeIndependentRegCode::RBP;
    default:          return SizeIndependentRegCode::RIP;
    }
}


inline const char* SCCX86Register::getName() {
    return X86Reg::nameOf(((X86Reg::Reg)this->_actualRegCode));
}

inline const char* SCCX86Register::get64bitName() {
    if (_actualRegCode >= X86Reg::RSP) {
        return getName();
    }
    return X86Reg::nameOf(((X86Reg::Reg)(_actualRegCode & (!0x3))));
}

void SCCX86Register::castTo(std::ostream& out, unsigned char size) {
    unsigned char currentSize = getSize();
    if (currentSize == size) return;
    if (currentSize < size) {
        //! Sign Extend current reg to 8 bytes
        out << "    movsx   %" << getName() << ", %" << get64bitName()
            << std::endl;
    }
    //! modify Reg code to reflect the change in size
    this->_actualRegCode = (this->_actualRegCode & (!0x3));
    if (size == 1) {
        this->_actualRegCode = _actualRegCode + 3;
    } else if (size == 2) {
        this->_actualRegCode = _actualRegCode + 2;
    } else if (size == 2) {
        this->_actualRegCode = _actualRegCode + 1;
    }
}

/**
 * Move this register to another register
 * @remark would modify this
 */
void SCCX86Register::moveTo(std::ostream& out, SCCX86Register::SizeIndependentRegCode dest) {
    switch (this->_actualRegCode & 0x3)
    {
        case 3: // 1 byte
        out << "    movb    ";break;
        case 2: // 2 byte
        out << "    movw    ";break;
        case 1: // 4 byte
        out << "    movl    ";break;
        default: // 8 byte
        out << "    movq    ";break;
    }
    out << "%" << getName();
    out << ", %" << SCCX86Register(dest, this->getSize()).getName();
    out << std::endl;
}

/**
 * Move this register to another location
 * @remark would modify this
 */
void SCCX86Register::moveTo(std::ostream& out, SCCDataLocation* dest){
    switch (this->_actualRegCode & 0x3)
    {
        case 3: // 1 byte
        out << "    movb    ";break;
        case 2: // 2 byte
        out << "    movw    ";break;
        case 1: // 4 byte
        out << "    movl    ";break;
        default: // 8 byte
        out << "    movq    ";break;
    }
    out << "%" << getName();
    out << ", " << dest->generateAccess();
    out << std::endl;
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
