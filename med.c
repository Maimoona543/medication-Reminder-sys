#include <stdio.h>
#include <string.h>

#define MAX 50
#define FILE_NAME "meds.txt"

// 1. STRUCTURE
struct Medicine
{
    int id;
    char name[30];
    char time[15];
    int pills;
    int taken;
    int missed;
};

// FUNCTION PROTOTYPES (using pointers)
void loadData(struct Medicine *meds, int *count);
void saveData(const struct Medicine *meds, int count);
void addMed(struct Medicine *meds, int *count);
void showMedsRecursive(const struct Medicine *meds, int index, int count);                               // RECURSION
void searchMedRecursive(const struct Medicine *meds, int index, int count, const char *key, int *found); // RECURSION
void checkDose(struct Medicine *meds, int count);
void deleteMed(struct Medicine *meds, int *count);
void clearInputBuffer(void);

int main()
{
    struct Medicine meds[MAX]; // Array of structures
    int count = 0;             // Total medicines stored
    int choice = 0;

    // Load saved medicines from file when program starts
    loadData(meds, &count);

    // DO-WHILE LOOP keeps menu running until user chooses 6
    do
    {
        printf("\n=========================================\n");
        printf("        MEDICATION REMINDER SYSTEM       \n");
        printf("=========================================\n");
        printf("1. Add Medicine\n");
        printf("2. View All Medicines\n");
        printf("3. Search Medicine by Name\n");
        printf("4. Mark Dose (Taken / Missed)\n");
        printf("5. Delete Medicine\n");
        printf("6. Save & Exit\n");
        printf("Enter choice: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input! Please enter a number.\n");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();

        switch (choice)
        {
        case 1:
            addMed(meds, &count);
            break;

        case 2:
            if (count == 0)
            {
                printf("\nNo medicines found.\n");
            }
            else
            {
                printf("\nID | Name            | Time     | Pills | Taken | Missed\n");
                printf("------------------------------------------------------------\n");
                showMedsRecursive(meds, 0, count);
            }
            break;

        case 3:
        {
            if (count == 0)
            {
                printf("\nNo medicines to search.\n");
            }
            else
            {
                char key[30];
                int found = 0;
                printf("Enter medicine name to search: ");
                scanf("%29s", key);
                clearInputBuffer();

                searchMedRecursive(meds, 0, count, key, &found);
                if (!found)
                {
                    printf("No medicine found matching '%s'.\n", key);
                }
            }
            break;
        }

        case 4:
            checkDose(meds, count);
            break;

        case 5:
            deleteMed(meds, &count);
            break;

        case 6:
            saveData(meds, count);
            printf("\nAll records saved to '%s'. Exiting...\n", FILE_NAME);
            break;

        default:
            printf("\nInvalid choice! Please select between 1 and 6.\n");
        }
    } while (choice != 6);

    return 0;
}

// Helper function to clear leftover characters in stdin
void clearInputBuffer(void)
{
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF)
    {
        // discard extra input
    }
}

// FILE HANDLING: Load records from text file
void loadData(struct Medicine *meds, int *count)
{
    FILE *fp = fopen(FILE_NAME, "r");
    if (fp == NULL)
    {
        *count = 0;
        return;
    }

    if (fscanf(fp, "%d", count) != 1 || *count < 0 || *count > MAX)
    {
        *count = 0;
        fclose(fp);
        return;
    }

    // FOR LOOP to read each medicine record
    for (int i = 0; i < *count; i++)
    {
        if (fscanf(fp, "%d %29s %14s %d %d %d",
                   &(meds + i)->id,
                   (meds + i)->name,
                   (meds + i)->time,
                   &(meds + i)->pills,
                   &(meds + i)->taken,
                   &(meds + i)->missed) != 6)
        {
            *count = i;
            break;
        }
    }

    fclose(fp);
}

// FILE HANDLING: Save records to text file
void saveData(const struct Medicine *meds, int count)
{
    FILE *fp = fopen(FILE_NAME, "w");
    if (fp == NULL)
    {
        printf("Error: Could not open '%s' for writing.\n", FILE_NAME);
        return;
    }

    fprintf(fp, "%d\n", count);

    // FOR LOOP to write each medicine record
    for (int i = 0; i < count; i++)
    {
        fprintf(fp, "%d %s %s %d %d %d\n",
                (meds + i)->id,
                (meds + i)->name,
                (meds + i)->time,
                (meds + i)->pills,
                (meds + i)->taken,
                (meds + i)->missed);
    }

    fclose(fp);
}

// ADD NEW MEDICINE (modifies array and *count via pointers)
void addMed(struct Medicine *meds, int *count)
{
    if (*count >= MAX)
    {
        printf("Storage full! Cannot add more than %d medicines.\n", MAX);
        return;
    }

    struct Medicine newMed;
    newMed.id = *count + 1;
    newMed.taken = 0;
    newMed.missed = 0;

    printf("Enter Medicine Name (single word, e.g. Panadol): ");
    scanf("%29s", newMed.name);
    clearInputBuffer();

    printf("Enter Scheduled Time (e.g. 08:00AM): ");
    scanf("%14s", newMed.time);
    clearInputBuffer();

    printf("Enter Number of Pills: ");
    while (scanf("%d", &newMed.pills) != 1 || newMed.pills < 0)
    {
        printf("Please enter a valid non-negative number of pills: ");
        clearInputBuffer();
    }
    clearInputBuffer();

    *(meds + *count) = newMed; // Pointer arithmetic
    (*count)++;                // Update count in main()
    saveData(meds, *count);

    printf("Medicine added and saved successfully!\n");
}

// RECURSION: Display all medicines one by one
void showMedsRecursive(const struct Medicine *meds, int index, int count)
{
    // Base case
    if (index >= count)
    {
        return;
    }

    printf("%-2d | %-15s | %-8s | %-5d | %-5d | %-6d",
           (meds + index)->id,
           (meds + index)->name,
           (meds + index)->time,
           (meds + index)->pills,
           (meds + index)->taken,
           (meds + index)->missed);

    if ((meds + index)->pills <= 5)
    {
        printf("  <-- LOW STOCK!");
    }
    printf("\n");

    // Recursive call
    showMedsRecursive(meds, index + 1, count);
}

// RECURSION: Search medicine by exact name
void searchMedRecursive(const struct Medicine *meds, int index, int count, const char *key, int *found)
{
    // Base case
    if (index >= count)
    {
        return;
    }

    if (strcmp((meds + index)->name, key) == 0)
    {
        *found = 1;
        printf("\nFound -> ID: %d | Name: %s | Time: %s | Pills: %d | Taken: %d | Missed: %d\n",
               (meds + index)->id,
               (meds + index)->name,
               (meds + index)->time,
               (meds + index)->pills,
               (meds + index)->taken,
               (meds + index)->missed);
    }

    // Recursive call
    searchMedRecursive(meds, index + 1, count, key, found);
}

// TRACK DOSE STATUS (Taken / Missed)
void checkDose(struct Medicine *meds, int count)
{
    if (count == 0)
    {
        printf("\nNo medicines available to track.\n");
        return;
    }

    int targetId, status, found = 0;
    printf("Enter Medicine ID: ");
    if (scanf("%d", &targetId) != 1)
    {
        printf("Invalid ID input.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    // FOR LOOP to locate medicine by ID
    for (int i = 0; i < count; i++)
    {
        if ((meds + i)->id == targetId)
        {
            found = 1;
            printf("1. Mark as TAKEN\n2. Mark as MISSED\nEnter status: ");
            if (scanf("%d", &status) != 1)
            {
                printf("Invalid status input.\n");
                clearInputBuffer();
                return;
            }
            clearInputBuffer();

            if (status == 1)
            {
                (meds + i)->taken++;
                if ((meds + i)->pills > 0)
                {
                    (meds + i)->pills--;
                }
                printf("Dose marked as TAKEN.\n");
                if ((meds + i)->pills <= 5)
                {
                    printf("LOW STOCK ALERT: Only %d pills left for %s!\n",
                           (meds + i)->pills, (meds + i)->name);
                }
            }
            else if (status == 2)
            {
                (meds + i)->missed++;
                printf("CAREGIVER ALERT: Missed dose for %s scheduled at %s!\n",
                       (meds + i)->name, (meds + i)->time);
            }
            else
            {
                printf("Invalid option! Choose 1 or 2.\n");
            }
            break;
        }
    }

    if (!found)
    {
        printf("Medicine ID %d not found.\n", targetId);
    }
    else
    {
        saveData(meds, count);
    }
}

// DELETE MEDICINE BY ID
void deleteMed(struct Medicine *meds, int *count)
{
    if (*count == 0)
    {
        printf("\nNo medicines available to delete.\n");
        return;
    }

    int targetId, found = 0;
    printf("Enter Medicine ID to delete: ");
    if (scanf("%d", &targetId) != 1)
    {
        printf("Invalid ID input.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    // FOR LOOP to find and shift remaining records left
    for (int i = 0; i < *count; i++)
    {
        if ((meds + i)->id == targetId)
        {
            found = 1;
            for (int j = i; j < *count - 1; j++)
            {
                *(meds + j) = *(meds + j + 1);
                (meds + j)->id = j + 1;
            }
            (*count)--;
            saveData(meds, *count);
            printf("Medicine deleted and file updated.\n");
            break;
        }
    }

    if (!found)
    {
        printf("Medicine ID %d not found.\n", targetId);
    }
}
