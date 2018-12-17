#include <string>
#include <cstdio>
#include <iostream>
#include <vector>
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

void del_file(string filename){
    int file_ind;
    bool found = false;
    for(int i = 0; i < fileNum; i++){
        if(filespace[i].name == filename){
            found = true;
            file_ind = i;
            break;
        }
    }
    if(found){
        int del_ptr = filespace[file_ind].start;
        
        for(int i = 0; i < filespace[file_ind].length; i++){
            
            int nxt = FAT[del_ptr];
            FAT[del_ptr] = 0;
            del_ptr = nxt;

            delete & del_ptr;
        }
        freespace += filespace[file_ind].length;
    }
    else{
        cout << "No such file named" << filename << endl;
    }

    for(int i = file_ind; i < fileNum; i++){
        filespace[i] = filespace[i + 1];
        fileNum--;
    }
}

void insert(string filename, int istpt, int ist_length){
    int file_space_ind = 0;
    bool found = false;
    if(ist_length > freespace){
        cout << "Space not enough" << endl;
        return;
    }
    for(int i = 0; i < fileNum; i++){
        if(filespace[i].name == filename){
            file_space_ind = i;
            found = true;
            break;
        }
    }

    if(found){
        
        int cut_in = filespace[file_space_ind].start;
        for(int i = 0; i < ist_length - 1; i++){
            cut_in = FAT[cut_in];
        }

        int fat_ind_before = cut_in;
        int fat_ind_after = FAT[cut_in];

        int write_ptr = 0;

        for(int i = 2; i < capacity ;i++){  //存文件
            if(FAT[i]==0){
                filespace[file_space_ind].start=i;//首个空闲块为文件开始块
                write_ptr=i;
                FAT[write_ptr]=FFF;
                break;
            }
        }
        FAT[fat_ind_before] = write_ptr;

        for(int i = 0; i < ist_length - 1; i++){
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
        FAT[write_ptr] = fat_ind_after;





    }
    else{
        cerr << "No Such File" << endl;
        return;
    }
}


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
        cout << endl << endl << endl;
        cout << ("                         0.exit      7.delete file                \n");
        cout << ("            1.write         2.Insert            3.Show documents     \n");
        cout << ("            4.Show FAT      5.Search Document   6.Search Block      \n");

        cout << ("      *********************************************************\n");
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
                    cout << "length" << endl;
                    int ist_length;
                    cin.sync();
                    cin >> ist_length;
                    insert(filename, is, ist_length);
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
            case 7: cout << "Filename" << endl;
                    cin.sync();
                    string chk_name;
                    cin.sync();
                    getline(cin, chk_name);
                    del_file(chk_name);
                    break;
        }
        
    }
    printFAT();
    return 0;
}





