#include "drawer.hh"

void Drawer::copy_color(const std::vector<unsigned char>& new_color) {
    for (int channel = 0; channel < 3; channel++)
        color_[channel] = new_color[channel];
}

void Drawer::save_img(const std::string& save_name) {
    std::experimental::filesystem::v1::create_directory(path_);
    const std::string n_tmp = path_ + save_name + ".bmp";
    char* full_name = new char[n_tmp.size() + 1];
	memcpy(full_name, n_tmp.c_str(), n_tmp.size() + 1);
    img_.save(full_name);
}

void Drawer::set_color(Color color) {

    std::vector<unsigned char> new_color(3, 0);

    switch (color) {

        case NOIR :
            std::cout << "NOIR";
            break;

        case BLEU :
            std::cout << "BLEU";
            new_color[1] = 80;
            new_color[2] = 181;
            break;

        case VERT :
            std::cout << "VERT";
            new_color[0] = 42;
            new_color[1] = 128;
            break;

        case ROUGE :
            std::cout << "ROUGE";
            new_color[0] = 139;
            break;

        case ROSE :
            std::cout << "ROSE";
            new_color[0] = 221;
            new_color[1] = 160;
            new_color[2] = 221;
            break;

        case JAUNE :
            std::cout << "JAUNE";
            new_color[0] = 255;
            new_color[1] = 199;
            new_color[2] = 44;
            break;

        case VIOLET :
            std::cout << "VIOLET";
            new_color[0] = 75;
            new_color[2] = 130;
            break;
    }

    copy_color(new_color);
    new_color.clear();
}

bool Drawer::exist_iter(const std::string& var) const {
    return (std::find(iterators_.begin(), iterators_.end(), var) != iterators_.end());
}

bool Drawer::check_decl(const std::string& var) const {

    // If the user wanted to declare in a loop, need to compare with the iteration var
    if (exist_iter(var))
        throw invalid_iterator(
            "La variable " + var + " a deja ete déclaree comme variable d'iteration."
        );

    // Also need to check if the variable has not already been instanciated
    if (variables_.find(var) != variables_.end()) {
        throw invalid_variable(
            "La variable " + var + " ne peut pas etre redeclaree."
        );
    }

    return true;
}

void Drawer::add_var(const std::string& var, const double value) {
    variables_.insert(std::pair<std::string, double>(var, value));
}

void Drawer::affect_val(const std::string& var, const double value) {
    // The program needs to check if the variable has been instanciated
    if (variables_.find(var) != variables_.end()) {
        variables_.at(var) = value;
    }
    else
        throw invalid_variable(
            "Affectation impossible : la variable " + var + " n'a pas ete declaree."
        );
}

void Drawer::visit_prog(const Prog* p) {

    // Image initialization
    img_ = CImg<unsigned char>(img_size_x, img_size_y, 1, 3);
    img_.fill(255);

    std::cout << "\n=== Lancement du programme ===\n\n";

    p->get_prog()->visit(*this);

    /*CImgDisplay disp;
    disp.display(img_);

    while (!disp.is_closed()) {
        if (disp.key() == cimg::keyQ) disp.close(); // Loop on events
        disp.wait();
    }*/

    save_img(img_name_);

    std::cout << "\n=== Fin du programme ===\n\n";
}

void Drawer::visit_seq(const Sequence* s) {
    SeqItem *t = s->getFirst();
    while(t != NULL) {
        t->get_inst()->visit(*this);
        t = t->get_next();
    }
}

void Drawer::visit_config(const ImgConfig* c) {

    std::cout << "Nouvelle configuration : ";

    switch (c->get_type()) {

        case NAME :
            std::cout << "NOUVEAU NOM = " << c->get_name();
            img_name_ = c->get_name();
            break;

        case SAVE :
            if (c->get_name() != "result") {
                std::cout << "SAUVEGARDE, Nom : " << c->get_name();
                save_img(c->get_name());
            }
            else {
                std::cout << "SAUVEGARDE" << c->get_name();
                save_img(img_name_);
            }
            break;

        case PATH :
            std::cout << "CHEMIN = " << c->get_path();
            path_ = c->get_path();
            break;

        case NEW :
            if (c->get_name() != "result") {
                std::cout << "NOUVELLE IMAGE = " << c->get_name();
                img_name_ = c->get_name();
            }
            else std::cout << "NOUVELLE IMAGE" << c->get_name();
            img_ = CImg<unsigned char>(img_size_x, img_size_y, 1, 3);
            img_.fill(255);
            pos_buf_ = std::pair<double, double>(img_size_x/2, img_size_y/2);
            break;
    }
    std::cout << "\n";
}

void Drawer::visit_pen(const Pen* p) {
    pen_state_ = p->get_state();
    if (pen_state_) std::cout << "Le crayon ecrit.\n";
    else std::cout << "Le crayon est leve.\n";
}

void Drawer::visit_double(const Double* d) {
    value_buf_ = d->get_value();
    std::cout << value_buf_;
}

void Drawer::visit_var(const Variable* v) {
     if (variables_.find(v->get_name()) != variables_.end()) {
        std::cout << v->get_name();
        value_buf_ = variables_.at(v->get_name());
    }
}

void Drawer::visit_operation(const Operation* o) {
    
    double result = 0;
    std::cout << " (";

    o->get_left()->visit(*this);
    double first = value_buf_;

    std::cout << ", ";
    
    o->get_right()->visit(*this);
    double second = value_buf_;

    std::string ope;

    switch(o->get_operator()) {

        case PLUS:
            ope = " + ";
            result = (first + second);
            break;

        case MINUS:
            ope = " - ";
            result = (first - second);
            break;

        case MULT:
            ope = " * ";
            result = (first * second);
            break;

        case DIV:
            ope = " / ";
            result = (first / second);
            break;
    }

    value_buf_ = result;
    std::cout << "," << ope << ") soit : " << first << ope << second;

    std::cout << " => " << result << " ";
}

void Drawer::visit_decl(const Declaration* d) {
    
    const std::string var = d->get_var();

    if (check_decl(var))
        add_var(var, 0);

    std::cout << "La variable " << var
    << " est déclarée.\n";
}

void Drawer::visit_affect(const Affect* a) {
    std::cout << "Affectation de " << a->get_var() << " : ";
    a->get_value()->visit(*this);
    std::cout << ";\n";
    affect_val(a->get_var(), value_buf_);
}

void Drawer::visit_move(const MovePen* m) {

    if (m->is_forced() || pen_state_) std::cout << "Ecriture ";
    else std::cout << "Deplacement de [";

    // Temp final position
    std::pair<double, double> final_pos;

    // The program stores the lenght of movement
    m->get_len()->visit(*this);
    double len = value_buf_;
    std::cout << "] vers ";

    // Computing the new position
    switch (m->get_dir()) {

        case HAUT :
            final_pos = std::pair<double, double>(pos_buf_.first, pos_buf_.second - len);
            std::cout << "le haut";
            break;

        case BAS :
            final_pos = std::pair<double, double>(pos_buf_.first, pos_buf_.second + len);
            std::cout << "le bas";
            break;

        case GAUCHE :
            final_pos = std::pair<double, double>(pos_buf_.first - len, pos_buf_.second);
            std::cout << "la gauche";
            break;

        case DROITE :
            final_pos = std::pair<double, double>(pos_buf_.first + len, pos_buf_.second);
            std::cout << "la droite";
            break;
    }

    // The program checks if the user wanted to draw a line, to move or is drawing
    if (m->is_forced() || pen_state_)
        img_.draw_line(
            pos_buf_.first, pos_buf_.second,
            final_pos.first, final_pos.second,
            color_, 3.0f
        );
    
    pos_buf_ = final_pos;
    std::cout << ";\n";
}

void Drawer::visit_center(const Center* c) {
    pos_buf_ = std::pair<double, double>(img_size_x/2, img_size_y/2);
}

void Drawer::visit_rect(const Rectangle* r) {

    std::cout << "Nouveau rectangle de taille [";

    r->get_len()->visit(*this);
    double len = value_buf_;
    std::cout << " * ";;
    r->get_width()->visit(*this);
    double width = value_buf_;
    std::cout << "] ( = " << len << " * " << width << ");\n";

    // Drawing rectangle
    img_.draw_rectangle(
        (pos_buf_.first - (len / 2)),
        (pos_buf_.second - (width / 2)),
        (pos_buf_.first + (len / 2)),
        (pos_buf_.second + (width / 2)),
        color_
    );
}

void Drawer::visit_circle(const Circle* c) {
    
    std::cout << "Nouveau cercle de diametre [";

    c->get_diam()->visit(*this);
    double diam = value_buf_;

    // Drawing circle
    img_.draw_circle(
        pos_buf_.first,
        pos_buf_.second,
        (diam / 2),
        color_
    );

    std::cout << "] ( = " << diam << ");\n";
}

void Drawer::visit_set_color(const SetColor* sc) {
    std::cout << "Nouvelle couleur : ";
    set_color(sc->get_color());
    std::cout << ";\n";
}

void Drawer::visit_for(const ForLoop* fl) {

    std::cout << "Entrée de boucle : ";
    
    const std::string var = fl->get_variable();

    if (check_decl(var)) {

        iterators_.push_back(var); // TODO : Put value

        fl->get_begin()->visit(*this);
        double loop_b = value_buf_;

        fl->get_end()->visit(*this);
        double loop_e = value_buf_;

        std::cout << "iterateur = " << var
        << " allant de " << loop_b
        << " a " << loop_e << "\n";

        std::cout << "\n[CONTENU]\n";
        for (double i = loop_b; i <= loop_e; i++) {
            fl->get_body()->visit(*this);
        }
        std::cout << "\n[FIN DE BOUCLE]\n\n";

        iterators_.pop_back();  // Deletes the last created iterator
    }

}
