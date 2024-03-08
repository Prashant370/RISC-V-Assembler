#include <bits/stdc++.h>
using namespace std;
#define ll long long
#include <fstream>
ofstream fout;
ifstream fin;
bool error = false;

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
    else{
        fout<<"\n\n**Error Detected**\n\n";
        fout<<"**Commmand Not Found**\n\n";
        error = true;
        return ;
    }
    
}
void getFunc3(string have, string s){  // For R,I,S,SB Format
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
void getFunc7(string have, string s){ // For R Format
     if(error) return;
     if(have == "add" || have == "or" || have == "sll" || have == "slt"|| have == "srl"|| have == "xor" ) s+="0000000";
     else if( have == "and"|| have == "sra"|| have == "sub") s+="0100000";
     

}
void getImmediate(string have, string s){ // For I,S,SB,U,UJ Format
    if(error) return;
    int temp;
    temp = stoi(s);


}
string decimalToBinary(int decimalNumber) {
    string binaryNumber = "";
    for (int i = 4; i >= 0; i--) {
        int bit = (decimalNumber >> i) & 1;
        binaryNumber += to_string(bit);
    }
    return binaryNumber;
}

void getRegisterValue(string have, string s){ // For R,I,S,SB,,U,UJ Format
    if(error) return;
    if(have[0] != 'x'){
        fout<<"\n\n**Error Detected**\n\n";
        fout<<"**Register Name is Wrong**\n\n";
        error = true;
        return;
    }
    have.erase(have.begin());  // Erase the first character that is x
   

    int temp = stoi(have);
    if(temp >= 32 || temp < 0) {
      
        fout<<"\n\n**Error Detected**\n\n";
        fout<<"**Register Not Found**\n\n";
        error = true;
        return;
    }
    // here temp is integer only other possibilites are revoked above
    s+=decimalToBinary(temp);
     
}

string Formatdecider(string have){
        
}
int main()
{
    

    string sentence;
    while (getline (fin, sentence)) { // take command line
        istringstream iss(sentence);
            string word;
            while (iss >> word) {

                if(word == ",") continue;
                if(word[word.size()-1] == ',' ) word.pop_back(); 
                // decide the format 
                if(Formatdecider(word) == "R"){
                    
                }
                if(Formatdecider(word) == "I"){

                }
                if(Formatdecider(word) == "S"){

                }
                if(Formatdecider(word) == "SB"){

                }
                if(Formatdecider(word) == "U"){

                }
                if(Formatdecider(word) == "UJ"){

                }

            }
     
    }
    fin.close();
    fout.close();
    return 0;
}
