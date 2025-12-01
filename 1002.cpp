#include <iostream>
#include <fstream>
#include <string>
using namespace::std;

// reads in a C++ program from a cpp file, and put it to the array program
void load(string* program, int& numLines);

// deletes the comment beginning with "//" from sourceLine if any
void delComment(string& sourceLine);

// deletes all string constants from sourceLine
void delStrConsts(string& sourceLine);

// deletes all character constants from sourceLine
void delCharConsts(string& sourceLine);

// extracts all identifiers from sourceLine, and
// put them into the array identifiers
void extractIdentifiers(string& sourceLine, string* identifiers,
    int& numIdentifiers);

// stores all non-keyword strings in the array identifiers into a text file
void store(string* identifiers, int numIdentifiers);

// return true if and only if "str" is a C++ keyword
bool keyword(string str);

// returns true iff identifiers[ pos ] belongs to identifiers[ 0 .. pos-1 ]
bool duplicate(string* identifiers, int pos);

const string keywords[] = { "auto", "break", "case", "char", "const",
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
    string* program = new string[500];
    int numLines = 0;

    // reads in a C++ program from a cpp file, and put it to the array program
    load(program, numLines);

    string* identifiers = new string[500];
    string null;
    int numIdentifiers = 0;

    for (int i = 0; i < numLines; i++)
    {
        delComment(program[i]); // deletes the comment beginning with "//" from program[ i ]
        delStrConsts(program[i]); // deletes all string constants from program[ i ]
        delCharConsts(program[i]); // deletes all character constants from program[ i ]

        if (program[i] != null)
            extractIdentifiers(program[i], identifiers, numIdentifiers);
        // extracts all identifiers from program[ i ], and put them into the array identifiers
    }

    // stores all non-keyword strings in the array identifiers into a text file
    store(identifiers, numIdentifiers);

    delete[] program;
    delete[] identifiers;
}

void load(string* program, int& numLines)
{
    string filename;
    cin >> filename;
    ifstream in(filename);
    while (numLines < 500 &&getline(in,program[numLines])) {
        numLines++;
    }
    in.close();
}

void delComment(string& sourceLine)
{
    size_t length = sourceLine.size();
    if (length > 1)
        for (size_t i = 0; i < length - 1; i++)
            if (sourceLine[i] == '/' && sourceLine[i + 1] == '/')
            {
                sourceLine.erase(i, length);
                break;
            }
}

void delStrConsts(string& sourceLine)
{
    bool isstring = false;
    size_t i = 0;
    size_t len = sourceLine.length();

    while (i < len) { 
        if (isstring && sourceLine[i] == '\\') {
            sourceLine[i] = ' ';
            i++;
            if (i < len) {
                sourceLine[i] = ' ';
            }
        }
        else if (sourceLine[i] == '\"') {
            isstring = !isstring;
            sourceLine[i] = ' ';
        }
        else if (isstring) {
            sourceLine[i] = ' ';
        }
        i++;
    }
}

void delCharConsts(string& sourceLine)
{
    bool isstring = false;
    size_t i = 0;
    size_t len = sourceLine.length();

    while (i < len) {
        if (isstring && sourceLine[i] == '\\') {
            sourceLine[i] = ' ';
            i++;
            if (i < len) {
                sourceLine[i] = ' ';
            }
        }
        else if (sourceLine[i] == '\'') {
            isstring = !isstring;
            sourceLine[i] = ' ';
        }
        else if (isstring) {
            sourceLine[i] = ' ';
        }
        i++;
    }
}

void extractIdentifiers(string& sourceLine, string* identifiers,
    int& numIdentifiers)
{
    size_t i = 0;
    size_t len = sourceLine.length();

    while (i < len)
    {
        if (!isalpha((unsigned char)sourceLine[i]) && sourceLine[i] != '_') {
            i++;
            continue;
        }
        identifiers[numIdentifiers] = "";
        while (i < len && (isalnum((unsigned char)sourceLine[i]) || sourceLine[i] == '_')) {
            identifiers[numIdentifiers] += sourceLine[i];
            i++;
        }
        if (!keyword(identifiers[numIdentifiers]) && !duplicate(identifiers, numIdentifiers)) {
            numIdentifiers++;
        }
    }
}

void store(string* identifiers, int numIdentifiers)
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

bool keyword(string str)
{
    const int numKeywords = 62;
    for (int i = 0; i < numKeywords; i++)
        if (keywords[i] == str)
            return true;

    return false;
}

bool duplicate(string* identifiers, int pos)
{
    for (int i = 0; i < pos; i++)
        if (identifiers[i] == identifiers[pos])
            return true;

    return false;
}
