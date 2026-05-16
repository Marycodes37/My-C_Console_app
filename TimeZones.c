#include <stdio.h>
#include <time.h>
#include <math.h>

// Country structure
    struct Country {
    char name[40];
    float utc_offset;      // Offset from UTC in hours
};

// Database of 20 countries
struct Country countries[20] = {
    {"Nigeria", 1},
    {"United Kingdom", 0},
    {"United States (New York)", -5},
    {"United States (Los Angeles)", -8},
    {"South Africa", 2},
    {"Egypt", 2},
    {"Kenya", 3},
    {"Brazil", -3},
    {"Argentina", -3},
    {"Russia (Moscow)", 3},
    {"UAE", 4},
    {"India", 5.5},
    {"Nepal", 5.75},
    {"Pakistan", 5},
    {"China", 8},
    {"Japan", 9},
    {"South Korea", 9},
    {"Australia (Sydney)", 10},
    {"Canada (Toronto)", -5},
    {"Saudi Arabia", 3}
};

// Function to display menu
void show_menu() {
    printf("\t===============================\n");
    puts("\t\tLOCAL TIME CHECKER");
    puts("\t===============================\n\n\n\n");
    printf("Welcome to my program!\n");
    printf("This program consists a list of twenty(20) countries and their corresponding UTC offset.\n");
    printf("Kindly input any country to check its current local time...\n\n");
    for (int i = 0; i < 20; i++) {
        printf("%d. %s (UTC %+g)\n", i+1, countries[i].name, countries[i].utc_offset);
    }
    printf("Select a country (1-20): ");
}

// Function to convert 24-hour to 12-hour format
void print_12hr_time(struct tm *time) {
    int hour = time->tm_hour;
    char *ampm = "AM";

    if (hour == 0) {
        hour = 12;  // Midnight
    } else if (hour == 12) {
        ampm = "PM";  // Noon
    } else if (hour > 12) {
        hour -= 12;
        ampm = "PM";
    }

    printf("%02d:%02d:%02d %s\n",
           hour,
           time->tm_min,
           time->tm_sec,
           ampm);
}

int main() {
    int choice;

    // Step 1: Display options
    show_menu();
    scanf("%d", &choice);

    // Validate input
    if (choice < 1 || choice > 20) {
        printf("Invalid selection!\n");
        return 1;
    }

    // Step 2: Get current UTC time
    time_t now = time(NULL);
    struct tm *utc = gmtime(&now);

    // Step 3: Apply UTC offset
    float offset = countries[choice-1].utc_offset;
    int offset_hr = (int)offset;
    int offset_min = (int)((offset - offset_hr) * 60);

    utc->tm_hour += offset_hr;
    utc->tm_min  += offset_min;

    // Step 4: Normalize using mktime
    time_t adjusted = mktime(utc);
    struct tm *local_time = localtime(&adjusted);

    // Step 5: Show result in 12-hour format
    printf("\nLocal Time in %s:\n", countries[choice-1].name);
    print_12hr_time(local_time);

    // Also print the date
    printf("Date: %02d-%02d-%04d\n",
           local_time->tm_mday,
           local_time->tm_mon + 1,
           local_time->tm_year + 1900);

    return 0;
}
