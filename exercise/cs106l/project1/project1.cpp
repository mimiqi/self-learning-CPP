#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>
#include <set>
#include <algorithm>
#include <cmath>

using namespace std;

vector<char> emptyChar = {'\n','\t','\r','\f','\v','\b','\a','\0','\\','\"','\'','\?','\(',')','[',']','{','}','\n','\t','\r','\f','\v','\b','\a','\0',',','.','/'};

vector<string > targetWords = {"and","the","to","of","is","in","at","by","for","with","an","as","be","this","from","that","it","to","with","as","by","for","in","of","on","up","with","but","not","no","yes","or","but","if","then","else","when","while","all","any","some","one","two","three","four","five","six","seven","eight","nine","ten"};


string fileToString(ifstream& file){
    string res = "";
    string line;
    getline(file,line);
    for(char c : line){
        if(find(emptyChar.begin(),emptyChar.end(),c) == emptyChar.end()){//not found in emptyChar
            res += c;
        }
        else{
            res += " ";
        }
    }
    return res;
}

void countWords(string& str,map<string,int>& wordCount){
    string target = "";
    for(char c : str){
        if(c != ' '){
            target += c;
        }
        else{
            if(find(targetWords.begin(),targetWords.end(),target) != targetWords.end()){
                wordCount[target]++;
            }
            target = "";
        }
    }
}

double calculateIndex(map<string,int>& wordCount1,map<string,int>& wordCount2){
    double index1,index2,index3,index4;
    index1 = index2 = index3 = index4 = 0;
    for(auto& pair : wordCount1){
        index1 += pair.second * pair.second;
    }
    for(auto& pair : wordCount2){
        index2 += pair.second * pair.second;
    }
    for(auto& pair1 : wordCount1){
        for(auto& pair2 : wordCount2){
            if(pair1.first == pair2.first){
                index3 += pair1.second * pair2.second;
            }
        }
    }

    if(index1 == 0 || index2 == 0){
        cout << "Error: index1 or index2 is 0" << endl;
        return 0;
    }
    else{
        return index3 / sqrt(index1 * index2);
    }
}

int main(){
    map<string,int> wordCount1,wordCount2,wordCount3;
    ifstream file("input1.txt");
    if(!file){
        cout << "Error opening file" << endl;
        return 1;
    }
    string ip1 = fileToString(file);
    countWords(ip1,wordCount1);

    ifstream file2("input2.txt");
    if(!file2){
        cout << "Error opening file" << endl;
        return 1;
    }
    string ip2 = fileToString(file2);
    countWords(ip2,wordCount2);

    ifstream file3("input3.txt");
    if(!file3){
        cout << "Error opening file" << endl;
        return 1;
    }
    string ip3 = fileToString(file3);
    countWords(ip3,wordCount3);
    
    double index1 = calculateIndex(wordCount1,wordCount3);
    double index2 = calculateIndex(wordCount2,wordCount3);

    cout << "Index1: " << index1 << endl;
    cout << "Index2: " << index2 << endl;
    
    if(index1 > index2){
        cout << "Input3 is more similar to Input1" << endl;
    }
    if(index1 < index2){
        cout << "Input3 is more similar to Input2" << endl;
    }
    if(index1 == index2){
        cout << "Input3 is equally similar to Input1 and Input2" << endl;
    }
    

}
