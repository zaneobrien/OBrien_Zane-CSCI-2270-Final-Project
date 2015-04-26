# OBrien_Zane-Final-Project
CSCI 2270

Project	Summary:
  My project builds off of Assignment 9 which only allowed the user to insert, delete, find, and display movies that were entered in by the user. My Final project allows the user to have many more options like selling movies, sorting the movies by year, sorting alphabetically (A-Z), displaying money made from selling movies, and displaying movies from a certain time period. Each movie struct will now include a price. 
  
How to Run:

  The user is immediately prompted with a main menu:
  
  ======Main Menu======
  1. Insert movie
  2. Delete movie
  3. Find movie in inventory
  4. Sort by Year (Ascending)
  5. Sort by Name (A-Z)
  6. Sell Movie
  7. Print movies sold
  8. Print current inventory
  9. Show hash table
  10. Print movies in time range
  11. Total Profit
  12. Quit
  // The user can choose from all of these option

  // The most common input is inserting a movie
  
  // Here is an example of inserting a movie into the inventory
  
  1
  Enter Title:
  "Toy Story"
  Enter Year:
  1995
  Enter price:
  20
  // this will enter "Toy Story" with a year of 1995 and a price of $20 into the inventory Hashtable


Dependencies:
  My program	does not rely on any third-party libraries that	needs	to	be	
installed.

System	Requirements:
My program will run on Windows,	Mac, Linux?	There	are no additional	system	
requirements other than the operating	system.

Group	Members:
  No group members

Contributors:
List	the	people	who	were	not	on	the	project	team,	but	may	have contributed	
comments,	enhancements,	and	bug	fixes.

Open	issues/bugs
- The way I had to implement the Bubble sort function seems to be really inefficent.
- Improve the printHashTable function. It is hard to visualize the hashTable 
- the bubble sort for years has a bug when there are movies with the same year.
