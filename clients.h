#ifndef CLIENTS_H
#define CLIENTS_H

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>

#include "movies.h"
#include "shared.h"
#include "settings.h"

using namespace std;

namespace clientsClass {
    // this class represents clients
    class client
    {
    private:
        string name;
        string surname;
        int pesel;
        int id;
        vector <string> rentalDate;
        vector <string> dueDate;
        vector <int> movieId;

    public:
        client(void): pesel(0), id(0) {};
        friend void add (vector <client>& tab);
        friend void reload (vector <client>& tab);
        void modify(vector <client>& tab, int n, vector <moviesClass::movie> movies);
        void setterId(const int idEnter) { id = idEnter; };
        int getterId(void) const { return id; };
        string getterName () { return name; };
        string getterSurname () { return surname; };
        int getterPesel () const { return pesel; };
        vector <string> getterRentalDate () { return rentalDate; };
        vector <string> getterDueDate () { return dueDate; };
        vector <int> getterMovieId () { return movieId; };
        void setterName (const string &nameEnter) { name = nameEnter; };
        void setterSurname (const string &surnameEnter) { surname = surnameEnter; };
        void setterPesel (const int peselEnter) { pesel = peselEnter; };
        void setterRentalDate (const vector <string> &rentalDateEnter ) { rentalDate = rentalDateEnter; };
        void setterDueDate (const vector <string> &dueDateEnter) { dueDate = dueDateEnter; };
        void setterMovieId (const vector <int> &movieIdEnter) { movieId = movieIdEnter; };
        void print() const;
        void printTwo() const;
        client(const int idEnter, const string &nameEnter, const string &surnameEnter, const int peselEnter, const vector <string> &rentalDateEnter, const vector <string> &dueDateEnter, const vector <int> &movieIdEnter):id(idEnter),name(nameEnter),surname(surnameEnter),pesel(peselEnter),rentalDate(rentalDateEnter),dueDate(dueDateEnter),movieId(movieIdEnter) {};
    };

    inline vector <client> load(void)
    {
        // open file for clients database
        ifstream fileIn;
        vector <client> clients;
        fileIn.open(FILE_OUT_CLIENTS);
        int counter {-1};
        if (fileIn.good()) {
            vector<string> dane;
            string sequence;
            while (getline(fileIn, sequence))
            {
                dane = sharedClass::tokanizer(sequence, SEP);
                clientsClass::client client(++counter, dane[1], dane[2], ((!sharedClass::isNumeric(dane[3])) ? 0 : stoi(dane[3])), ((dane[4]!="") ? sharedClass::tokanizer(dane[4], DATE_SEP) : vector <string> {}), ((dane[5]!="") ? sharedClass::tokanizer(dane[5], DATE_SEP) : vector <string> {}), ((counter==-1 || dane[6]=="") ? vector <int> {} : sharedClass::stoiElem(sharedClass::tokanizer(dane[6], DATE_SEP))));
                clients.push_back(client);
                dane.clear();
            }
        }
        // close file for clients database
        fileIn.close();

        return clients;
    }
    
    inline bool peselUnique(vector <client> const &clients, int const comparedValue) {
        for (auto elem : clients) {
            if (comparedValue == elem.getterPesel())
                return false;
        }
        return true;
    }

    inline void add(vector <client>& tab) {
        client helper;
        string sequence;
        cin.ignore();
        bool helperValue = false;
        do {
            std::cout << "Please enter, " << tab[0].name << ": ";
            getline(cin, sequence);
        } while (sequence.empty());
        helper.name = sequence;

        do {
            std::cout << "Please enter, " << tab[0].surname << ": ";
            getline(cin, sequence);
        } while (sequence.empty());
        helper.surname = sequence;
        
        do {
            std::cout << "Please enter, Pesel: ";
            getline(cin, sequence);
            try {
                if (stoi(sequence) <= 0)
                    throw 2;
                if (!peselUnique(tab, stoi(sequence)))
                    throw 1;
                helper.pesel = stoi(sequence);
                helperValue = true;
            } catch (...)
            {
                cout << "Conversion error, bad format. Pesel must an unique, positive integer." << endl;
            }
        } while (!sharedClass::isNumeric(sequence) || !helperValue);

        cout << "Success!" << endl;

        helper.rentalDate = vector <string> {};
        helper.dueDate = vector <string> {};
        helper.movieId = vector <int> {};
    
        tab.push_back(helper);
    }

    inline void client::print() const {
        if (id == 0)
            sharedClass::setConsoleColor(FIRST_ROW_TEXT_COLOR, FIRST_ROW_BACKGROUND_COLOR);
        else
            sharedClass::setConsoleColor(CLIENT_TEXT_COLOR, CLIENT_BACKGROUND_COLOR);
        std::cout << setw(20) << ((id==0) ? "Index" : to_string(id)) << setw(20) << name << setw(20) << surname << setw(20) << ((pesel==0) ? "Pesel" : to_string(pesel));
        printTwo();
        cout << endl;
    }

    inline void client::printTwo() const {
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

    inline void reload(vector <client>& tab) {
        ofstream fileOut;
        int helper = -1;
        for (auto& elem:tab)
        {
            elem.setterId(++helper);
        }
        fileOut.open(FILE_OUT_CLIENTS);
        int counter = 0;
        for (auto elem:tab)
        {
            counter = 0;
            fileOut << elem.id << SEP << elem.name << SEP << elem.surname << SEP << elem.pesel << SEP;
            for (auto record:elem.rentalDate)
            {
                if (elem.id != 0 && ++counter != elem.rentalDate.size())
                    fileOut << record << DATE_SEP;
                else
                    fileOut << record;
            }
            fileOut << SEP;
            counter = 0;
            for (auto record:elem.dueDate)
            {
                if (elem.id != 0 && ++counter != elem.dueDate.size())
                    fileOut << record << DATE_SEP;
                else
                    fileOut << record;
            }
            fileOut << SEP;
            if (elem.id == 0)
                fileOut << "Movie ID";
            counter = 0;
            for (auto record:elem.movieId)
            {
                if (++counter != elem.movieId.size())
                    fileOut << record << DATE_SEP;
                else
                    fileOut << record;
            }
            fileOut << endl;
        }
        fileOut.close();
    }

    inline void client::modify(vector <client> &tab, int n, vector <moviesClass::movie> movies)
    {
        int op = 0;
        cin.ignore();
        bool helper = false;
        if (n <= tab.size())
        {
            string sequence;

            std::cout << "Please enter for " << n << " record, " << tab[0].name << ": ";
            getline(cin, sequence);
            if (!sequence.empty())
                tab[n].name = sequence;

            std::cout << "Please enter for " << n << " record, " << tab[0].surname << ": ";
            getline(cin, sequence);
            if (!sequence.empty())
                tab[n].surname = sequence;

            do {
            std::cout << "Please enter for " << n << " record, Pesel: ";
            getline(cin, sequence);
            try {
                if (sequence.empty()) {
                    helper = true;
                    continue;
                }
                if (stoi(sequence) <= 0)
                    throw 2;
                if (!peselUnique(tab, stoi(sequence)))
                    throw 1;
                if (!sequence.empty())
                    tab[n].pesel = stoi(sequence);
                helper = true;
            } catch (...)
            {
                 cout << "Conversion error, bad format. Pesel must be an unique, positive integer." << endl;
            }
            } while (!sharedClass::isNumeric(sequence) || !helper);

            int help = true;
            do
            {
                sharedClass::setConsoleColor(INTERFACE_TEXT_COLOR, INTERFACE_BACKGROUND_COLOR);
                std::cout << "Please enter for " << n << " record, register/modify/del new movie rental. First choose number of operation: 0.end; 1.add; 2.del; sub-record; 3.modify; 4.del all: ";
                cin >> op;
                switch (op)
                {
                    case 0:
                        help = 0;
                        break;
                    case 1:
                        helper = false;
                        cin.ignore();
                        do {
                            cout << "Please enter new record in " << tab[0].rentalDate[0] << ": ";
                            getline(cin, sequence);
                        } while (!sequence.empty());
                        tab[n].rentalDate.push_back(sequence);
                        do {
                            cout << "Please enter new record in " << tab[0].dueDate[0] << ": ";
                            getline(cin, sequence);
                        } while (!sequence.empty());
                        tab[n].dueDate.push_back(sequence);
                        do {
                        cout << "Please enter index of record of an movie" << ": ";
                        getline(cin, sequence);

                        try {
                            if (stoi(sequence) > movies.size() || stoi(sequence) <= 0)
                                throw 1;
                            tab[n].movieId.push_back(movies[stoi(sequence)].getterMovieId());
                            helper = true;
                        } catch (...)
                        {
                            cout << "Conversion error, movie index must be valid movie index and an integer." << endl;
                            helper = false;
                        }
                        } while (!sharedClass::isNumeric(sequence) || !helper);
                        for (auto elem:tab)
                        {
                            elem.print();
                        }
                        break;
                    case 2:
                        do {
                            do {
                                cout << "Enter number of sub-record to del, or 0 to cancel: ";
                                cin >> sequence;
                            } while (!sharedClass::isNumeric(sequence));

                            op = stoi(sequence);
                            if (op <= 0)
                                break;
                            if (op-1 <= tab[n].rentalDate.size())
                            {
                                tab[n].rentalDate.erase(rentalDate.begin()+op-1);
                                tab[n].dueDate.erase(dueDate.begin()+op-1);
                                tab[n].movieId.erase(movieId.begin()+op-1);
                            }
                            for (auto elem:tab)
                            {
                                elem.print();
                            }
                            break;
                        } while(true);
                        break;
                    case 3:
                        helper = false;
                        do {
                            cout << "Please enter number of the sub-record or 0 to cancel: ";
                            cin >> sequence;
                        } while (!sharedClass::isNumeric(sequence));

                        op = stoi(sequence);
                        cin.ignore();
                        if (op <= 0 || op > tab[n].rentalDate.size())
                            break;
                        cout << "Please enter, " << tab[0].rentalDate[0] << " ";
                        getline(cin, sequence);
                        if (!sequence.empty())
                            tab[n].rentalDate[op-1] = sequence;
                        cout << "Please enter, " << tab[0].dueDate[0] << " ";
                        getline(cin, sequence);
                        if (!sequence.empty())
                            tab[n].dueDate[op-1] = sequence;
                        do {
                        cout << "Please enter, " << "index of a movie record" << ": ";
                        getline(cin, sequence);
                        try {
                            if (sequence.empty()) {
                                helper = true;
                                continue;
                            }
                            if (stoi(sequence) > movies.size() || stoi(sequence) <= 0)
                                throw 1;
                            if (!sequence.empty())
                                tab[n].movieId[op-1] = movies[stoi(sequence)].getterMovieId();
                            helper = true;
                        } catch (...)
                        {
                             cout << "Conversion error, movie index must be valid movie index and an integer." << endl;
                            helper = false;
                        }
                        } while (!sharedClass::isNumeric(sequence) || !helper) ;
                        for (auto elem:tab)
                        {
                            elem.print();
                        }
                        break;
                    case 4:
                        tab[n].rentalDate.clear();
                        tab[n].dueDate.clear();
                        tab[n].movieId.clear();
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

    inline vector <int> searchClients(const string &phrase, vector <clientsClass::client> clients, const int clientsCategory) {
        string helper;
        vector <string> helperTab;
        vector <int> clientsIndex;
        int pos;
        for (int i = 1; i < clients.size(); i++)
        {
            helper =  to_string(clients[i].getterId());
            pos = helper.find(phrase);
            if ( pos != string::npos )
            {
                if (clientsCategory == 1 || clientsCategory == 0)
                    clientsIndex.push_back(i);
                continue;
            }

            helper =  clients[i].getterName();
            pos = helper.find(phrase);
            if ( pos != string::npos )
            {
                if (clientsCategory == 2 || clientsCategory == 0)
                    clientsIndex.push_back(i);
                continue;
            }

            helper =  clients[i].getterSurname();
            pos = helper.find(phrase);
            if ( pos != string::npos )
            {
                if (clientsCategory == 3 || clientsCategory == 0)
                    clientsIndex.push_back(i);
                continue;
            }

            helper =  to_string(clients[i].getterPesel());
            pos = helper.find(phrase);
            if ( pos != string::npos )
            {
                if (clientsCategory == 4 || clientsCategory == 0)
                    clientsIndex.push_back(i);
                continue;
            }

            helperTab =  clients[i].getterRentalDate();
            for (auto elem:helperTab)
            {
                pos = elem.find(phrase);
                if ( pos != string::npos )
                {
                    if (clientsCategory == 5 || clientsCategory == 0)
                        clientsIndex.push_back(i);
                    break;
                }
            }
            helperTab.clear();
            if (pos != string::npos)
                continue;

            helperTab =  clients[i].getterDueDate();
            for (auto elem:helperTab)
            {
                pos = elem.find(phrase);
                if ( pos != string::npos )
                {
                    if (clientsCategory == 5 || clientsCategory == 0)
                        clientsIndex.push_back(i);
                    break;
                }
            }
            helperTab.clear();
            if (pos != string::npos)
                continue;

            for (auto elem:clients[i].getterMovieId())
            {
                helperTab.push_back(to_string(elem));
            }
            for (auto elem:helperTab)
            {
                pos = elem.find(phrase);
                if ( pos != string::npos )
                {
                    if (clientsCategory == 5 || clientsCategory == 0)
                        clientsIndex.push_back(i);
                    break;
                }
            }
            if (pos != string::npos)
                continue;
        }

        return clientsIndex;
    }

}

#endif