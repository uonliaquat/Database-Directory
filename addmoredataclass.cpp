#include <iostream>
#include <string>
#include "mainwindow.h"

using namespace std;
class AddMoreDataClass : AddMoreData{

public:
    AddMoreDataClass(string value){
        str = value;
    }

private:
   string str;

};
