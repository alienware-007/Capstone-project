// A C program for a bus reservation system

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

// Define the maximum number of buses and seats
#define MAX_BUSES 10
#define MAX_SEATS 40

// Define a structure for a bus
typedef struct bus {
    int id; // A unique identifier for the bus
    char name[20]; // The name of the bus
    char source[20]; // The source station of the bus
    char destination[20]; // The destination station of the bus
    int seats[MAX_SEATS]; // An array of seats, 0 means available, 1 means booked
    int count; // The number of booked seats
    struct bus *next; // A pointer to the next bus in the list
} bus;

// Define a structure for a ticket
typedef struct ticket {
    int bus_id; // The id of the bus
    int seat_no; // The seat number
    char passenger_name[20]; // The name of the passenger
    struct ticket *next; // A pointer to the next ticket in the list
} ticket;

// Declare global variables
bus *head = NULL; // A pointer to the head of the bus list
ticket *t_head = NULL; // A pointer to the head of the ticket list
int bus_id = 1; // A variable to generate unique bus ids
char filename[] = "buses.txt"; // The name of the file to store bus data
char t_filename[] = "tickets.txt"; // The name of the file to store ticket data

// Declare function prototypes
void login(); //requires password to access the system
void add_bus(); // A function to add a new bus
void delete_bus(); // A function to delete an existing bus
void view_buses(); // A function to view all buses
void book_seat(); // A function to book a seat
void print_ticket(); // A function to print a ticket
void cancel_ticket(); // A function to cancel a ticket
void view_bookings(); // A function to view all bookings
void save_data(); // A function to save the bus data to a file
void load_data(); // A function to load the bus data from a file
void save_tickets(); // A function to save the ticket data to a file
void load_tickets(); // A function to load the ticket data from a file
void display_menu(); // A function to display the main menu
void exit_program(); // A function to exit the program

// The main function
int main() {

    login();
    // Load the bus and ticket data from the files
    load_data();
    load_tickets();

    // Display the main menu
    display_menu();

    // Return 0 to indicate successful termination
    return 0;
}

void login()
{
    int i=0, j=0;
    char ch;
    char admin[12] = "JOYCE";
    char pass[12]= "pass";
    do{
        system("cls");
        printf("\n\n\t\t\t\t===============================USER LOGIN=============================\n\n\n\n");
        printf("\n**ENTER YOUR PASSWORD:\n      ");
          while((ch= getch())!=13){
          pass[i]=ch;
          printf(".");
          i++;
            }
            pass[i] = '\0';
            i = 0;
            if(strcmp(pass,"pass")==0){
                printf("\n\n\t**WELCOME %s ,LOGIN SUCCESFUL\n",admin);
                printf("press any key");
                getch();
                break;
            }
            else
            {
                printf("\n\n\t**WRONG PASSWORD TRY AGAIN\n");
                getch();
                j++;
            }
    }while(j <=2 );
    if(j > 2){
        printf("==========================*SYSTEM BLOCKED, PLEASE RESTART!!!=============================");
        getch();
        exit(0);
    }

}

// A function to add a new bus
void add_bus() {
    system("cls");
    printf("\n\t\t\t-------------------------------------------------------------------------------------\t");
    printf("\n\t\t\t\t\t\t***GYTOR BUS RESERVATION SYSTEM***\t\t\t\t\n");
    printf("\t\t\t-------------------------------------------------------------------------------------\t\n\n");
    printf("\t\t\t\t\t================================================\n");
    printf("\t\t\t\t\t\t     **ADD A BUS SCHEDULE**");
    printf("\n\t\t\t\t\t================================================\n\n\n");
    // Declare local variables
    bus *new_bus, *temp;
    char name[20], source[20], destination[20];
    int i;

    // Allocate memory for the new bus
    new_bus = (bus *)malloc(sizeof(bus));

    // Check if memory allocation was successful
    if (new_bus == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    // Get the details of the new bus from the user
    printf("Enter the name of the bus: ");
    scanf("%s", name);
    printf("Enter the source station of the bus: ");
    scanf("%s", source);
    printf("Enter the destination station of the bus: ");
    scanf("%s", destination);

    // Assign the details to the new bus
    new_bus->id = bus_id++;
    strcpy(new_bus->name, name);
    strcpy(new_bus->source, source);
    strcpy(new_bus->destination, destination);
    for (i = 0; i < MAX_SEATS; i++) {
        new_bus->seats[i] = 0;
    }
    new_bus->count = 0;
    new_bus->next = NULL;

    // Check if the bus list is empty
    if (head == NULL) {
        // Make the new bus the head of the list
        head = new_bus;
    } else {
        // Traverse the list to find the last bus
        temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        // Append the new bus to the end of the list
        temp->next = new_bus;
    }

    // Display a success message
    printf("Bus added successfully.\n");
}

// A function to delete an existing bus
void delete_bus() {
    system("cls");
    printf("\n\t\t\t-------------------------------------------------------------------------------------\t");
    printf("\n\t\t\t\t\t\t***GYTOR BUS RESERVATION SYSTEM***\t\t\t\t\n");
    printf("\t\t\t-------------------------------------------------------------------------------------\t\n\n");
    printf("\t\t\t\t\t================================================\n");
    printf("\t\t\t\t\t\t     **DELETE A BUS SCHEDULE**");
    printf("\n\t\t\t\t\t================================================\n\n\n");
    // Declare local variables
    bus *temp, *prev;
    int id, flag = 0;

    // Check if the bus list is empty
    if (head == NULL) {
        printf("No buses available.\n");
        return;
    }

    // Get the id of the bus to be deleted from the user
    printf("Enter the id of the bus to be deleted: ");
    scanf("%d", &id);

    // Traverse the list to find the bus with the given id
    temp = head;
    prev = NULL;
    while (temp != NULL) {
        // Check if the id matches
        if (temp->id == id) {
            // Set the flag to indicate that the bus was found
            flag = 1;
            break;
        }
        // Update the previous and current pointers
        prev = temp;
        temp = temp->next;
    }

    // Check if the bus was found
    if (flag == 0) {
        // Display an error message
        printf("Bus not found.\n");
        return;
    }

    // Check if the bus is the head of the list
    if (prev == NULL) {
        // Make the next bus the head of the list
        head = temp->next;
    } else {
        // Remove the bus from the list by skipping it
        prev->next = temp->next;
    }
    // Free the memory allocated for the bus
    free(temp);

    // Display a success message
    printf("Bus deleted successfully.\n");
}

// A function to view all buses
void view_buses() {
    system("cls");
    printf("\n\t\t\t-------------------------------------------------------------------------------------\t");
    printf("\n\t\t\t\t\t\t***GYTOR BUS RESERVATION SYSTEM***\t\t\t\t\n");
    printf("\t\t\t-------------------------------------------------------------------------------------\t\n\n");
    printf("\t\t\t\t\t================================================\n");
    printf("\t\t\t\t\t\t     **ALL BUS SCHEDULES**");
    printf("\n\t\t\t\t\t================================================\n\n\n");
    // Declare local variables
    bus *temp;
    int i;

    // Check if the bus list is empty
    if (head == NULL) {
        printf("No buses available.\n");
        return;
    }
    // Display the header of the table
    printf("ID\tName\tSource\tDestination\tSeats\n");

    // Traverse the list to display the details of each bus
    temp = head;
    while (temp != NULL) {
        // Display the id, name, source and destination of the bus
        printf("%d\t%s\t%s\t%s\t", temp->id, temp->name, temp->source, temp->destination);
        // Display the seats of the bus
        for (i = 0; i < MAX_SEATS; i++) {
            printf("%d", temp->seats[i]);
        }
        printf("\n");
        // Move to the next bus
        temp = temp->next;
    }
}

// A function to book a seat
void book_seat() {
    system("cls");
    printf("\n\t\t\t-------------------------------------------------------------------------------------\t");
    printf("\n\t\t\t\t\t\t***GYTOR BUS RESERVATION SYSTEM***\t\t\t\t\n");
    printf("\t\t\t-------------------------------------------------------------------------------------\t\n\n");
    printf("\t\t\t\t\t================================================\n");
    printf("\t\t\t\t\t\t\t**BOOK SEAT**");
    printf("\n\t\t\t\t\t================================================\n\n\n");
    // Declare local variables
    bus *temp;
    ticket *new_ticket, *t_temp;
    int id, seat_no, flag = 0;

    // Check if the bus list is empty
    if (head == NULL) {
        printf("No buses available.\n");
        return;
    }

    // Get the id of the bus to be booked from the user
    printf("Enter the id of the bus to be booked: ");
    scanf("%d", &id);

    // Traverse the list to find the bus with the given id
    temp = head;
    while (temp != NULL) {
        // Check if the id matches
        if (temp->id == id) {
            // Set the flag to indicate that the bus was found
            flag = 1;
            break;
        }
        // Move to the next bus
        temp = temp->next;
    }

    // Check if the bus was found
    if (flag == 0) {
        // Display an error message
        printf("Bus not found.\n");
        return;
    }

    // Check if the bus is full
    if (temp->count == MAX_SEATS) {
        // Display an error message
        printf("Bus is full.\n");
        return;
    }

    // Get the seat number to be booked from the user
    printf("Enter the seat number to be booked (1-%d): ", MAX_SEATS);
    scanf("%d", &seat_no);

    // Validate the seat number
    if (seat_no < 1 || seat_no > MAX_SEATS) {
        // Display an error message
        printf("Invalid seat number.\n");
        return;
    }

    // Check if the seat is already booked
    if (temp->seats[seat_no - 1] == 1) {
        // Display an error message
        printf("Seat is already booked.\n");
        return;
    }
    // Allocate memory for the new ticket
    new_ticket = (ticket *)malloc(sizeof(ticket));

    // Check if memory allocation was successful
    if (new_ticket == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    // Assign the details to the new ticket
    new_ticket->bus_id = id;
    new_ticket->seat_no = seat_no;
    printf("Enter the name of the passenger: ");
    scanf("%s", new_ticket->passenger_name);
    new_ticket->next = NULL;

    // Update the bus information
    temp->seats[seat_no - 1] = 1;
    temp->count++;

    // Check if the ticket list is empty
    if (t_head == NULL) {
        // Make the new ticket the head of the list
        t_head = new_ticket;
    } else {
        // Traverse the list to find the last ticket
        t_temp = t_head;
        while (t_temp->next != NULL) {
            t_temp = t_temp->next;
        }
        // Append the new ticket to the end of the list
        t_temp->next = new_ticket;
    }

    // Display a success message
    printf("Seat booked successfully.\n");
}

// A function to print a ticket
void print_ticket() {
    system("cls");
    printf("\n\t\t\t-------------------------------------------------------------------------------------\t");
    printf("\n\t\t\t\t\t\t***GYTOR BUS RESERVATION SYSTEM***\t\t\t\t\n");
    printf("\t\t\t-------------------------------------------------------------------------------------\t\n\n");
    printf("\t\t\t\t\t================================================\n");
    printf("\t\t\t\t\t\t     **TICKET PRINT**");
    printf("\n\t\t\t\t\t================================================\n\n\n");
    // Declare local variables
    ticket *temp;
    int id, seat_no, flag = 0;

    // Check if the ticket list is empty
    if (t_head == NULL) {
        printf("No bookings available.\n");
        return;
    }

    // Get the bus id and seat number from the user
    printf("Enter the bus id: ");
    scanf("%d", &id);
    printf("Enter the seat number: ");
    scanf("%d", &seat_no);

    // Traverse the list to find the ticket with the given bus id and seat number
    temp = t_head;
    while (temp != NULL) {
        // Check if the bus id and seat number match
        if (temp->bus_id == id && temp->seat_no == seat_no) {
            // Set the flag to indicate that the ticket was found
            flag = 1;
            break;
        }
        // Move to the next ticket
        temp = temp->next;
    }
    // Check if the ticket was found
    if (flag == 0) {
        // Display an error message
        printf("Ticket not found.\n");
        return;
    }

    // Display the ticket details
    system("cls");
    printf("\t\t\t\t\t================================================\n");
    printf("\t\t\t\t\t\t\t**GYTOR TICKETS**");
    printf("\n\t\t\t\t\t================================================\n");
    printf("\t\t\t\t\t\t---------------\n");
    printf("\t\t\t\t\t\tTicket details\n");
    printf("\t\t\t\t\t\t---------------\n");
    printf("\t\t\t\t\t\t        Bus ID:: %d\n", temp->bus_id);
    printf("\t\t\t\t\t\t   Seat Number:: %d\n", temp->seat_no);
    printf("\t\t\t\t\t\tPassenger Name:: %s\n", temp->passenger_name);
}

// void to cancel a booked ticket
void cancel_ticket() {
    system("cls");
    printf("\n\t\t\t-------------------------------------------------------------------------------------\t");
    printf("\n\t\t\t\t\t\t***GYTOR BUS RESERVATION SYSTEM***\t\t\t\t\n");
    printf("\t\t\t-------------------------------------------------------------------------------------\t\n\n");
    printf("\t\t\t\t\t================================================\n");
    printf("\t\t\t\t\t\t     **CANCEL TICKET**");
    printf("\n\t\t\t\t\t================================================\n\n\n");
    // Declare local variables
    ticket *temp, *prev;
    int id, seat_no, flag = 0;

    // Check if the ticket list is empty
    if (t_head == NULL) {
        printf("No bookings available.\n");
        return;
    }

    // Get the bus id and seat number from the user
    printf("Enter the bus id: ");
    scanf("%d", &id);
    printf("Enter the seat number: ");
    scanf("%d", &seat_no);

    // Traverse the list to find the ticket with the given bus id and seat number
    temp = t_head;
    prev = NULL;
    while (temp != NULL) {
        // Check if the bus id and seat number match
        if (temp->bus_id == id && temp->seat_no == seat_no) {
            // Set the flag to indicate that the ticket was found
            flag = 1;
            break;
        }
        // Update the previous and current pointers
        prev = temp;
        temp = temp->next;
    }

    // Check if the ticket was found
    if (flag == 0) {
        // Display an error message
        printf("Ticket not found.\n");
        return;
    }

    // Update the bus information
    temp = t_head;
    while (temp != NULL) {
        if (temp->bus_id == id && temp->seat_no == seat_no) {
            bus *b_temp = head;
            while (b_temp != NULL) {
                if (b_temp->id == id) {
                    b_temp->seats[seat_no - 1] = 0;
                    b_temp->count--;
                    break;
                }
                b_temp = b_temp->next;
            }
            break;
        }
        temp = temp->next;
    }
    // Check if the ticket is the head of the list
    if (prev == NULL) {
        // Make the next ticket the head of the list
        t_head = temp->next;
    } else {
        // Remove the ticket from the list by skipping it
        prev->next = temp->next;
    }

    // Free the memory allocated for the ticket
    free(temp);

    // Display a success message
    printf("Ticket canceled successfully.\n");
}

// A function to view all bookings
void view_bookings() {
    system("cls");
    printf("\n\t\t\t-------------------------------------------------------------------------------------\t");
    printf("\n\t\t\t\t\t\t***GYTOR BUS RESERVATION SYSTEM***\t\t\t\t\n");
    printf("\t\t\t-------------------------------------------------------------------------------------\t\n\n");
    printf("\t\t\t\t\t================================================\n");
    printf("\t\t\t\t\t\t     **BOOKINGS LIST**");
    printf("\n\t\t\t\t\t================================================\n\n\n");
    // Declare local variables
    ticket *temp;

    // Check if the ticket list is empty
    if (t_head == NULL) {
        printf("No bookings available.\n");
        return;
    }

    // Display the header of the table
    printf("Bus ID\tSeat Number\tPassenger Name\n");

    // Traverse the list to display the details of each ticket
    temp = t_head;
    while (temp != NULL) {
        // Display the bus id, seat number, and passenger name of the ticket
        printf("%d\t%d\t\t%s\n", temp->bus_id, temp->seat_no, temp->passenger_name);
        // Move to the next ticket
        temp = temp->next;
    }
}

// A function to save the bus data to a file
void save_data() {
    // Declare local variables
    FILE *file;
    bus *temp;

    // Open the file for writing
    file = fopen(filename, "w");

    // Check if the file was opened successfully
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }
    // Traverse the list to write each bus's data to the file
    temp = head;
    while (temp != NULL) {
        fprintf(file, "%d %s %s %s ", temp->id, temp->name, temp->source, temp->destination);
        for (int i = 0; i < MAX_SEATS; i++) {
            fprintf(file, "%d ", temp->seats[i]);
        }
        fprintf(file, "%d\n", temp->count);

        // Move to the next bus
        temp = temp->next;
    }
    // Close the file
    fclose(file);
}

// A function to load the bus data from a file
void load_data() {
    // Declare local variables
    FILE *file;
    bus *new_bus, *temp;
    int id, count, seat;

    // Open the file for reading
    file = fopen(filename, "r");

    // Check if the file was opened successfully
    if (file == NULL) {
        printf("Error opening file for reading.\n");
        return;
    }

    // Read each line from the file to create bus structures
    while (fscanf(file, "%d", &id) != EOF) {
        // Allocate memory for the new bus
        new_bus = (bus *)malloc(sizeof(bus));

        // Check if memory allocation was successful
        if (new_bus == NULL) {
            printf("Memory allocation failed.\n");
            fclose(file);
            exit(1);
        }

        // Assign the id to the new bus
        new_bus->id = id;

        // Read the name, source, and destination of the bus
        fscanf(file, "%s %s %s", new_bus->name, new_bus->source, new_bus->destination);

        // Read the seat information of the bus
        for (int i = 0; i < MAX_SEATS; i++) {
            fscanf(file, "%d", &seat);
            new_bus->seats[i] = seat;
        }

        // Read the count of booked seats
        fscanf(file, "%d", &count);
        new_bus->count = count;

        // Set the next pointer to NULL
        new_bus->next = NULL;

        // Check if the bus list is empty
        if (head == NULL) {
            // Make the new bus the head of the list
            head = new_bus;
        } else {
            // Traverse the list to find the last bus
            temp = head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            // Append the new bus to the end of the list
            temp->next = new_bus;
        }
    }
    // Close the file
    fclose(file);
}

// A function to save the ticket data to a file
void save_tickets() {
    // Declare local variables
    FILE *file;
    ticket *temp;

    // Open the file for writing
    file = fopen(t_filename, "w");

    // Check if the file was opened successfully
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }
    // Traverse the list to write each ticket's data to the file
    temp = t_head;
    while (temp != NULL) {
        fprintf(file, "%d %d %s\n", temp->bus_id, temp->seat_no, temp->passenger_name);

        // Move to the next ticket
        temp = temp->next;
    }
    // Close the file
    fclose(file);
}

// A function to load the ticket data from a file
void load_tickets() {
    // Declare local variables
    FILE *file;
    ticket *new_ticket, *temp;
    int bus_id, seat_no;

    // Open the file for reading
    file = fopen(t_filename, "r");

    // Check if the file was opened successfully
    if (file == NULL) {
        printf("Error opening file for reading.\n");
        return;
    }

    // Read each line from the file to create ticket structures
    while (fscanf(file, "%d", &bus_id) != EOF) {
        // Allocate memory for the new ticket
        new_ticket = (ticket *)malloc(sizeof(ticket));

        // Check if memory allocation was successful
        if (new_ticket == NULL) {
            printf("Memory allocation failed.\n");
            fclose(file);
            exit(1);
        }
        // Assign the bus_id and seat_no to the new ticket
        new_ticket->bus_id = bus_id;
        fscanf(file, "%d", &seat_no);
        new_ticket->seat_no = seat_no;

        // Read the passenger name of the ticket
        fscanf(file, "%s", new_ticket->passenger_name);

        // Set the next pointer to NULL
        new_ticket->next = NULL;

        // Check if the ticket list is empty
        if (t_head == NULL) {
            // Make the new ticket the head of the list
            t_head = new_ticket;
        } else {
            // Traverse the list to find the last ticket
            temp = t_head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            // Append the new ticket to the end of the list
            temp->next = new_ticket;
        }
    }
    // Close the file
    fclose(file);
}

// A function to display the main menu
void display_menu() {
    int choice;
    do {
        system("cls");
        printf("\n\t\t\t-------------------------------------------------------------------------------------\t");
        printf("\n\t\t\t\t\t\t***GYTOR BUS RESERVATION SYSTEM***\t\t\t\t\n");
        printf("\t\t\t-------------------------------------------------------------------------------------\t\n\n");
        printf("\n\t\t\t\t\t-------------------------------------------\n");
        printf("\t\t\t\t\t\t::ENTER YOUR CHOICE TO ACCESS::                    \n");
        printf("\t\t\t\t\t-------------------------------------------\n");
        printf("\t\t\t\t\t 1: Add Bus Schedule 	  \n");
        printf("\t\t\t\t\t 2: Delete Bus Schedule  \n");
        printf("\t\t\t\t\t 3: View All Bus  \n");
        printf("\t\t\t\t\t 4: Book Seat	  \n");
        printf("\t\t\t\t\t 5: Print Ticket	  \n");
        printf("\t\t\t\t\t 6: Cancel Ticket		  \n");
        printf("\t\t\t\t\t 7: View Bookings	  \n");
        printf("\t\t\t\t\t 0: Exit	          \n");
        printf("\t\t\t\t\t-------------------------------------------\n");
        printf("\t\t\tEnter Your Choice:: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                add_bus();
                getch();
                break;
            case 2:
                delete_bus();
                getch();
                break;
            case 3:
                view_buses();
                getch();
                break;
            case 4:
                book_seat();
                getch();
                break;
            case 5:
                print_ticket();
                getch();
                break;
            case 6:
                cancel_ticket();
                getch();
                break;
            case 7:
                view_bookings();
                getch();
                break;
            case 0:
                exit_program();
                getch();
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
                getch();
        }
    } while (choice != 0);
}

// A function to exit the program
void exit_program() {
    // Save the bus and ticket data to files before exiting
    save_data();
    save_tickets();

    // Free the memory allocated for buses and tickets
    bus *b_temp, *b_prev;
    ticket *t_temp, *t_prev;

    b_temp = head;
    while (b_temp != NULL) {
        b_prev = b_temp;
        b_temp = b_temp->next;
        free(b_prev);
    }
    t_temp = t_head;
    while (t_temp != NULL) {
        t_prev = t_temp;
        t_temp = t_temp->next;
        free(t_prev);
    }
    // Display an exit message
    printf("Exiting program.\n");
}