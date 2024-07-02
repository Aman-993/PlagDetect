#include <bits/stdc++.h>
#define max 1000
using namespace std;

int levenshtein(const char *s, const char *t);
int max2(int a, int b);

int main() 
{
    char filename1[100], filename2[100];
    cout << "Enter file name 1: ";
    cin >> filename1;
    cout << "Enter file name 2: ";
    cin >> filename2;

    // Read the contents of the two files into strings
    string str1;
    string str2;
    string buffer;
    ifstream input1(filename1);
    while (getline(input1, buffer))
        str1 += (buffer + '\n');
    ifstream input2(filename2);
    while (getline(input2, buffer))
        str2 += (buffer + '\n');

    // Calculate plagiarism using Levenshtein distance
    float maximum = max2(str1.size(), str2.size());
    float leven = levenshtein(str1.c_str(), str2.c_str()) / maximum;
    float plag = (1 - leven) * 100;
    cout << plag << "% similarity" << endl;
    if (plag >= 50 && plag <= 100) {
        cout << "plagiarised" << endl;
    } else {
        cout << "not plagiarised" << endl;
    }

    return 0;
}

int max2(int a, int b)
{
    return a > b ? a : b;
}

int levenshtein(const char *s, const char *t)
{
    if (strcmp(s, t) == 0)
    {
        return 0;
    }
    if (strlen(s) == 0)
    {
        return strlen(t);
    }
    if (strlen(t) == 0)
    {
        return strlen(s);
    }
    int len1 = strlen(s);
    int len2 = strlen(t);
    int column[len1 + 1];
    for (int y = 1; y <= len1; y++)
        column[y] = y;
    for (int x = 1; x <= len2; x++) 
    {
        column[0] = x;
        int ld = x - 1;
        for (int y = 1; y <= len1; y++)
        {
            int od = column[y];
            column[y] = min({column[y] + 1, column[y - 1] + 1, ld + (s[y - 1] == t[x - 1] ? 0 : 1)});
            ld = od;
        }
    }
    return column[len1];
}
