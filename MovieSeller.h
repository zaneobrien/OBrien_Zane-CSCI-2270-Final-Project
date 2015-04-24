#ifndef MOVIESELLER_H
#define MOVIESELLER_H
#include <vector>
#include <string>

struct Movie{
    std::string title;
    int year;
    int price;


    Movie(){};

    Movie(std::string in_title, int in_year, int in_price)
    {
        title = in_title;
        year = in_year;
        price = in_price;

    }

};

class MovieSeller
{
    public:
        MovieSeller(int);
        ~MovieSeller();
        void insertMovie(std::string in_title, int in_year, int in_price);
        Movie* findMovie(std::string in_title, int *index);
        void deleteMovie(std::string in_title);
        void printInventory();
        int hashsum(std::string);
        void YearbubbleSort();
        void alphabeticalBubbleSort();
        int sellMovie(std::string in_title, MovieSeller& m);
        void printTimeperiod(int startyear, int endyear);
        void printHashTable();

    protected:
    private:
        std::vector <Movie*> *hashTable;
        int len;
};

#endif
