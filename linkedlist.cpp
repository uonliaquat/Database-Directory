#pragma once

#include <iostream>
#include "node.cpp"

using namespace std;

class LinkedList{

private:
      Node * root = nullptr;

public:

    bool insert(string table_name, string row[], int noOFColoumns){
        Node * temp = root;
        while(temp != nullptr){
            if(temp->table_name == table_name){
                temp->no_of_entries++;
                temp->tree_root->AVL_insert(row, noOFColoumns);
                return true;
            }
            else{
                temp = temp->next;
            }
        }
        temp = root;
        if(!is_full()){
            Node * newNode = new Node();
            newNode->table_name= table_name;
            if(temp == nullptr){
                root = newNode;
                root->no_of_entries++;
                newNode->tree_root->AVL_insert(row, noOFColoumns);
                return true;
            }
            while(temp->next != nullptr){
                temp = temp->next;
            }
            temp->next = newNode;
            newNode->tree_root->AVL_insert(row, noOFColoumns);
            return true;
        }
        else{
            return false;
        }
    }

    bool BST_insert(string table_name, string row[], int noOFColoumns){
        Node * temp = root;
        while(temp != nullptr){
            if(temp->table_name == table_name){
                temp->no_of_entries++;
                temp->tree_root->BST_insert(row, noOFColoumns);
                return true;
            }
            else{
                temp = temp->next;
            }
        }
        temp = root;
        if(!is_full()){
            Node * newNode = new Node();
            newNode->table_name= table_name;
            if(temp == nullptr){
                root = newNode;
                root->no_of_entries++;
                newNode->tree_root->BST_insert(row, noOFColoumns);
                return true;
            }
            while(temp->next != nullptr){
                temp = temp->next;
            }
            temp->next = newNode;
            newNode->tree_root->BST_insert(row, noOFColoumns);
            return true;
        }
        else{
            return false;
        }
    }

    bool delete_data(string table_name, string id_s){
        Node * temp = root;
        while(temp != nullptr){
            if(temp->table_name == table_name){
             return temp->tree_root->delete_data(table_name, id_s, temp->tree_root->getStart());
            }
            else{
                temp = temp->next;
            }
        }
        string * str = new string[1];
        str[0] = "NO_TABLE";
        return str;
    }

    string * getColoumnData(){
        Node * temp = root;
        return temp->coloumns;
    }

    void getRowData(string table_name, string ** row, int noOfColoumns, int noOfRows, int * index){
        Node * temp = root;
        while(temp != nullptr){
            if(temp->table_name == table_name){
             temp->tree_root->getPreOrder(temp->tree_root->getStart(), row, noOfColoumns, noOfRows, index);
             break;
            }
            else{
                temp = temp->next;
            }
        }
    }

    void getPreOrder(string table_name, string ** row, int noOfColoumns, int noOfRows, int * index){
        Node * temp = root;
        while(temp != nullptr){
            if(temp->table_name == table_name){
             temp->tree_root->getPreOrder(temp->tree_root->getStart(), row, noOfColoumns, noOfRows, index);
             break;
            }
            else{
                temp = temp->next;
            }
        }
    }

    int getNoOfColoumns(){
        Node * temp = root;
        return temp->no_of_coloumns;
    }

    int getNoOfEntries(){
        Node * temp = root;
        return temp->no_of_entries;
    }

    void insertColoumns(string table_name, int no_of_coloumns, string coloumnName[]){
       Node * newNode = new Node(no_of_coloumns, coloumnName);
       newNode->no_of_coloumns = no_of_coloumns + 1;
       newNode->table_name = table_name;
       root = newNode;
       for(int i = 0; i < no_of_coloumns; i++){
           QString str = QString::fromStdString(newNode->coloumns[i]);
           qDebug() <<str;
       }
    }

    string * search(string table_name, string id){
        Node * temp = root;
        while(temp != nullptr){
            if(temp->table_name == table_name){
             return temp->tree_root->search(id, temp->tree_root->getStart());
            }
            else{
                temp = temp->next;
            }
        }
        string * str = new string[1];
        str[0] = "NO_TABLE";
        return str;
    }

    void uodate(string table_name, string * data, string id_s, int no_of_coloumns){
        Node * temp = root;
        while(temp != nullptr){
            if(temp->table_name == table_name){
             temp->tree_root->update(id_s, data,no_of_coloumns, temp->tree_root->getStart());
             break;
            }
            else{
                temp = temp->next;
            }
        }
    }

    bool is_empty(){
        if(root == nullptr){
            return true;
        }
        return false;
    }

    bool is_full(){
        try{
            Node * test = new Node();
            delete test;
            return false;
        }catch(exception e){
            return true;
        }
    }
};
