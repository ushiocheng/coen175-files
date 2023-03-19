#include "SCCASTAssign.hpp"

#include "../code-generation-classes/data-classes/SCCData.hpp"
#include "../code-generation-classes/instruction-helper/X86InstructionHelper.hpp"

SCCASTClasses::Assignment::Assignment(ExprTreeClasses::ExprTreeNode* lhs,
                                      ExprTreeClasses::ExprTreeNode* rhs)
    : lhs(lhs), rhs(rhs) {}

SCCASTClasses::Assignment::~Assignment() {
    delete lhs;
    delete rhs;
}

#include "../exceptions/SCCError.hpp"

bool SCCASTClasses::Assignment::performTypeChecking() const {
    SCCType lhsType = lhs->getType();
    if (lhsType.isError()) return false;
    SCCType rhsType = rhs->getType();
    if (rhsType.isError()) return false;
    //! Check is LValue
    if (!lhsType.isLValue()) {
        return false;
    }
    //! Check compatible
    if (!rhsType.isCompatible(lhsType)) {
        return false;
    }
    return true;
}

void SCCASTClasses::Assignment::generateCode(std::ostream& out) const {
    SCCData* lhsRes = lhs->generateCode(out, true);
    SCCData* rhsRes = rhs->generateCode(out);
    SCCX86Register tmp = SCCRegisterManager::useAnyReg(out, rhsRes->size());
    rhsRes->loadTo(out, tmp.siRegCode());
    if (rhsRes->size() != lhsRes->size()) {
        tmp.castTo(out, lhsRes->size());
    }
    out << "    " << X86InstructionHelper::movForSize(lhsRes->size()) << "    "
        << "%" << tmp.getName() << ", " << lhsRes->location()->generateAccess();
    SCCRegisterManager::releaseReg(tmp);
}
