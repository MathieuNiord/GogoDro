#include "drawer.hh"

void Drawer::get_color(Color color) {}

bool Drawer::check_var(const Variable* var) const {

    const std::string var_name = var->get_name();

    if (iterators_.find(var_name) != iterators_.end()) {
        std::cout << "Vous ne pouvez pas redéclarer "
        << var_name << " dans cette boucle.\n";
        exit(EXIT_FAILURE); 
    }

    if (variables_.find(var_name) != variables_.end()) {
        std::cout << "La variable "
        << var_name << " a déjà été déclarée.\n";
        exit(EXIT_FAILURE); 
    }

    return true;
}

void Drawer::add_iter(const Variable* var) {
    iterators_.insert(std::pair<std::string, Variable>(var->get_name(), *var));
}

void Drawer::add_var(const Variable* var) {
    variables_.insert(std::pair<std::string, Variable>(var->get_name(), *var));
}

void Drawer::erase_iter(const Variable* var) {
    iterators_.insert(iterators_.begin(), iterators_.find(var->get_name()));
}

void Drawer::erase_var(const Variable* var) {
    variables_.insert(variables_.begin(), variables_.find(var->get_name()));
}

void Drawer::visit_seq(const Sequence* s) {
    SeqItem *t = s->getFirst();
    while(t != NULL) {
        t->get_inst()->visit(*this);
        t = t->get_next();
    }
}

void Drawer::visit_pen(const Pen* p) {
    const bool state = p->get_state();
    if (state) std::cout << "Le crayon écrit.\n";
    else std::cout << "Le crayon est levé.\n";
}

void Drawer::visit_integer(const Integer* i) {
    std::cout << i->get_value();
}

void Drawer::visit_var(const Variable* v) {
    std::cout << v->get_name();
}

void Drawer::visit_operation(const Operation* o) {
    
    std::cout << "Opération : ";

    o->get_left()->visit(*this);

    switch(o->get_operator()) {

        case PLUS:
            std::cout<<" + "; break;

        case MINUS:
            std::cout<<" - "; break;

        case MULT:
            std::cout<<" * "; break;

        case DIV:
            std::cout<<" / ";
            break;

        default:
            std::cout<<"[ERREUR] Opérateur inconnu.\n";
            exit(EXIT_FAILURE);
    }

    o->get_right()->visit(*this);
    std::cout << ";";
}

void Drawer::visit_decl(const Declaration* d) {
    
    const Variable* var = d->get_var();

    if (check_var(var))
        add_var(var);

    std::cout << "La variable " << var->get_name()
    << " est déclarée.\n";
}

void Drawer::visit_affect(const Affect* a) {
    const Variable* var = a->get_var();
    std:cout << var->get_name() << " = ";
    a->get_value()->visit(*this);
}

void Drawer::visit_move(const MovePen* m) {
        
    std::cout << "Deplace : ";

    switch (m->get_dir()) {

        case HAUT: std::cout<<"haut"; break;
        case BAS: std::cout<<"bas"; break;
        case GAUCHE: std::cout<<"gauche"; break;
        case DROITE: std::cout<<"droite"; break;
        default:
            std::cout<<"[ERREUR] Direction inconnue.\n";
            exit(EXIT_FAILURE);
    }

    std::cout << " de ";
    m->get_len()->visit(*this);
    std::cout << " cases;\n";
}

void Drawer::visit_rect(const Rectangle* r) {
    std::cout << "Nouveau rectangle de taille ";
    r->get_len()->visit(*this);
    std::cout << " X ";
    r->get_width()->visit(*this);
    std::cout << ";\n";
}

void Drawer::visit_set_color(const SetColor* sc) {

    std::cout << "Nouvelle couleur : ";
    
    switch (sc->get_color()) {

        case NOIR: cout<<"NOIR"; break;
        case BLEU: cout<<"BLEU"; break;
        case VERT: cout<<"VERT"; break;
        case ROUGE: cout<<"ROUGE"; break;
        case ROSE: cout<<"ROSE"; break;
        case JAUNE: cout<<"JAUNE"; break;
        case VIOLET: cout<<"VIOLET"; break;
        default:
            std::cout<<"[ERREUR] Couleur non reconnue.\n";
            exit(EXIT_FAILURE);
    }

    std::cout << ";\n";
}

void Drawer::visit_for(const ForLoop* fl) {
    std::cout << "Entrée de boucle : ";
    
    const Variable* var = fl->get_variable();

    if (check_var(var)) {
        add_iter(var);
        std::cout << " iterateur = " << var->get_name()
        << " allant de ";
        fl->get_begin()->visit(*this);
        std::cout << " a ";
        fl->get_end()->visit(*this);
        std::cout << "\n[CONTENU]\n";
        fl->get_body()->visit(*this);
        std::cout << "\n[FIN DE BOUCLE]\n";
    }

}
