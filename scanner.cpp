#include <bits/stdc++.h>
#include <iostream>
#include "token.h"
using namespace std;

int line =1;
char *token;

static void skipToken(char A){
    while((!(end_of_file()))&&!(token[0]==A)){
        token++;
    }
    if(end_of_file()){
     error("unexpected end of file on line",line);
    }
}
static void skipToken(char A,char B){
    while((!(end_of_file()))&& (!(token[0]==A)&&(token[1]==B))){
        token++;
    }token++;
    if(end_of_file()){
        error("unexpecter end of file on line",line);
    }else{
        token=token+2;
    }
}
bool end_of_file(){
  if(token[0]='\0'){
    return true;
  }
  return false;
  
}



void skip_whitespace(){
 switch(*token){
    case ' ':
    token++;
    skip_whitespace();
    break;
    case '\r':
    token++;
    skip_whitespace();
    break;
    case '\t':
    token++;
    skip_whitespace();
    break;
    case '\n':
    token++;
    line++;
    skip_whitespace();
    break;
    case '/':
    if(token[1] == '/'){
        token++;
        skipToken('\n');
        line++;
    }
    else if(token[1] == '*'){
        token++;
        skipToken('*','/');
        line++;
    }
    else{
        makeToken(TOKEN_SLASH);
        token++;
    }
    skip_whitespace();
    break;
   default:
    break;
   
 }
}
void generateToken(TokenType type);
bool isNum(char B){
    // to convert thr char type to integer we subract it with 0 and assign to integer

   int A=B-'0';
   if(A >=0 && A<=9 ){
     return true;
   }
   else{
      return false;
   }
}
static bool checkKeyword(string charValue, int numChar, TokenType type){
    if(!(isAlphabet(token[numChar+1])) && !(isNum(token[numChar+1]))){

        for(int i = numChar; i > 0; i--){ 
                    
            if(charValue[i-1] != token[i]){

                return false;
            }
        }
        if(type ==TOKEN_ENDL){
            makeToken("'/n'",TOKEN_STRING);
        }else        
        {
        makeToken(type); 
        }return true;
    }return false;
}
static void keywordToken(){
    switch(*token){
        case 'b':
            if(checkKeyword( "reak", 4, TOKEN_BREAK)){token = token+4;}
            else if(checkKeyword("ool", 3, TOKEN_BOOL)){token = token+3;}              
            else{generateToken(TOKEN_IDENTIFIER);}
            break;
        case 'c':
            if(checkKeyword("ase", 3, TOKEN_CASE)){token = token+3;}
            else if(checkKeyword("out", 3, TOKEN_COUT)){token = token+3;}
            else if(checkKeyword("ontinue", 7, TOKEN_CONTINUE)){token = token+7;}                           
            else{generateToken(TOKEN_IDENTIFIER);}
            break;
        case 'd':
            if(checkKeyword("efault", 6, TOKEN_DEFAULT)){token = token+6;}
            else{generateToken(TOKEN_IDENTIFIER);}
            break;            
        case 'e':
            if(checkKeyword("lse", 3, TOKEN_ELSE)){token = token+3;}
            else if(checkKeyword("ndl", 3, TOKEN_ENDL)){token = token+3;}
            else{generateToken(TOKEN_IDENTIFIER);}            
            break;
        case 'f':
            if(checkKeyword("or", 2, TOKEN_FOR)){
                token = token+2;}              
            else if(checkKeyword("alse", 4, TOKEN_FALSE)){
                token = token+4;}
            else{generateToken(TOKEN_IDENTIFIER);}          
            break;
        case 'g':
            if(checkKeyword("oto", 3, TOKEN_GOTO)){
                token = token+3;}              
            else{generateToken(TOKEN_IDENTIFIER);}          
            break;
        case 'i':
            if(checkKeyword("f", 1, TOKEN_IF)){token++;}
            else
            if(checkKeyword("nt", 2, TOKEN_VAR)){
                token = token+ 2;}
            else{generateToken(TOKEN_IDENTIFIER);}          
            break;            
        case 'n':
            if(checkKeyword("il", 2, TOKEN_NIL)){token = token+2;}
            else{generateToken(TOKEN_IDENTIFIER);}
            break;
        case 'p':
            if(checkKeyword("rint", 4, TOKEN_PRINT)){
                token = token+4;}
            else if(!checkKeyword("in", 2, TOKEN_PIN)){
                    generateToken(TOKEN_IDENTIFIER);}               
            break;
        case 'r':
            if(checkKeyword("eturn", 5, TOKEN_RETURN)){token = token+5;}
            else{generateToken(TOKEN_IDENTIFIER);}
            break;
        case 's':
            if(checkKeyword("witch", 5, TOKEN_SWITCH)){
                token = token+5;
            }else            
            if(checkKeyword("tring", 5, TOKEN_STRINGVAR)){  
                token = token+5;}           
            else{generateToken(TOKEN_IDENTIFIER);}
            break;            
        case 't':
            if(checkKeyword("rue", 3, TOKEN_TRUE)){token = token+3;}
            else{generateToken(TOKEN_IDENTIFIER);}
            break;
        case 'w':
            if(checkKeyword("hile", 4, TOKEN_WHILE)){token = token+4;}
            else{generateToken(TOKEN_IDENTIFIER);}
            break;
        case 'v':
            if(checkKeyword("oid", 3, TOKEN_VOID)){token = token+3;}
            else{generateToken(TOKEN_IDENTIFIER);}
            break;            
        default:
            generateToken(TOKEN_IDENTIFIER);
            break;
    }
}
void charToken();
bool isAlphabet(char A){
    if((A>='a' && A<='z') || (A>= 'A' && A<= 'Z') || A =='_'){
     return true;
    }
    else{
     return false;
    }
    
}
void makeToken(TokenType type);
void scanner(char* buffer){
    token=buffer;
    while(!end_of_file()){
        skip_whitespace();
        if(isNum(*token)){
            generateToken(TOKEN_NUMBER);
        }
        else if(isAlphabet(*token)){
            keywordToken();
        }
        else{
            charToken();
        }
        token++;
    }
    if(end_of_file()){
        makeToken(TOKEN_EOF);
    }
}