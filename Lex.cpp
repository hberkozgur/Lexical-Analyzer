#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include "lex.h"



using namespace std;

int main(int argc, char *argv[])
{
    ifstream file;
    string filename = "";

    bool verbose = false;
    bool print_nconsts = false;
    bool print_sconsts = false;
    bool print_idents = false;
    int filenum = 0;
    
    for (int i = 1; i < argc; i++)
    {
        
        string arg = argv[i];
        if(arg[0] != '-'){
            filename = arg;
            file.open(filename);
            filenum = filenum+1;
        }
        if(filenum >1)
        {
            cout << "ONLY ONE FILE NAME IS ALLOWED." << endl;
            return 0;  
        }
        
        
    }
    if(filename == ""){
        cout << "NO SPECIFIED INPUT FILE." << endl;
        return 0;    
    }
    else if (file.is_open() == false){
            cout << "CANNOT OPEN THE FILE " << filename << endl;
            return 0;
        }

        
    for (int i = 1; i < argc; i++){
        string arg = argv[i];
        if (arg == "-v")
        {
            verbose = true;
        }
        else if (arg == "-nconst")
        {
            print_nconsts = true;
        }
        else if (arg == "-sconst")
        {
            print_sconsts = true;
        }
        else if (arg == "-ident")
        {
            print_idents = true;
        }
        else if (arg.size() > 0 && arg[0] == '-')
        {
            cout << "UNRECOGNIZED FLAG {" << arg << '}'<< endl;
            return 0;
        }
    }
        
        
    int str_count=0;
    int num_count =0;
    int total_token_count = 0;
    set<string> idents;
    set<float> nconsts;
    set<string> sconsts;
    int linenumber = 0;
    
    while (file)
    {
            
        LexItem X = getNextToken(file, linenumber);
            
        if (X.GetToken() == ERR)
        {
            if(verbose || print_nconsts || print_sconsts || print_idents) {
                cout << "Error on line " << linenumber << " ("<< X.GetLexeme() << ")" << endl;
            }
            return 0;
            
            
        }
        else if (X.GetToken() == IDENT || X.GetToken() == SIDENT || X.GetToken() == NIDENT)
        {
            if(verbose || print_nconsts || print_sconsts || print_idents) {
                cout << X;
            }
              
            idents.insert(X.GetLexeme());
        }
        else if (X.GetToken() == ICONST || X.GetToken() == RCONST)
        {
            float num = stof(X.GetLexeme());
            num_count = num_count+1;
            if(verbose || print_nconsts || print_sconsts || print_idents) {
                cout << X;
            } 
            nconsts.insert(num);
        }
        else if (X.GetToken() == SCONST)
        {
            str_count = str_count+1;
            if(verbose || print_nconsts || print_sconsts || print_idents) {
                cout << X;
            }  
            sconsts.insert(X.GetLexeme());
        }
        else if (X.GetToken() == DONE)
        {
            continue;
        }
        else{
            if(verbose || print_nconsts || print_sconsts || print_idents) {
                cout << X;
            }  
        }
        total_token_count++;
        if (verbose)
        {
            
        }
    }

    
    if(linenumber !=0 &&((verbose || print_nconsts || print_sconsts || print_idents))){
        cout << "\n" << "Lines: " << linenumber << "\n";
        cout <<"Total Tokens: " << total_token_count << endl;
        cout << "Identifiers: " << idents.size() << endl;
        cout << "Numbers: " << num_count  << endl;
        cout << "Strings: " << str_count << endl;
        if (print_idents)
        {
            int i = 0;
            cout << "IDENTIFIERS:" << endl;
            set<string> sorted_idents(idents.begin(), idents.end()); 
            for (const auto &ident : sorted_idents)
            {
        cout << ident; 
        if (i < idents.size()-1) {
            cout << ", ";
        }
        i++;
       
            
    }
    cout << endl;
    }

    
    if (print_nconsts)
    {
        int i = 0;
        cout << "NUMBERS:" << endl;
        set<float> sorted_nconst(nconsts.begin(), nconsts.end());
        for (const auto &nconst : sorted_nconst)
        {
            cout << nconst; 
            if (i < nconsts.size()-1) {
                cout << endl;
            }
            i++;
            
        }
        cout << "\n";
    }
    }
    if (print_sconsts)
    {
        int i = 0;
        cout << "STRINGS:" << endl;
        set<string> sorted_sconst(sconsts.begin(), sconsts.end());
        for (const auto &sconst : sconsts)
        {
            cout << '\''<< sconst; 
            cout << '\''<< endl;

    
        }
    }
    else if(linenumber>0) {
        cout << "\n" << "Lines: " << linenumber << "\n";
        cout <<"Total Tokens: " << total_token_count << endl;
        cout << "Identifiers: " << idents.size() << endl;
        cout << "Numbers: " << num_count  << endl;
        cout << "Strings: " << str_count << endl;
    }
    else{
        cout << "Lines: " << linenumber << "\n";
        cout << "Empty File." << "\n";
    }
    
    
    
    
}    
