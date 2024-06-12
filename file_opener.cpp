#include<stdio.h>
#include<iostream>
#include<bits/stdc++.h>
#include "scanner.h"
using namespace std;

int main(int argc,char** argv){
    char *fileOpen=argv[1];
    FILE *filePointer;
    filePointer=fopen(fileOpen,"r");
    if(filePointer==NULL){
        cout<<"failed to open file";
        exit(1);
    }
    else{
     fseek(filePointer,0,SEEK_END);
     int fileSize=ftell(filePointer);
    fseek(filePointer,0,SEEK_SET);
    char *buffer=NULL;
    buffer=new(nothrow) char[fileSize+1];
    if(!buffer){
        cout<<"allocation of memory failed";
    }
    else{
    fread(buffer,sizeof(char),fileSize,filePointer);
    cout<<"file opened successfully";
    scanner(buffer);
    }
    delete buffer;
    fclose(filePointer);
    }

    return 0;
}