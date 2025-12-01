#include <iostream>
#include <cstring>
#include <fstream>
#include<string>
using namespace::std;

// reads in a C++ program from a cpp file, and put it to the array program
void load(char(*program)[100], int& numLines);

// deletes the comment beginning with "//" from sourceLine if any
void delComment(char sourceLine[]);

// deletes all string constants from sourceLine
void delStrConsts(char sourceLine[]);

// deletes all character constants from sourceLine
void delCharConsts(char sourceLine[]);

// extracts all identifiers from sourceLine, and put them into the array identifiers
void extractIdentifiers(char sourceLine[], char identifiers[][32], int& numIdentifiers);

// stores all non-keyword strings in the array identifiers into a text file
void store(char (*identifiers)[32], int numIdentifiers);

// returns true if and only if str is a C++ keyword
bool keyword(char str[]);

// returns true if and only if identifiers[ pos ] belongs to identifiers[ 0 .. pos-1 ]
bool duplicate(char (*identifiers)[32], int pos);

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
    char (*program)[100] = new char[500][100];
    int numLines = 0;

    // reads in a C++ program from a cpp file, and put it to the array program
    load(program, numLines);

    char (*identifiers)[32] = new char[500][32];
    int numIdentifiers = 0;

    for (int i = 0; i < numLines; i++)
    {
        delComment(program[i]); // deletes the comment beginning with "//" from program[ i ]
        delStrConsts(program[i]); // deletes all string constants from program[ i ]
        delCharConsts(program[i]); // deletes all character constants from program[ i ]

        if (strcmp(program[i], "") != 0)
            extractIdentifiers(program[i], identifiers, numIdentifiers);
        // extracts all identifiers from program[ i ], and put them into the array identifiers
    }

    // stores all non-keyword strings in the array identifiers into a text file
    store(identifiers, numIdentifiers);

    delete[] program;
    delete[] identifiers;
}

void load(char(*program)[100], int& numLines)
{
    char filename[100];
    cin >> filename;

    ifstream in;
    in.open(filename);

    if (!in) {
        cout << "Cannot open file: " << filename << endl;
        return;
    }
    while (numLines < 500 && in.getline(program[numLines], 100)) {
        numLines++;
    }
    in.close();
}

void delComment(char sourceLine[])
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

void delStrConsts(char sourceLine[])
{
    bool isstring = false;
    int i = 0;
    while (sourceLine[i] != '\0') {
        if (isstring && sourceLine[i] == '\\') {
            sourceLine[i] = ' ';
            i++;
            if (sourceLine[i] != '\0') {
                sourceLine[i] = ' ';
            }
        }
        else if (sourceLine[i] == '"') {
            isstring = !isstring;
            sourceLine[i] = ' ';
        }
        else if (isstring) {
            sourceLine[i] = ' ';
        }
        i++;
    }
}

void delCharConsts(char sourceLine[])
{
    bool ischar = false;
    int i = 0;
    while (sourceLine[i] != '\0') {
        if (ischar && sourceLine[i] == '\\') {
            sourceLine[i] = ' ';
            i++;
            if (sourceLine[i] != '\0') {
                sourceLine[i] = ' ';
            }
        }
        else if (sourceLine[i] == '\'') {
            ischar = !ischar;
            sourceLine[i] = ' ';
        }
        else if (ischar) {
            sourceLine[i] = ' ';
        }
        i++;
    }
}

void extractIdentifiers(char sourceLine[], char identifiers[][32], int& numIdentifiers)
{
    int i = 0;
    while (sourceLine[i] != '\0')
    {
        if (!isalpha((unsigned char)sourceLine[i]) && sourceLine[i] != '_') {
            i++;
            continue;
        }
        int k = 0;
        while (isalnum((unsigned char)sourceLine[i]) || sourceLine[i] == '_') {
            if (k < 31) {
                identifiers[numIdentifiers][k] = sourceLine[i];
                k++;
            }
            i++;
        }
        identifiers[numIdentifiers][k] = '\0';
        if (!keyword(identifiers[numIdentifiers]) && !duplicate(identifiers, numIdentifiers)) {
            numIdentifiers++;
        }
    }
}

void store(char (*identifiers)[32], int numIdentifiers)
{
    ofstream out("identifiers.txt");

    if (!out) {
        cout << "無法建立檔案" << endl;
        return;
    }
    for (int i = 0; i < numIdentifiers; i++)
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

bool duplicate(char (*identifiers)[32], int pos)
{
    for (int i = 0; i < pos; i++)
        if (strcmp(identifiers[i], identifiers[pos]) == 0)
            return true;

    return false;
}
