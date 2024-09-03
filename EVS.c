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
void registerVoter();
void castVote();
void getWinner();
void printInvalidOption();
int totalCandidates = 0;

struct Candidate {
    char name[100];
    int votes;
};

struct Candidate *candidates = NULL; // Dynamic array of candidates

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
    int choice;

    printf("\n--- Voter Panel ---\n");
    printf("1. Register Voter\n");
    printf("2. Cast Vote\n");
    printf("3. Back to Main Menu\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            registerVoter();
            break;
        case 2:
            castVote();
            break;
        case 3:
            return;
        default:
            printInvalidOption();
    }
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
    printf("Enter the number of candidates: ");
    scanf("%d", &totalCandidates);

    candidates = (struct Candidate *)malloc(totalCandidates * sizeof(struct Candidate));

    if (candidates == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    FILE *file = fopen("candidates.txt", "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    for (int i = 0; i < totalCandidates; i++) {
        printf("Enter the name of candidate %d: ", i + 1);
        clearInputBuffer();
        fgets(candidates[i].name, 100, stdin);
        candidates[i].name[strcspn(candidates[i].name, "\n")] = '\0'; // Remove newline character
        candidates[i].votes = 0;
        fprintf(file, "%s\n", candidates[i].name); // Write each candidate's name to the file
    }

    fclose(file);
    printf("Candidates saved.\n");
}

// Register Voter
void registerVoter() {
    char voterID[20];
    FILE *file = fopen("voters.txt", "a");

    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    printf("Enter your Voter ID: ");
    scanf("%s", voterID);

    fprintf(file, "%s\n", voterID); // Save the Voter ID to the file
    fclose(file);

    printf("Voter registered successfully.\n");
}

// Verify Voter ID
int verifyVoterID(char *voterID) {
    char id[20];
    FILE *file = fopen("voters.txt", "r");

    if (file == NULL) {
        printf("Error opening file.\n");
        return 0;
    }

    while (fgets(id, sizeof(id), file)) {
        id[strcspn(id, "\n")] = '\0'; // Remove newline character
        if (strcmp(id, voterID) == 0) {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

// Cast Vote
void castVote() {
    char voterID[20];
    int choice;

    printf("Enter your Voter ID: ");
    scanf("%s", voterID);

    if (!verifyVoterID(voterID)) {
        printf("Voter ID not registered.\n");
        return;
    }

    printf("Vote for your preferred candidate:\n");

    for (int i = 0; i < totalCandidates; i++) {
        printf("%d. %s\n", i + 1, candidates[i].name);
    }

    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (choice >= 1 && choice <= totalCandidates) {
        candidates[choice - 1].votes++;
        printf("Thank you for voting!\n");
    } else {
        printf("Invalid choice, vote not counted.\n");
    }
}

// Get Winner
void getWinner() {
    int maxVotes = -1;
    char winner[100];

    for (int i = 0; i < totalCandidates; i++) {
        if (candidates[i].votes > maxVotes) {
            maxVotes = candidates[i].votes;
            strcpy(winner, candidates[i].name);
        }
    }

    if (maxVotes == 0) {
        printf("No votes have been cast yet.\n");
    } else {
        printf("The winner is %s with %d votes.\n", winner, maxVotes);
    }
}

// Print Invalid Option
void printInvalidOption() {
    printf("Invalid option, please try again.\n");
}

// Main function
int main() {
    mainMenu();

    if (candidates != NULL) {
        free(candidates); // Free allocated memory
    }

    return 0;
}
