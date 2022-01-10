#ifndef EXEC_HPP
#define EXEC_HPP
#include <string>
#include <vector>
#include <iostream>
using namespace std;

struct PersonInfo {
public:
    PersonInfo() : id(0), name("") {}
    PersonInfo(const string& name, int id) : id(id), name(name) {}
    ~PersonInfo() {}
public:
    int id;
    const string& name;
};

class PersonInfoManager {
public:
    PersonInfoManager();
    ~PersonInfoManager();
    void add(PersonInfo* personinfo);
    void clear() { v.clear(); }
public:
    std::vector<PersonInfo*> v; 
};

PersonInfoManager* get_person_manager();
#endif