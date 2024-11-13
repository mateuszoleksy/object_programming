#ifndef SHARED
#define SHARED

#include <string>
#include <windows.h>
#include <vector>

using namespace std;

namespace shared
{

    void setconsolecolor(int textColor, int bgColor) {
      SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (textColor + (bgColor * 16)));
   }

    // function for separation of words in string:str with given separator:sep
    vector<string> tokanizer(const string& str, const string& sep)
    {
        vector <string> wektor;
        int index = 0;
        int indexold = 0;
    do
    {
        index = str.find(sep, index);
        if(index >0 && index < str.size())
        {
            wektor.push_back(str.substr(indexold, index-indexold));
        indexold = index+1;
        index += sep.size();
        }
    } while (index != string::npos);
        wektor.push_back(str.substr(indexold, str.size()));
        return wektor;
    }

    //main class
    vector <int> stoiElem(vector <string> tab)
    {
        vector <int> numbers;
        for (int i = 0; i < tab.size(); i++)
        {
        numbers.push_back(stoi(tab[i]));
        }

        return numbers;
    }
}


#endif