#include "seq.hh"

SeqItem::SeqItem(Instruction *inst, SeqItem *next)
  : inst_(inst),next_(next) {}

SeqItem::~SeqItem() {
  delete inst_;
  if(next_ != NULL)
    delete next_;
}

void SeqItem::add(Instruction *i) {
  if(next_ == NULL)
    next_ = new SeqItem(i);
  else
    next_->add(i);  
}

Sequence::Sequence(Instruction *inst)
  : first_(NULL)
{
  if(inst != NULL) {
    first_ = new SeqItem(inst);
  }
}

Sequence::~Sequence() {
  if(first_ != NULL)
    delete first_;
}

void Sequence::visit(Visitor& visitor) const {
  visitor.visit_seq(this);
}

void Sequence::add(Instruction *inst) {
  if(first_ == NULL)
    first_ = new SeqItem(inst,first_);
  else
    first_->add(inst);
}
