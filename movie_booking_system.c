#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MOVIES 100
#define MAX_SEATS 10

typedef struct {
    char name[100];
    int seats[MAX_SEATS];
    float totalRating;
    int ratingCount;
} Movie;

Movie movies[MAX_MOVIES];
int movieCount = 0;

void saveData() {
    FILE *fp = fopen("movies.txt", "w");
    if (fp == NULL) return;
    fprintf(fp, "%d\n", movieCount);
    for (int i = 0; i < movieCount; i++) {
        fprintf(fp, "%s\n%d %.2f\n", movies[i].name, movies[i].ratingCount, movies[i].totalRating);
        for (int j = 0; j < MAX_SEATS; j++) fprintf(fp, "%d ", movies[i].seats[j]);
        fprintf(fp, "\n");
    }
    fclose(fp);
}

void loadData() {
    FILE *fp = fopen("movies.txt", "r");
    if (fp == NULL) {
        // Load default movies if file not found
        strcpy(movies[0].name, "Avengers: Endgame");
        strcpy(movies[1].name, "Inception");
        strcpy(movies[2].name, "Final Destination - Bloodline");
        strcpy(movies[3].name, "Housefull");
        strcpy(movies[4].name, "Interstellar");

        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < MAX_SEATS; j++) movies[i].seats[j] = 0;
            movies[i].totalRating = 0;
            movies[i].ratingCount = 0;
        }
        movieCount = 5;
        return;
    }

    fscanf(fp, "%d\n", &movieCount);
    for (int i = 0; i < movieCount; i++) {
        fgets(movies[i].name, sizeof(movies[i].name), fp);
        movies[i].name[strcspn(movies[i].name, "\n")] = '\0';
        fscanf(fp, "%d %f\n", &movies[i].ratingCount, &movies[i].totalRating);
        for (int j = 0; j < MAX_SEATS; j++) fscanf(fp, "%d", &movies[i].seats[j]);
        fscanf(fp, "\n");
    }
    fclose(fp);
}

void showMovies() {
    printf("\nAvailable Movies:\n");
    for (int i = 0; i < movieCount; i++) {
        float avg = movies[i].ratingCount ? movies[i].totalRating / movies[i].ratingCount : 0;
        printf("%d. %s [Rating: %.1f/5]\n", i + 1, movies[i].name, avg);
    }
}

void bookSeat(Movie *m) {
    int seat;
    printf("\nBooking for: %s\n", m->name);
    for (int i = 0; i < MAX_SEATS; i++)
        printf("Seat %d: %s\n", i + 1, m->seats[i] ? "Booked" : "Available");

    printf("Enter seat number to book (1-%d): ", MAX_SEATS);
    scanf("%d", &seat);
    if (seat < 1 || seat > MAX_SEATS || m->seats[seat - 1]) {
        printf("Invalid or already booked.\n");
    } else {
        m->seats[seat - 1] = 1;
        printf("Seat %d booked successfully.\n", seat);
    }
}

void cancelSeat(Movie *m) {
    int seat;
    printf("\nBooked Seats for: %s\n", m->name);
    int found = 0;
    for (int i = 0; i < MAX_SEATS; i++) {
        if (m->seats[i]) {
            printf("Seat %d\n", i + 1);
            found = 1;
        }
    }
    if (!found) {
        printf("No seats are booked.\n");
        return;
    }
    printf("Enter seat number to cancel: ");
    scanf("%d", &seat);
    if (seat < 1 || seat > MAX_SEATS || !m->seats[seat - 1]) {
        printf("Invalid or not booked.\n");
    } else {
        m->seats[seat - 1] = 0;
        printf("Seat %d booking cancelled.\n", seat);
    }
}

void rateMovie(Movie *m) {
    int rating;
    printf("Enter your rating for '%s' (1 to 5): ", m->name);
    scanf("%d", &rating);
    if (rating >= 1 && rating <= 5) {
        m->totalRating += rating;
        m->ratingCount++;
        printf("Thank you! Your rating has been recorded.\n");
    } else {
        printf("Invalid rating.\n");
    }
}

void addMovie() {
    if (movieCount >= MAX_MOVIES) {
        printf("Movie limit reached.\n");
        return;
    }
    getchar(); // flush newline
    printf("Enter new movie name: ");
    fgets(movies[movieCount].name, sizeof(movies[movieCount].name), stdin);
    movies[movieCount].name[strcspn(movies[movieCount].name, "\n")] = '\0';
    for (int i = 0; i < MAX_SEATS; i++) movies[movieCount].seats[i] = 0;
    movies[movieCount].totalRating = 0;
    movies[movieCount].ratingCount = 0;
    movieCount++;
    printf("Movie added successfully.\n");
}

void deleteMovie() {
    showMovies();
    printf("Enter the number of the movie to delete: ");
    int idx;
    scanf("%d", &idx);
    if (idx < 1 || idx > movieCount) {
        printf("Invalid choice.\n");
        return;
    }
    for (int i = idx - 1; i < movieCount - 1; i++) {
        movies[i] = movies[i + 1];
    }
    movieCount--;
    printf("Movie deleted successfully.\n");
}

void menu() {
    int choice, m;
    do {
        printf("\n--- Movie Ticket Booking System ---\n");
        printf("1. Show Movies\n");
        printf("2. Book Ticket\n");
        printf("3. Cancel Booking\n");
        printf("4. Rate Movie\n");
        printf("5. Add Movie\n");
        printf("6. Delete Movie\n");
        printf("7. Save and Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                showMovies();
                break;
            case 2:
                showMovies();
                printf("Choose movie number: ");
                scanf("%d", &m);
                if (m >= 1 && m <= movieCount) bookSeat(&movies[m - 1]);
                else printf("Invalid choice.\n");
                break;
            case 3:
                showMovies();
                printf("Choose movie number: ");
                scanf("%d", &m);
                if (m >= 1 && m <= movieCount) cancelSeat(&movies[m - 1]);
                else printf("Invalid choice.\n");
                break;
            case 4:
                showMovies();
                printf("Choose movie number: ");
                scanf("%d", &m);
                if (m >= 1 && m <= movieCount) rateMovie(&movies[m - 1]);
                else printf("Invalid choice.\n");
                break;
            case 5:
                addMovie();
                break;
            case 6:
                deleteMovie();
                break;
            case 7:
                saveData();
                printf("Data saved. Exiting...\n");
                return;
            default:
                printf("Invalid option.\n");
        }
    } while (1);
}

int main() {
    loadData();
    menu();
    return 0;
}
