#include <string>
#include <cstdio>
#include <iostream>
#define FDF -2
#define FFF -1
using namespace std;

const int capacity = 100;       // Capacity of the form
const int doc_num_max = 20;     // Maximum capacity of #documents
int freespace = 100;                  // Variable for documenting #freespace
int fileNum = 0;
/*
 * Description of a file
 * including its name, start index and length
 */
struct file{
    string name;
    int start;
    int length;
};

int FAT[capacity] = {0};              // FAT Form, initialized with 0
file filespace[doc_num_max];

void print_file_info(){
    cout << "File quantity" << fileNum << endl;
    cout << "DocName    start index    length" << endl;
    for (int i = 0; i < fileNum; i++){
        cout << filespace[i].name << "    " << filespace[i].start << "    " << filespace[i].length << endl;
    }
    return;
}


void printFAT(){
    cout << "Free block Number: " << freespace<< endl;
    for(int i = 0; i < fileNum; i++){
        cout << "Block No. " << FAT[i] << endl;
    }
    return;
}

void search_file(string filename){
    for(int i = 0; i < fileNum; i++){
        if(filename == filespace[i].name){
            cout << "Found document " << filename << "at " << filespace[i].start << " length = " << filespace[i].length;
            return;
        }
    }
    cout << "No Such File" << endl;
    return;
}

int ind_file(int file_ind, int search_ind){
    int ret = -1;
    int chk = filespace[file_ind].start;
    for(int i = 0; FAT[chk] != -1; i++){
        if(chk == search_ind){
            ret = 
            break;
        }
    }

}


void search_point(int index){
    if(index == 0 || index == 1){
        cout << "Permission denied: System area." << endl;
    }
    else{

    }
}

void parser(string cmd, )

int main(int argc, char const *argv[])
{
    // First 2 unit is for documenting the type of the disk
    // documenting is from index = 2
    FAT[0] = FDF;
    FAT[1] = FFF;
    freespace -= 2;

    
    while(true){
        printf("                            0.exit                      \n");
        printf("            1.write         2.Insert            3.Show documents     \n");
        printf("            4.Show FAT      5.Search Document   6.Search Block      \n");

        printf("      *********************************************************\n");

        int cmd;
        getline(cin, cmd);
        switch()
        
    }

    return 0;
}





