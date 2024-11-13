#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iomanip>

#define SEP "&"

using namespace std;

vector <string> tokanizer(const string& str, const string& sep)
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

void print(vector<string>nazwa)
    {
        for(auto elem:nazwa)
        {
            cout << setw(20) << elem ;
        }
        cout << endl;
    }

int main()
{
    string sequence {""};
    int size {0};
    vector <vector <string>> dane;
    ifstream fileIn;
    ofstream fileOut;
    vector <string> pomocniczny;
    fileIn.open("baza.txt");
    int licznik {-1};
    if (fileIn.good())
    {
        while (getline(fileIn, sequence))
        {
            dane.push_back(tokanizer(sequence, SEP));
            licznik++;
        }
        fileIn.close();
        int operation {1};
        do 
        {   
            cout << endl << "Lista najlepszych trackow: " << endl << endl;
            for (int i=0; i < dane.size(); i++)
            {
                print(dane[i]);
            }
            sequence = "";
            cout << "Co chcesz zrobic: \n 0.Wyjsc \n 1.Dodac rekord \n 2.Usunac rekord \n 3.Modyfikacja rekordu: " << endl;
            cin >> operation;
            if (operation == 0)
                break;
        switch (operation)
        {
            case 1:
                pomocniczny.push_back(to_string(++licznik));
                cout << "Rekord nr " << licznik << " " << endl;
                cin.ignore();
                for (int i=1; i<dane[0].size(); i++)
                {
                    cout << "Prosze podac " << dane[0][i] << " :" << endl;
                    getline(cin, sequence);
                    pomocniczny.push_back(sequence);
                }
                fileOut.open("baza.txt", std::ios_base::app);
                fileOut << endl << licznik << SEP;
                dane.push_back(pomocniczny);
                for (int i=1; i<dane.size(); i++)
                {
                    fileOut << i << SEP;
                    for (int y = 1; y < dane[0].size(); y++)
                    {
                        fileOut << dane[i][y];
                         if (y!=dane[0].size()-1)
                            fileOut << SEP;
                    }
                    fileOut << endl;
                }
                fileOut.close();
                size = pomocniczny.size();
                for (int i=0; i < size; i++)
                {
                    pomocniczny.pop_back();
                }
                break;
            case 2:
                cout << "Ktory rekord chcesz usunac (0 - anuluj):" << endl;
                cin >> operation;
                if (operation == 0 || operation > dane.size()-1)
                    break;
                fileOut.open("baza.txt");
                licznik--;
                dane.erase(dane.begin() + operation);
                // aktualizuj indeksy
                for (int i=1; i<dane.size(); i++)
                {
                    dane[i][0] = to_string(i);
                }
                cout << " Zapisuje dane do pliku... " << endl;
               for (int i = 0; i < dane[0].size(); i++)
               {
                fileOut << dane[0][i];
                if (i!=dane[0].size()-1)
                    fileOut << SEP;
               }
               fileOut << endl;
                for (int i=1; i<dane.size(); i++)
                {
                    fileOut << i << SEP;
                    for (int y = 1; y < dane[0].size(); y++)
                    {
                        fileOut << dane[i][y];
                         if (y!=dane[0].size()-1)
                            fileOut << SEP;
                    }
                    fileOut << endl;
                }
                cout << "... done " << endl;
                fileOut.close();
                break;
            case 3:
                cout << "Ktory rekord chcesz modyfikowac (0 - anuluj):" << endl;
                cin >> operation;
                if (operation == 0 || operation > dane.size()-1)
                    break;
                fileOut.open("baza.txt");
                sequence = "";
                cin.ignore();
                pomocniczny.push_back(to_string(operation));
                for (int i=1; i<dane[0].size(); i++)
                {
                    cout << "Prosze podac " << dane[0][i] << " :" << endl;
                    getline(cin, sequence);
                    pomocniczny.push_back(sequence);
                }
                dane[operation] = pomocniczny;
                size = pomocniczny.size();
                for (int i=0; i < size; i++)
                {
                    pomocniczny.pop_back();
                }
                print(pomocniczny);
                cout << " Zapisuje dane do pliku... " << endl;
                  for (int i = 0; i < dane[0].size(); i++)
               {
                fileOut << dane[0][i];
                if (i!=dane[0].size()-1)
                    fileOut << SEP;
               }
               fileOut << endl;
                for (int i=1; i<dane.size(); i++)
                { 
                    fileOut << i << SEP;
                    for (int y = 1; y < dane[0].size(); y++)
                    {
                        fileOut << dane[i][y];
                         if (y!=dane[0].size()-1)
                            fileOut << SEP;
                    }
                    fileOut << endl;
                }
                cout << "... done " << endl;
                fileOut.close();
            default:
                break;
        } 
        } while (1);
    }
    fileOut.close();
    return 0;
}