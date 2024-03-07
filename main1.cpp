#include <bits/stdc++.h>
using namespace std;
#define ll long long
#include <fstream>

void getopCode(string have, string s){ // For R,I,S,SB,U,UJ Format
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
void getFunc3(string have, string s){  // For R,I,S,SB Format
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
void getFunc7(string have, string s){ // For R Format
     if(have == "add" || have == "or" || have == "sll" || have == "slt"|| have == "srl"|| have == "xor" ) s+="0000000";
     else if( have == "add"|| have == "sra"|| have == "sub")s+="0100000";

}
void getImmediate(string have, string s){ // For I,S,SB,U,UJ Format
    int temp;
    temp = stoi(s);

}
void getRegisterValue(string have, string s){ // For R,I,S,SB,,U,UJ Format
    
}


int main()
{
    
    ofstream fout;
    ifstream fin;

    string line;
    while (getline (fin, line)) {
        
    }
    fin.close();
    fout.close();
    return 0;
}