#ifndef CLIENTS
#define CLIENTS
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>
#include <windows.h>
#include "settings.h"
#include "shared.h"
#include "movies.h"

using namespace shared;
using namespace movies;

namespace clients
{
 // this class represents clients
    class client
    {
        private:
        string name;
        string surname;
        string pesel;
        int id;
        vector <string> rentalDate;
        vector <string> dueDate;
        vector <int> movieId;

        public:
        client(void){};
        friend void add (vector <client>& tab);
        friend void reload (vector <client>& tab);
        void modificate(vector <client>& tab, int n, vector <movies::movie> movies);
        void setterId(int idEnter) { id = idEnter; };
        int getterId(void) { return id; };
        void print();
        void printTwo();
        client(int idEnter, string nameEnter, string surnameEnter, string peselEnter, vector <string> rentalDateEnter, vector <string> dueDateEnter, vector <int> movieIdEnter):id(idEnter),name(nameEnter),surname(surnameEnter),pesel(peselEnter),rentalDate(rentalDateEnter),dueDate(dueDateEnter),movieId(movieIdEnter) {};
    };

    vector <client> load(void)
    {
         // open file for clients database
        ifstream fileIn;
        vector<string> dane;
        string sequence;
        vector <client> clients;
        fileIn.open(FILE_OUT_CLIENTS);
        int licznik {-1};
        if (fileIn.good())
        {
            while (getline(fileIn, sequence))
            {
                dane = tokanizer(sequence, SEP);
                clients::client client(++licznik, dane[1], dane[2], dane[3], ((dane[4]!="") ? tokanizer(dane[4], DATE_SEP) : vector <string> {}), ((dane[5]!="") ? tokanizer(dane[5], DATE_SEP) : vector <string> {}), ((licznik==-1 || dane[6]=="") ? vector <int> {} : stoiElem(tokanizer(dane[6], DATE_SEP))));
                clients.push_back(client);
                dane.clear();
            }
        }
        // close file for clients database
        fileIn.close();

        return clients;
    }

     void add(vector <client>& tab)
    {
        client helper;
        string sequence;
        cin.ignore();
        std::cout << "Please enter, " << tab[0].name << ": ";
        getline(cin, sequence);
        helper.name = sequence;

        std::cout << "Please enter, " << tab[0].surname << ": ";
        getline(cin, sequence);
        helper.surname = sequence;
        
        std::cout << "Please enter, " << tab[0].pesel << ": ";
        getline(cin, sequence);
        helper.pesel = sequence;

        helper.rentalDate = vector <string> {};
        helper.dueDate = vector <string> {};
        helper.movieId = vector <int> {};
    
        tab.push_back(helper);
    }

    void client::print()
    {
        if (id == 0)
                 setconsolecolor(FIRST_ROW_TEXT_COLOR, FIRST_ROW_BACKGROUND_COLOR);
        else
                 setconsolecolor(CLIENT_TEXT_COLOR, CLIENT_BACKGROUND_COLOR);
        std::cout << setw(20) << ((id==0) ? "Index" : to_string(id)) << setw(20) << name << setw(20) << surname << setw(20) << pesel;
        printTwo();
        cout << endl;
    }

        void client::printTwo()
    {
        for(int i = 0; i < rentalDate.size(); i++)
        {
            if (id != 0)
                if (i == 0)
                    std::cout << setw(20)  << to_string(i+1)+". "+rentalDate[i] << setw(20) << dueDate[i] << setw(20) << movieId[i] <<  endl;
                else
                    std::cout << setw(100) << to_string(i+1)+". "+ rentalDate[i] << setw(20) << dueDate[i] << setw(20) << movieId[i] << endl;
            else
                std::cout << setw(20) <<  rentalDate[0] << setw(20) << dueDate[0] << setw(20) << "Movie Id" << endl;
        }
    }

    void reload(vector <client>& tab)
    {
        ofstream fileOut;
        int helper = -1;
        for (auto& elem:tab)
        {
            elem.setterId(++helper);
        }
        fileOut.open(FILE_OUT_CLIENTS);
        int licznik = 0;
        for (auto elem:tab)
        {
            licznik = 0;
            fileOut << elem.id << SEP << elem.name << SEP << elem.surname << SEP << elem.pesel << SEP;
            for (auto record:elem.rentalDate)
            {
                 if (elem.id != 0 && ++licznik != elem.rentalDate.size())
                    fileOut << record << DATE_SEP;
                else
                    fileOut << record;
            }
            fileOut << SEP;
            licznik = 0;
            for (auto record:elem.dueDate)
            {
                 if (elem.id != 0 && ++licznik != elem.dueDate.size())
                    fileOut << record << DATE_SEP;
                else
                    fileOut << record;
            }
            fileOut << SEP;
            if (elem.id == 0)
                fileOut << "Movie ID";
            licznik = 0;
            for (auto record:elem.movieId)
            {
                if (++licznik != elem.movieId.size())
                    fileOut << record << DATE_SEP;
                else
                    fileOut << record;
            }
            fileOut << endl;
        }
        fileOut.close();
    }

    void client::modificate(vector <client> &tab, int n, vector <movies::movie> movies)
    {
        int op;
        string sequence;
        cin.ignore();
        if (n <= tab.size())
        {

        std::cout << "Please enter for " << n << " record, " << tab[0].name << ": ";
        getline(cin, sequence);
        if (!sequence.empty())
            tab[n].name = sequence;

        std::cout << "Please enter for " << n << " record, " << tab[0].surname << ": ";
        getline(cin, sequence);
        if (!sequence.empty())
            tab[n].surname = sequence;

        std::cout << "Please enter for " << n << " record, " << tab[0].pesel << ": ";
        getline(cin, sequence);
        if (!sequence.empty())
            tab[n].pesel = sequence;

        int help = 1;
        do
        {
            std::cout << "Please enter for " << n << " record, register/modify/del new movie rental. First choose number of operation: 0.end 1.add, 2.del sub-record, 3.modify, 4.del all: ";
            cin >> op;
            switch (op)
            {
                case 0:
                    help = 0;
                    break;
                case 1:
                    cin.ignore();
                    cout << "Please enter new record in " << tab[0].rentalDate[0] << ": ";
                    getline(cin, sequence);
                    tab[n].rentalDate.push_back(sequence);
                    cout << "Please enter new record in " << tab[0].dueDate[0] << ": ";
                    getline(cin, sequence);
                    tab[n].dueDate.push_back(sequence);
                    cout << "Please enter index of record of an movie" << ": ";
                    getline(cin, sequence);
                    tab[n].movieId.push_back(movies[stoi(sequence)].getterMovieId());
                    for (auto elem:tab)
                    {
                        elem.print();
                    }
                    break;
                case 2:
                    do {
                        cout << "Enter number of sub-record to del, or 0 to quit deleting: ";
                        cin >> op;
                        if (!op)
                            break;
                        if (op <= tab[n].rentalDate.size())
                        {
                            tab[n].rentalDate.erase(rentalDate.begin()+op);
                            tab[n].dueDate.erase(dueDate.begin()+op);
                            tab[n].movieId.erase(movieId.begin()+op);
                        }
                        for (auto elem:tab)
                        {
                            elem.print();
                        }
                        break;
                    } while(1);
                    break;
                case 3:
                    cout << "Please enter number of the sub-record: ";
                    cin >> op;
                    cin.ignore();
                    if (!op)
                        break;
                    cout << "Please enter, " << tab[0].rentalDate[0] << " ";
                    getline(cin, sequence);
                    if (!sequence.empty())
                        tab[n].rentalDate[op-1] = sequence;    
                    cout << "Please enter, " << tab[0].dueDate[0] << " ";
                    getline(cin, sequence);
                    if (!sequence.empty())
                        tab[n].dueDate[op-1] = sequence;    
                    cout << "Please enter, " << "index of a movie record" << ": ";
                    getline(cin, sequence);
                    if (!sequence.empty())
                        tab[n].movieId[op-1] = movies[stoi(sequence)].getterMovieId();  
                    for (auto elem:tab)
                    {
                        elem.print();
                    }
                    break;
                case 4:
                    tab[n].rentalDate.clear();
                    for (auto elem:tab)
                    {
                        elem.print();
                    }
                    break;
                default:
                    break;
            }
            
        } while (help);
        }
    }
    

}



#endif