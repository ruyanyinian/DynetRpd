#ifndef EXCEPT_HPP
#define EXCEPT_HPP

#include <stdexcept>
#include <sstream>
#include <iostream>

namespace dynet {
class out_of_memory : public std::runtime_error {
public:
    out_of_memory(const std::string& what_arg) : runtime_error(what_arg) {}
};

class cuda_not_implement : public std::logic_error {
public:
    cuda_not_implement(const std::string& what_arg) : logic_error(what_arg) {}
};

class cuda_exception : public std::runtime_error {
 public:
  cuda_exception(const std::string& what_arg) : runtime_error(what_arg) {}
};
}
#endif