#ifndef MODELS_H
#define MODELS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_NAME          64
#define MAX_EMAIL         64
#define MAX_DATE          16
#define MAX_VENUE         64
#define MAX_TICKET_TYPES   3
#define MAX_EVENTS        20
typedef struct {
    char  name[16];
    double price;
} TicketType;
typedef struct {
    int    bookingId;        /* 0 means empty seat */
    char   name[MAX_NAME];
    char   email[MAX_EMAIL];
    int    ticketTypeIndex;  /* index into ticketTypes[] */
    int    seatNumber;       /* 1-based; -1 when on waitlist */
} Attendee;
struct WaitNode {
    Attendee           data;
    struct WaitNode   *next;
};
typedef struct WaitNode WaitNode;
typedef struct {
    char        name[MAX_NAME];
    char        date[MAX_DATE];
    char        venue[MAX_VENUE];

    int         capacity;
    Attendee   *seats;                 /* dynamic array size=capacity */

    int         numTicketTypes;
    TicketType  ticketTypes[MAX_TICKET_TYPES];

    int         seatsBooked;
    double      revenue;
    int         nextBookingId;

    WaitNode   *waitHead;
    WaitNode   *waitTail;
} Event;
void print_event_summary(const Event *e, int idx);
void print_attendee_list(const Event *e);
void print_waitlist(const Event *e);
void print_all_events(Event events[], int eventCount);
void init_event(Event *e, const char *name, const char *date, const char *venue, int capacity);
void add_ticket_type(Event *e, const char *name, double price);
void free_event(Event *e);
bool book_ticket(Event *e, const char *custName, const char *email,
                 int ticketTypeIndex, int *outBookingId, bool *outWaitlisted);
bool cancel_booking(Event *e, int bookingId);
#endif 
