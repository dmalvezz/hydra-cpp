# hydra-cpp
  <p align="center">
    <i>A simple header-only library to quickly define configurations and 
    add <a href="https://github.com/facebookresearch/hydra">hydra</a> support to your cpp projects.</i>
  </p>

## Requirements
 - [`Boost.Python`](https://www.boost.org/doc/libs/1_82_0/libs/python/doc/html/index.html)
 - [`Boost.Preprocessor`](https://www.boost.org/doc/libs/1_82_0/libs/preprocessor/doc/index.html)
 - [`yaml-cpp`](https://github.com/jbeder/yaml-cpp)

## Getting started
### Defining the configuration
Defining a configuration only requires data-type, name, default value and a required flag.
```cpp
#include <configuration.h>

CONFIGURATION_SCHEMA(
    DBConfig,
    ((std::string,  driver,     "",     true ))
    ((std::string,  user,       "",     true ))
    ((std::string,  pass,       "",     true ))
    ((int,          timeout,    0,      false))
);
```

### Parsing the configuration
The functions to encode/decode the configuration to/from a YAML file are automatically generated, so you can directly use `yaml-cpp` as 

```c++
#include <iostream>
#include <yaml-cpp/yaml.h>

void app(const DBConfig& config){
    std::cout << "Driver: "   << config.db.driver << std::endl;
    std::cout << "User: "     << config.db.user   << std::endl;
    std::cout << "Password: " << config.db.pass   << std::endl;
}

int main(){
    YAML::Node node = YAML::LoadFile("config/config.yaml");
    DBConfig config = node.as<DBConfig>();
    app(config);
    return 0;
}
``` 

### Using with Hydra
A simple Python binding can be used to connect the cpp project to Hydra
```c++
void run_app_with_cfg(const std::string& config_str){
    YAML::Node node = YAML::Load(config_str);
    DBConfig config = node.as<DBConfig>();
    app(config);
}

BOOST_PYTHON_MODULE(app)
{
    using namespace boost::python;
    def("run_app_with_cfg", run_app_with_cfg);
}
```
Then create a simple experiment script in Python as
```python
import hydra
from omegaconf import DictConfig, OmegaConf

# Compiled binding
from app import run_app_with_cfg

@hydra.main(version_base=None, config_path="config", config_name="config")
def my_experiment(cfg : DictConfig) -> None:
    config = OmegaConf.to_object(cfg)

    # Convert YAML to string and pass it to the C++ project
    run_app_with_cfg(str(config))

if __name__ == "__main__":
    my_experiment()
```
Read [`hydra`](https://github.com/facebookresearch/hydra) documentation for more info about its functionalities.

## Running the example
This repo contains a simple example to test the library.  
Open it with Visual Studio Code Dev Containers extensions to get a ready-to-use development environment.  
You can run the example using the Python-wrapper [experiment.py](experiment.py) to use all the `hydra` functionalities or run the main executable.

## TODOs
- [x] `std` container support
- [ ] Improve configuration printing
- [ ] More testing

## :warning: Warning :warning:
This library has not been tested properly yet!  
Use it at your own risk and open an issue if necessary :satisfied:

## License
`hydra-cpp` is released under the MIT license. See [LICENSE](LICENSE) for additional details about it.