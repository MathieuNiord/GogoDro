/* Auteurs : Frejoux Gaetan & Niord Mathieu */

#ifndef _IMG_CONF_H
#define _IMG_CONF_H

#include "inst.hh"

enum ConfigType {
    NAME,
    SAVE,
    NEW,
    PATH
};

class ImgConfig : public Instruction {

    ConfigType type_;
    std::string img_name_;
    std::string img_path_;

public:

    ImgConfig(ConfigType type, const std::string& name = "result", const std::string& path = "");
    ~ImgConfig() = default;

    inline ConfigType const get_type() const { return type_; }
    inline std::string const get_name() const { return img_name_; }
    inline std::string const get_path() const { return img_path_.substr(1, img_path_.size()); }

    void visit(Visitor& visitor) const;
};

#endif