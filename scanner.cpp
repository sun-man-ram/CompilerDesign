#include <bits/stdc++.h>
#include <iostream>
#include "token.h"
using namespace std;
int parenCount=0;
int braceCount=0;
int line =1;
char *token;
bool end_of_file(){
  if(token[0]='\0'){
    return true;
  }
  return false;
  
}

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
static void checkField(int type){
    switch(type){
        case 1:
        if(parenCount ==0){
            error("unexpected ')' on line",line);
        }
        break;
        case 2:
        if(parenCount!=0){
            error("unexpected { on line",line);
        }
        break;
        case 3:
        if(braceCount ==0){
            error("unexoected '}' on line ",line);
        }
        if(parenCount!=0){
            error("unexpected '}' on line",line);
        }
        break;
        
    }
}
static void charToken(){
    if(end_of_file()){
        return;}
    switch(*token){
        case '(':
        checkField(0);
        parenCount++;
        makeToken(TOKEN_LEFT_PAREN);
        break;
        case ')':
        checkField(1);
        parenCount--;
        makeToken(TOKEN_RIGHT_PAREN);
        break;
        case '{':
        checkField(2);
        braceCount++;
        makeToken(TOKEN_LEFT_BRACE);
        break;
        case '}':
        checkField(3);
        makeToken(TOKEN_RIGHT_BRACE);
        braceCount--;
        break;
        case ';':
        if(token[1] == ';'){
        generateToken(TOKEN_INFINITE);
        token++;
        }else{      
        makeToken(TOKEN_SEMICOLON);}
        break;
        case ',':
        makeToken(TOKEN_COMMA);
        break;
        case '.':
        makeToken(TOKEN_DOT);
        break;
        case '-':
        if(token[1] == '+'){
        makeToken(TOKEN_SUB);
        token++;
        }else
        if(token[1] == '-'){
        makeToken(TOKEN_SUB_SELF);
        token++; 
        }else
        if(token[1] == '='){
        makeToken(TOKEN_SUB_ASS);
        token++;                         
        }else{
        makeToken(TOKEN_SUB);
        }          
        break;
        case '+':
        if(token[1] == '+'){
        makeToken(TOKEN_ADD_SELF);
        token++;
        }else
        if(token[1] == '-'){
        makeToken(TOKEN_SUB);
        token++; 
        }else
        if(token[1] == '='){
        makeToken(TOKEN_ADD_ASS);
        token++;                          
        }else{
        makeToken(TOKEN_PLUS);
        }          
        break;
        case '/':
        if(token[1] == '='){
        makeToken(TOKEN_SLASH_ASS);
        token++;                          
        }else{
        makeToken(TOKEN_SLASH);
        }          
        break;        
        case '*':
        if(token[1] == '='){
        makeToken(TOKEN_STAR_ASS);
        token++;                          
        }else{
        makeToken(TOKEN_STAR);
        }          
        break;  
        case ':':
        makeToken(TOKEN_COLON);
        break;
        case '?':
        makeToken(TOKEN_TENARY);
        break; 
        case '^':
        if(token[1] == '='){
            makeToken(TOKEN_ASS_XOR);
            token++;
        }else{
            makeToken(TOKEN_BIT_XOR);
        }  
        case '~':
        makeToken(TOKEN_INVERSE);
        break;
        case '%':
        makeToken(TOKEN_MODULUS);
        break;
        case '[':
        makeToken(TOKEN_LEFT_BLOCK);
        break;
        case ']':
        makeToken(TOKEN_RIGHT_BLOCK);
        break;
        case '"':
        token++;
        generateToken(TOKEN_STRING);
        break;
        case '!':
        if(token[1] == '='){
            makeToken(TOKEN_BANG_EQUAL);
            token++;
        }else{
            makeToken(TOKEN_BANG);
        }          
        break;
        case '&':
        if(token[1] == '&'){
            makeToken(TOKEN_LOGICAL_AND);
            token++;
        }else if(token[1] == '='){
            makeToken(TOKEN_ASS_AND);
            token++;                  
        }else{
            makeToken(TOKEN_BIT_AND);
        }          
        break;  
        case '|':
        if(token[1] == '|'){
            makeToken(TOKEN_LOGICAL_OR);
            token++;
        }else if(token[1] == '='){
            makeToken(TOKEN_ASS_OR);
            token++;                  
        }else{
            makeToken(TOKEN_BIT_OR);
        }          
        break;                        
        case '=':
        if(token[1] == '='){
            makeToken(TOKEN_EQUAL_EQUAL);
            token++;
        }else{
            makeToken(TOKEN_EQUAL);
        }          
        break;
        case '<':
        if(token[1] == '='){
            makeToken(TOKEN_LESS_EQUAL);
            token++;
        }else if(token[1] == '<'){
            makeToken(TOKEN_SHIFT_LEFT);
            token++;                
        }else{
            makeToken(TOKEN_LESS);
        }          
        break;
        case '>':
        if(token[1] == '='){
            makeToken(TOKEN_GREATER_EQUAL);
            token++;
        }else if(token[1] == '>'){
            makeToken(TOKEN_SHIFT_RIGHT);
            token++;                  
        }else{
            makeToken(TOKEN_GREATER);
        }          
        break;  
        default:
        skip_whitespace();                   
    }
}
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