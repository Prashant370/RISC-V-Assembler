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

InstructionDetails Extraction(string& line) {
    istringstream iss(line);
    string token;

    iss >> token; // core
    iss >> token; // 0:
    iss >> token; // PC 
    string PC ="";
    string sign;
    int valueAfterPC = 0;
    string instruction ="";
    PC = token;
    iss >> token; // (MC)
    iss >> token; // instruction
    
    instruction = token;
    if(instruction[0] == 'b'){
        while (iss >> token && token != "pc") {}
        string sign;
        iss >> token; // sign
        sign = token;
        
        iss >> token;
        valueAfterPC = stoi(token);

        if(sign == "-") valueAfterPC *= -1; 
    }


    return {instruction,valueAfterPC,PC};
}




string getPC(string have) {
    // Store the current position of the file pointer
    ifstream fin("input.txt");
    string line;
    string pc = "";
    while(getline(fin,line)){
        if(line == have){
            getline(fin,line);
            istringstream iss(line);
            string word;
            iss >> word ;
            if (word == "core") {
                iss >> pc; 
                iss >> pc; 
            }
            break;
        }
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
void BTB_Display(){
    ifstream fin;
    ofstream fout;
    fin.open("input.txt");
    fout.open("BTB.txt");
    string line;
    map<string,string> BTB;
    while(getline(fin, line)) {
        InstructionDetails details = Extraction(line);
        
        //cout<<details.instruction<<" "<<details.valueAfterPC<<" "<<details.PC<<endl;
        if (details.instruction[0] == 'b') {
            //cout<<details.instruction<<endl;
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
        
        fout<<"Predicted : ";
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

    fout.close();

    fout.open("BHT_oneBit.txt");
    fout<<"*******************************Branch History Table***************************\n\n";
    fout<<"One_Bit_predictor\n\n";
     i = 1;
    for(auto val:oneBit_predicated){
        fout<<"("<<i++<<") BHT for PC "<<val.first<<" \n";
        
        fout<<"Predicated : ";
        int sz = oneBit_predicated[val.first].size();
        
        for(int j = 0; j < sz; j++){
            if(j == sz - 1){
                fout<<oneBit_predicated[val.first][j];
            }
            else{
                fout<<oneBit_predicated[val.first][j]<<" | ";
            }
        }
        fout<<endl;
        fout<<"Actual     : ";
        for(int j = 0; j < sz; j++){
            if(j == sz - 1){
                fout<<oneBit_actual[val.first][j];
            }
            else{
                fout<<oneBit_actual[val.first][j]<<" | ";
            }
        }
        fout<<endl;
        fout<<"Hit/Miss   : ";
        for(int j = 0; j < sz; j++){
            if(j == sz - 1){
                fout<<Hm_oneBit[val.first][j];
            }
            else{
                fout<<Hm_oneBit[val.first][j]<<" | ";
            }
        }
        fout<<endl;
        fout<<"State      : ";
        for(int j = 0; j < sz; j++){
            if(j == sz - 1){
                fout<<State_oneBit[val.first][j];
            }
            else{
                fout<<State_oneBit[val.first][j]<<" | ";
            }
        }
        fout<<"\n------------------------------------------\n";
      
    }
    fout.close();
    fout.open("BHT_twoBit.txt");
    fout<<"*******************************Branch History Table***************************\n\n";
    fout<<"Two_Bit_predictor\n\n";
     i = 1;
    for(auto val:twoBit_predicated){
        fout<<"("<<i++<<") BHT for PC "<<val.first<<" \n";
        
        fout<<"Predicated : ";
        int sz = twoBit_predicated[val.first].size();
        
        for(int j = 0; j < sz; j++){
            if(j == sz - 1){
                fout<<twoBit_predicated[val.first][j];
            }
            else{
                fout<<twoBit_predicated[val.first][j]<<" | ";
            }
        }
        fout<<endl;
        fout<<"Actual     : ";
        for(int j = 0; j < sz; j++){
            if(j == sz - 1){
                fout<<twoBit_actual[val.first][j];
            }
            else{
                fout<<twoBit_actual[val.first][j]<<" | ";
            }
        }
        fout<<endl;
        fout<<"Hit/Miss   : ";
        for(int j = 0; j < sz; j++){
            if(j == sz - 1){
                fout<<Hm_twoBit[val.first][j];
            }
            else{
                fout<<Hm_twoBit[val.first][j]<<" | ";
            }
        }
        fout<<endl;
        fout<<"State      : ";
        for(int j = 0; j < sz; j++){
            if(j == sz - 1){
                fout<<State_twoBit[val.first][j];
            }
            else{
                fout<<State_twoBit[val.first][j]<<" | ";
            }
        }
        fout<<"\n------------------------------------------\n";
      
    }

}


void Always_Taken_predictor(){

    // Branch History Table Should be Printed here accordingly 
    
    // State is always fixed T , predication is also always fixed to T
    bool pred = true;
    ifstream fin("input.txt"); // curr 
    ifstream finn("input.txt"); // next
    string line2;
    getline(finn,line2);

    string line;
    while(getline(fin,line)){
        getline(finn,line2); // next line
        //cout<<line<<endl;
        InstructionDetails details = Extraction(line);
        InstructionDetails details2 = Extraction(line2);
        if(details.instruction[0] == 'b'){
            string currPC = details.PC;
            string targetPC = addHex(currPC,details.valueAfterPC);
            string nextPC ;
            nextPC = details2.PC;
            
            // string s;
            // getline(fin,s);
            // cout<<s<<endl;
            // two cases arises 
            if(targetPC == nextPC){
           // cout<<currPC<<" "<<targetPC<<" "<<nextPC<<endl;
                // predication right
               // cout<<T_actual.size()<<endl;
                T_actual[currPC].push_back("T");
                T_predicated[currPC].push_back("T");
                State_T[currPC].push_back("T");
                Hm_T[currPC].push_back("H");
                //if(T_actual["0x80005b98"].size() > 0) cout<<T_actual["0x80005b98"][0];
            }
            else{
                // cout<<currPC<<" "<<targetPC<<" "<<nextPC<<endl;
                //  cout<<currPC<<" "<<nextPC<<endl;
                // predication not right 
                T_actual[currPC].push_back("NT");
                T_predicated[currPC].push_back("T");
                State_T[currPC].push_back("T");
                Hm_T[currPC].push_back("M");
                //cout<<T_actual.size()<<endl;
                //if(T_actual["0x80005b98"].size() > 0) cout<<T_actual["0x80005b98"][0];
            }
        }
        
        //cout<<T_actual.size()<<endl;
    }
}

void Always_Not_Taken_predictor(){
    // Branch History Table Should be Printed here accordingly 
    
    // State is always fixed NT , predication is also always fixed to NT
    bool pred = false;
    ifstream fin("input.txt");
    ifstream finn("input.txt"); // next
    string line2;
    getline(finn,line2);
    string line;
    while(getline(fin,line)){
        getline(finn,line2);
        InstructionDetails details = Extraction(line);
        InstructionDetails details2 = Extraction(line2);
        if(details.instruction[0] == 'b'){
            string currPC = details.PC;
            string targetPC = addHex(currPC,details.valueAfterPC);
            string nextPC = details2.PC;
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
    map<string,string> pred;
    map<string,string> state;

    ifstream fin("input.txt");

    string line;
    // local Branch Predication that's why we need map to get locally predicted values
    while(getline(fin,line)){
        InstructionDetails details = Extraction(line);
        if(details.instruction[0] == 'b'){
            string currPC = details.PC;
            pred[currPC] = "NT";
            state[currPC] = "NT";
        }
    }

    fin.close();
    line.clear();
    fin.open("input.txt");
    ifstream finn("input.txt"); // next
    string line2;
    getline(finn,line2);
    while(getline(fin,line)){
        getline(finn,line2);
        InstructionDetails details = Extraction(line);
        InstructionDetails details2 = Extraction(line2);
        if(details.instruction[0] == 'b'){
            string currPC = details.PC;
            string targetPC = addHex(currPC,details.valueAfterPC);
            string nextPC = details2.PC;
            // two cases arises 
            if(targetPC == nextPC){
                // T
                if(pred[currPC] == "T"){
                    oneBit_actual[currPC].push_back("T");
                    oneBit_predicated[currPC].push_back("T");
                    State_oneBit[currPC].push_back("T");
                    Hm_oneBit[currPC].push_back("H");
                }
                else{
                    oneBit_actual[currPC].push_back("T");
                    oneBit_predicated[currPC].push_back("NT");
                    State_oneBit[currPC].push_back("NT");
                    Hm_oneBit[currPC].push_back("M");
                }
                pred[currPC] = state[currPC] = "T";
            }
            else{
                // NT
                if(pred[currPC] == "T"){
                    oneBit_actual[currPC].push_back("NT");
                    oneBit_predicated[currPC].push_back("T");
                    State_oneBit[currPC].push_back("T");
                    Hm_oneBit[currPC].push_back("M");                
                }
                else{
                    oneBit_actual[currPC].push_back("NT");
                    oneBit_predicated[currPC].push_back("NT");
                    State_oneBit[currPC].push_back("NT");
                    Hm_oneBit[currPC].push_back("H");
                }
                pred[currPC] = state[currPC] = "NT";

            }
        }
    }
}
void double_bit_predictor(){
    // Branch History Table Should be Printed here accordingly 
    map<string,string> pred;
    map<string,string> state;

    ifstream fin;
    fin.open("input.txt");
    string line;
    // local Branch Predication that's why we need map to get locally predicted values
    while(getline(fin,line)){
        InstructionDetails details = Extraction(line);
        if(details.instruction[0] == 'b'){
            string currPC = details.PC;
            pred[currPC] = "NT";
            state[currPC] = "NT,NT";
        }
    }

    fin.close();
    line.clear();
    fin.open("input.txt");
    ifstream finn("input.txt"); // next
    string line2;
    getline(finn,line2);
    while(getline(fin,line)){
        getline(finn,line2);
        InstructionDetails details = Extraction(line);
        InstructionDetails details2 = Extraction(line2);
        if(details.instruction[0] == 'b'){
            string currPC = details.PC;
            string targetPC = addHex(currPC,details.valueAfterPC);
            string nextPC = details2.PC;
            // two cases arises 
            if(targetPC == nextPC){
                // T
                if(pred[currPC] == "T"){
                    twoBit_actual[currPC].push_back("T");
                    twoBit_predicated[currPC].push_back("T");
                    Hm_twoBit[currPC].push_back("H");
                    State_twoBit[currPC].push_back(state[currPC]);

                    if(state[currPC] == "NT,NT"){ // 00
                       state[currPC] = "NT,T";
                       pred[currPC] = "NT";
                    }
                    else if(state[currPC] == "NT,T"){ // 01
                        state[currPC] = "T,NT";
                        pred[currPC] = "T";
                    }
                    else if(state[currPC] == "T,NT"){ // 10
                        state[currPC] = "T,T";
                        pred[currPC] = "T";
                    }
                    else if(state[currPC] == "T,T"){ // 11
                        state[currPC] = "T,T";
                        pred[currPC] = "T";
                    }

                }
                else{
                    twoBit_actual[currPC].push_back("T");
                    twoBit_predicated[currPC].push_back("NT");
                    Hm_twoBit[currPC].push_back("M");
                    State_twoBit[currPC].push_back(state[currPC]);

                    if(state[currPC] == "NT,NT"){ // 00
                       state[currPC] = "NT,T";
                       pred[currPC] = "NT";
                    }
                    else if(state[currPC] == "NT,T"){ // 01
                        state[currPC] = "T,NT";
                        pred[currPC] = "T";
                    }
                    else if(state[currPC] == "T,NT"){ // 10
                        state[currPC] = "T,T";
                        pred[currPC] = "T";
                    }
                    else if(state[currPC] == "T,T"){ // 11
                        state[currPC] = "T,T";
                        pred[currPC] = "T";
                    }

                }
            
            }
            else{
                // NT
                if(pred[currPC] == "T"){
                    twoBit_actual[currPC].push_back("NT");
                    twoBit_predicated[currPC].push_back("T");
                    State_twoBit[currPC].push_back(state[currPC]);
                    Hm_twoBit[currPC].push_back("M");    

                    if(state[currPC] == "NT,NT"){ // 00
                       state[currPC] = "NT,NT";
                       pred[currPC] = "NT";
                    }
                    else if(state[currPC] == "NT,T"){ // 01
                        state[currPC] = "NT,NT";
                        pred[currPC] = "NT";
                    }
                    else if(state[currPC] == "T,NT"){ // 10
                        state[currPC] = "NT,T";
                        pred[currPC] = "NT";
                    }
                    else if(state[currPC] == "T,T"){ // 11
                        state[currPC] = "T,NT";
                        pred[currPC] = "T";
                    }
            
                }
                else{
                    twoBit_actual[currPC].push_back("NT");
                    twoBit_predicated[currPC].push_back("NT");
                    State_twoBit[currPC].push_back(state[currPC]);
                    Hm_twoBit[currPC].push_back("H");
                    if(state[currPC] == "NT,NT"){ // 00
                       state[currPC] = "NT,NT";
                       pred[currPC] = "NT";
                    }
                    else if(state[currPC] == "NT,T"){ // 01
                        state[currPC] = "NT,NT";
                        pred[currPC] = "NT";
                    }
                    else if(state[currPC] == "T,NT"){ // 10
                        state[currPC] = "NT,T";
                        pred[currPC] = "NT";
                    }
                    else if(state[currPC] == "T,T"){ // 11
                        state[currPC] = "T,NT";
                        pred[currPC] = "T";
                    }

                }
            }
        }
    }
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
