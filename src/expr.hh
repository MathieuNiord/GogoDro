/* Authors : Frejoux Gaetan & Niord Mathieu */

#ifndef _EXPR_H
#define _EXPR_H

#include "term.hh"

class Expression : public Term {

public:

	virtual ~Expression() = default;
};

#endif
