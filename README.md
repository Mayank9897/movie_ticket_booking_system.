# movie_ticket_booking_system.

Created by: Mayank Dobhal
BCA First Year Student
This is my first C language project. I am a beginner and made this project to learn the basics of programming and file handling.

About the Project
This is a simple command-line project made in the C programming language. It allows a user to:
View available movies
Book seats for a movie
Cancel a booking
Rate a movie
Add a new movie
Delete an existing movie
Save and load all data using file handling

The project stores data like movie names, seat booking status, and ratings in a file so that the data is saved even after the program is closed.

How the Project Works
When the program starts, it loads movie data from a file named movies.txt
If the file is not available, it adds 5 default movies automatically.
A menu is displayed where the user can select actions such as booking a seat or adding a new movie.
After the user exits, all changes are saved in the movies.txt file.

Code Explanation-
loadData()
Reads movie details from movies.txt.
If the file doesn’t exist, it loads 5 default movies.
It initializes all seat data and ratings.

showMovies()
Shows all available movies with their average rating.

bookSeat()
Displays the 10 seats for the selected movie.
Allows the user to choose a seat and marks it as booked.

cancelSeat()
Shows the seats that are already booked.
Lets the user cancel a booking for a specific seat.

rateMovie()
Asks the user to enter a rating between 1 and 5.
Updates the total rating and rating count for the movie.

addMovie()
Lets the user type the name of a new movie.
Adds it with all seats available and rating set to 0.

deleteMovie()
Displays all movies.
Allows the user to remove any one from the list.

saveData()
Saves the movie list, ratings, and seat status to movies.txt.

menu()
The main function that shows the menu repeatedly until the user chooses to exit.

main()
Starts the program by loading data and calling the menu.

Files Used
movies.txt: This file stores movie names, ratings, and seat booking data. It is used to save and load data between runs.

Note
This project was made for learning purposes. It uses simple logic and C features like arrays, structures, file handling, loops, and conditionals.
If you are also a beginner in C programming, you can use this project to understand how basic booking systems work.
