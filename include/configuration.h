#ifndef _CONFIGURATION_H_
#define _CONFIGURATION_H_

#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/stringize.hpp>
#include <container_output.h>
#include <yaml-cpp/yaml.h>

class MissingPropertyException : public std::exception {
    private:
        const char* message;

    public:
        MissingPropertyException(const char* msg) : message(msg) {}
        
        const char* what() const noexcept {
            return message;
        }
};

#define PROPERTY_TYPE(t) BOOST_PP_TUPLE_ELEM(0, t)
#define PROPERTY_NAME(t) BOOST_PP_TUPLE_ELEM(1, t)
#define PROPERTY_NAME_STR(t) BOOST_PP_STRINGIZE(PROPERTY_NAME(t))
#define PROPERTY_DEFAULT(t) BOOST_PP_TUPLE_ELEM(2, t)
#define PROPERTY_REQUIRED(t) BOOST_PP_TUPLE_ELEM(3, t)

#define DECLARE_PROPERTY(r, data, elem) PROPERTY_TYPE(elem) PROPERTY_NAME(elem);
#define INITIALIZE_PROPERTY(r, data, elem) data.PROPERTY_NAME(elem) = PROPERTY_DEFAULT(elem);
#define PRINT_PROPERTY(r, data, elem) \
    if(__property_line_index++ > 0) { \
        out << std::endl; \
    } \
    out << std::string((__property_print_depth_level - 1) * 2, ' ') << "- " << PROPERTY_NAME_STR(elem) << ": " << data.PROPERTY_NAME(elem);
#define CHECK_PROPERTY_EXISTS(r, data, elem) \
    if(PROPERTY_REQUIRED(elem) && !node[PROPERTY_NAME_STR(elem)]){ \
        throw MissingPropertyException("Missing required property " PROPERTY_NAME_STR(elem)); \
    }
#define DECODE_PROPERTY(r, data, elem) data.PROPERTY_NAME(elem) = node[PROPERTY_NAME_STR(elem)].as<PROPERTY_TYPE(elem)>(PROPERTY_DEFAULT(elem));
#define ENCODE_PROPERTY(r, data, elem) node[PROPERTY_NAME_STR(elem)] = data.PROPERTY_NAME(elem);

static int __property_print_depth_level = 0;

#define CONFIGURATION_SCHEMA(name, ...) \
    typedef struct name { \
        BOOST_PP_SEQ_FOR_EACH(DECLARE_PROPERTY, _, __VA_ARGS__) \
        \
        static name get_default(){ \
            name __config__; \
            BOOST_PP_SEQ_FOR_EACH(INITIALIZE_PROPERTY, __config__, __VA_ARGS__) \
            return __config__; \
        } \
        \
        friend std::ostream& operator<<(std::ostream& out, const name& __config__){ \
            __property_print_depth_level++; \
            if(__property_print_depth_level > 1) std::cout << std::endl; \
            int __property_line_index = 0; \
            BOOST_PP_SEQ_FOR_EACH(PRINT_PROPERTY, __config__, __VA_ARGS__) \
            __property_print_depth_level--; \
            return out; \
        } \
    } name;\
    \
    namespace YAML { \
        template<> \
        struct convert<name> { \
            static YAML::Node encode(const name& rhs) { \
                YAML::Node node; \
                BOOST_PP_SEQ_FOR_EACH(ENCODE_PROPERTY, rhs, __VA_ARGS__) \
                return node;\
            } \
            \
            static bool decode(const YAML::Node& node, name& rhs) { \
                BOOST_PP_SEQ_FOR_EACH(CHECK_PROPERTY_EXISTS, _, __VA_ARGS__) \
                BOOST_PP_SEQ_FOR_EACH(DECODE_PROPERTY, rhs, __VA_ARGS__) \
                return true;\
            } \
        }; \
    }

#endif