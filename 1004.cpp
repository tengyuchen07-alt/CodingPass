#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype> 

using namespace std;

// reads in a C++ program from a cpp file, and put it to the vector program
void load(vector< string >& program);

// deletes the comment beginning with "//" from sourceLine if any
void delComment(string& sourceLine);

// deletes all string constants from sourceLine
void delStrConsts(string& sourceLine);

// deletes all character constants from sourceLine
void delCharConsts(string& sourceLine);

// extracts all identifiers from sourceLine, and
// put them into the vector identifiers
void extractIdentifiers(string& sourceLine, vector< string >& identifiers);

// stores all non-keyword strings in the vector identifiers into a text file
void store(vector< string >& identifiers);

// return true if and only if "str" is a C++ keyword
bool keyword(string str);

// returns true iff identifiers[ pos ] belongs to identifiers[ 0 .. pos-1 ]
bool duplicate(vector< string >& identifiers, int pos);

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
    vector< string > program;

    // reads in a C++ program from a cpp file, and put it to the vector program
    load(program);

    vector< string > identifiers;
    string null;

    for (size_t i = 0; i < program.size(); i++)
    {
        delComment(program[i]); // deletes the comment beginning with "//" from program[ i ]
        delStrConsts(program[i]); // deletes all string constants from program[ i ]
        delCharConsts(program[i]); // deletes all character constants from program[ i ]

        if (program[i] != null)
            extractIdentifiers(program[i], identifiers);
        // extracts all identifiers from program[ i ], and put them into the vector identifiers
    }

    // stores all non-keyword strings in the vector identifiers into a text file
    store(identifiers);
}

void load(vector< string >& program)
{
    string filename;
    cin >> filename;

    ifstream in(filename); 
    if (!in) return;

    string line;
    while (getline(in, line))
    {
        program.push_back(line);
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
    bool isString = false;
    size_t i = 0;
    size_t len = sourceLine.length();

    while (i < len)
    {
        if (isString && sourceLine[i] == '\\')
        {
            sourceLine[i] = ' ';
            i++;
            if (i < len) sourceLine[i] = ' ';
        }
        else if (sourceLine[i] == '\"')
        {
            isString = !isString;
            sourceLine[i] = ' ';
        }
        else if (isString)
        {
            sourceLine[i] = ' ';
        }
        i++;
    }
}

void delCharConsts(string& sourceLine)
{
    bool isChar = false;
    size_t i = 0;
    size_t len = sourceLine.length();

    while (i < len)
    {
        if (isChar && sourceLine[i] == '\\')
        {
            sourceLine[i] = ' ';
            i++;
            if (i < len) sourceLine[i] = ' ';
        }
        else if (sourceLine[i] == '\'')
        {
            isChar = !isChar;
            sourceLine[i] = ' ';
        }
        else if (isChar)
        {
            sourceLine[i] = ' ';
        }
        i++;
    }
}

void extractIdentifiers(string& sourceLine, vector< string >& identifiers)
{
    size_t i = 0;
    size_t len = sourceLine.length();

    while (i < len)
    {
        if (!isalpha((unsigned char)sourceLine[i]) && sourceLine[i] != '_')
        {
            i++; continue;
        }

        string temp = "";
        while (i < len && (isalnum((unsigned char)sourceLine[i]) || sourceLine[i] == '_'))
        {
            temp += sourceLine[i];
            i++;
        }
        identifiers.push_back(temp);
        int currentPos = identifiers.size() - 1;
        if (keyword(temp) || duplicate(identifiers, currentPos))
        {
            identifiers.pop_back();
        }
    }
}

void store(vector< string >& identifiers)
{
    ofstream out("identifiers.txt");
    if (!out) return;

    for (size_t i = 0; i < identifiers.size(); i++)
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

bool duplicate(vector< string >& identifiers, int pos)
{
    for (int i = 0; i < pos; i++)
        if (identifiers[i] == identifiers[pos])
            return true;

    return false;
}
