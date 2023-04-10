// Cache Simulation C++.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <math.h>
using namespace std;
#include <string.h>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <cstring>
#include <vector>
#include <map>
vector<vector<string>> DM2DVector;
multimap<string, string> directMappedMap;
multimap<string, string> FIFOfAssMap;
multimap<string, string> FIFOsetAssMap;
multimap<string, string> LRUfAssMap;
multimap<string, string> LRUsetAssMap;
float directMissCount = 0.0;
float directHitCount = 0.0;

float FIFOsetAssMissCount = 0.0;
float FIFOsetAssHitCount = 0.0;

float FIFOfullyAssMissCount = 0.0;
float FIFOfullyAssHitCount = 0.0;

float LRUsetAssMissCount = 0.0;
float LRUsetAssHitCount = 0.0;

float LRUfullyAssMissCount = 0.0;
float LRUfullyAssHitCount = 0.0;

string hexConvertToDecimal(string theHexString) {
    char charArray[11];
    string binaryVector;
    string returnString;
    for (int i = 2; i < 10; i++) {
        charArray[i] = (theHexString.at(i));
        switch (theHexString.at(i)) {
        case '0':
            //cout << "0000";
            binaryVector.append("0000");
            break;
        case '1':
          //  cout << "0001";
            binaryVector.append("0001");
            break;
        case '2':
           // cout << "0010";
            binaryVector.append("0010");
            break;
        case '3':
           // cout << "0011";
            binaryVector.append("0011");
            break;
        case '4':
           // cout << "0100";
            binaryVector.append("0100");
            break;
        case '5':
          //  cout << "0101";
            binaryVector.append("0101");
            break;
        case '6':
          //  cout << "0110";
            binaryVector.append("0110");
            break;
        case '7':
           // cout << "0111";
            binaryVector.append("0111");
            break;
        case '8':
          //  cout << "1000";
            binaryVector.append("1000");
            break;
        case '9':
          //  cout << "1001";
            binaryVector.append("1001");
            break;
        case 'a':
          //  cout << "1010";
            binaryVector.append("1010");
            break;
        case 'A':
            //  cout << "1010";
            binaryVector.append("1010");
            break;
        case 'b':
           // cout << "1011";
            binaryVector.append("1011");
            break;
        case 'B':
            // cout << "1011";
            binaryVector.append("1011");
            break;
        case 'c':
           // cout << "1100";
            binaryVector.append("1100");
            break;
        case 'C':
            // cout << "1100";
            binaryVector.append("1100");
            break;
        case 'd':
          //  cout << "1101";
            binaryVector.append("1101");
            break;
        case 'D':
            //  cout << "1101";
            binaryVector.append("1101");
            break;
        case 'e':
          //  cout << "1110";
            binaryVector.append("1110");
            break;
        case 'E':
            //  cout << "1110";
            binaryVector.append("1110");
            break;
        case 'f':
           // cout << "1111";
            binaryVector.append("1111");
            break;
        case 'F':
            // cout << "1111";
            binaryVector.append("1111");
            break;
        default:
            cout << "oop" << endl;
        }
    }
   // cout << binaryVector << endl;
    return binaryVector;
}

void directMapped(int cacheSize, int blockSize, int linesPerSet, string binaryString ) {
    string directTag;
    string directLine;
    int directCounter = 0;
    int index;
    string temp;
    map<string, string>::iterator it;
    int numLines = cacheSize / linesPerSet;
    int lineSizeField = log2(numLines);
    
    
    //cout << binaryString << endl;
    for (int k = 0; k < 23; k++) {
        temp = binaryString.at(k);
        directLine.append(temp);
    }
    for (int h = 23; h < 26; h++) {
        temp = binaryString.at(h);
        directTag.append(temp);
    }
    //cout << directLine << " & " << directTag << endl;
    //DM2DVector[0][0] = 1;
    it = directMappedMap.find(directTag);
    
    if (it == directMappedMap.end() || it->second != directLine) { //if the key is not present in the map
        if (directMappedMap.size() < cacheSize) {
        directMappedMap.insert(pair<string, string>(directTag, directLine));
        directCounter = 0;
        directMissCount++;
        }
        else {
            directMappedMap.erase(it);
            directMappedMap.insert(pair<string, string>(directTag, directLine));
            directCounter = 0;
            directMissCount++;
        }
    }
    else { //change value in map of key if key exists
        it->second = directLine;
        directCounter++;
        directHitCount++;
    }

  //  for (auto itr = directMappedMap.begin();
   //     itr != directMappedMap.end(); ++itr) {
   //     cout << itr->first << '\t' << itr->second << '\n';
  //  }
    
}

void fullyAss(int cacheSize, int blockSize, int linesPerSet, string binaryString) {
    string fullTag;
    string fullOffset;
    int fullCounter = 0;
    int index;
    string temp;
    map<string, string>::iterator it;
    int numLines = cacheSize / linesPerSet;
    int lineSizeField = log2(numLines);

    for (int k = 0; k < 27; k++) {
        temp = binaryString.at(k);
        fullTag.append(temp);
    }
    for (int h = 27; h < 31; h++) {
        temp = binaryString.at(h);
        fullOffset.append(temp);
    }
    it = FIFOfAssMap.find(fullTag);

    if (it == FIFOfAssMap.end() || it->second != fullOffset) { //if the key is not present in the map
        if (FIFOfAssMap.size() < cacheSize) {
            FIFOfAssMap.insert(pair<string, string>(fullTag, fullOffset));
            fullCounter = 0;
            FIFOfullyAssMissCount++;
        }
        else {
            //fAssMap.erase(it);
            FIFOfAssMap.insert(pair<string, string>(fullTag, fullOffset));
            fullCounter = 0;
            FIFOfullyAssMissCount++;
        }
    }
    else { //change value in map of key if key exists
        it->second = fullOffset;
        fullCounter++;
        FIFOfullyAssHitCount++;
    }


    it = LRUfAssMap.find(fullTag);

    if (it == LRUfAssMap.end() || it->second != fullOffset) { //if the key is not present in the map
        if (LRUfAssMap.size() < cacheSize) {
            LRUfAssMap.insert(pair<string, string>(fullTag, fullOffset));
            fullCounter = 0;
            LRUfullyAssHitCount++;
        }
        else {
            //fAssMap.erase(it);
            LRUfAssMap.insert(pair<string, string>(fullTag, fullOffset));
            fullCounter = 0;
            LRUfullyAssMissCount++;
        }
    }
    else { //change value in map of key if key exists
        it->second = fullOffset;
        fullCounter++;
        LRUfullyAssHitCount++;
    }


}


void setAss(int cacheSize, int blockSize, int linesPerSet, string binaryString) {
    string setTag;
    string setOffset;
    string setSet;
    int setCounter = 0;
    int index;
    string temp;
    map<string, string>::iterator it;
    int numLines = cacheSize / linesPerSet;
    int lineSizeField = log2(numLines);

    for (int k = 0; k < 22; k++) {
        temp = binaryString.at(k);
        setTag.append(temp);
    }
    for (int h = 22; h < 27; h++) {
        temp = binaryString.at(h);
        setSet.append(temp);
    }
    for (int h = 27; h <= 31; h++) {
        temp = binaryString.at(h);
        setOffset.append(temp);
    }
    it = FIFOsetAssMap.find(setTag);

    if (it == FIFOsetAssMap.end() || it->second != setOffset) { //if the key is not present in the map
        if (FIFOsetAssMap.size() < cacheSize) {
            FIFOsetAssMap.insert(pair<string, string>(setTag, setOffset));
            setCounter = 0;
            FIFOsetAssMissCount++;
        }
        else {
           
            FIFOsetAssMap.insert(pair<string, string>(setTag, setOffset));
            setCounter = 0;
            FIFOsetAssMissCount++;
        }
    }
    else { //change value in map of key if key exists
        it->second = setOffset;
        setCounter++;
        FIFOsetAssHitCount++;
    }
    it = LRUsetAssMap.find(setTag);

    if (it == LRUsetAssMap.end() || it->second != setOffset) { //if the key is not present in the map
        if (LRUsetAssMap.size() < cacheSize) {
            LRUsetAssMap.insert(pair<string, string>(setTag, setOffset));
            setCounter = 0;
            LRUsetAssHitCount++;
        }
        else {

            LRUsetAssMap.insert(pair<string, string>(setTag, setOffset));
            setCounter = 0;
            LRUsetAssMissCount++;
        }
    }
    else { //change value in map of key if key exists
        it->second = setOffset;
        setCounter++;
        LRUsetAssHitCount++;
    }


}












void dMPrinter(int cacheSize){
    cout << "DirectMapped" << endl;
    cout << "Cache size: " << cacheSize << endl;
    cout << "Hits: " << directHitCount << endl;
    cout << "Misses: " << directMissCount << endl;
    float directHitRate = directHitCount / (directHitCount + directMissCount);
    cout << "Hitrate: " << directHitRate << endl;
    cout << "==================" << endl;
}

void LRUsetPrinter(int cacheSize) {
    cout << "LRU: Set Associative" << endl;
    cout << "Cache size: " << cacheSize << endl;
    cout << "Hits: " << LRUsetAssHitCount << endl;
    cout << "Misses: " << LRUsetAssMissCount << endl;
    float setAssHitRate = LRUsetAssHitCount / (LRUsetAssHitCount + LRUsetAssMissCount);
    cout << "Hitrate: " << setAssHitRate << endl;
    cout << "==================" << endl;
}

void LRUfullyPrinter(int cacheSize) {
    cout << "LRU: Fully Associative" << endl;
    cout << "Cache size: " << cacheSize << endl;
    cout << "Hits: " << LRUfullyAssHitCount << endl;
    cout << "Misses: " << LRUfullyAssMissCount << endl;
    float fullyHitRate = LRUfullyAssHitCount / (LRUfullyAssHitCount + LRUfullyAssMissCount);
    cout << "Hitrate: " << fullyHitRate << endl;
    cout << "==================" << endl;
}

void FIFOsetPrinter(int cacheSize) {
    cout << "FIFO: Set Associative" << endl;
    cout << "Cache size: " << cacheSize << endl;
    cout << "Hits: " << FIFOsetAssHitCount << endl;
    cout << "Misses: " << FIFOsetAssMissCount << endl;
    float setAssHitRate = FIFOsetAssHitCount / (FIFOsetAssHitCount + FIFOsetAssMissCount);
    cout << "Hitrate: " << setAssHitRate << endl;
    cout << "==================" << endl;
}

void FIFOfullyPrinter(int cacheSize) {
    cout << "FIFO: Fully Associative" << endl;
    cout << "Cache size: " << cacheSize << endl;
    cout << "Hits: " << FIFOfullyAssHitCount << endl;
    cout << "Misses: " << FIFOfullyAssMissCount << endl;
    float fullyHitRate = FIFOfullyAssHitCount / (FIFOfullyAssHitCount + FIFOfullyAssMissCount);
    cout << "Hitrate: " << fullyHitRate << endl;
    cout << "==================" << endl;
}


int main()
{
    string line;
    int linenumber = 0;
    char ccc;
    string sss;
    int ignore;
    string newString;
    string binaryString;
    cout << "Beginning Cache Simulation\n";
    ifstream thedangfile("gcc.trace");
    if (thedangfile.is_open()) {
        cout << "File gcc.trace is open"<< endl << endl;
        int CacheSize = 16392;
        while (getline(thedangfile, line)) {
            linenumber++;
            istringstream input(line);
            input >> ccc;
            input >> sss;
            input >> ignore;
            binaryString = hexConvertToDecimal(sss);
            
            directMapped(CacheSize,64,1, binaryString);
            fullyAss(CacheSize, 64, 1, binaryString);
            setAss(CacheSize, 64, 1, binaryString);
          //  cout << sss << endl;
           // cout << binaryVector.at(0)<<binaryVector.at(1)<<binaryVector.at(2)<<binaryVector.at(3) <<endl;

       //     for (int i = 0; i < binaryString.length(); i++){
       //         cout << binaryString.at(i);
       // }
        //    cout << endl;
            //here's where the cache part starts jfc
        //lets start with ughhhhh directmapped
            //tag is first 23 numbers //line is next 3 /// offset is remaining 6



        }
        dMPrinter(CacheSize);
       
        FIFOfullyPrinter(CacheSize);
        FIFOsetPrinter(CacheSize);
        LRUfullyPrinter(CacheSize);
        LRUsetPrinter(CacheSize);
        
    }


}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
