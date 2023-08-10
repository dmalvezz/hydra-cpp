
#include "app.h"
#include <boost/python.hpp>
#include <filesystem>

void app(const AppConfig& config){
    std::cout << "Testing db " << config.db.driver << " using " << config.db.user << ":" << config.db.pass << std::endl;
    for(const auto& site : config.site){
        std::cout << " - Test " << site.first << " -> " << site.second.domain << ":" << site.second.port << std::endl;
    }
}

void run_app_with_cfg(const std::string& config_str){
    YAML::Node node;
    if(std::filesystem::exists(config_str)){
        node = YAML::LoadFile(config_str);
    } 
    else{
        node = YAML::Load(config_str);
    }

    AppConfig config = node.as<AppConfig>();
    app(config);
}

BOOST_PYTHON_MODULE(app)
{
    using namespace boost::python;
    def("run_app_with_cfg", run_app_with_cfg);
}