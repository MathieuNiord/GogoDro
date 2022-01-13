#include "img_config.hh"

ImgConfig::ImgConfig(ConfigType type, const std::string& name, const std::string& path)
    : type_(type), img_name_(name), img_path_(path) {}

void ImgConfig::visit(Visitor& visitor) const {
    return visitor.visit_config(this);
}