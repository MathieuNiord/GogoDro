/* Authors : Frejoux Gaetan & Niord Mathieu */

#ifndef _SEQ_H
#define _SEQ_H

#include "inst.hh"

class SeqItem {

	Instruction* inst_;
	SeqItem* next_;

public:

	SeqItem(Instruction* i, SeqItem* next = nullptr);
	~SeqItem();

	inline const Instruction* get_inst() const { return inst_; }
	inline bool has_next() const { return (next_ != nullptr); }
	inline SeqItem* get_next() const { return next_; }

	void add(Instruction* i);
};


class Sequence : public Instruction {

	SeqItem* first_;

public:

	Sequence(Instruction* first = nullptr);
	~Sequence();

	inline SeqItem* getFirst() const { return first_; }

	void visit(Visitor& visitor) const override;

	void add(Instruction* i); // attention risque d'inversion! (a vous de voir...)

};

#endif