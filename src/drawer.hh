/* AUteurs : Frejoux Gaetan & Niord Mathieu */

#ifndef _MY_DRAWER_H
#define _MY_DRAWER_H

#include <iostream>
#include <vector>
#include <iterator>
#include <unordered_map>
#include <algorithm>
#include <experimental/filesystem>
#include "res/CImg.h"

#include "visitor.hh"
#include "prog.hh"
#include "seq.hh"
#include "img_config.hh"
#include "pen.hh"
#include "double.hh"
#include "var.hh"
#include "ope.hh"
#include "decl.hh"
#include "affect.hh"
#include "move_pen.hh"
#include "rect.hh"
#include "center.hh"
#include "circle.hh"
#include "set_color.hh"
#include "for_loop.hh"

#include "exceptions/invalid_iterator.hh"
#include "exceptions/invalid_variable.hh"

constexpr int img_size_x = 800;
constexpr int img_size_y = 600;

using namespace cimg_library;

class Drawer : public Visitor {

    CImg<unsigned char> img_;
    std::string img_name_ = "result";
    std::string path_ = "";
    
    bool pen_state_;
    float value_buf_;
    std::pair<double, double> pos_buf_;
    std::unordered_map<std::string, double> variables_;
    std::vector<std::string> iterators_;
    unsigned char color_[3] = { 0, 0, 0 };

    /**
     * @brief Used to save the image through the path_ attribute and its name
     * @param save_name : const std::string
     */
    void save_img(const std::string& save_name);

    /**
     * @brief Used to set a new color into the color_ attribute
     * @param color : Color
     */
    void set_color(Color color);

    /**
     * @brief Used to fill new color's data from a vector to the color_ array
     * @param new_color : const std::vector<unsigned char>
     */
    void copy_color(const std::vector<unsigned char>& new_color);

    /**
     * @brief Checks if a variable already exist inside the declared iteration variables
     * @param var : const std::string
     * @return true 
     * @return false 
     */
    bool exist_iter(const std::string& var) const;

    /**
     * @brief Checks if a new variable can be instanciated based on its name
     * @param var : const std::string
     * @return true 
     * @return false
     * @throw invalid_iterator
     * @throw invalid_variable
     */
    bool check_decl(const std::string& var) const;

    /**
     * @brief Chacks and adds a variable (declaration) inside the varaibles_ map attribute
     * @param var : const std::string
     * @param value 
     */
    void add_var(const std::string& var, const double value);

    /**
     * @brief Affects a value to the dedicated instanciated variable
     * @param var : const std::string
     * @param value : const double
     * @throw invalid_variable
     */
    void affect_val(const std::string& var, const double value);

public:

    Drawer() : pen_state_(false), value_buf_(0), pos_buf_((img_size_x/2), (img_size_y/2)) {}

    void visit_prog(const Prog* p);
	void visit_seq(const Sequence* s);
    void visit_config(const ImgConfig* c);
	void visit_pen(const Pen* p);
	void visit_double(const Double* d);
	void visit_var(const Variable* v);
	void visit_operation(const Operation* o);
	void visit_decl(const Declaration* d);
	void visit_affect(const Affect* a);
	void visit_move(const MovePen* m);
    void visit_center(const Center* c);
	void visit_rect(const Rectangle* r);
    void visit_circle(const Circle* c);
	void visit_set_color(const SetColor* sc);
	void visit_for(const ForLoop* fl);

};


#endif