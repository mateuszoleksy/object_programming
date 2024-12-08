#ifndef SHARED_H_
#define SHARED_H_

#include <string>
#include <vector>
#include <windows.h>

using namespace std;

namespace sharedClass {
    inline void setConsoleColor(const int textColor, const int bgColor) {
      SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (textColor + (bgColor * 16)));
   }

    inline bool isNumeric(const string &s)
   {
        for (int i = 0; i < s.size(); i++ )
        {
            if ((s[i]>='0' && s[i]<='9') == false)
                return false;
        }

        return true;
   }

    //main class
    inline vector <int> stoiElem(const vector <string> &tab)
    {
        vector <int> numbers;
        for (int i = 0; i < tab.size(); i++)
        {
        numbers.push_back(stoi(tab[i]));
        }

        return numbers;
    }

    // function for separation of words in string:str with given separator:sep
    inline vector<string> tokanizer(const string& str, const string& sep)
    {
        vector <string> vector;
        int index = 0;
        int indexOld = 0;
        do
        {
            index = str.find(sep, index);
            if(index >0 && index < str.size())
            {
                vector.push_back(str.substr(indexOld, index-indexOld));
                indexOld = index+1;
                index += sep.size();
            }
        } while (index != string::npos);
        vector.push_back(str.substr(indexOld, str.size()));
        return vector;
    }
}

#endif