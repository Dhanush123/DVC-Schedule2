// Programmer: Dhanush Patel
// Programmer's ID: 1553428

#define _CRT_SECURE_NO_WARNINGS

#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

#include <cstring> // for strtok and strcpy

#include "DynamicArray.h"
#include "StaticArray.h"

struct CInfo{
    string code;
    int typeTotal;
};

struct termInfo{
    string term;
    int numSectionsSeen;
    DynamicArray<string> seenSections;
};

void updateRecords(const string&, DynamicArray<CInfo>&, int&);
bool duplicateCheck(const string&, const string&, int&, StaticArray<termInfo, 200>&);

int main() {
  cout << "Programmer: Dhanush Patel\n";
  cout << "Programmer's ID: 1553428\n";
  cout << "File: " << __FILE__ << endl;

  // for parsing the inputfile
  char *token;
  char buf[1000];
  const char *const tab = "\t";

  // open the input file
  ifstream fin;
  fin.open("dvc-schedule.txt");
  if (!fin.good()) throw "I/O error";

  DynamicArray<CInfo> recordKeep;

  int dupCount = 0;
  int rKeep = 0;
  double count = 0.0;

  int aSeenIndex = 0; // to track where we are in the following "array"
  StaticArray<termInfo, 200> termsRecord; // 200 should be plenty for the number of terms

  // read the input file
  while (fin.good()) {
    count++;
    cout << (count / 74411) * 100 << "% \r";
    cout.flush();
    // read the line
    string line;
    getline(fin, line);
    strcpy(buf, line.c_str());
    if (buf[0] == 0) continue; // skip blank lines

    // parse the line
    const string term(token = strtok(buf, tab));
    const string section(token = strtok(0, tab));
    const string course((token = strtok(0, tab)) ? token : "");
    const string instructor((token = strtok(0, tab)) ? token : "");
    const string whenWhere((token = strtok(0, tab)) ? token : "");
    if (course.find('-') == string::npos) continue; // invalid line: no dash in course name
    const string subjectCode(course.begin(), course.begin() + course.find('-'));

    bool isDuplicate = duplicateCheck(term, section, aSeenIndex, termsRecord);
    if(isDuplicate){
      dupCount++;
    }
    else{
      updateRecords(subjectCode, recordKeep, rKeep);
    }
  }

  for (int i = 0; i < rKeep; i++) {
    for (int j = 0; j < rKeep; j++) {
      if (recordKeep[i].code < recordKeep[j].code)
        swap(recordKeep[i], recordKeep[j]);
    }
  }
  
  cout  << "Number of duplicates: " << dupCount << endl;

  for (int i = 0; i < recordKeep.capacity(); i++) {
    if (recordKeep[i].code == "" || recordKeep[i].typeTotal == 0) {
      continue;
    }
    cout << recordKeep[i].code << ": " << recordKeep[i].typeTotal << endl;
  }

  fin.close();
}

bool duplicateCheck(const string &term, const string &section, int &termsIndex, StaticArray<termInfo, 200> &termsRecord){
  //check if known/duplicate section in a existing term
  for(int i = 0; i < termsIndex; i++){
    if(termsRecord[i].term == term){
      for(int j = 0; j < termsRecord[i].numSectionsSeen; j++){
        if(termsRecord[i].seenSections[j] == section){
          return true;
        }
      }
      //this means couldn't find duplicate section in the given term, so adding new one to it
      termsRecord[i].seenSections[termsRecord[i].numSectionsSeen] = section;
      termsRecord[i].numSectionsSeen++;
      return false;
    }
  }
  //this means that term doesn't exist, so will have to make new term and add section
  termsRecord[termsIndex].term = term;
  termsRecord[termsIndex].numSectionsSeen++;
  termsRecord[termsIndex].seenSections[0] = section;
  //updating how many terms exist
  termsIndex++;
  return false;
}

void updateRecords(const string &course, DynamicArray<CInfo> &rk, int &used) {
  bool found = false;
  for (int i = 0; i < used; i++) {
    if (rk[i].code == course) {
      rk[i].typeTotal++;
      found = true;
      break;
    }
  }
  if (!found) {
    CInfo ci;
    ci.code = course;
    ci.typeTotal = 1;
    rk[used] = ci;
    used++;
  }
}