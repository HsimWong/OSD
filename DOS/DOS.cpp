#include <string>
#include <cstdio>
#include <iostream>
#define FDF -2
#define FFF -1
using namespace std;

const int capacity = 100;       // Capacity of the form
const int doc_num_max = 20;     // Maximum capacity of #documents
int freespace = 100;            // Variable for documenting #freespace
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
    for(int i = 0; i < capacity; i++){
        cout << FAT[i] << "\t";
        if(i % 10 == 9){
        	cout << endl;
        }
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

void search_point(int index){
    if(index == 0 || index == 1){
        cout << "Permission denied: System area." << endl;
    }

    if (FAT[index] == 0){
        cout << "This block belongs to no one" << endl;
        return;
    }

    for(int i = 0; i < fileNum; i++){
        int ptr = filespace[i].start;
        for(int j = 0; j < filespace[i].length; j++){
            if(ptr == index){
                cout << "Block No." << index << "belongs to "<<endl;
                cout << filespace[i].name << "and is its " << j << "th block" << endl;
                return;
            }
            else{
                ptr = FAT[ptr];
                continue;
            }
        }
    }
}

int checkEmptyFrom(int start){
    // int write_ptr = 0;
    for(int i = start; i < doc_num_max; i++){       // find the first empty space
        if(FAT[i] == 0){
            filespace[fileNum].start = i;
            return i;
        }
        else{
            cout << "Space is Full" << endl;
            break;
        }
    }
}

void write(string filename, int length){
    if(length > freespace){
        cout << "Space is not enough" << endl;
        return;
    }


    filespace[fileNum].name = filename;
    filespace[fileNum].length = length;

    int write_ptr = 0;

    for(int i = 2; i < capacity ;i++){	//存文件
        if(FAT[i]==0){
            filespace[fileNum].start=i;//首个空闲块为文件开始块
            write_ptr=i;
            FAT[write_ptr]=FFF;
            break;
        }
    }


    for(int i = 0; i < length - 1; i++){
        for(int j = write_ptr; j < capacity; j++){
            if(FAT[j] == 0){
                cout << "found empty block at " << j << endl;
                FAT[write_ptr] = j;
                write_ptr = j;
                FAT[write_ptr] = FFF;
                // FAT[write_ptr] = FFF;
                break;
            }
        }
    }
    FAT[write_ptr] = FFF;
    freespace -= length;
    fileNum++;
    cout << "Document " << filename << " with length " << length << "written" << endl;

}

void insert(string filename, int istpt){

    int write_ptr = 0;

    int scan_ptr = filespace[write_ptr].start;
    for(int i = 0; i < fileNum; i++){
        if(filespace[i].name == filename){

            write_ptr = i;
            break;
        }
    }
    for(int j = 0; j < capacity; j++){
        if(FAT[j] == 0){
            FAT[j] = FAT[scan_ptr];
            FAT[scan_ptr] = j;
            break;
        }
    }
    filespace[write_ptr].length++;
    freespace--;
    cout << filename << filespace[write_ptr].length << endl;

    for(int i = 0; i < istpt - 1; i++){
        scan_ptr = FAT[scan_ptr];

    }

}

// void parser(string cmd, )

int main(int argc, char const *argv[])
{
    // First 2 unit is for documenting the type of the disk
    // documenting is from index = 2
    FAT[0] = FDF;
    FAT[1] = FFF;
    freespace -= 2;
    string filename;
    int length;

    while(true){
        printf("                            0.exit                      \n");
        printf("            1.write         2.Insert            3.Show documents     \n");
        printf("            4.Show FAT      5.Search Document   6.Search Block      \n");

        printf("      *********************************************************\n");
        cout << endl;
        int cmd;
        cout << "CHoose one option" << endl;
        cout.flush();
        cin >> cmd;
        cin.sync();
        int is = 0;
        char * temp;
        switch(cmd){
            case 0:exit(0);
            case 1: printf("FileName:\n");

                cout.flush();
                cin.sync();
                getline(cin, filename);

                cout << "length:" << endl;
                cout.flush();
                cin.sync();
                cin >> length;
                cin.sync();
                write(filename, length);
                break;
            case 2: cout << "Filename:" << endl;
                cout.flush();
                cin.sync();
                getline(cin, filename);
                cout << "index insert" << endl;
                cout.flush();
                cin.sync();
                cin >> is;
                cin.sync();
                insert(filename, is);
                break;
            case 3: print_file_info();
                break;
            case 4: printFAT();
                break;
            case 5: cout << "Filename" << endl;
                cin.sync();
                cout.flush();
                cin.sync();
                getline(cin, filename);
                cin.sync();
                filename = temp;
                search_file(filename);
                break;
            case 6: cout << "Check index" << endl;
                int searchpt;
                cout.flush();
                cin.sync();
                cin >> searchpt;
                cin.sync();
                cout.flush();
                search_point(searchpt);
                break;



        }
        cout << filename;

    }
    printFAT();
    return 0;
}





