#include <bits/stdc++.h>
#include <fstream>
#include <regex>
using namespace std;

// Branch History Table 
map<string,vector<string>> NT_actual;
map<string,vector<string>> NT_predicated;
map<string,vector<string>> T_actual;
map<string,vector<string>> T_predicated;
map<string,vector<string>> oneBit_actual;
map<string,vector<string>> oneBit_predicated;
map<string,vector<string>> twoBit_actual;
map<string,vector<string>> twoBit_predicated;

// STATE INITIALISATIONS
map<string,vector<string>> State_NT;
map<string,vector<string>> State_T;
map<string,vector<string>> State_oneBit;
map<string,vector<string>> State_twoBit;

// HIT or MISS
map<string,vector<string>> Hm_NT;
map<string,vector<string>> Hm_T;
map<string,vector<string>> Hm_oneBit;
map<string,vector<string>> Hm_twoBit;


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

string getPC(ifstream& file) {
    // Store the current position of the file pointer
    streampos originalPos = file.tellg();

    // Read the next line to get the PC
    string line;
    getline(file, line);
    istringstream iss(line);
    string word;
    iss >> word ;
    string pc = "";
    if (word == "core") {
        iss >> pc; 
        iss >> pc; 
    }
        // Restore the file pointer to its original position
        file.seekg(originalPos);
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
void BTB_Display(){
    ifstream fin;
    ofstream fout;
    fin.open("input.txt");
    fout.open("BTB.txt");
    string line;
    map<string,string> BTB;
    while(getline(fin, line)) {
        InstructionDetails details = Extraction(line);

        if (details.instruction[0] == 'b') {
            string currPC = details.PC;
            string targetPC = addHex(currPC,details.valueAfterPC);
            BTB[currPC] = targetPC;
        }
    }
    fout<<"*****************************Branch Target Buffer***************************\n";
    fout<<"Current PC | Target PC\n";
    fout<<"-----------------------\n";
    for(auto val:BTB){
        fout<<val.first<<" | "<<val.second<<endl;
    }

    fin.close();
    fout.close();
}

void BHT_Display(){
    ofstream fout;
    fout.open("BHT_T.txt");
    fout<<"*******************************Branch History Table***************************\n\n";
    fout<<"Always_Taken_predictor\n\n";
    int i;
    i = 1;
    for(auto val:T_predicated){
        fout<<"("<<i++<<") BHT for PC "<<val.first<<" \n";
        
        fout<<"Predicated : ";
        int sz = T_predicated[val.first].size();
        
        for(int j = 0; j < sz; j++){
            if(j == sz - 1){
                fout<<T_predicated[val.first][j];
            }
            else{
                fout<<T_predicated[val.first][j]<<" | ";
            }
        }
        fout<<endl;
        fout<<"Actual     : ";
        for(int j = 0; j < sz; j++){
            if(j == sz - 1){
                fout<<T_actual[val.first][j];
            }
            else{
                fout<<T_actual[val.first][j]<<" | ";
            }
        }
        fout<<endl;
        fout<<"Hit/Miss   : ";
        for(int j = 0; j < sz; j++){
            if(j == sz - 1){
                fout<<Hm_T[val.first][j];
            }
            else{
                fout<<Hm_T[val.first][j]<<" | ";
            }
        }
        fout<<endl;
        fout<<"State      : ";
        for(int j = 0; j < sz; j++){
            if(j == sz - 1){
                fout<<State_T[val.first][j];
            }
            else{
                fout<<State_T[val.first][j]<<" | ";
            }
        }
        fout<<"\n------------------------------------------\n";
      
    }
    
    fout.close();
    fout.open("BHT_NT.txt");
    fout<<"*******************************Branch History Table***************************\n\n";
    fout<<"Always_Not_Taken_predictor\n\n";
     i = 1;
    for(auto val:NT_predicated){
        fout<<"("<<i++<<") BHT for PC "<<val.first<<" \n";
        
        fout<<"Predicated : ";
        int sz = NT_predicated[val.first].size();
        
        for(int j = 0; j < sz; j++){
            if(j == sz - 1){
                fout<<NT_predicated[val.first][j];
            }
            else{
                fout<<NT_predicated[val.first][j]<<" | ";
            }
        }
        fout<<endl;
        fout<<"Actual     : ";
        for(int j = 0; j < sz; j++){
            if(j == sz - 1){
                fout<<NT_actual[val.first][j];
            }
            else{
                fout<<NT_actual[val.first][j]<<" | ";
            }
        }
        fout<<endl;
        fout<<"Hit/Miss   : ";
        for(int j = 0; j < sz; j++){
            if(j == sz - 1){
                fout<<Hm_NT[val.first][j];
            }
            else{
                fout<<Hm_NT[val.first][j]<<" | ";
            }
        }
        fout<<endl;
        fout<<"State      : ";
        for(int j = 0; j < sz; j++){
            if(j == sz - 1){
                fout<<State_NT[val.first][j];
            }
            else{
                fout<<State_NT[val.first][j]<<" | ";
            }
        }
        fout<<"\n------------------------------------------\n";
      
    }

}


void Always_Taken_predictor(){

    // Branch History Table Should be Printed here accordingly 
    
    // State is always fixed T , predication is also always fixed to T
    bool pred = true;
    ifstream fin("input.txt");
    string line;
    while(getline(fin,line)){
        InstructionDetails details = Extraction(line);
        if(details.instruction[0] == 'b'){
            string currPC = details.PC;
            string targetPC = addHex(currPC,details.valueAfterPC);
            string nextPC = getPC(fin);

            // two cases arises 
            if(targetPC == nextPC){
                // predication right
                T_actual[currPC].push_back("T");
                T_predicated[currPC].push_back("T");
                State_T[currPC].push_back("T");
                Hm_T[currPC].push_back("H");
            }
            else{
                // predication not right 
                T_actual[currPC].push_back("NT");
                T_predicated[currPC].push_back("T");
                State_T[currPC].push_back("T");
                Hm_T[currPC].push_back("M");
            }
        }
    }
}

void Always_Not_Taken_predictor(){
    // Branch History Table Should be Printed here accordingly 
    
    // State is always fixed NT , predication is also always fixed to NT
    bool pred = false;
    ifstream fin("input.txt");
    string line;
    while(getline(fin,line)){
        InstructionDetails details = Extraction(line);
        if(details.instruction[0] == 'b'){
            string currPC = details.PC;
            string targetPC = addHex(currPC,details.valueAfterPC);
            string nextPC = getPC(fin);
            // two cases arises 
            if(targetPC == nextPC){
               
                NT_actual[currPC].push_back("T");
                NT_predicated[currPC].push_back("NT");
                State_NT[currPC].push_back("NT");
                Hm_NT[currPC].push_back("M");
            }
            else{
                // predication not right 
                NT_actual[currPC].push_back("NT");
                NT_predicated[currPC].push_back("NT");
                State_NT[currPC].push_back("NT");
                Hm_NT[currPC].push_back("H");
            }
        }
    }
}


void single_bit_predictor(){
    // Branch History Table Should be Printed here accordingly 

}
void double_bit_predictor(){
    // Branch History Table Should be Printed here accordingly 
}


void check_Accuracy_NT(){

}
void check_Accuracy_T(){

}
void check_Accuracy_oneBit(){

}
void check_Accuracy_twoBit(){

}


int main() {
    
   
    BTB_Display();
    Always_Taken_predictor();
    Always_Not_Taken_predictor();
    single_bit_predictor();
    double_bit_predictor();
    BHT_Display();
    return 0;
}