#include "dynet/dim.hpp"
#include <vector>
#include <string>
#include <iostream>
using namespace std;
using namespace dynet;

struct Person {
    Person() : name(""), id() {}
    const std::string name;
    int id;
};

std::ostream& operator<<(std::ostream& os, Person& p) {
    std::cout << p.name << std::endl;
} 
int main() {
    std::vector<Person> p(10);
    std::cout << p[2] <<endl;
    return 0;
}