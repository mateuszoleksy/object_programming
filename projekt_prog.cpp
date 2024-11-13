#include <iostream>
#include "movies.h"
#include "clients.h"
#include "shared.h"
#include <fstream>

using namespace shared;
using namespace movies;
using namespace clients;
using namespace std;

int main()
{
    string sequence {""};
    vector<string> dane;  // helper vector for data intialization
    vector<movies::movie> movies;
    vector<clients::client> clients;

    // #wypozyczanie jednym kliknieciem itd
    // wyszukiwanie
    // propozycje kiedy mija waznosc?
    // ustawienia czy cos
    // id filmu unikalne

    movies = movies::load();
    clients = clients::load();

        int operation {1};
        do 
        {   
            setconsolecolor(MOVIES_TEXT_COLOR, MOVIES_BACKGROUND_COLOR);
            cout << endl << "-------------------Movies--------------------: " << endl << endl;
            for (auto elem:movies)
            {
                elem.print();
            }
            setconsolecolor(CLIENT_TEXT_COLOR, CLIENT_BACKGROUND_COLOR);
            cout << endl << "--------------------Clients--------------------:" << endl << endl;
            for (auto elem:clients)
            {
                elem.print();
            }
            sequence = "";
            setconsolecolor(INTERFACE_TEXT_COLOR, INTERFACE_BACKGROUND_COLOR);
            cout << "Please enter a number of database to edit 0.Exit, 1. Clients, 2.Movies : ";
            cin >> operation;
            setconsolecolor(INTERFACE_TEXT_COLOR, INTERFACE_BACKGROUND_COLOR);
            if (operation == 0)
                break;
            switch (operation)
            {
                case 1:
                    cout << "Please enter the operation: \n 0. Cancel \n 1. Add new record \n 2. Delete the record \n 3. Modify the record" << endl;
                    cin >> operation;
                    switch (operation)
                    {
                        case 0:
                            break;
                        case 1:
                            add(clients);
                            reload(clients);
                            break;
                        case 2:
                            cout << "Enter number of the record: ";
                            cin >> operation;
                            if (operation <= clients.size()-1)
                                clients.erase(clients.begin()+operation);
                            reload(clients);
                            break;
                        case 3:
                            cout << "Enter number of the record: ";
                            cin >> operation;
                            if (operation <= clients.size()-1)
                                clients[operation].modificate(clients, operation, movies);
                            reload(clients);
                            break;
                        default:
                            break;
                    }
                    break;
                case 2:
                    cout << "Please enter the operation: \n 0. Cancel \n 1. Add new record \n 2. Modify the record \n 3. Delete the record:" << endl;
                    cin >> operation;
                    switch (operation)
                    {
                        case 0:
                            break;
                        case 1:
                            add(movies);
                            reload(movies);
                            break;
                        case 2:
                            cout << "Enter number of the record: ";
                            cin >> operation;
                            if (operation <= movies.size()-1)
                                modificate(movies, operation);
                            reload(movies);
                            break;
                        case 3:
                             cout << "Enter number of the record: ";
                            cin >> operation;
                            if (operation <= movies.size()-1)
                                movies.erase(movies.begin()+operation);
                            reload(movies);
                            break;
                        default:
                            break;
                    }
                    break;
                default:
                    break;
            }
            
        } while (1);

    return 0;
}