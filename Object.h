//
// Created by Mohammed Hossam on 28/10/2023.
//

#ifndef PROGRAMMING_III_M1_OBJECT_H
#define PROGRAMMING_III_M1_OBJECT_H
#include <iostream>
using namespace std;
class Object{
private:
    char type;

public:
    Object();
    Object(char type);
    virtual char getType() const;
    void setType(char type);
    ~Object();
    friend ostream& operator<< (ostream& os, Object& obj);
};
#endif //PROGRAMMING_III_M1_OBJECT_H
