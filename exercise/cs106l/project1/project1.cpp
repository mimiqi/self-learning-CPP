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

vector<char> emptySignals{' ', '\n', '\r', '\t', '.', '\0', '?', '!', ',', '(', ')', '[', ']', '{', '}', '<', '>', '/', '\\', '|', '+', '-', '*', '&', '^', '%', '$', '#', '@', '\''};

vector<string> targetWords{"the", "and", "you", "that", "was", "for", "with", "have", "this", "but", "not", "what", "all", "were", "will", "can", "said", "there", "use", "an", "each", "which", "she", "do", "how", "their", "if", "will", "up", "other", "about", "out", "many", "then", "them", "these", "so", "some", "her", "would", "make", "like", "him", "into", "time", "has", "look", "two", "more", "write", "go", "see", "number", "no", "way", "could", "people", "my", "than", "first", "water", "been", "call", "who", "oil", "its", "now", "find", "long", "down", "day", "did", "get", "come", "made", "may", "part"};

map<string,int> targetWordsCount1;
map<string,int> targetWordsCount2;
map<string,int> targetWordsCount3;



string fileToString(ifstream& input){
    string currentLine;
    string result;
    char currentChar;
    while(getline(input, currentLine)){
        for(char c : currentLine){
            if(find(emptySignals.begin(),emptySignals.end(),c) != emptySignals.end()){
                result = result + " ";
                continue;
            }
            else{
                currentChar = tolower(c);
                result = result + currentChar;
            }
        }
    }
    return result;
}

void findTargetWords(string& file, map<string,int>& targetWordsCount){
    string currentword;
    for(char c : file){
        if(c == ' '){
            if(find(targetWords.begin(),targetWords.end(),currentword) != targetWords.end()){
                targetWordsCount[currentword]++;
            }
            currentword = "";
        }
        else{
            currentword = currentword + c;
        }
    }
}

double calculateIndex(map<string,int>& targetWordsCount1, map<string,int>& targetWordsCount2){
    double index1 = 0;
    double index2 = 0;
    double index3 = 0;
    double index4 = 0;

    for(auto& pair1 : targetWordsCount1){
        index1 += pair1.second * pair1.second;
    }
    for(auto& pair2 : targetWordsCount2){
        index2 += pair2.second * pair2.second;
    }
    for(auto& pair1 : targetWordsCount1){
        for(auto& pair2 : targetWordsCount2){
            if(pair1.first == pair2.first){
                index3 += pair1.second * pair2.second;
            }
        }
    }
    if(index1 == 0 || index2 == 0){
        cout << "Error: index1 or index2 is 0" << endl;
        return 0;
    }
    index4 = index3 / (sqrt(index1) * sqrt(index2));

    return index4;
}

int main(){

    ifstream input1("input1.txt");
    if(!input1.is_open()){
        cout << "Failed to open file" << endl;
        return 1;
    }
    string file1 = fileToString(input1);
    input1.close();

    findTargetWords(file1, targetWordsCount1);

    ifstream input2("input2.txt");
    if(!input2.is_open()){
        cout << "Failed to open file" << endl;
        return 1;
    }
    string file2 = fileToString(input2);
    input2.close();

    findTargetWords(file2, targetWordsCount2);

    ifstream input3("input3.txt");
    if(!input3.is_open()){
        cout << "Failed to open file" << endl;
        return 1;
    }
    string file3 = fileToString(input3);
    input3.close();

    findTargetWords(file3, targetWordsCount3);

    double index1 = calculateIndex(targetWordsCount1, targetWordsCount2);
    double index2 = calculateIndex(targetWordsCount1, targetWordsCount3);
    double index3 = calculateIndex(targetWordsCount2, targetWordsCount3);

    if(index2 > index3){
        cout << "Article 3 is more similar to article 1 than article 2" << endl;
    }
    else if(index2 < index3){
        cout << "Article 3 is more similar to article 2 than article 1" << endl;
    }
    else{
        cout << "Article 3 is equally similar to article 1 and article 2" << endl;
    }
}
