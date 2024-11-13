#ifndef MOVIES // include guard
#define MOVIES
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <windows.h>
#include "settings.h"
#include "shared.h"

using namespace std;
using namespace shared;

namespace movies
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
        movie(void) {};
        friend void modificate(vector <movie>& tab, int n);
        friend void add(vector <movie>& tab);
        friend void reload(vector <movie>& tab);
        movie(int index, string titleEnter, string durationEnter, string dateEnter, string authorEnter, string genreEnter, string descriptionEnter, int movieIdEnter):index(index),title(titleEnter),author(authorEnter),duration(durationEnter),genre(genreEnter),date(dateEnter),description(descriptionEnter),movieId(movieIdEnter) {};
        void print();
        void setterIndex(int indexEnter) { index = indexEnter; };
        void setterTitle(string titleEnter) { title = titleEnter; };
        void setterAuthor(string auhorEnter) { author = auhorEnter; };
        void setterDuration(string durationEnter) { duration = durationEnter; };
        void setterDate(string dateEnter) { date = dateEnter; };
        void setterGenre(string genreEnter) { genre = genreEnter; };
        void setterDescription(string descriptionEnter) { description = descriptionEnter; };
        void setterMovieId(int movieIdEnter) { movieId = movieIdEnter; };
        int getterIndex (void) { return index; };
        string getterTitle(void) { return title; };
        string getterAuthor(void) { return author; };
        string getterDuration(void) { return duration; };
        string getterDate(void) { return date; };
        string getterGenre(void) { return genre; };
        string getterDescription(void) { return description; };
        int getterMovieId(void) { return movieId; };
    };

    vector <movie> load(void)
    {
        // open main file which is database
        ifstream fileIn;
        vector<string> dane;
        string sequence;
        vector <movie> movies;
        fileIn.open(FILE_OUT_MOVIES);
        int licznik {-1};
        if (fileIn.good())
        {
            // data enter from file to vector helper, tokanizer returns vector so does vector helper have to be simply vector type
            while (getline(fileIn, sequence))
            {
                dane = tokanizer(sequence, SEP);
                movies::movie movie(++licznik, dane[1], dane[2], dane[3], dane[4], dane[5], dane[6], ((licznik==-1) ? 0 : stoi(dane[7])) );
                movies.push_back(movie);
                dane.clear();
            }
        }  
        // close file for movies database
        fileIn.close();

        return movies;
    }

    // method printing records
    void movie::print()
        {
            if (index == 0)
                 setconsolecolor(FIRST_ROW_TEXT_COLOR, FIRST_ROW_BACKGROUND_COLOR);
            else
                 setconsolecolor(MOVIES_TEXT_COLOR, MOVIES_BACKGROUND_COLOR);
            std::cout << setw(20) << ((index==0) ? "Index" : to_string(index))  << setw(20) << title << setw(20) << author << setw(20) << duration << setw(20) << date << setw(20) << genre << setw(20) << description << setw(20) << ((index==0) ? "Movie Id" : to_string(movieId)) << endl;
        }

    void add(vector <movie>& tab)
    {
        movie helper;
        string sequence;
        cin.ignore();
        std::cout << "Please enter, " << tab[0].title << ": ";
        getline(cin, sequence);
        helper.title = sequence;

        std::cout << "Please enter, " << tab[0].duration << ": ";
        getline(cin, sequence);
        helper.duration = sequence;
        
       std::cout << "Please enter, " << tab[0].date << ": ";
       getline(cin, sequence);
        helper.date = sequence;

         std::cout << "Please enter, " << tab[0].author << ": ";
        getline(cin, sequence);
        helper.author = sequence;

         std::cout << "Please enter, " << tab[0].genre << ": ";
        getline(cin, sequence);
        helper.genre = sequence;

         std::cout << "Please enter, " << tab[0].description << ": ";
        getline(cin, sequence);
        helper.description = sequence;

         std::cout << "Please enter, Movie ID: ";
        getline(cin, sequence);
        helper.movieId = stoi(sequence);

        tab.push_back(helper);
    }

    void reload(vector <movie>& tab )
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


void modificate(vector <movie>& tab, int n)
    {
        string sequence;
        cin.ignore();
        std::cout << "Please enter, " << tab[0].title << ": ";
        getline(cin, sequence);
        tab[n].title = sequence;

        std::cout << "Please enter, " << tab[0].duration << ": ";
        getline(cin, sequence);
        tab[n].duration = sequence;
        
       std::cout << "Please enter, " << tab[0].date << ": ";
        getline(cin, sequence);
        tab[n].date = sequence;

         std::cout << "Please enter, " << tab[0].author << ": ";
        getline(cin, sequence);
        tab[n].author = sequence;

         std::cout << "Please enter, " << tab[0].genre << ": ";
        getline(cin, sequence);
        tab[n].genre = sequence;

        std::cout << "Please enter, " << tab[0].description << ": ";
        getline(cin, sequence);
        tab[n].description = sequence;

         std::cout << "Please enter, Movie ID: ";
        getline(cin, sequence);
        tab[n].movieId = stoi(sequence);
    }
}


#endif