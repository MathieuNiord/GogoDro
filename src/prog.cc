#include "prog.hh"

Prog::Prog(Instruction* prog)
    : prog_(prog) {}

Prog::~Prog() {
    delete prog_;
}

void Prog::visit(Visitor& visitor) const {
    return visitor.visit_prog(this);
}