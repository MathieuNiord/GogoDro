/* Authors : Frejoux Gaetan & Niord Mathieu */

#ifndef VISITOR_H
#define VISITOR_H

class Prog;
class Sequence;
class ImgConfig;
class Pen;
class Double;
class Variable;
class Operation;
class Declaration;
class Affect;
class MovePen;
class Center;
class Rectangle;
class Circle;
class SetColor;
class ForLoop;


class Visitor {

public:

	virtual void visit_prog(const Prog* p) = 0;
	virtual void visit_seq(const Sequence* s) = 0;
	virtual void visit_config(const ImgConfig* c) = 0;
	virtual void visit_pen(const Pen* p) = 0;
	virtual void visit_double(const Double* d) = 0;
	virtual void visit_var(const Variable* v) = 0;
	virtual void visit_operation(const Operation* o) = 0;
	virtual void visit_decl(const Declaration* d) = 0;
	virtual void visit_affect(const Affect* a) = 0;
	virtual void visit_move(const MovePen* m) = 0;
	virtual void visit_center(const Center* c) = 0;
	virtual void visit_rect(const Rectangle* r) = 0;
	virtual void visit_circle(const Circle* c) = 0;
	virtual void visit_set_color(const SetColor* sc) = 0;
	virtual void visit_for(const ForLoop* fl) = 0;
	
};

#endif