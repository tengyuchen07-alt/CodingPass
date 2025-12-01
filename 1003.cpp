#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <fstream>
#include<string>
#include <vector>
#include <cctype>
using namespace::std;

// reads in a C++ program from a cpp file, and put it to the vector program
void load(vector< char* >& program);

// deletes the comment beginning with "//" from sourceLine if any
void delComment(char* sourceLine);

// deletes all string constants from sourceLine
void delStrConsts(char* sourceLine);

// deletes all character constants from sourceLine
void delCharConsts(char* sourceLine);

// extracts all identifiers from sourceLine, and
// put them into the vector identifiers
void extractIdentifiers(char* sourceLine, vector< char* >& identifiers);

// stores all non-keyword strings in the vector identifiers into a text file
void store(vector< char* >& identifiers);

// returns true if and only if str is a C++ keyword
bool keyword(char str[]);

// returns true iff identifiers[ pos ] belongs to identifiers[ 0 .. pos-1 ]
bool duplicate(vector< char* >& identifiers, int pos);

const char keywords[][20] = { "auto", "break", "case", "char", "const",
                                "continue", "default", "define","do", "double",
                                "else", "enum", "extern", "float", "for",
                                "goto", "if", "int", "long", "register",
                                "return", "short", "signed", "sizeof",
                                "static", "struct", "switch", "typedef",
                                "union", "unsigned", "void", "volatile",
                                "while", "bool", "catch", "class",
                                "const_cast", "delete", "dynamic_cast",
                                "explicit", "false", "friend", "inline",
                                "mutable", "namespace", "new", "operator",
                                "private", "protected", "public",
                                "reinterpret_cast", "static_cast", "template",
                                "this", "throw", "true", "try", "typeid",
                                "typename", "using", "virtual", "include" };

int main()
{
    vector< char* > program;

    // reads in a C++ program from a cpp file, and put it to the vector program
    load(program);

    vector< char* > identifiers;
    for (size_t i = 0; i < program.size(); i++)
    {
        delComment(program[i]); // deletes the comment beginning with "//" from program[ i ]
        delStrConsts(program[i]); // deletes all string constants from program[ i ]
        delCharConsts(program[i]); // deletes all character constants from program[ i ]

        if (strcmp(program[i], "") != 0)
            extractIdentifiers(program[i], identifiers);
        // extracts all identifiers from program[ i ], and put them into the vector identifiers
    }

    // stores all non-keyword strings in the vector identifiers into a text file
    store(identifiers);

    for (size_t i = 0; i < identifiers.size(); i++)
        delete[] identifiers[i];

    for (size_t i = 0; i < program.size(); i++)
        delete[] program[i];
}

void load(vector< char* >& program)
{
    string filename;
    cin >> filename;
    ifstream in(filename);
    if (!in)return;
    char buffer[200];
    while (in.getline(buffer, 200)) {
        char* line = new char[strlen(buffer) + 1];
        strcpy(line,buffer);
        program.push_back(line);
    }
}

void delComment(char* sourceLine)
{
    size_t length = strlen(sourceLine);
    if (length > 1)
        for (size_t i = 0; i < length - 1; i++)
            if (sourceLine[i] == '/' && sourceLine[i + 1] == '/')
            {
                sourceLine[i] = '\0';
                return;
            }
}

void delStrConsts(char* sourceLine)
{
    bool isstring = false;
    size_t i = 0;
    while (sourceLine[i] != '\0')
    {
        if (isstring && sourceLine[i] == '\\')
        {
            sourceLine[i] = ' ';
            i++;
            if (sourceLine[i] != '\0') sourceLine[i] = ' ';
        }
        else if (sourceLine[i] == '\"')
        {
            isstring = !isstring;
            sourceLine[i] = ' ';
        }
        else if (isstring)
        {
            sourceLine[i] = ' ';
        }
        i++;
    }
}

void delCharConsts(char* sourceLine)
{
    bool ischar = false;
    size_t i = 0;
    while (sourceLine[i] != '\0')
    {
        if (ischar && sourceLine[i] == '\\')
        {
            sourceLine[i] = ' ';
            i++;
            if (sourceLine[i] != '\0') sourceLine[i] = ' ';
        }
        else if (sourceLine[i] == '\'') // 單引號
        {
            ischar = !ischar;
            sourceLine[i] = ' ';
        }
        else if (ischar)
        {
            sourceLine[i] = ' ';
        }
        i++;
    }
}

void extractIdentifiers(char* sourceLine, vector< char* >& identifiers)
{
    size_t i = 0;
    while (sourceLine[i] != '\0')
    {
        // 1. 跳過不合法開頭
        if (!isalpha((unsigned char)sourceLine[i]) && sourceLine[i] != '_')
        {
            i++; continue;
        }
        char buffer[100];
        int k = 0;
        while (isalnum((unsigned char)sourceLine[i]) || sourceLine[i] == '_')
        {
            if (k < 99)
            {
                buffer[k++] = sourceLine[i];
            }
            i++;
        }
        buffer[k] = '\0';

        char* newId = new char[k + 1];
        strcpy(newId, buffer);
        identifiers.push_back(newId);
        size_t currentPos = identifiers.size() - 1;

        if (keyword(identifiers[currentPos]) || duplicate(identifiers, currentPos))
        {
            delete[] identifiers[currentPos];
            identifiers.pop_back();
        }
    }
}

void store(vector< char* >& identifiers)
{
    ofstream out("identifiers.txt");
    if (!out) return;

    for (size_t i = 0; i < identifiers.size(); i++)
    {
        out << identifiers[i] << endl;
    }
    out.close();
}

bool keyword(char str[])
{
    size_t numKeywords = sizeof(keywords) / 20;
    for (size_t i = 0; i < numKeywords; i++)
        if (strcmp(keywords[i], str) == 0)
            return true;

    return false;
}

bool duplicate(vector< char* >& identifiers, int pos)
{
    for (int i = 0; i < pos; i++)
        if (strcmp(identifiers[i], identifiers[pos]) == 0)
            return true;

    return false;
}
