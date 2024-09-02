#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function prototypes
void adminPanel();
void authenticateAdmin();
void initiateNewElection();
void saveElectionInfoInFile();
void createCandidatesFiles();
void voterPanel();
void getWinner();
void printInvalidOption();

// Function to clear the input buffer
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Main menu
void mainMenu() {
    int choice;

    while (1) {
        printf("\n--- Main Menu ---\n");
        printf("1. Admin Panel\n");
        printf("2. Voter Panel\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                adminPanel();
                break;
            case 2:
                voterPanel();
                break;
            case 3:
                exit(0);
                break;
            default:
                printInvalidOption();
        }
    }
}

// Admin Panel
void adminPanel() {
    authenticateAdmin();
    int choice;

    while (1) {
        printf("\n--- Admin Panel ---\n");
        printf("1. Initiate New Election\n");
        printf("2. Continue Previous Election\n");
        printf("3. View Results\n");
        printf("4. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                initiateNewElection();
                break;
            case 2:
                printf("Continue Previous Election is selected.\n");
                // Implementation needed here.
                break;
            case 3:
                getWinner();
                break;
            case 4:
                return;
            default:
                printInvalidOption();
        }
    }
}

// Voter Panel
void voterPanel() {
    printf("\n--- Voter Panel ---\n");
    // Implementation for voter functionalities.
}

// Authenticate Admin
void authenticateAdmin() {
    char username[20], password[20];

    printf("Enter Admin Username: ");
    scanf("%s", username);
    printf("Enter Admin Password: ");
    scanf("%s", password);

    if (strcmp(username, "admin") == 0 && strcmp(password, "password") == 0) {
        printf("Logged in successfully.\n");
    } else {
        printf("Wrong username/password.\n");
        exit(0);
    }
}

// Initiate New Election
void initiateNewElection() {
    printf("New Election initiated.\n");
    saveElectionInfoInFile();
    createCandidatesFiles();
}

// Save Election Info in File
void saveElectionInfoInFile() {
    FILE *file = fopen("election_info.txt", "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    // Save election details to file (implement as needed)
    fprintf(file, "Election Info\n");
    fclose(file);
}

// Create Candidates Files
void createCandidatesFiles() {
    FILE *file = fopen("candidates.txt", "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    // Add candidate details (implement as needed)
    fprintf(file, "Candidate1\nCandidate2\n");
    fclose(file);
}

// Get Winner
void getWinner() {
    printf("Winner is calculated.\n");
    // Implementation for calculating the winner
}

// Print Invalid Option
void printInvalidOption() {
    printf("Invalid option, please try again.\n");
}

// Main function
int main() {
    mainMenu();
    return 0;
}
