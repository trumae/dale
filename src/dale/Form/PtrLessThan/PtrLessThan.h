#ifndef DALE_FORM_PTRLESSTHAN
#define DALE_FORM_PTRLESSTHAN

namespace dale
{
namespace Form
{
namespace PtrLessThan
{
bool execute(Generator *gen,
             Element::Function *fn,
             llvm::BasicBlock *block,
             Node *node,
             bool get_address,
             bool prefixed_with_core,
             ParseResult *pr);
}
}
}

#endif