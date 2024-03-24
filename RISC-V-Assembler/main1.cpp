#include <bits/stdc++.h>
using namespace std;
#define ll long long
#include <fstream>
ofstream fout;
ifstream fin;
vector<vector<char>> memory(8192,vector<char>(8,'0'));// 0x10000000 to 0x10007FFC
bool error = false;
ll pc = 0; // program counter starts with 0x00000000
vector<string> final;
string having;
unordered_map <string, int> label;
ll dc = 268468220; // data counter satrts with 0x10000000 ends with 0x10007FFC 
// dc -= 4



map<string, string> riscv_registers = {
    {"x0", "x0"},
    {"x1", "x1"},
    {"x2", "x2"},
    {"x3", "x3"},
    {"x4", "x4"},
    {"x5", "x5"},
    {"x6", "x6"},
    {"x7", "x7"},
    {"x8", "x8"},
    {"x9", "x9"},
    {"x10", "x10"},
    {"x11", "x11"},
    {"x12", "x12"},
    {"x13", "x13"},
    {"x14", "x14"},
    {"x15", "x15"},
    {"x16", "x16"},
    {"x17", "x17"},
    {"x18", "x18"},
    {"x19", "x19"},
    {"x20", "x20"},
    {"x21", "x21"},
    {"x22", "x22"},
    {"x23", "x23"},
    {"x24", "x24"},
    {"x25", "x25"},
    {"x26", "x26"},
    {"x27", "x27"},
    {"x28", "x28"},
    {"x29", "x29"},
    {"x30", "x30"},
    {"x31", "x31"},
    {"zero", "x0"},
    {"ra", "x1"},
    {"sp", "x2"},
    {"gp", "x3"},
    {"tp", "x4"},
    {"t0", "x5"},
    {"t1", "x6"},
    {"t2", "x7"},
    {"s0", "x8"},
    {"s1", "x9"},
    {"a0", "x10"},
    {"a1", "x11"},
    {"a2", "x12"},
    {"a3", "x13"},
    {"a4", "x14"},
    {"a5", "x15"},
    {"a6", "x16"},
    {"a7", "x17"},
    {"s2", "x18"},
    {"s3", "x19"},
    {"s4", "x20"},
    {"s5", "x21"},
    {"s6", "x22"},
    {"s7", "x23"},
    {"s8", "x24"},
    {"s9", "x25"},
    {"s10", "x26"},
    {"s11", "x27"},
    {"t3", "x28"},
    {"t4", "x29"},
    {"t5", "x30"},
    {"t6", "x31"}
};

string binaryToHex(string& binary) { 
    // Convert binary string to hexadecimal
    if(error == true) return "";
    stringstream ss;
    ss << hex << setw(8) << setfill('0')<< bitset<32>(binary).to_ulong();

    // Add "0x" prefix to the hexadecimal string
    string hex = ss.str();
    hex = "0x" + hex;
    transform(hex.begin() + 2, hex.end(), hex.begin() + 2, ::toupper);
    return hex;
}
string decimalToBinary(int decimalNumber) {
    if(error == true) return "";
    string binaryNumber = "";
    for (int i = 4; i >= 0; i--) {
        int bit = (decimalNumber >> i) & 1;
        binaryNumber += to_string(bit);
    }
    return binaryNumber;
}
string intToHex(int number) {
    stringstream stream;
    stream << "0x" << uppercase << setfill('0') << setw(8) << hex << number;
    return stream.str();
}

void getopCode(string have, string &s){ // For R,I,S,SB,U,UJ Format
    if(error) return;
    if(have == "add" || have == "and" || have == "or"|| have == "sll"|| have == "slt"|| have == "sra"
        || have == "srl"|| have == "sub"|| have == "xor"|| have == "mul"|| have == "div"|| have == "rem")
        s+="0110011";
    else if(have == "andi" || have == "addi" || have == "ori") s+="0010011";
    else if(have == "lb" || have == "ld" || have == "lh"|| have == "lw") s+="0000011";
    else if(have == "jalr") s+="1100111";
    else if (have == "sb" || have == "sw"|| have == "sd" || have == "sh") s+="0100011";
    else if (have == "beq" || have == "bne"|| have == "bge" || have == "blt") s+="1100011";
    else if (have == "auipc") s+="0010111";
    else if (have == "lui") s+="0110111";
    else if (have == "jal") s+="1101111";

    
}
void getFunc3(string have, string &s){  // For R,I,S,SB Format
    if(error) return;
    if(have == "add" ||have == "sub" ||have == "lb" ||have == "jalr" || have == "beq"|| have == "sb" || have == "addi"){
        s+="000";
    }
    else if(have == "sll" ||have == "lh" || have == "sh" || have == "bne" ){
        s+="001";
    }
    else if(have == "slt" || have == "lw" || have == "sw" ){
        s+="010";
    }
    else if(have == "ld"){
        s+="011";
    }
    else if(have == "blt" || have == "xor"){
        s+="100";
    }
    else if(have == "srl" || have == "sra"||have == "bge"){
        s+="101";
    }
    else if(have == "or" || have == "ori"){
        s+="110";
    }
    else if(have == "and" || have == "andi"){
        s+="111";
    }
   
}
void getFunc7(string have, string &s){ // For R Format
     if(error) return;
     if(have == "add" || have == "or" || have == "sll" || have == "slt"|| have == "srl"|| have == "xor" ) s+="0000000";
     else if( have == "and"|| have == "sra"|| have == "sub") s+="0100000";
     

}

string immediateToBinary12(string& immediate) {
    // Check if the immediate value is in decimal, binary, or hexadecimal format
    if(error == true) return "";
    ll value;
    if (immediate.substr(0, 2) == "0b") {
        // Binary format
        value = stoll(immediate.substr(2), nullptr, 2);
    } else if (immediate.substr(0, 2) == "0x") {
        // Hexadecimal format
        value = stoll(immediate.substr(2), nullptr, 16);
    } else {
        // Decimal format
        value = stoll(immediate);
    }
    if(value >= 2048 || value <= -2049){
        fout<<"\n\n*****Error Detected*****\n\n";
        fout<<"*****Value Overflow*****\n\n";
        error = true;
        return "Error";     
    }
    // Convert the value to a 12-bit binary string
    bitset<12> bits(value);
    return bits.to_string();
}

string immediateToBinary13(string& immediate) {
    // Check if the immediate value is in decimal, binary, or hexadecimal format
    if(error == true) return "";
    ll value;
    if (immediate.substr(0, 2) == "0b") {
        // Binary format
        value = stoll(immediate.substr(2), nullptr, 2);
    } else if (immediate.substr(0, 2) == "0x") {
        // Hexadecimal format
        value = stoll(immediate.substr(2), nullptr, 16);
    } else {
        // Decimal format
        value = stoll(immediate);
    }
    if(value >= 4096 || value <= -4097){
        fout<<"\n\n*****Error Detected*****\n\n";
        fout<<"*****Value Overflow*****\n\n";
        error = true;
        return "Error";     
    }
    // Convert the value to a 12-bit binary string
    bitset<13> bits(value);
    return bits.to_string();
}
string immediateToBinary20(string& immediate) {
    if(error == true) return "";
    // Check if the immediate value is in decimal, binary, or hexadecimal format
    ll value;
    if (immediate.substr(0, 2) == "0b") {
        // Binary format
        value = stoll(immediate.substr(2), nullptr, 2);
    } else if (immediate.substr(0, 2) == "0x") {
        // Hexadecimal format
        value = stoll(immediate.substr(2), nullptr, 16);
    } else {
        // Decimal format
        value = stoll(immediate);
    }

    if(value >= 1048576 || value <= -1){
        fout<<"\n\n*****Error Detected*****\n\n";
        fout<<"*****Value Overflow*****\n\n";
        error = true;
        return "Error";     
    }
    // Convert the value to a 12-bit binary string
    bitset<20> bits(value);
    return bits.to_string();
}
string immediateToBinary21(string& immediate) {
    if(error == true) return "";
    // Check if the immediate value is in decimal, binary, or hexadecimal format
    ll value;
    if (immediate.substr(0, 2) == "0b") {
        // Binary format
        value = stoll(immediate.substr(2), nullptr, 2);
    } else if (immediate.substr(0, 2) == "0x") {
        // Hexadecimal format
        value = stoll(immediate.substr(2), nullptr, 16);
    } else {
        // Decimal format
        value = stoll(immediate);
        
    }
    // never overflows

    // Convert the value to a 12-bit binary string
    bitset<21> bits(value);
    return bits.to_string();
}
void getImmediateI(string have, string &s){ // For I,S,SB,U,UJ Format
    if(error == true) return ;
    if(have[0] == 'x'){
        fout<<"\n\n*****Error Detected*****\n\n";
        fout<<"*****This is not Immediate Value*****\n\n";
        error = true;
        return;
    }
    // have can be in any format
    s+=immediateToBinary12(have);
}
void getImmediateSlast(string have, string &s){ // For I,S,SB,U,UJ Format
    // have can be in any format
    if(error == true) return;
    if(have[0] == 'x'){
        fout<<"\n\n*****Error Detected*****\n\n";
        fout<<"*****This is not Immediate Value*****\n\n";
        error = true;
        return;
    }
    string bin = immediateToBinary12(have); 

    for(int i = 0; i <= 6 ;i++){
        s.push_back(bin[i]);
    }
}
void getImmediateSfirst(string have, string &s){ // For I,S,SB,U,UJ Format
    // have can be in any format
    if(error == true) return ;
    if(have[0] == 'x'){
        fout<<"\n\n*****Error Detected*****\n\n";
        fout<<"*****This is not Immediate Value*****\n\n";
        error = true;
        return;
    }
    string bin = immediateToBinary12(have); 
    for(int i = 7; i <= 11 ;i++){
        s.push_back(bin[i]);
    }
}

void getImmediateSBlast(string have, string &s){ // For I,S,SB,U,UJ Format
    // have can be in any format
    if(error == true) return;
    if(have[0] == 'x'){
        fout<<"\n\n*****Error Detected*****\n\n";
        fout<<"*****This is not Immediate Value*****\n\n";
        error = true;
        return;
    }
    string bin = immediateToBinary13(have); 
    s.push_back(bin[0]);
    for(int i = 2; i <= 7 ;i++){
        s.push_back(bin[i]);
    }
}

void getImmediateSBfirst(string have, string &s){ // For I,S,SB,U,UJ Format
    // have can be in any format
    if(error == true) return ;
    if(have[0] == 'x'){
        fout<<"\n\n*****Error Detected*****\n\n";
        fout<<"*****This is not Immediate Value*****\n\n";
        error = true;
        return;
    }
    string bin = immediateToBinary13(have); 
    for(int i = 8; i <= 11 ;i++){
        s.push_back(bin[i]);
    }
    s.push_back(bin[1]);
}
void getImmediateU(string have, string &s){ // For I,S,SB,U,UJ Format
    // have can be in any format
    if(error == true) return ;
    if(have[0] == 'x'){
        fout<<"\n\n*****Error Detected*****\n\n";
        fout<<"*****This is not Immediate Value*****\n\n";
        error = true;
        return;
    }
    string bin = immediateToBinary20(have); 
    for(int i = 0; i <= 19 ;i++){
        s.push_back(bin[i]);
    }
    
}
void getImmediateUJ(string have, string &s){ // For I,S,SB,U,UJ Format
    // have can be in any format
    if(error == true) return ;
    if(have[0] == 'x'){
        fout<<"\n\n*****Error Detected*****\n\n";
        fout<<"*****This is not Immediate Value*****\n\n";
        error = true;
        return;
    }
    string bin = immediateToBinary21(have); 
    s.push_back(bin[0]);
    for(int i = 10; i <= 19 ;i++){
        s.push_back(bin[i]);
    }
    s.push_back(bin[9]);
    for(int i = 1; i <= 8 ;i++){
        s.push_back(bin[i]);
    }
    
}


void getRegisterValue(string have, string &s){ // For R,I,S,SB,,U,UJ Format
    if(error) return;
    have = riscv_registers[have];
    if(have[0] != 'x'){
         
        fout<<"\n\n*****Error Detected*****\n\n";
        fout<<"*****Register Name is Wrong, Make sure spaces are there*****\n\n";
        error = true;
        return;
    }
    have.erase(have.begin());  // Erase the first character that is x
   
   
    // check for integer input 
    int flag = 0;
    for (int i = 0; i < have.size(); i++){
        ll get = have[i] - '0';
        if (get > 9 || get < 0)
        {
            flag++;
            break;
        }
    }
    if (flag) {
        error = true;
        return ;
    }
    ll temp = stoll(have);
    if(temp >= 32 || temp < 0) {
      
        fout<<"\n\n*****Error Detected*****\n\n";
        fout<<"*****Register Not Found*****\n\n";
        error = true;
        return;
    }
    // here temp is integer only other possibilites are revoked above
     s+=decimalToBinary(temp);
     
}

string Formatdecider(string have){
    if(error == true) return "";
    if(have == "add" ||have == "and" ||have == "or" ||have == "sll" ||have == "slt" ||have == "sra" ||
        have == "srl" ||have == "sub" ||have == "xor" ||have == "mul" ||have == "div" ||have == "rem") return "R";
    else if (have == "addi"||have == "andi" ||have == "ori" ||have == "lb" ||have == "ld" ||have == "lh" ||have == "lw" ||
            have == "jalr") return "I";
    else if (have == "sb"||have == "sw" ||have == "sd" ||have == "sh") return "S";
    else if(have == "beq" ||have == "bne" ||have == "bge" ||have == "blt") return "SB";
    else if(have == "auipc" ||have == "lui") return "U";
    else if(have == "jal") return "UJ";
    else return "NULL";
}
void helper_R(string sentence){
     if(error) return;
        istringstream iss(sentence);
        string word;
        int count = 1;
        string command,rs1,rs2,rd;
        // add x3, x5 , x6
        while(iss >> word){
            
            if(word == ",") continue;
            if(word[word.size()-1] == ',' ) word.pop_back(); 
            
            if(count == 1) {
                command = word;
                count++;
                continue;
            }
            if(count == 2){
                rd = word;
                count++;
                continue;
            }
            if(count == 3){
                rs1 = word;
                count++;
                continue;
            }
            if(count == 4){
                rs2 = word;
                count++;
                continue;
            }
            count++;
        }
        
        if(count != 5){
            fout<<"\n\n*****Error Detected*****\n\n";
            fout<<"*****It requires 3 arguments, make sure spaces are there*****\n\n";
            error = true;
            return;
        }
        string ans;
        getFunc7(command,ans);
        getRegisterValue(rs2,ans);
        getRegisterValue(rs1,ans);
        getFunc3(command,ans);
        getRegisterValue(rd,ans);
        getopCode(command,ans);
        having = binaryToHex(ans);
        
}

void helper_I(string sentence){
    if(error) return;
        istringstream iss(sentence);
        string word;
        iss >> word;
        if(word == "addi" || word == "andi" || word == "ori" || word == "jalr"){
            // normal one easiest
            istringstream iss(sentence);
            string word;
            int count = 1;
            string command,rs1,rd,imm;
         // addi x3, x0 , 5  ||| jalr x1, x0 , 4 ;; 4 act as offset
        while(iss >> word){
            
            if(word == ",") continue;
            if(word[word.size()-1] == ',' ) word.pop_back(); 
            
            if(count == 1) {
                command = word;
                count++;
                continue;
            }
            if(count == 2){
                rd = word;
                count++;
                continue;
            }
            if(count == 3){
                rs1 = word;
                count++;
                continue;
            }
            if(count == 4){
                imm = word;
                count++;
                continue;
            }
            count++;
        }
            string ans;
        if(count != 5){
            fout<<"\n\n*****Error Detected*****\n\n";
            fout<<"*****It requires 3 arguments, make sure spaces are there*****\n\n";
            error = true;
            return;
        }
        
            getImmediateI(imm,ans);
            getRegisterValue(rs1,ans);
            getFunc3(command,ans);
            getRegisterValue(rd,ans);
            getopCode(command,ans);
            
            having = binaryToHex(ans);
        
        }
        else{
            // having offset lw x5, 4(x3)  --> NOT supported
            // lw x5 4 x3 :: lw x5, 4 (  x3 )  --> supported
            istringstream iss(sentence);
            string word;
            int count = 1;
            string command,rs1,rd,imm;
       
            while(iss >> word){
               string keep; 
            if(word == "," || word == ")" || word == "(") continue;
            if(word[word.size()-1] == ',' ) word.pop_back(); 
            if(word[word.size()-1] == ')' ) word.pop_back(); 
            if(word[0] == '(' ) {
                for(int i = 1; i < word.size();i++) keep.push_back(word[i]);
                word = keep;
                if(word == "x") {
                    // as it is separated from original register
                    fout<<"\n\n*****Error Detected*****\n\n";
                    fout<<"*****Register Not Found*****\n\n";
                    error = true;
                    return;          
                }
            }
            
            if(count == 1) {
                command = word;
                count++;
                continue;
            }
            if(count == 2){
                rd = word;
                count++;
                continue;
            }
            if(count == 3){
                imm = word;
                count++;
                continue;
            }
            if(count == 4){
                rs1 = word;
                count++;
                continue;
            }
            count++;
        }
        if(count != 5){
            fout<<"\n\n*****Error Detected*****\n\n";
            fout<<"*****It requires 3 arguments, make sure spaces are there*****\n\n";
            error = true;
            return;
        }
            string ans;
    
            getImmediateI(imm,ans);
            getRegisterValue(rs1,ans);
            getFunc3(command,ans);
            getRegisterValue(rd,ans);
            getopCode(command,ans);
            having = binaryToHex(ans);
            
        }
   
}

void helper_S(string sentence){
        // having offset sw x5, 4(x3)  --> NOT supported
        // sw x5 4 x3 :: sw x5, 4 (  x3 )  --> supported
        if(error == true) return ;
        istringstream iss(sentence);
        string word;
        int count = 1;
        string command,rs1,rs2,imm;

        while(iss >> word){
            string keep; 
        if(word == "," || word == ")" || word == "(") continue;
        if(word[word.size()-1] == ',' ) word.pop_back(); 
        if(word[word.size()-1] == ')' ) word.pop_back(); 
        if(word[0] == '(' ) {
            for(int i = 1; i < word.size();i++) keep.push_back(word[i]);
            word = keep;
            if(word == "x") {
                // as it is separated from original register
                fout<<"\n\n*****Error Detected*****\n\n";
                fout<<"*****Register Not Found*****\n\n";
                error = true;
                return;          
            }
        }
       
        if(count == 1) {
            command = word;
            count++;
            continue;
        }
        if(count == 2){
            rs2 = word;
            count++;
            continue;
        }
        if(count == 3){
            imm = word;
            count++;
            continue;
        }
        if(count == 4){
            rs1 = word;
            count++;
            continue;
        }
        count++;
    }
        if(count != 5){
            fout<<"\n\n*****Error Detected*****\n\n";
            fout<<"*****It requires 3 arguments, make sure spaces are there*****\n\n";
            error = true;
            return;
        }
        string ans;
    
        getImmediateSlast(imm,ans);
        getRegisterValue(rs2,ans);
        getRegisterValue(rs1,ans);
        getFunc3(command,ans);
        getImmediateSfirst(imm,ans);
        getopCode(command,ans);
        having = binaryToHex(ans);
}

// two case direct imm or labelwise in SB , U , UJ format

void helper_SB(string sentence){
    if(error == true) return ;
    // can have any label or direct immediate value
    // label[***] - current pc = imm
    // value can be negative  --> can be overflow take care

        // beq rs1, rs2, label/imm
        istringstream iss(sentence);
        string word;
        int count = 1;
        string command,rs1,rs2,imm,tag;

        while(iss >> word){
            string keep; 
        if(word == "," || word == ")" || word == "(") continue;
        if(word[word.size()-1] == ',' ) word.pop_back(); 
        if(word[word.size()-1] == ')' ) word.pop_back(); 
        if(word[0] == '(' ) {
            for(int i = 1; i < word.size();i++) keep.push_back(word[i]);
            word = keep;
            if(word.size() == 1) {
                // as it is separated from original register
                fout<<"\n\n*****Error Detected*****\n\n";
                fout<<"*****Register Not Found*****\n\n";
                error = true;
                return;          
            }
        }
       
        if(count == 1) {
            command = word;
            count++;
            continue;
        }

        if(count == 2){
            rs1 = word;
            count++;
            continue;
        }
        if(count == 3){
            rs2 = word;
            count++;
            continue;
        }
        if(count == 4){
            tag = word;
            count++;
            continue;
        }
        count++;
    }
        if(count != 5){
            fout<<"\n\n*****Error Detected*****\n\n";
            fout<<"*****It requires 3 arguments, make sure spaces are there*****\n\n";
            error = true;
            return;
        }
        string ans;
        // tag can contains imm value or label that we have in our map
       

        if(label.find(tag) != label.end()){
            // tag found
            
           // cout<<"okay "<<label[tag]<<" "<<pc<<endl;
            imm = to_string(label[tag] - pc);
            //cout<<imm<<endl;
        }
        else imm = tag;
  
        getImmediateSBlast(imm,ans);
        getRegisterValue(rs2,ans);
        getRegisterValue(rs1,ans);
        getFunc3(command,ans);
        getImmediateSBfirst(imm,ans);
        getopCode(command,ans);
        having = binaryToHex(ans);
}
void helper_U(string sentence){
    if(error == true) return;
    // can have any label or direct immediate value
    // label [***] = imm  {both lui and auipc acts like this}
    // value can't be negative  --> can be overflow take care


        istringstream iss(sentence);
        string word;
        int count = 1;
        string command,rd,tag,imm;

        while(iss >> word){
            string keep; 
        if(word == "," || word == ")" || word == "(") continue;
        if(word[word.size()-1] == ',' ) word.pop_back(); 
        if(word[word.size()-1] == ')' ) word.pop_back(); 
        if(word[0] == '(' ) {
            for(int i = 1; i < word.size();i++) keep.push_back(word[i]);
            word = keep;
            if(word.size() == 1) {
                // as it is separated from original register
                fout<<"\n\n*****Error Detected*****\n\n";
                fout<<"*****Register Not Found*****\n\n";
                error = true;
                return;          
            }
        }
       
        if(count == 1) {
            command = word;
            count++;
            continue;
        }
        if(count == 2){
            rd = word;
            count++;
            continue;
        }
        if(count == 3){
            tag = word;
            count++;
            continue;
        }
        count++;
       
    }
        if(count != 4){
            fout<<"\n\n*****Error Detected*****\n\n";
            fout<<"*****It requires 3 arguments, make sure spaces are there*****\n\n";
            error = true;
            return;
        }
        string ans;
        // tag can contains imm value or label that we have in our map
       

        if(label.find(tag) != label.end()){
            // tag found
            
           // cout<<"okay "<<label[tag]<<" "<<pc<<endl;
            imm = to_string(label[tag]);
            //cout<<imm<<endl;
        }
        else imm = tag;
     
        // cout<<imm<<endl;
        getImmediateU(imm,ans);
        getRegisterValue(rd,ans);
        getopCode(command,ans);
        
        having = binaryToHex(ans);
}

void helper_UJ(string sentence){
    if(error == true) return ;
    // can have any label or direct immediate value
    // label[***] - current pc = imm 
    // value can be negative --> never overflow
        istringstream iss(sentence);
        string word;
        int count = 1;
        string command,rd,tag,imm;

        while(iss >> word){
            string keep; 
        if(word == "," || word == ")" || word == "(") continue;
        if(word[word.size()-1] == ',' ) word.pop_back(); 
        if(word[word.size()-1] == ')' ) word.pop_back(); 
        if(word[0] == '(' ) {
            for(int i = 1; i < word.size();i++) keep.push_back(word[i]);
            word = keep;
            if(word.size() == 1) {
                // as it is separated from original register
                fout<<"\n\n*****Error Detected*****\n\n";
                fout<<"*****Register Not Found*****\n\n";
                error = true;
                return;          
            }
        }
       
        if(count == 1) {
            command = word;
            count++;
            continue;
        }
        if(count == 2){
            rd = word;
            count++;
            continue;
        }
        if(count == 3){
            tag = word;
            count++;
            continue;
        }
        count++;
       
    }
        if(count != 4){
            fout<<"\n\n*****Error Detected*****\n\n";
            fout<<"*****It requires 3 arguments, make sure spaces are there*****\n\n";
            error = true;
            return;
        }
        string ans;
        // tag can contains imm value or label that we have in our map
       

        if(label.find(tag) != label.end()){
            // tag found
            
           // cout<<"okay "<<label[tag]<<" "<<pc<<endl;
            imm = to_string(label[tag] - pc);
            
            //cout<<imm<<endl;
        }
        else {
            imm = tag;
        }
    
        getImmediateUJ(imm,ans);
        getRegisterValue(rd,ans);
        getopCode(command,ans);
        
        having = binaryToHex(ans);
}

string memConverter(string& value, int digits) {
    // Convert value to decimal
    if(error == true) return "";
    ll decimalValue;
    if (value.substr(0, 2) == "0b") {
        // Binary format
        decimalValue = stoll(value.substr(2), nullptr, 2);
    } else if (value.substr(0, 2) == "0x") {
        // Hexadecimal format
        decimalValue = stoll(value.substr(2), nullptr, 16);
    } else {
        // Decimal format
        decimalValue = stoll(value);
        
    }
    // Mask to limit the value to the specified number of digits
    if(digits != 16){

    long long mask = (1LL << (digits * 4)) - 1;
    
    decimalValue &= mask;
    }
    // Convert decimal value to hexadecimal string with specified number of digits
    stringstream ss;
    
    ss << hex << setw(digits) << setfill('0') << uppercase << decimalValue;
    
    return ss.str();
}


void read_data(){

    if(error == true) return ;
    ifstream file;
    file.open("comment_free_test_file.asm");
    string sentence;
    bool start = false;
    int row = 8191, col = 7;
    // row [0-8191]  , col [0-7]
    while(getline(file,sentence)){
        istringstream iss(sentence);
        string word;
        iss >> word;
        if(word == "\0") continue;
        if(word == ".text") {start = false; continue;}
        if(word == ".data"){ start = true; continue;}
        if(start){
            istringstream isss(sentence);
            
            string directives;
            isss >> directives;
            string keep = directives;
            if(directives[directives.size()-1]==':') {
                isss >> directives;  
                if(keep == directives) continue; // as strean is stuck               
            }
            
            if(directives == ".byte"){
                while(isss >> directives){
                    if(directives[directives.size()-1]==',') directives.pop_back();
                     string temp = memConverter(directives,2);
                    
                    int idx = temp.size() - 1, i = row, j = col;
                        
                        for( ;idx >= 0;){
                            memory[i][j--] = temp[idx--];
                            if(j == -1){
                                i--;
                                j = 7;
                            }
                        }
                    if(j == -1){
                         j = 7;
                         i--;
                    }
                    col = j;
                    row = i; // update the row and column
                }
            }
            else if(directives == ".word"){
              
                while(isss >> directives){
                    if(directives[directives.size()-1]==',') directives.pop_back();
                     string temp = memConverter(directives,8);
                        
                    int idx =  temp.size() - 1, i = row, j = col;
                        
                        for( ;idx >= 0;){
                            memory[i][j--] = temp[idx--];
                            if(j == -1){

                                i--;
                                j = 7;
                            }
                        }
                    
                    if(j == -1){
                         j = 7;
                         i--;
                    }
                    col = j;
                    row = i; // update the row and column
                   
                }
            }
            else if(directives == ".half"){
                while(isss>> directives){
                    if(directives[directives.size()-1]==',') directives.pop_back();
                     string temp = memConverter(directives,4);
                    
                    int idx = temp.size() - 1, i = row, j = col;
                        
                        for( ;idx >= 0;){
                            memory[i][j--] = temp[idx--];
                            if(j == -1){
                                i--;
                                j = 7;
                            }
                        }
                    
                    if(j == -1){
                         j = 7;
                         i--;
                    }
                    col = j;
                    row = i; // update the row and column
                }
            }
            else if(directives == ".dword"){
                while(isss >> directives){
                    if(directives[directives.size()-1]==',') directives.pop_back();
                     string temp = memConverter(directives,16);
                    
                    int idx = temp.size() - 1, i = row, j = col;
                        
                        for( ;idx >= 0;){
                            memory[i][j--] = temp[idx--];
                            if(j == -1){
                                i--;
                                j = 7;
                            }
                        }
                    
                    if(j == -1){
                         j = 7;
                         i--;
                    }
                    col = j;
                    row = i; // update the row and column
                }
            }
            else if(directives == ".asciiz"){
                getline(isss,directives);
                
                
                string keep ;
                // as I need to remove "  " from string
                
                for(int i = 2; i < directives.size() - 1; i++) keep.push_back(directives[i]);
           
                for(int k = 0; k <= keep.size(); k++){
                    string p;
                    p = to_string((int)(keep[k]));
                    string temp = memConverter(p,2);
                    
                    int idx = temp.size() - 1, i = row, j = col;
                        
                        for( ;idx >= 0;){
                            memory[i][j--] = temp[idx--];
                            if(j == -1){
                                i--;
                                j = 7;
                            }
                        }
                    
                    if(j == -1){
                         j = 7;
                         i--;
                    }
                    col = j;
                    row = i; // update the row and column
                }
            }
            else {
                
                if(directives == "\0" || directives == " ") continue;
                fout<<"\n\n*****Error Detected*****\n\n";
                fout<<"*****No Such Assembly Directive is available *****\n\n";
                error = true;
                
                return;               
            }
        }
        
    }
    // testing purpose
    
    // for(int i = 0; i < 50; i++){
    //     for(int j = 0; j < 8; j++){
    //         if(j%2 == 0)cout<<" ";
    //         cout<<memory[i][j];
    //     }
    //     cout<<endl;
    // }

    file.close();
}
void capture_label(){
    
    if(error == true) return ;
    ifstream file;
    file.open("comment_free_test_file.asm");
    string sentence;
    ll tempPC = 0;
    while(getline(file,sentence)){
        istringstream iss(sentence);
        string word;
        iss >> word;
        if(word[word.size()-1]==':') {
            if(label.find(word) == label.end()) {
                word.pop_back();
                label[word] = tempPC;
            }
            else{
                
                fout<<"\n\n*****Error Detected*****\n\n";
                fout<<"*****label is already declared !! *****\n\n";
                error = true;
                return;     
            }
        }
        if(Formatdecider(word) != "NULL") tempPC+=4;
    }

    // for testing purpose

    // for(auto val:label){
    //     cout<<val.first<<" "<<val.second<<endl;
    // }

    file.close();
}

void remove_comment(){
    ifstream infile("test_file.asm");
    

    ofstream outfile("comment_free_test_file.asm");
  
    string line;
    while (getline(infile, line)) {
        // Find the position of '#' character
        size_t comment_pos = line.find('#');
        if (comment_pos != string::npos) {
            // Remove all characters from '#' to the end of the line
            line.erase(comment_pos);
        }
        // Write the modified line to the output file
        outfile << line << std::endl;
    }

    infile.close();
    outfile.close();

}

int main()
{
    remove_comment();
    fin.open("comment_free_test_file.asm");
    fout.open("output.mc");
    // scan one time for reading the data segment
    read_data();
    // scan once again for capturing the label in the given code 
 
    capture_label();
    string sentence;
    while (getline (fin, sentence)) { // take command line
        istringstream iss(sentence);
        string word;
        iss >> word;
        // decide the format 
        
        if(word[word.size()-1]==':') {
            continue;
        }
        if(word == ".data" || word == ".text" || word == ".byte" ||
           word == ".word" || word == ".half" || word == ".dword" || word == ".asciiz") continue;
        
        //cout<<Formatdecider(word)<<"    "<<word<<endl;
        
        if(word == "\0") continue;
        if(Formatdecider(word) == "R"){
            helper_R(sentence);
            string temp;
            stringstream ss;
            ss << "0x" << hex << pc;
            temp+=ss.str();
            temp+="         ";
            temp+=having;
            
            final.push_back(temp); 
            having.clear();
        }
        if(Formatdecider(word) == "I"){
            helper_I(sentence);
            string temp;
            stringstream ss;
            ss << "0x" << hex << pc;
            temp+=ss.str();
            temp+="         ";
            temp+=having;
            
            final.push_back(temp); 
            having.clear();
        }
        if(Formatdecider(word) == "S"){
            helper_S(sentence);
            string temp;
            stringstream ss;
            ss << "0x" << hex << pc;
            temp+=ss.str();
            temp+="         ";
            temp+=having;
             
            final.push_back(temp); 
            having.clear();
        }
        if(Formatdecider(word) == "SB"){
            helper_SB(sentence);
            string temp;
            stringstream ss;
            ss << "0x" << hex << pc;
            temp+=ss.str();
            temp+="         ";
            temp+=having;
            final.push_back(temp); 
            having.clear();
        }
        if(Formatdecider(word) == "U"){
            helper_U(sentence);
            string temp;
            stringstream ss;
            ss << "0x" << hex << pc;
            temp+=ss.str();
            temp+="         ";
            temp+=having;
            final.push_back(temp); 
            having.clear();
        }
        if(Formatdecider(word) == "UJ"){
            helper_UJ(sentence);
            string temp;
            stringstream ss;
            ss << "0x" << hex << pc;
            temp+=ss.str();
            temp+="         ";
            temp+=having;
            final.push_back(temp); 
            having.clear();
        }       
        if(Formatdecider(word) == "NULL"){
            fout<<"\n\n*****Error Detected*****\n\n";
            fout<<"*****Commmand Not Found*****\n\n";
            error = true;
            break;
        }       
        // after completion of one instructions
        pc+=4;
    }



    // for testing
    // for(auto val:final){
    //     cout<<val<<endl;
    // }
    
    // move all the things into separate file
    fout<<"*********************Machine Code****************************\n";
    for(auto val:final){
        fout<<val<<endl;
    }
    fout<<"*********************Memory Segment***************************\n";
    vector<string> memSeg;
    for(auto val:memory){
        fout<<intToHex(dc)<<"       ";
        for(int i = 0; i < val.size(); i++){
            if(i%2 == 0) fout<<" ";
            fout<<val[i];
        }
        fout<<endl;
        dc -= 4;
    }

    fin.close();
    fout.close();
    return 0;
}