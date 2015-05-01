#include "MovieSeller.h"
#include <vector>
#include <iostream>

using namespace std;

//Constructor
MovieSeller::MovieSeller(int t)
{
    len = t;
    hashTable = new vector <Movie*> [t];
}


//Destructor
MovieSeller::~MovieSeller()
{
    // loop through the array and delete all elements
    for (int i = 0; i < len;i++)
    {
        for (int j = 0; j < hashTable[i].size();j++)
        {
            delete hashTable[i][j];
        }
    }
    // finally, delete the array
    delete[] hashTable;
}


/** \Function prototype:
 *  int MovieSeller::hashsum(string)
 *
 * \Function description:
 * This function calculates the hash code for a string by summing the ascii values of the individual elements of the string and % the sum by the size of the hash table.
 *
 * \Example:
 * HashTable ht
 * int sum = ht.hashsum("Toy Story")
 *
 * \Precondition:
 * hashLen is integer > 0. inputString is valid ascii string
 *
 * \Postcondition:
 * returns non negative integer
 */
int MovieSeller::hashsum(string s)
{
    int sum = 0;
    // Loop through the string and count up the ascii numbers and get a sum
    for (int i = 0; i< s.length();i++)
    {
        sum += (int)s[i];
    }

    return sum % len;
}


/** \Function prototype:
 *  void MovieSeller::insertMovie(string,int,int)
 *
 * \Function description:
 * This function creates a movie instance in the array of vectors. It gets the index of where it should be placed by the hashsum function and places it there.
 * It adds a year and price to the movie.
 *
 * \Example:
 * ht.insertMovie("Toy Story",1996,12)
 *
 * \Precondition:
 * year and price must be an integers => 0
 *
 * \Postcondition:
 * the movie is inserted into the array.
 */
void MovieSeller::insertMovie(std::string in_title, int in_year, int in_price)
{
    Movie *m = new Movie(in_title, in_year, in_price);
    //get the index by hashsum
    int index = hashsum(in_title);
    // if there is not a movie in that array index
    if(hashTable[index].size() == 0)
    {
        hashTable[index].push_back(m);
    }

    // Oh no! There is a collision in the HashTable! We will solve this by chaining the movies alphabetically.
    else
    {
        vector<Movie*>::iterator it = hashTable[index].begin();
        for(; it != hashTable[index].end(); it++)
        {
            //
            if((*it)->title.compare(in_title) >= 0)
            {
                break;
            }
        }
        hashTable[index].insert(it, m);
    }
}


/** \Function prototype:
 *  int MovieSeller::findMovie(string, int)
 *
 * \Function description:
 * This function hashsums the string from the input and with that information, finds the location of where the movie is in the array.
 * Then it finds and returns a pointer to that movie.
 *
 * \Example:
 * HashTable ht
 * int a;
 * Movie *b = ht.findMovie("Toy Story", &a)
 *
 * \Precondition:
 * Input string is a valid ascii string
 *
 * \Postcondition:
 * returns a pointer to the movie you input.
 */

Movie* MovieSeller::findMovie(std::string in_title, int *index)
{
    int i = hashsum(in_title);
    *index = i;

    for (int j = 0;j<hashTable[i].size();j++)
            {
                // if the movie is found return it
                if(hashTable[i][j]->title == in_title)
                {
                    return hashTable[i][j];
                }

            }
            // its not here
            cout<<"Not found"<<endl;
            return NULL;
}


/** \Function prototype:
 *  void MovieSeller::deleteMovie(string)
 *
 * \Function description:
 *  This method calculates the hashcode for the input movie name, and deletes the movie from the hash table. Handles cases where movie is first, mid, or last node in the chain.
 *
 * \Example:
 *  HashTable ht
 *  ht.deleteMovie("Toy Story")
 *
 * \Precondition:
 *  Unused locations in hashTable vector are NULL. Movies stored using correctly calculated hash code calculated from movie title. The input string name is movie title.
 * \Postcondition:
 *  movie node deleted from chain and memory freed. Pointers updated to bypass deleted movie.
 */
void MovieSeller::deleteMovie(std::string in_title)
{
    int del = hashsum(in_title);

        for(int j = 0; j < hashTable[del].size(); j++)
        {
                if(hashTable[del][j]->title == in_title)
                {
                    Movie* temp =  hashTable[del][j];
                    hashTable[del].erase(hashTable[del].begin() + j);
                    delete temp;
                }
        }

}


/** \Function prototype:
 *  void MovieSeller::printInventory()
 *
 * \Function description:
 * This function loops through the array of movies YOU HAVE INSERTED and each vector in the array and prints everything that is not NULL
 *
 * \Example:
 * HashTable ht
 * ht.printInventory()
 *
 * \Precondition:
 * A HashTable has been created.
 *
 * \Postcondition:
 *  everything in your movie hashtable has been printed
 */
void MovieSeller::printInventory()
{
    bool isempty = true;
    // loop through all indices in the array
    for (int i = 0;i < len; i++)
        {
                // loop through all vectors in the array and print
                for (int j = 0;j< hashTable[i].size();j++)
                {
                    //initialize as not empty
                    isempty = false;
                    cout << (hashTable[i])[j]->title << ":" <<(hashTable[i])[j]->year << endl;
                }
        }
        // there is nothing in the array
        if (isempty == true)
        {
            cout<<"Empty"<<endl;
        }
}


/** \Function prototype:
 *  int MovieSeller::sellMovie(string, &a)
 *
 * \Function description:
 * This function uses the find function to get the movie from the inventory. Then it inserts that same movie into a separate hashTable that contains all of
 * the SOLD MOVIES. Then it deletes that movie from the INVENTORY.
 *
 * \Example:
 * HashTable ht
 * HastTable a
 * int value = ht.sellMovie("Toy Story",a )
 *
 * \Precondition:
 * The function takes in the string of the movie to be deleted and also an instance of the class of deleted movies.
 *
 * \Postcondition:
 * returns non negative integer which is the value($) of the movie sold.
 */
int MovieSeller::sellMovie(string s, MovieSeller& m)
{
    int a;
    // grab the movie using the find function
    Movie* sold = findMovie(s,&a);
    // if the movie is not in the inventory
    if(sold == NULL)
    {
        cout<<"You do not own this movie"<<endl;
        return 0;
    }
    // insert into a separate hashTable of the SOLD MOVIES.
    m.insertMovie(s,sold->year,sold->price);
    // delete the movie from the hashTable of movies inserted.
    deleteMovie(s);
    // get the price of the movie
    int value = sold->price;
    cout<<"You have sold the movie "<< s << " and $"<< value << " has been added to your account"<<endl;
    // return what the value of the movie you sold
    return value;
}


/** \Function prototype:
 *  void MovieSeller::YearbubbleSort()
 *
 * \Function description:
 * This function is an implemented bubble sort algorithm. This sorts the movies in the inventory by Year
 *
 * \Example:
 * HashTable ht
 * ht.YearbubbleSort()
 *
 * \Precondition:
 *  Years for each movie should be integers > 0
 *
 * \Postcondition:
 * prints the movies in Ascending order by year.
 */
void MovieSeller::YearbubbleSort()
{
    vector <int> Years;

    for (int i = 0;i < len; i++)  // put all the years into a vector
        {
                for (int j = 0;j< hashTable[i].size();j++)
                {
                    int temp = (hashTable[i])[j]->year;
                    bool found = false;
                    for(int k = 0; k < Years.size(); k++){
                        if(Years[k] == temp){
                            found = true;
                        }
                    }
                    if(found == false){
                        Years.push_back((hashTable[i])[j]->year);
                    }
                }
        }

    // bubble sort the vector
    int s;
    for(int c = 0; c < Years.size()-1; c++)
    {
        for(int d = 0; d < Years.size() - c-1; d++)
        {
            if(Years[d] > Years[d+1])
            {
                s = Years[d];
                Years[d] = Years[d+1];
                Years[d+1] = s;
            }
        }
    }

    cout<<"sorted list, ascending order:"<<endl;
    // search the array of pointers to vectors and print them in sorted order
    for(int c = 0; c < Years.size(); c++)
        for (int i = 0;i < len; i++)
        {
            for (int j = 0;j< hashTable[i].size();j++)
            {
                if(Years[c] == (hashTable[i])[j]->year)
                {
                    cout<< (hashTable[i])[j]->title << ":" <<(hashTable[i])[j]->year <<endl;
                }
            }
        }

}



/** \Function prototype:
 *  int MovieSeller::alphabeticalBubbleSort()
 *
 * \Function description:
 * This function sorts the inventory of movies alphabetically using bubble sort.
 *
 * \Example:
 * HashTable ht
 * ht.alphabeticalBubbleSort()
 *
 * \Precondition:
 * all titles of movies are valid strings
 *
 * \Postcondition:
 * the movies in the inventory will sort alphabetically (A-Z)
 */
void MovieSeller::alphabeticalBubbleSort()
{
    vector <Movie*> titles;
    for (int i = 0;i < len; i++)  // put all the titles into a vector
        {
                for (int j = 0;j< hashTable[i].size();j++)
                {
                    titles.push_back((hashTable[i])[j]);
                }
        }


    // bubble sort
    Movie* s;
    for(int c = 0; c < titles.size()-1; c++)
    {
        for(int d = 0; d < titles.size() - c-1; d++)
        {
            if(titles[d]->title.compare(titles[d+1]->title) >= 0)
            {
                s = titles[d];
                titles[d] = titles[d+1];
                titles[d+1] = s;
            }
        }
    }

    // print that titles
    for (int i = 0;i<titles.size();i++)
    {
        cout<<titles[i]->title<<":"<< titles[i]->year<<endl;
    }


}


/** \Function prototype:
 *  int MovieSeller::printTimeperiod(int, int)
 *
 * \Function description:
 * This function prints movies if they are within a certain time range
 *
 * \Example:
 * HashTable ht
 * ht.printTimeperiod(1993,2001)
 *
 * \Precondition:
 * the start year must be less than the end year
 *
 * \Postcondition:
 *
 */
void MovieSeller::printTimeperiod(int s, int e)
{
    for (int i = 0;i < len; i++)  // loop and if they are between the years inputed print them
        {
                for (int j = 0;j< hashTable[i].size();j++)
                {
                    if(hashTable[i][j]->year <= e && hashTable[i][j]->year >= s)
                    {
                        cout<<hashTable[i][j]->title<<":"<< hashTable[i][j]->year<<endl;
                    }
                }
        }

}


/** \Function prototype:
 *  void MovieSeller::printHashTable()
 *
 * \Function description:
 * This function prints all the movies in th HashTable and shows which elements in the array are occupied and which are NULL
 *
 * \Example:
 * HashTable ht
 * ht.printHashTable()
 *
 * \Precondition:
 *
 *
 * \Postcondition:
 * prints the Hashtable showing which movies are where.
 */
void MovieSeller::printHashTable()
{
    for (int i = 0;i < len; i++)
    {
        // if that place in the array in NULL
        if (hashTable[i].empty())
        {
		cout<<i<<": NULL"<<endl;
        }
	else {
		cout << i << ": " << endl;
	        // when there are movies print them
        	for (int j = 0;j< hashTable[i].size();j++)
	        {
	            cout << "\t" << (hashTable[i])[j]->title << " (" <<(hashTable[i])[j]->year << ")" << endl;
	        }
	}
    }

}
