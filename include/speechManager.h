#pragma once
#include<iostream>
#include<vector>
#include<map>
#include<speecher.h>

using namespace std;


class speechManager
{
public:
    speechManager();
    ~speechManager();

public:
    void showMenu();

    void history();

    void start();

    void quite();


public:
    vector<int> v1,v2,v3;
    map<int,speecher> speecher_;
    int index_;
    

};
