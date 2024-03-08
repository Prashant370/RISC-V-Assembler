#include <bits/stdc++.h>
using namespace std;
#define ll long long
#include <fstream>
ofstream fout;
ifstream fin;
bool error = false;

vector<string> finalhexadecimal;

string binaryToHex(string& binary) { 
    // Convert binary string to hexadecimal
    stringstream ss;
    ss << hex << setw(8) << setfill('0')<< bitset<32>(binary).to_ulong();

    // Add "0x" prefix to the hexadecimal string
    string hex = ss.str();
    hex = "0x" + hex;
    transform(hex.begin() + 2, hex.end(), hex.begin() + 2, ::toupper);
    return hex;
}
string decimalToBinary(int decimalNumber) {
    string binaryNumber = "";
    for (int i = 4; i >= 0; i--) {
        int bit = (decimalNumber >> i) & 1;
        binaryNumber += to_string(bit);
    }
    return binaryNumber;
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
    else if (have == "auipc" || have == "lui") s+="0100011";
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
    int value;
    if (immediate.substr(0, 2) == "0b") {
        // Binary format
        value = stoi(immediate.substr(2), nullptr, 2);
    } else if (immediate.substr(0, 2) == "0x") {
        // Hexadecimal format
        value = stoi(immediate.substr(2), nullptr, 16);
    } else {
        // Decimal format
        value = stoi(immediate);
    }

    // Convert the value to a 12-bit binary string
    bitset<12> bits(value);
    return bits.to_string();
}
string immediateToBinary13(string& immediate) {
    // Check if the immediate value is in decimal, binary, or hexadecimal format
    int value;
    if (immediate.substr(0, 2) == "0b") {
        // Binary format
        value = stoi(immediate.substr(2), nullptr, 2);
    } else if (immediate.substr(0, 2) == "0x") {
        // Hexadecimal format
        value = stoi(immediate.substr(2), nullptr, 16);
    } else {
        // Decimal format
        value = stoi(immediate);
    }

    // Convert the value to a 12-bit binary string
    bitset<13> bits(value);
    return bits.to_string();
}
string immediateToBinary20(string& immediate) {
    // Check if the immediate value is in decimal, binary, or hexadecimal format
    int value;
    if (immediate.substr(0, 2) == "0b") {
        // Binary format
        value = stoi(immediate.substr(2), nullptr, 2);
    } else if (immediate.substr(0, 2) == "0x") {
        // Hexadecimal format
        value = stoi(immediate.substr(2), nullptr, 16);
    } else {
        // Decimal format
        value = stoi(immediate);
    }

    // Convert the value to a 12-bit binary string
    bitset<20> bits(value);
    return bits.to_string();
}
string immediateToBinary21(string& immediate) {
    // Check if the immediate value is in decimal, binary, or hexadecimal format
    int value;
    if (immediate.substr(0, 2) == "0b") {
        // Binary format
        value = stoi(immediate.substr(2), nullptr, 2);
    } else if (immediate.substr(0, 2) == "0x") {
        // Hexadecimal format
        value = stoi(immediate.substr(2), nullptr, 16);
    } else {
        // Decimal format
        value = stoi(immediate);
    }

    // Convert the value to a 12-bit binary string
    bitset<21> bits(value);
    return bits.to_string();
}
void getImmediateI(string have, string &s){ // For I,S,SB,U,UJ Format
    // have can be in any format
    s+=immediateToBinary12(have);
}


void getRegisterValue(string have, string &s){ // For R,I,S,SB,,U,UJ Format
    if(error) return;
    if(have[0] != 'x'){
        fout<<"\n\n*****Error Detected*****\n\n";
        fout<<"*****Register Name is Wrong*****\n\n";
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
    int temp = stoi(have);
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
        }
        
        
        string ans;
        
        getFunc7(command,ans);
        getRegisterValue(rs2,ans);
        getRegisterValue(rs1,ans);
        getFunc3(command,ans);
        getRegisterValue(rd,ans);
        getopCode(command,ans);
        
        finalhexadecimal.push_back(binaryToHex(ans)); 
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
        }
            string ans;
    
            getImmediateI(imm,ans);
            getRegisterValue(rs1,ans);
            getFunc3(command,ans);
            getRegisterValue(rd,ans);
            getopCode(command,ans);
            
            finalhexadecimal.push_back(binaryToHex(ans)); 
        
        }
        else{
            // having offset lw x5, 4(x3)  ::: lw x5, 4 ( x3 ) --> NOT supported
            // lw x5 4 x3 -->supported
            istringstream iss(sentence);
            string word;
            int count = 1;
            string command,rs1,rd,imm;
       
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
                imm = word;
                count++;
                continue;
            }
            if(count == 4){
                rs1 = word;
                count++;
                continue;
            }
        }
            string ans;
    
            getImmediateI(imm,ans);
            getRegisterValue(rs1,ans);
            getFunc3(command,ans);
            getRegisterValue(rd,ans);
            getopCode(command,ans);
            
            finalhexadecimal.push_back(binaryToHex(ans)); 
        }
   
}
void helper_S(string sentence){
    
}
void helper_SB(string sentence){

}
void helper_U(string sentence){

}
void helper_UJ(string sentence){

}

int main()
{
    
    fin.open("SuperbasicTest.txt");
    string sentence;
    while (getline (fin, sentence)) { // take command line
        istringstream iss(sentence);
            string word;
        iss >> word;
        // decide the format 
        
        if(Formatdecider(word) == "R"){
            helper_R(sentence);
            
        }
        if(Formatdecider(word) == "I"){
            helper_I(sentence);
        }
        if(Formatdecider(word) == "S"){
            helper_S(sentence);
        }
        if(Formatdecider(word) == "SB"){
            helper_SB(sentence);
        }
        if(Formatdecider(word) == "U"){
            helper_U(sentence);
        }
        if(Formatdecider(word) == "UJ"){
            helper_UJ(sentence);
        }       
        if(Formatdecider(word) == "NULL"){
            fout<<"\n\n*****Error Detected*****\n\n";
            fout<<"*****Commmand Not Found*****\n\n";
            error = true;
        }       

    }
    
    for(auto val:finalhexadecimal){
        cout<<val<<endl;
    }
    fin.close();
    fout.close();
    return 0;
}