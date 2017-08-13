#ifndef CLASS_EXAMPLE_H
#define CLASS_EXAMPLE_H

#include "Singleton.h"

/********************************************************/
/* C++类，单例，注册到lua中使用                         */
/********************************************************/
class ClassExample : public Singleton<ClassExample>
{
public:
    ClassExample() : data(0) {}
    virtual ~ClassExample() {}

public:
    void SetData(int d) { data = d; }
    int GetData() { return data; }

protected:
    int data;
};

#define sClassExample (*ClassExample::Instance())

#endif