#pragma once
#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
using namespace std;
class Engine
{
public:
    Engine();
    void show(int p);
    void set_argument(string leixing);
    ~Engine(){}
private:
    string leixing;///发动机类型
};

