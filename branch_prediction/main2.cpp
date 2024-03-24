#include <bits/stdc++.h>
#include <fstream>
#include <regex>
using namespace std;


struct InstructionDetails {
    string instruction;
    int valueAfterPC;
    string PC; 
};

// use regex for matching the string to given format 
InstructionDetails Extraction(const string& line) {
    regex pattern(R"(core\s+(\d+):\s+(0x[0-9a-fA-F]+)\s+\((0x[0-9a-fA-F]+)\)\s+(b[a-z]*)\s+.*pc \+ (\d+).*)");
    smatch match;

    if (regex_match(line, match, pattern)) {
        string instruction = match[4];
        int valueAfterPC = stoi(match[5]);
        string PC = match[2];

        return {instruction, valueAfterPC, PC};
    }
    return {"", 0, ""}; 
}

string getPC(string &have) {
    vector<string> branchPCs; 

    string line = have;
        istringstream iss(line);
        string word;
        iss >> word;
        string pc;
        if (word == "core") {
            iss >> pc; 
            iss >> pc;
        }

        return pc;
}

string addHex(string& hexString, int val) {
    stringstream ss;
    ss << hex << hexString;
    unsigned int hexValue;
    ss >> hexValue;
    hexValue += val;

    stringstream result;
    result << "0x" << hex << hexValue;
    return result.str();
}

void Always_Taken_predictor(){

    ifstream fin;
    ofstream fout;
    fin.open("input.txt");
    fout.open("output.txt");
    string line;
    map<string,string> BTB;
    while(getline(fin, line)) {
        InstructionDetails details = Extraction(line);

        if (!details.instruction.empty() && details.instruction[0] == 'b') {
            string currPC = details.PC;
            string targetPC = addHex(currPC,details.valueAfterPC);
            fout<<currPC<<" "<<targetPC<<endl;
            BTB[currPC] = targetPC;
        }
    }
    // for(auto val:BTB){
    //     fout<<val.first<<" "<<val.second<<endl;
    // }

    fin.close();
}


void Always_Not_Taken_predictor(){

}
void single_bit_predictor(){

}
void double_bit_predictor(){

}
int main() {
    
   
    
    Always_Taken_predictor();
    Always_Not_Taken_predictor();
    single_bit_predictor();
    double_bit_predictor();

    return 0;
}
