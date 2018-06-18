#pragma once
#include <iostream>
using namespace std;

class TreeNode{
public:
    TreeNode(int noOfColoumns, string row[]){
      data = new string[noOfColoumns];
      for(int i = 0; i < noOfColoumns; i++){
          data[i] = row[i];
      }
    }
    string * data;
    TreeNode * left = nullptr;
    TreeNode * right = nullptr;
    int noOfEntries;
    int height = -1;
    int bf = -1;
    TreeNode * parent = nullptr;
};
