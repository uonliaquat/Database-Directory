#include <iostream>
#include <fstream>
#include <QMessageBox>
#include <QString>
#include "mainwindow.h"
#include "mainwindow.h"
#include <sstream>
#include <QWindow>
using namespace std;

class FileHandling{
private:
    HashTable * hash;
public:
    FileHandling(){

    }
    FileHandling(HashTable * hashtable){
        hash = hashtable;
    }

    void writeTable(string table_name, string ** row, int noOfEntries, int noOfColoumns){
        ofstream myfile;
        myfile.open("/Users/apple/Desktop/Qt\ Projects/DataStructures_Project/Files/"+ table_name, ios::out);
        if(myfile.is_open()){
            for(int i = 0; i < noOfEntries; i++){
                for(int j = 0; j < noOfColoumns; j++){
                    myfile <<row[i][j];
                    myfile <<" ";
                }
                myfile <<endl;
            }
            myfile.close();
        }
        else{

        }
        writeRowCount(table_name, noOfEntries);
    }

    void writeList(string table_name, int noOfColoumns, string * coloumndata){
        ofstream myfile;
        myfile.open("/Users/apple/Desktop/Qt\ Projects/DataStructures_Project/Files/list_data.txt", ios::app);
        if(myfile.is_open()){
            myfile << table_name;
            myfile << " ";
            myfile << noOfColoumns;
            myfile << " ";
            for(int i = 0; i < noOfColoumns; i++){
                myfile<<coloumndata[i];
                myfile<<" ";
            }
            myfile<<endl;
            myfile.close();
        }
        else{

        }
        writeTableCount();
//        readList();
//        readList();
    }


    string ** readTable(string table_name, int no_of_coloumns){
        ifstream file;
        ifstream myfile;
        file.open("/Users/apple/Desktop/Qt\ Projects/DataStructures_Project/Files/rowCount_" + table_name, ios::in);
        myfile.open("/Users/apple/Desktop/Qt\ Projects/DataStructures_Project/Files/" + table_name, ios::in);
        if(file.is_open()){
            string all_data;
            int no_of_entries;
            string noOfEntries_s;
            file>>noOfEntries_s;
            stringstream geek(noOfEntries_s);
            geek >> no_of_entries;
            file.close();
            if(myfile.is_open()){
               string ** row_data = new string *[no_of_entries];
               for(int i = 0; i < no_of_entries; i++){
                   row_data[i] = new string[no_of_coloumns];
               }
               for(int i = 0; i < no_of_entries; i++){
                   for(int j = 0; j < no_of_coloumns; j++){
                       myfile >> all_data;
                       row_data[i][j] = all_data;
                   }
               }
               myfile.close();
               return row_data;
            }
        }
    }

    string ** readList(){
//        MainWindow* mainWindow = nullptr;
//        QList<QWindow *> qList = QGuiApplication::allWindows();
//        for(int i = 0; i < qList.size(); i++){
//            QWindow * qWindow = qList.at(i);
//            if(qWindow->objectName() == "MainWindowWindow"){
//                mainWindow = dynamic_cast<MainWindow*>(qWindow);
//            }
//        }
//        HashTable * hashtable = mainWindow->getHashTable();

        string ** list_data = new string*[readTableCount()];
        ifstream myfile;
        myfile.open("/Users/apple/Desktop/Qt\ Projects/DataStructures_Project/Files/list_data.txt", ios::in);
        if(myfile.is_open()){
            string table_name;
            int i = 0;

            while (myfile >> table_name)
            {
                int noOfColoumns;
                string no_of_coloumns_s;
                int j = 1;
                string sLine;
                getline(myfile, sLine);
                while(sLine[j] != ' '){
                    no_of_coloumns_s = no_of_coloumns_s + sLine[j];
                    j++;
                }
                stringstream geek(no_of_coloumns_s);
                geek >> noOfColoumns;
                string * newString = new string[noOfColoumns + 2];
                bool checkspace = false;
                int m = 0;
                int index = 0;
                while(!myfile.eof()){
                    while(sLine[m] != ' '){
                        checkspace = true;
                        m++;
                    }
                    m++;
                    if(checkspace){
                        while(sLine[m] != ' ' && sLine[m] != 0){
                            newString[index] = newString[index] + sLine[m];
                            m++;
                            QString str = QString::fromStdString(newString[index]);
                            qDebug() << str;
                        }
                        index++;
                     }
                    if(sLine[m] == myfile.eof()){
                        break;
                    }
                }



                list_data[i] = new string[noOfColoumns + 2];

                for(int a = 0; a < noOfColoumns + 2; a++){
                    if(a == 0){
                      list_data[i][a] = table_name;
                    }
                    else if(a == 1){
                        list_data[i][a] = no_of_coloumns_s;
                    }
                    else{
                         list_data[i][a] = newString[a-2];
                    }
                }
//                myfile.ignore(numeric_limits<streamsize>::max(), '\n');
                i++;
                if(i == readTableCount()){
                    break;
                }
            }
            myfile.close();
            return list_data;
        }
        else{

        }
    }


    void writeTableCount(){
        int x = 0;
        ifstream readfile;
        ofstream writefile;
        readfile.open("/Users/apple/Desktop/Qt\ Projects/DataStructures_Project/Files/table_count.txt", ios::in);
        if(readfile.is_open()){
            string sLine;
            getline(readfile, sLine);
            stringstream geek(sLine);
            geek >> x;
            x++;
            readfile.close();
            writefile.open("/Users/apple/Desktop/Qt\ Projects/DataStructures_Project/Files/table_count.txt", ios::out);
            if(writefile.is_open()){
                writefile<<x;
                writefile.close();
            }

        }
        else{
           int x = 1;
           writefile.open("/Users/apple/Desktop/Qt\ Projects/DataStructures_Project/Files/table_count.txt", ios::out);
           if(writefile.is_open()){
               writefile << x;
               writefile.close();

           }

        }
    }

    void writeRowCount(string table_name, int noOfEntries){
        ofstream writefile;
        writefile.open("/Users/apple/Desktop/Qt\ Projects/DataStructures_Project/Files/rowCount_" + table_name, ios::out);
        if(writefile.is_open()){
            writefile<<noOfEntries;
            writefile.close();
        }
    }

    int readRowCount(string table_name){
        ifstream writefile;
        writefile.open("/Users/apple/Desktop/Qt\ Projects/DataStructures_Project/Files/rowCount_" + table_name, ios::in);
        if(writefile.is_open()){
            string s;
            getline(writefile,s);
            stringstream geek(s);
            int x = 0;
            geek >> x;
            writefile.close();
            return x;
        }
    }

    int readTableCount(){
        int x = 0;
        ifstream readfile;
        readfile.open("/Users/apple/Desktop/Qt\ Projects/DataStructures_Project/Files/table_count.txt", ios::in);
        if(readfile.is_open()){
            string sLine;
            getline(readfile, sLine);
            stringstream geek(sLine);
            geek >> x;
            readfile.close();
            return x;
        }
        else{
            return 0;
        }
    }



    string  ReadTableRow(string table_name){
        string line;
        string row;
        ifstream myfile;
           myfile.open("/Users/apple/Desktop/Qt\ Projects/DataStructures_Project/Files/" + table_name, ios::in);
           if(myfile.is_open()){
               while(getline(myfile, line)){
                   row = line;
               }
           }
           return row;
   }


};
