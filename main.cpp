#include <iostream>
#include "MovieSeller.h"
#include <stdlib.h>


using namespace std;

int main()
{
    string choice;
    //Hash Table of movies in inventory
    MovieSeller h = MovieSeller(10);
    //HashTable of movies sold
    MovieSeller f = MovieSeller(10);
    int profit = 0;

    while( choice != "13" )
    {

    cout << "======Main Menu======" << endl;
    cout << "1. Insert movie" << endl;
    cout << "2. Delete movie" << endl;
    cout << "3. Find movie in inventory" << endl;
    cout << "4. Sort by Year (Ascending)" << endl;
    cout << "5. Sort by Name (A-Z)" << endl;
    cout << "6. Sell Movie" << endl;
    cout << "7. Print movies sold" << endl;
    cout << "8. Print current inventory" << endl;
    cout << "9. Show hash table" << endl;
    cout << "10. Print movies in time range" << endl;
    cout << "11. Total Profit" << endl;
    cout << "12. Read movies in from file" << endl;
    cout << "13. Quit" << endl;

    getline(cin,choice);

        if(choice == "1")
        {
            string title;
            string syear;
            int year;
            int price;
            string sprice;
            cout << "Enter title:" << endl;
            getline(cin,title);
            cout << "Enter year:" << endl;
            getline(cin,syear);
            year = atoi(syear.c_str());
            cout<< "Enter price:"<<endl;
            getline(cin,sprice);
            price = atoi(sprice.c_str());

            h.insertMovie(title,year, price);
        }

        else if (choice == "2")
        {
            string title;
            cout << "Enter title:" << endl;
            getline(cin,title);
            h.deleteMovie(title);
        }
        else if (choice == "3")
        {
            string title;
            int a;
            Movie* b;
            cout << "Enter title:" << endl;
            getline(cin,title);
            b = h.findMovie(title, &a);
            if (b != NULL)
            {
                cout<<a << ":" <<title<< ":"<<b->year<< ":"<< b->price<<endl;
            }
        }

        else if (choice == "4")
        {
            h.YearbubbleSort();
        }

        else if(choice == "5")
        {
            h.alphabeticalBubbleSort();
        }
        else if(choice == "6")
        {
            string selling;
            cout<< "Which movie do you want to sell"<<endl;
            getline(cin, selling);
            // value is the amount the movie is worth.
            int value = h.sellMovie(selling,f);
            // for all movies that are sold, keep adding them to the profit.
            profit += value;
        }
        else if (choice == "7")
        {
            f.printInventory();

        }
        else if (choice == "8")
        {
            h.printInventory();
        }
        else if (choice == "9")
        {
            h.printHashTable();
        }
        else if (choice == "10")
        {
            string startyear;
            string endyear;
            cout<<"Start year: "<<endl;
            getline(cin,startyear);
            cout<<"End year: "<<endl;
            getline(cin,endyear);

            h.printTimeperiod(atoi(startyear.c_str()),atoi(endyear.c_str()));
        }
        else if (choice == "11")
        {
            cout<<"----------- Statement ------------"<<endl;
            cout<<"You have made: $" <<profit<<endl;
        }

        else if (choice == "12")
        {
            string fileName;
            cout << "Enter filename:" << endl;
            getline(cin,fileName);
            h.readMoviesFromFile(fileName);
        }
        else if (choice == "13")
        {
            cout << "Goodbye!" << endl;
            break;
        }
        else
        {
            cout<<"Choose a correct option"<<endl;
        }


    }


}
