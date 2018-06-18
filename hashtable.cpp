#pragma once

#include <iostream>
#include "linkedlist.cpp"
using namespace std;

class HashTable{

public:
    HashTable(){
        list = new LinkedList[HashSize];
    }

    int getHashKey(string str){
        int key = 0;
        for(int i = 0; i < str.length(); i++){
            key = (str[i] * i) + key;
        }
        key = key % HashSize;
        return key;
    }

    void insert(string table_name, string row[], int noOfColoumns){
        int key = getHashKey(table_name);
        list[key].insert(table_name, row, noOfColoumns);
    }


    void BST_insert(string table_name, string row[], int noOfColoumns){
        int key = getHashKey(table_name);
        list[key].BST_insert(table_name, row, noOfColoumns);
    }

    void insertColoumns(string table_name, int no_of_coloumns, string coloumnsName[]){
       int key = getHashKey(table_name);
       list[key].insertColoumns(table_name, no_of_coloumns, coloumnsName);
    }

    bool delete_data(string table_name, string id_s){
        int key = getHashKey(table_name);
        list[key].delete_data(table_name, id_s);
    }

    string * getColoumnData(string table_name){
        int key = getHashKey(table_name);
        return list[key].getColoumnData();
    }

    void update(string table_name, string * data, string id_s, int no_of_coloumns){
        int key = getHashKey(table_name);
        list[key].uodate(table_name, data, id_s, no_of_coloumns);
    }

    void getRowData(string table_name, string ** row, int noOfColoumns, int noOfEntries, int*index){
       int key = getHashKey(table_name);
       list[key].getRowData(table_name, row, noOfColoumns, noOfEntries, index);
    }

    void getPreOrder(string table_name, string ** row, int noOfColoumns, int noOfEntries, int*index){
       int key = getHashKey(table_name);
       list[key].getPreOrder(table_name, row, noOfColoumns, noOfEntries, index);
    }

    int getNoOfColoumns(string table_name){
        int key = getHashKey(table_name);
        return list[key].getNoOfColoumns();
    }

    int getNoOFEntries(string table_name){
       int key = getHashKey(table_name);
       return list[key].getNoOfEntries();
    }

    string * search(string table_name, string id){
     int key = getHashKey(table_name);
     return list[key].search(table_name, id);
    }
private:
    LinkedList * list;
    int HashSize = 1000;

};
