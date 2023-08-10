#ifndef _APP_H_
#define _APP_H_

#include <configuration.h>

CONFIGURATION_SCHEMA(
    DBConfig,
    ((std::string,  driver,     "",     true ))
    ((std::string,  user,       "",     true ))
    ((std::string,  pass,       "",     true ))
    ((int,          timeout,    0,      false))
);

CONFIGURATION_SCHEMA(
    SiteConfig,
    ((std::string,  domain,     "",     true))
    ((int,          port,       0,      true))
);

using MapOfSiteConfig = std::map<std::string, SiteConfig>;

CONFIGURATION_SCHEMA(
    AppConfig,
    ((DBConfig,         db,         DBConfig::get_default(),     true))
    ((MapOfSiteConfig,  site,       MapOfSiteConfig(),           true))
);

extern void app(const AppConfig& config);
extern void run_app_with_cfg(const std::string& config_str);

#endif