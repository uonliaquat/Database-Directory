#pragma once

#include <iostream>
#include "tree.cpp"

using namespace std;

struct Node{
    string  table_name;
    string * coloumns;
    Node * next = nullptr;
    Tree * tree_root = nullptr;
    int no_of_coloumns = 1;
    int no_of_entries = 0;
 public:
     Node(){
          tree_root = new Tree();
      }

     Node (int noOfColoumns, string col[]){
         coloumns = new string[noOfColoumns];
         for(int i = 0; i < noOfColoumns; i++){
             coloumns[i] = col[i];
         }
         tree_root = new Tree();
     }

};
