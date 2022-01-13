#include "for_loop.hh"

ForLoop::ForLoop(const std::string& var, Expression* begin, Expression* end, Instruction* body)
    : var_(var), begin_(begin), end_(end), body_(body) {}

ForLoop::~ForLoop() {
    delete begin_;
    delete end_;
    delete body_;
}

void ForLoop::visit(Visitor& visitor) const {
    return visitor.visit_for(this);
}
