#include "models.h"
void print_event_summary(const Event *e, int idx) {
    printf("\n--------------------------------------------------\n");
    printf("Event #%d: %s\n", idx, e->name);
    printf("Date: %s | Venue: %s\n", e->date, e->venue);
    printf("Capacity: %d | Booked: %d | Available: %d\n",
           e->capacity, e->seatsBooked, e->capacity - e->seatsBooked);

    printf("Ticket Types:\n");
    for (int i = 0; i < e->numTicketTypes; ++i) {
        printf("  [%d] %-10s : Rs %.2f\n", i, e->ticketTypes[i].name, e->ticketTypes[i].price);
    }
    printf("Revenue: Rs %.2f\n", e->revenue);
}
void print_attendee_list(const Event *e) {
    printf("\nConfirmed Attendees:\n");
    printf("  %-5s %-24s %-28s %-8s %-5s\n", "Seat", "Name", "Email", "Type", "BID");
    int shown = 0;
    for (int i = 0; i < e->capacity; ++i) {
        if (e->seats[i].bookingId != 0) {
            const Attendee *a = &e->seats[i];
            const char *typeName = (a->ticketTypeIndex>=0 && a->ticketTypeIndex<e->numTicketTypes)
                  ? e->ticketTypes[a->ticketTypeIndex].name : "?";
            printf("  %-5d %-24s %-28s %-8s %-5d\n",
                   a->seatNumber, a->name, a->email, typeName, a->bookingId);
            shown++;
        }
    }
    if (shown == 0) printf("  (none)\n");
}
void print_waitlist(const Event *e) {
    printf("\nWaitlist:\n");
    if (!e->waitHead) { printf("  (empty)\n"); return; }
    printf("  %-5s %-24s %-28s %-8s %-5s\n", "Pos", "Name", "Email", "Type", "BID");
    int pos = 1;
    for (const WaitNode *n = e->waitHead; n; n = n->next) {
        const Attendee *a = &n->data;
        const char *typeName = (a->ticketTypeIndex>=0 && a->ticketTypeIndex<e->numTicketTypes)
              ? e->ticketTypes[a->ticketTypeIndex].name : "?";
        printf("  %-5d %-24s %-28s %-8s %-5d\n",
               pos++, a->name, a->email, typeName, a->bookingId);
    }
}
void print_all_events(Event events[], int eventCount) {
    printf("\n================= EVENTS =================\n");
    for (int i = 0; i < eventCount; ++i) {
        printf("[%d] %s (on %s at %s)  Seats: %d/%d  Revenue: Rs %.2f\n",
               i, events[i].name, events[i].date, events[i].venue,
               events[i].seatsBooked, events[i].capacity, events[i].revenue);
    }
    if (eventCount == 0) printf("(no events yet)\n");
    printf("==========================================\n");
}
