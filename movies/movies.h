#ifndef MOVIES_H_ // include guard
#define MOVIES_H_
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>

#include "../shared.h"
#include "../settings.h"

using namespace std;

namespace moviesClass
{
    // this class represents movies
    class movie
    {
        private:
        int index;
        string title;
        string author;
        string duration;
        string date;
        string genre;
        string description;
        int movieId;
        public:
        movie(void): index(0), movieId(0) {} ;
        friend int modify(vector <movie>& tab, int n);
        friend void add(vector <movie>& tab);
        friend void reload(vector <movie>& tab);
        movie(const int index, const string &titleEnter, const string &durationEnter, const string &dateEnter, const string &authorEnter, const string &genreEnter, const string &descriptionEnter, const int movieIdEnter):index(index),title(titleEnter),author(authorEnter),duration(durationEnter),genre(genreEnter),date(dateEnter),description(descriptionEnter),movieId(movieIdEnter) {};
        void print() const;
        void setterIndex(const int indexEnter) { index = indexEnter; };
        void setterTitle(const string &titleEnter) { title = titleEnter; };
        void setterAuthor(const string &authorEnter) { author = authorEnter; };
        void setterDuration(const string &durationEnter) { duration = durationEnter; };
        void setterDate(const string &dateEnter) { date = dateEnter; };
        void setterGenre(const string &genreEnter) { genre = genreEnter; };
        void setterDescription(const string &descriptionEnter) { description = descriptionEnter; };
        void setterMovieId(const int movieIdEnter) { movieId = movieIdEnter; };
        int getterIndex (void) const { return index; };
        string getterTitle(void) { return title; };
        string getterAuthor(void) { return author; };
        string getterDuration(void) { return duration; };
        string getterDate(void) { return date; };
        string getterGenre(void) { return genre; };
        string getterDescription(void) { return description; };
        int getterMovieId(void) const { return movieId; };
    };

    inline vector <movie> load(void)
    {
        // open main file which is database
        ifstream fileIn;
        vector<string> dane;
        string sequence;
        vector <movie> movies;
        fileIn.open(FILE_OUT_MOVIES);
        int counter {-1};
        if (fileIn.good())
        {
            // data enter from file to vector helper, tokanizer returns vector so does vector helper have to be simply vector type
            while (getline(fileIn, sequence))
            {
                dane = sharedClass::tokanizer(sequence, SEP);
                movie movie(++counter, dane[1], dane[2], dane[3], dane[4], dane[5], dane[6], ((counter==-1) ? 0 : stoi(dane[7])) );
                movies.push_back(movie);
                dane.clear();
            }
        }  
        // close file for movies database
        fileIn.close();

        return movies;
    }

    // method printing records
    inline void movie::print() const {
            if (index == 0)
                sharedClass::setConsoleColor(FIRST_ROW_TEXT_COLOR, FIRST_ROW_BACKGROUND_COLOR);
            else
                sharedClass::setConsoleColor(MOVIES_TEXT_COLOR, MOVIES_BACKGROUND_COLOR);
            std::cout << setw(20) << ((index==0) ? "Index" : to_string(index))  << setw(20) << title << setw(20) << author << setw(20) << duration << setw(20) << date << setw(20) << genre << setw(20) << description << setw(20) << ((index==0) ? "Movie Id" : to_string(movieId)) << endl;
        }

    inline bool movieIdUnique(vector <moviesClass::movie> const &movies, int const comparedValue) {
        for (auto elem : movies) {
            if (comparedValue == elem.getterMovieId()) {
                return false;
            }
        }
        return true;
    }

    inline void add(vector <movie>& tab) {
        movie helper;
        string sequence;
        bool helperValue {false};
        cin.ignore();
        do {
            std::cout << "Please enter, " << tab[0].title << ": ";
            getline(cin, sequence);
        } while (sequence.empty());
        helper.title = sequence;    
        if (sequence == "0")
            return;

        do {
            std::cout << "Please enter, " << tab[0].duration << ": ";
            getline(cin, sequence);
        }  while (sequence.empty());
        helper.duration = sequence;
        if (sequence == "0")
            return;

        do {
            std::cout << "Please enter, " << tab[0].date << ": ";
            getline(cin, sequence);
        } while (sequence.empty());
        helper.date = sequence;
        if (sequence == "0")
            return;

        do {
            std::cout << "Please enter, " << tab[0].author << ": ";
            getline(cin, sequence);
        } while (sequence.empty());
        helper.author = sequence;
        if (sequence == "0")
            return;

        do {
            std::cout << "Please enter, " << tab[0].genre << ": ";
            getline(cin, sequence);
        } while (sequence.empty());
        helper.genre = sequence;
        if (sequence == "0")
            return;

        do {
            std::cout << "Please enter, " << tab[0].description << ": ";
            getline(cin, sequence);
        } while (sequence.empty());
        helper.description = sequence;
        if (sequence == "0")
            return;

        do {
            std::cout << "Please enter, Movie ID: ";
            getline(cin, sequence);
            try {
                if ( stoi(sequence) <= 0)
                    throw 1;
                if ( !movieIdUnique(tab, stoi(sequence)) )
                    throw 2;
                helper.movieId = stoi(sequence);
                helperValue = true;
            } catch (...)
            {
                cout << "Conversion error, Movie ID must be an unique, positive integer." << endl;
            }
        } while (!sharedClass::isNumeric(sequence) || !helperValue);

        cout << "Success!" << endl;

        tab.push_back(helper);
    }

    inline void reload(vector <movie>& tab )
    {
        ofstream fileOut;
        int helper = -1;
        for (auto& elem:tab)
        {
            elem.setterIndex(++helper);
        }
        fileOut.open(FILE_OUT_MOVIES);
        for (auto elem:tab)
        {
            fileOut << ((elem.index == 0) ? "Index" : to_string(elem.index)) << SEP << elem.title << SEP << elem.duration << SEP << elem.date << SEP << elem.author << SEP << elem.genre << SEP << elem.description << SEP << ((elem.index == 0) ? "Movie ID" : to_string(elem.movieId)) << endl;
        }
        fileOut.close();
    }

    inline vector <int> searchMovies(const string &phrase, vector <moviesClass::movie> movies, const int moviesCategory)
   {
        string helper;
        vector <int> moviesIndex;
        int pos;
        for (int i = 1; i < movies.size(); i++)
        {
            helper =  to_string(movies[i].getterIndex());
            pos = helper.find(phrase);
            if ( pos != string::npos )
            {
                if (moviesCategory == 1 || moviesCategory == 0) {
                    moviesIndex.push_back(i);
                    continue;
                }
            }

            helper =  movies[i].getterTitle();
            pos = helper.find(phrase);
            if ( pos != string::npos )
            {
                if (moviesCategory == 2 || moviesCategory == 0) {
                    moviesIndex.push_back(i);
                    continue;
                }
            }

            helper =  movies[i].getterAuthor();
            pos = helper.find(phrase);
            if ( pos != string::npos )
            {
                if (moviesCategory == 3 || moviesCategory == 0) {
                    moviesIndex.push_back(i);
                    continue;
                }
            }

            helper =  movies[i].getterDuration();
            pos = helper.find(phrase);
            if ( pos != string::npos )
            {
                if (moviesCategory == 4 || moviesCategory == 0) {
                    moviesIndex.push_back(i);
                    continue;
                }
            }
            helper =  movies[i].getterGenre();
            pos = helper.find(phrase);
            if ( pos != string::npos )
            {
                if (moviesCategory == 5 || moviesCategory == 0) {
                    moviesIndex.push_back(i);
                    continue;
                }
            }


            helper =  movies[i].getterDate();
            pos = helper.find(phrase);
            if ( pos != string::npos )
            {
                if (moviesCategory == 6 || moviesCategory == 0) {
                    moviesIndex.push_back(i);
                    continue;
                }
            }


            helper =  movies[i].getterDescription();
            pos = helper.find(phrase);
            if ( pos != string::npos )
            {
                if (moviesCategory == 7 || moviesCategory == 0) {
                    moviesIndex.push_back(i);
                    continue;
                }
            }

            helper =  to_string(movies[i].getterMovieId());
            pos = helper.find(phrase);
            if ( pos != string::npos )
            {
                if (moviesCategory == 8 || moviesCategory == 0) {
                    moviesIndex.push_back(i);
                    continue;
                }
            }
        }


        return moviesIndex;
   }


    inline int modify(vector <movie>& tab, const int n)
    {
        string sequence = "";
        bool helperValue = false;
        movie helper = tab[n];
        cin.ignore();
        std::cout << "Please enter, " << tab[0].title << ": ";
        getline(cin, sequence);
        if (!sequence.empty())
            helper.title = sequence;

        std::cout << "Please enter, " << tab[0].duration << ": ";
        getline(cin, sequence);
        if (!sequence.empty())
            helper.duration = sequence;
        
       std::cout << "Please enter, " << tab[0].date << ": ";
        getline(cin, sequence);
        if (!sequence.empty())
            helper.date = sequence;

         std::cout << "Please enter, " << tab[0].author << ": ";
        getline(cin, sequence);
        if (!sequence.empty())
            helper.author = sequence;


         std::cout << "Please enter, " << tab[0].genre << ": ";
        getline(cin, sequence);
        if (!sequence.empty())
            helper.genre = sequence;

        std::cout << "Please enter, " << tab[0].description << ": ";
        getline(cin, sequence);
        if (!sequence.empty())
            helper.description = sequence;

        int old_value = 0;
        do {
            std::cout << "Please enter, Movie ID: ";
            getline(cin, sequence);
            try {
                if (sequence.empty()) {
                    helperValue = true;
                    continue;
                }
                if ( stoi(sequence) <= 0)
                    throw 1;
                if ( !movieIdUnique(tab, stoi(sequence)) )
                    throw 2;
                old_value = tab[n].movieId;
                helper.movieId = stoi(sequence);
                helperValue = true;
            } catch (...)
            {
                cout << "Conversion error, Movie ID must be an unique, positive integer." << endl;
            }
        } while (!sharedClass::isNumeric(sequence) || !helperValue);
        tab[n] = helper;

        return old_value;
    }
}

#endif