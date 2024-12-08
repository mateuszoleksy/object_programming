#include <iostream>
#include <fstream>
#include "movies.h"
#include "clients.h"
#include "shared.h"
#include <conio.h>

using namespace std;

int main()
{
    string sequence;
    vector<int> helper;  // helper vector for searching
    vector<moviesClass::movie> movies;
    vector<clientsClass::client> clients;


    movies = moviesClass::load();
    clients = clientsClass::load();
    cout << "Press any key to start: "<< endl;

        int operation {1};
        string menu;
        do 
        {
            getch();
            system("cls");
            sharedClass::setConsoleColor(MOVIES_TEXT_COLOR, MOVIES_BACKGROUND_COLOR);
            cout << endl << "-------------------Movies--------------------: " << endl << endl;
            for (auto elem:movies)
            {
                elem.print();
            }
            sharedClass::setConsoleColor(CLIENT_TEXT_COLOR, CLIENT_BACKGROUND_COLOR);
            cout << endl << "--------------------Clients--------------------:" << endl << endl;
            for (auto elem:clients) {
                elem.print();
            }
            sequence = "";
            do {
                sharedClass::setConsoleColor(INTERFACE_TEXT_COLOR, INTERFACE_BACKGROUND_COLOR);
                cout << "Please enter a number of database to edit 0.Exit, 1. Clients, 2.Movies 3.Search: ";
                cin >> menu;
                sharedClass::setConsoleColor(INTERFACE_TEXT_COLOR, INTERFACE_BACKGROUND_COLOR);
            } while (!sharedClass::isNumeric(menu));
            operation = stoi(menu);
            if (operation == 0)
                break;
            switch (operation) {
                case 1:
                    do {
                        cout << "Please enter the operation: \n 0. Cancel \n 1. Add new record \n 2. Delete the record \n 3. Modify the record \n 4. Custom search:" << endl;
                        cin >> menu;
                    } while (!sharedClass::isNumeric(menu));
                operation = stoi(menu);
                switch (operation) {
                    case 0:
                        break;
                    case 1:
                        add(clients);
                        reload(clients);
                    break;
                    case 2:
                        do {
                            do {
                                cout << "Enter number of the record: ";
                                cin >> menu;
                            } while (!sharedClass::isNumeric(menu));
                            operation = stoi(menu);
                            if (operation <= clients.size()-1 && operation > 0)
                                clients.erase(clients.begin()+operation);
                            reload(clients);
                            for (auto elem:clients) {
                                elem.print();
                            }
                        } while (operation > 0);
                    break;
                    case 3:
                        do {
                            cout << "Enter number of the record: ";
                            cin >> menu;
                        } while(!sharedClass::isNumeric(menu));
                    operation = stoi(menu);
                    if (operation <= 0)
                        break;
                    if (operation <= clients.size()-1)
                        clients[operation].modify(clients, operation, movies);
                    reload(clients);
                    break;
                    case 4:
                        do {
                            cout << "Enter number of the search category: \n 0. Cancel \n 1. Index \n 2. " << clients[0].getterName() << " \n 3. " << clients[0].getterSurname() << " \n 4. " << clients[0].getterPesel() << " \n 5. " << clients[0].getterRentalDate()[0] << " \n 6. " << clients[0].getterDueDate()[0] << " \n 7. MovieID" << endl;
                            cin >> menu;
                        } while (!sharedClass::isNumeric(menu));
                        operation = stoi(menu);
                        cin.ignore();
                        cout << "Please enter the search phrase: " << endl;
                        getline(cin, menu);
                        switch (operation) {
                            case 1:
                                helper = clientsClass::searchClients(menu, clients, 1);
                            break;
                            case 2:
                                helper = clientsClass::searchClients(menu, clients, 2);
                            break;
                            case 3:
                                helper = clientsClass::searchClients(menu, clients, 3);
                            break;
                            case 4:
                                helper = clientsClass::searchClients(menu, clients, 4);
                            break;
                            case 5:
                                helper = clientsClass::searchClients(menu, clients, 5);
                            break;
                            case 6:
                                helper = clientsClass::searchClients(menu, clients, 6);
                            break;
                            case 7:
                                helper = clientsClass::searchClients(menu, clients, 7);
                            break;
                            default:
                                break;
                        }
                        sharedClass::setConsoleColor(CLIENT_TEXT_COLOR, CLIENT_BACKGROUND_COLOR);
                        if (helper.size() != 0)
                            cout << endl << "-------------------Clients-------------------: " << endl << endl;
                        for (int i = 0; i < helper.size(); i++)
                        {
                            clients[helper[i]].print();
                        }
                        helper.clear();
                        break;
                    default:
                        break;
                }
                break;
                case 2:
                        do {
                            cout << "Please enter the operation: \n 0. Cancel \n 1. Add new record \n 2. Modify the record \n 3. Delete the record: \n 4. Custom search:" << endl;
                            cin >> menu;
                        } while (!sharedClass::isNumeric(menu));
                    operation = stoi(menu);
                    switch (operation)
                    {
                        case 0:
                            break;
                        case 1:
                            add(movies);
                        reload(movies);
                        break;
                        case 2:
                            do {
                                cout << "Enter number of the record: ";
                                cin >> menu;
                            } while (!sharedClass::isNumeric(menu));
                        operation = stoi(menu);
                        if (operation == 0)
                            break;
                        if (operation <= movies.size()-1)
                            modify(movies, operation);
                        reload(movies);
                        break;
                        case 3:
                            do {
                                cout << "Enter number of the record: ";
                                cin >> menu;
                            } while (!sharedClass::isNumeric(menu));
                        operation = stoi(menu);
                        if (operation == 0)
                            break;
                        if (operation <= movies.size()-1)
                            movies.erase(movies.begin()+operation);
                        reload(movies);
                        break;
                        case 4:
                            do {
                                cout << "Enter number of the search category: \n 0. Cancel \n 1. Index \n 2. " << movies[0].getterTitle() << " \n 3. " << movies[0].getterAuthor() << " \n 4. " << movies[0].getterDuration() << " \n 5. " << movies[0].getterGenre() << " \n 6. " << movies[0].getterDate() << " \n 7. " << movies[0].getterDescription() << " \n 8. MovieID" << endl;
                                cin >> menu;
                            } while (!sharedClass::isNumeric(menu));
                        operation = stoi(menu);
                        cin.ignore();
                        cout << "Please enter the search phrase: " << endl;
                        getline(cin, menu);
                        switch (operation) {
                            case 1:
                                helper = moviesClass::searchMovies(menu, movies, 1);
                            break;
                            case 2:
                                helper = moviesClass::searchMovies(menu, movies, 2);
                            break;
                            case 3:
                                helper = moviesClass::searchMovies(menu, movies, 3);
                            break;
                            case 4:
                                helper = moviesClass::searchMovies(menu, movies, 4);
                            break;
                            case 5:
                                helper = moviesClass::searchMovies(menu, movies, 5);
                            break;
                            case 6:
                                helper = moviesClass::searchMovies(menu, movies, 6);
                            break;
                            case 7:
                                helper = moviesClass::searchMovies(menu, movies, 7);
                            break;
                            case 8:
                                helper = moviesClass::searchMovies(menu, movies, 8);
                            break;
                            default:
                                break;
                        }
                        sharedClass::setConsoleColor(MOVIES_TEXT_COLOR, MOVIES_BACKGROUND_COLOR);
                        if (helper.size() != 0)
                            cout << endl << "-------------------Movies--------------------: " << endl << endl;
                        for (int i = 0; i < helper.size(); i++)
                        {
                            movies[helper[i]].print();
                        }
                        helper.clear();
                        break;
                        default:
                            break;
                    }
                    sharedClass::setConsoleColor(INTERFACE_TEXT_COLOR, INTERFACE_BACKGROUND_COLOR);
                    cout << "End of search" << endl;
                    break;
                    case 3:
                        cout << "Please enter phrase to find in databases: ";
                    cin >> menu;
                    helper = moviesClass::searchMovies(menu, movies, 0);
                    cout << "Search results for: " << endl;
                    sharedClass::setConsoleColor(MOVIES_TEXT_COLOR, MOVIES_BACKGROUND_COLOR);
                    if (helper.size() != 0)
                        cout << endl << "-------------------Movies--------------------: " << endl << endl;
                    for (int i = 0; i < helper.size(); i++) {
                        movies[helper[i]].print();
                    }
                    helper = clientsClass::searchClients(menu, clients, 0);
                    sharedClass::setConsoleColor(CLIENT_TEXT_COLOR, CLIENT_BACKGROUND_COLOR);
                    if (helper.size() != 0)
                        cout << endl << "-------------------Clients-------------------: " << endl << endl;
                    for (int i = 0; i < helper.size(); i++)
                    {
                        clients[helper[i]].print();
                    }
                    sharedClass::setConsoleColor(INTERFACE_TEXT_COLOR, INTERFACE_BACKGROUND_COLOR);
                    cout << "End of search" << endl;
                    break;
                    default:
                        break;
                }
            cout << "Press any key to confirm:" << endl;

        } while (true);

    return 0;
}