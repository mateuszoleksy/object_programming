#include <iostream>
#include <fstream>
#include "movies.h"
#include "clients.h"
#include "shared.h"
#include <conio.h>

using namespace std;

int login(const string& user="", const string& pass="") {
    string name, password;
    string nameEnter=user, passwordEnter=pass, pesel;
    string mode; // if mode admin return 1, if mode client return 2, if no login return 0
    if (user.empty() && pass.empty()) {
        cout << "Enter username, password: ";
        cin >> nameEnter >> passwordEnter;
    }
    ifstream users;
    users.open("users.txt");
    while (users >> name >> password >> mode >> pesel) {
        if (name == nameEnter && passwordEnter == password && !nameEnter.empty() && !passwordEnter.empty()) {
            if (mode == "admin") {
                users.close();
                return 1;
            }
            if (mode == "standard")
                users.close();
                return stoi(pesel);
            }
        }
    users.close();
    return 0;
}

int register_record(int admin, vector <clientsClass::client> &tab) { // if admin 1, can provide admin mod
    string name, surname, password, modeEnter, username;
    bool helperValue = false;
    string nameEnter, passwordEnter, mode, peselEnter, surnameEnter, usernameEnter;
    do {
        cout << "Enter username, password, your real personal ID: ";
        cin >> username >> passwordEnter >> peselEnter;
        try {
            if (peselEnter.empty())
                throw 3;
            if (stoi(peselEnter) <= 0)
                throw 2;
            if (!clientsClass::peselUnique(tab, stoi(peselEnter)))
                throw 1;
            if (stoi(peselEnter) == 1)
                throw 4;
            helperValue = true;
        } catch (...)
        {
            cout << "Conversion error, bad format. Given pesel already exists or wrong format, pesel must be an unique, positive integer." << endl;
        }
    } while (!sharedClass::isNumeric(peselEnter) || !helperValue);

    if (login(username, passwordEnter) == 0) {
        ofstream users;
        users.open("users.txt", ios::app);
            string pesel;
            clientsClass::client helper;
            cout << "Enter an real name: " << endl;
            cin >> nameEnter;
            helper.setterName(nameEnter);
            cout << "Enter an real surname: " << endl;
            cin >> surnameEnter;
            helper.setterSurname(surnameEnter);
            helper.setterPesel(stoi(peselEnter));
            users << endl << username << " " << passwordEnter << " standard " << stoi(peselEnter);
            cout << "Registered successfully!\n";
            tab.push_back(helper);
            reload(tab);
            users.close();
            return 1;
    } else {
        cout << "Invalid username or password.\n";
    }
    return 0;
}

void deleteLineFromFile(const string& filename, int lineToDelete) {
    ifstream inputFile(filename);

    vector<string> lines;
    string line;
    int currentLine = 1;

    while (getline(inputFile, line)) {
        if (currentLine != lineToDelete) {
            lines.push_back(line);
        }
        currentLine++;
    }
    inputFile.close();

    ofstream outputFile(filename);

    for (size_t i = 0; i < lines.size(); ++i) {
        outputFile << lines[i];
        if (i != lines.size() - 1) {
            outputFile << '\n';
        }
    }
    outputFile.close();
}


int main()
{
    string sequence;
    vector<int> helper;  // helper vector for searching
    vector<moviesClass::movie> movies;
    vector<clientsClass::client> clients;

    int operation {1};
    string menu;
    int logged = 0;

    movies = moviesClass::load();
    clients = clientsClass::load();
    cout << "Welcome to DVD Rental Program!\n";
    do {
        do {
            cout << "0. Exit \n1. Login\n2. Register\n";
            cin >> menu;
        } while (!sharedClass::isNumeric(menu));

        operation = stoi(menu);
        switch (operation) {
            case 0:
                exit(0);
                break;
            case 1:
                logged = login();
                break;
            case 2:
                register_record(0, clients);
                break;
            default:
                logged = 0;
                break;
        }
    } while (!logged);

    cout << "Press any key to start: "<< endl;
    if (logged == 1) {
        do 
        {
            getch();
            system("cls");
            sharedClass::setConsoleColor(MOVIES_TEXT_COLOR, MOVIES_BACKGROUND_COLOR);
            cout << endl << "-------------------Movies--------------------: " << endl << endl;
            for (const auto& elem:movies)
            {
                elem.print();
            }
            sharedClass::setConsoleColor(CLIENT_TEXT_COLOR, CLIENT_BACKGROUND_COLOR);
            cout << endl << "--------------------Clients--------------------:" << endl << endl;
            for (const auto& elem:clients) {
                elem.print();
            }
            sequence = "";
            do {
                sharedClass::setConsoleColor(INTERFACE_TEXT_COLOR, INTERFACE_BACKGROUND_COLOR);
                cout << "Please enter a number of database to edit 0.Exit, 1. Clients, 2.Movies, 3.Search: ";
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
                            if (operation <= clients.size()-1 && operation > 0) {
                                string username, pass, pesel, mode;
                                ifstream userFile;
                                userFile.open("users.txt");
                                int index = 0;
                                while (userFile >> username >> pass >> mode >> pesel) {
                                    index++;
                                        if (clients[operation].getterPesel() == stoi(pesel)) {
                                            deleteLineFromFile("users.txt", index);
                                            break;
                                        }
                                }
                                clients.erase(clients.begin()+operation);
                            }
                            reload(clients);
                            for (const auto& elem:clients) {
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
                            cout << "Enter number of the search category: \n 0. All \n 1. Index \n 2. " << clients[0].getterName() << " \n 3. " << clients[0].getterSurname() << " \n 4. Pesel \n 5. " << clients[0].getterRentalDate()[0] << " \n 6. " << clients[0].getterDueDate()[0] << " \n 7. MovieID" << endl;
                            cin >> menu;
                        } while (!sharedClass::isNumeric(menu));
                    operation = stoi(menu);
                    cin.ignore();
                    cout << "Please enter the search phrase: " << endl;
                    getline(cin, menu);
                    switch (operation) {
                        case 0:
                            helper = clientsClass::searchClients(menu, clients, 0);
                        break;
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
                    if (!helper.empty())
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
                switch (operation) {
                    case 0:
                        break;
                    case 1:
                        add(movies);
                    reload(movies);
                    break;
                    case 2:
                        int old_value;
                    do {
                        cout << "Enter number of the record: ";
                        cin >> menu;
                    } while (!sharedClass::isNumeric(menu));
                    operation = stoi(menu);
                    if (operation <= 0)
                        break;
                    if (operation <= movies.size()-1)
                        old_value = modify(movies, operation);
                    // przeladuj indeksy
                    helper.clear();
                    for (auto &elem:clients) {
                        if (elem.getterId() != 0) {
                            for (auto elem2:elem.getterMovieId()) {
                                if (elem2 == old_value && old_value != 0){
                                    helper.push_back(movies[operation].getterMovieId());
                                } else {
                                    helper.push_back(elem2);
                                }
                            }
                            elem.setterMovieId(helper);
                            helper.clear();
                        }
                    }
                    helper.clear();
                    reload(movies);
                    reload(clients);
                    break;
                    case 3:
                        do {
                            cout << "Enter number of the record: ";
                            cin >> menu;
                        } while (!sharedClass::isNumeric(menu));
                    operation = stoi(menu);
                    if (operation <= 0)
                        break;
                    if (operation <= movies.size()-1)
                        movies.erase(movies.begin()+operation);
                    reload(movies);
                    break;
                    case 4:
                        do {
                            cout << "Enter number of the search category: \n 0. All \n 1. Index \n 2. " << movies[0].getterTitle() << " \n 3. " << movies[0].getterAuthor() << " \n 4. " << movies[0].getterDuration() << " \n 5. " << movies[0].getterGenre() << " \n 6. " << movies[0].getterDate() << " \n 7. " << movies[0].getterDescription() << " \n 8. MovieID" << endl;
                            cin >> menu;
                        } while (!sharedClass::isNumeric(menu));
                    operation = stoi(menu);
                    cin.ignore();
                    cout << "Please enter the search phrase: " << endl;
                    getline(cin, menu);
                    switch (operation) {
                        case 0:
                            helper = moviesClass::searchMovies(menu, movies, 0);
                        break;
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
                    if (!helper.empty())
                        cout << endl << "-------------------Movies--------------------: " << endl << endl;
                    for (int i : helper)
                    {
                        movies[i].print();
                    }
                    helper.clear();
                    sharedClass::setConsoleColor(INTERFACE_TEXT_COLOR, INTERFACE_BACKGROUND_COLOR);
                    cout << "End of search" << endl;
                    break;
                    default:
                        break;
                }
                break;
                case 3:
                    cout << "Please enter phrase to find in databases: ";
                cin >> menu;
                helper = moviesClass::searchMovies(menu, movies, 0);
                cout << "Search results for: " << endl;
                sharedClass::setConsoleColor(MOVIES_TEXT_COLOR, MOVIES_BACKGROUND_COLOR);
                if (!helper.empty())
                    cout << endl << "-------------------Movies--------------------: " << endl << endl;
                for (int i : helper) {
                    movies[i].print();
                }
                helper = clientsClass::searchClients(menu, clients, 0);
                sharedClass::setConsoleColor(CLIENT_TEXT_COLOR, CLIENT_BACKGROUND_COLOR);
                if (!helper.empty())
                    cout << endl << "-------------------Clients-------------------: " << endl << endl;
                for (int i : helper)
                {
                    clients[i].print();
                }
                sharedClass::setConsoleColor(INTERFACE_TEXT_COLOR, INTERFACE_BACKGROUND_COLOR);
                cout << "End of search" << endl;
                break;
                default:
                    break;
            }
            cout << "Press any key to confirm:" << endl;

        } while (true);
    } else if (logged > 1) {
        do
        {
            int index;
            getch();
            system("cls");
            sharedClass::setConsoleColor(MOVIES_TEXT_COLOR, MOVIES_BACKGROUND_COLOR);
            cout << endl << "-------------------Movies--------------------: " << endl << endl;
            for (const auto& elem:movies)
            {
                elem.print();
            }
            sharedClass::setConsoleColor(CLIENT_TEXT_COLOR, CLIENT_BACKGROUND_COLOR);
            cout << endl << "--------------------Clients--------------------:" << endl << endl;
            for (const auto& elem:clients) {
                if (elem.getterPesel() == logged || elem.getterId() == 0) {
                    elem.print();
                    index = elem.getterId();
                }
            }
            sequence = "";
            do {
                sharedClass::setConsoleColor(INTERFACE_TEXT_COLOR, INTERFACE_BACKGROUND_COLOR);
                cout << "Please enter a number of database to edit 0.Exit, 1.Search, 2.Rent an movie, 3. Return an movie, 4. Change username and password: ";
                cin >> menu;
                sharedClass::setConsoleColor(INTERFACE_TEXT_COLOR, INTERFACE_BACKGROUND_COLOR);
            } while (!sharedClass::isNumeric(menu));
            operation = stoi(menu);
            if (operation == 0)
                break;
            string passwd, userna;
            switch (operation) {
                case 1:
                    do {
                        cout << "Please enter the operation: \n 0. Cancel \n 1. Search \n" << endl;
                        cin >> menu;
                    } while (!sharedClass::isNumeric(menu));
                operation = stoi(menu);
                switch (operation) {
                    case 0:
                        break;
                    case 1:
                        do {
                            cout << "Enter number of the search category: \n 0. All \n 1. Index \n 2. " << movies[0].getterTitle() << " \n 3. " << movies[0].getterAuthor() << " \n 4. " << movies[0].getterDuration() << " \n 5. " << movies[0].getterGenre() << " \n 6. " << movies[0].getterDate() << " \n 7. " << movies[0].getterDescription() << " \n 8. MovieID" << endl;
                            cin >> menu;
                        } while (!sharedClass::isNumeric(menu));
                    operation = stoi(menu);
                    cin.ignore();
                    cout << "Please enter the search phrase: " << endl;
                    getline(cin, menu);
                    switch (operation) {
                        case 0:
                            helper = moviesClass::searchMovies(menu, movies, 0);
                        break;
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
                    if (!helper.empty())
                        cout << endl << "-------------------Movies--------------------: " << endl << endl;
                    for (int i : helper)
                    {
                        movies[i].print();
                    }
                    helper.clear();
                    sharedClass::setConsoleColor(INTERFACE_TEXT_COLOR, INTERFACE_BACKGROUND_COLOR);
                    cout << "End of search" << endl;
                    break;
                    default:
                        break;
                }
                break;
                case 2:
                    clientsClass::registerMovie(clients, movies, index);
                    break;
                case 3:
                    clientsClass::returnMovie(clients, movies, index);
                    break;
                case 4:
                    
                    do {
                        cout << "Enter new username: ";
                        cin >> userna;
                    } while (userna.empty());

                    do {
                        cout << "Enter new password: ";
                        cin >> passwd;
                    } while (passwd.empty());

                    if (!login(userna, passwd)) {
                        ifstream login;
                        login.open("users.txt");
                        string peselEnter;
                        string mode;
                        string passwordEnter;
                        string user;
                        vector <vector <string>> data;
                        while (login >> user >> passwordEnter >> mode >> peselEnter) {
                            vector <string> lines;
                            if (logged == stoi(peselEnter)) {
                                lines.push_back(userna);
                                lines.push_back(passwd);
                            }else {
                                lines.push_back(user);
                                lines.push_back(passwordEnter);
                            }
                            lines.push_back(mode);
                                lines.push_back(peselEnter);
                            data.push_back(lines);
                        }
                        login.close();
                        ofstream logout;
                        logout.open("users.txt");
                        for (int i = 0; i < data.size(); i++) {
                            if (i == data.size() - 1)
                                logout << data[i][0] << " " << data[i][1] << " " << data[i][2] << " " << data[i][3];
                            else
                                logout << data[i][0] << " " << data[i][1] << " " << data[i][2] << " " << data[i][3] << endl;
                        }
                        logout.close();
                    }
                    break;
                default:
                    break;
            }
            cout << "Press any key to confirm:" << endl;

        } while (true);
    }

    return 0;
}