#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct train {
    char name[50];
    int age;
    char place[50];
    int trate;
    int tcls;  
    int tnumber;
    struct train *link;
};



void push(struct train **top, struct train *node) {
    node->link = *top;
    *top = node;
}

struct train* pop(struct train **top) {
    if (*top == NULL) {
        return NULL;
    }
    struct train *temp = *top;
    *top = (*top)->link;
    temp->link = NULL;
    return temp;
}

void createnode(struct train **q, char *name, int age, char *place, int cls,int rate) {
    struct train *nn = (struct train*)malloc(sizeof(struct train));
    strcpy(nn->name, name);
    nn->age = age;
    nn->tcls = cls;
    strcpy(nn->place, place);
    if(nn->tcls==1){
       nn->tnumber=101;
    }
    else if(nn->tcls==2){
       nn->tnumber=201;
    }
    else{
        nn->tnumber=301;
    }
   
    nn->trate=rate;
    nn->link = NULL;

    if (*q == NULL) {
        *q = nn;
    } else {
        struct train *temp = *q;
        while (temp->link != NULL) {
            temp = temp->link;
        }
        temp->link = nn;
        nn->tnumber++;
    }
    printf("%s ticket booked successfully\n", nn->name);
}

void show(struct train *q) {
    if (q == NULL) {
        printf("No tickets booked\n");
    } else {
        int i = 1;
        printf("No  TicketNumber Class Name  Age  Place  Rate\n");
        while (q != NULL) {
            printf("%d) %d %d %s  %d  %s  %d\n", i, q->tnumber,q->tcls, q->name, q->age, q->place, q->trate);
            q = q->link;
            i++;
        }
    }
    printf("\n");
}

void deletenode(struct train **q, struct train **top, int number) {
    struct train *temp = *q, *pre = NULL;

    if (*q == NULL) {
        printf("No tickets are booked\n");
        return;
    }

    if (temp->tnumber == number) {
        *q = temp->link;
        push(top, temp);
        printf("Your ticket is removed successfully\n");
        return;
    }

    while (temp != NULL && temp->tnumber != number) {
        pre = temp;
        temp = temp->link;
    }

    if (temp == NULL) {
        printf("No ticket found with number %d\n", number);
        return;
    }

    pre->link = temp->link;
    push(top, temp);
    printf("Your ticket is removed successfully\n");
}

void undo(struct train **q, struct train **top) {
    struct train *nn = pop(top);
    if (nn == NULL) {
        printf("No ticket to rebook\n");
        return;
    }

    if (*q == NULL) {
        *q = nn;
    } else {
        struct train *temp = *q;
        while (temp->link != NULL) {
            temp = temp->link;
        }
        temp->link = nn;
    }
    printf("%d ticket  has been rebooked successfully\n", nn->tnumber);
}

int clsrate(int cls) {
if(cls==1){
    return 500;
}
else if(cls==2){
    return 300;
}
else{
    return 200;
}
}

int countseats(struct train *q, int cls) {
    int count = 0;
    while (q != NULL) {
        if (q->tcls == cls) {
            count++;
        }
        q = q->link;
    }
    return count;
}

void viewseats(struct train *q,int cls){
    int bseats=countseats(q,cls);
    if(cls==1){
        int a=10-bseats;
        printf("First class Seats booked are %d\n",bseats);
        printf("Available seats %d",a);
        return ;
    }
    else if(cls==2){
        int a=10-bseats;
         printf("Second class Seats booked are %d\n",bseats);
        printf("Available seats %d",a);
        return ;
    }
    else{
         int a=10-bseats;
         printf("Third class Seats booked are %d\n",bseats);
        printf("Available seats %d",a);
        return ;
    }
}

int main() {
    char name[50];
    int age, cls, rate;
    char place[50];
    struct train *head = NULL;
    struct train *top = NULL;

    while (1) {
        printf("1. Book Ticket\n2. Delete Ticket\n3. Display Tickets\n4. View Seats\n5. Exit\n");
        int p;
        printf("Enter your option: ");
        scanf("%d", &p);

        switch (p) {
            case 1:
                printf("Enter your name: ");
                scanf(" %[^\n]s", name);
                printf("Enter your age: ");
                scanf(" %d", &age);
                printf("Enter your destination: ");
                scanf(" %s", place);
                printf("1 --> First Class\n2 --> Second Class\n3 --> Third Class\n");
                printf("Enter your class: ");
                scanf(" %d", &cls);
                rate = clsrate(cls);
                createnode(&head, name, age, place,cls,rate);
                break;

            case 2: {
                int num;
                printf("Enter your Ticket Number: ");
                scanf("%d", &num);
                deletenode(&head, &top, num);

                char rebook;
                printf("Would you like to rebook the last deleted ticket? (y/n): ");
                scanf(" %c", &rebook);
                if (rebook == 'y' || rebook == 'Y') {
                    undo(&head, &top);
                }
                break;
            }

            case 3:
                show(head);
                break;

            case 4: {
                int cls;
                printf("1 --> First Class\n2 --> Second Class\n3 --> Third Class\n");
                printf("Enter your class to view: ");
                scanf("%d", &cls);
                viewseats(head, cls);
                break;
            }

            case 5:
                exit(0);

            default:
                printf("Invalid option\n");
                break;
        }
    }

    return 0;
}