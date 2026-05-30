#include <stdio.h>
#include <stdlib.h>

/* Time structure */
typedef struct Time
{
    int hour;
    int min;
} Time;

/* Vehicle node */
typedef struct vehicle
{
    int number;
    Time entry_time;
    char is_vip;
    struct vehicle *next;
} vehicle;

/* Parking system */
typedef struct Parking
{
    vehicle *vip;
    vehicle *f1;
    vehicle *f2;
    vehicle *f3;
    float income;
} Parking;
void init_parking(Parking *p)
{
    p->vip = NULL;
    p->f1 = NULL;
    p->f2 = NULL;
    p->f3 = NULL;
    p->income = 0;
}
vehicle *create_vehicle()
{
    vehicle *v = (vehicle *)malloc(sizeof(vehicle));
    if (!v)
    {
        printf("Memory allocation failed!\n");
        return NULL;
    }

    printf("Enter vehicle number: ");
    scanf("%d", &v->number);

    printf("Enter entry time:\n");

    do
    {
        printf("Hour (0-23): ");
        scanf("%d", &v->entry_time.hour);
    } while (v->entry_time.hour < 0 || v->entry_time.hour > 23);

    do
    {
        printf("Minute (0-59): ");
        scanf("%d", &v->entry_time.min);
    } while (v->entry_time.min < 0 || v->entry_time.min > 59);

    v->next = NULL;

    return v;
}
int exists(vehicle *head, int number)
{
    while (head)
    {
        if (head->number == number)
            return 1;
        head = head->next;
    }
    return 0;
}
void insert_end(vehicle **head, vehicle *v)
{
    if (*head == NULL)
    {
        *head = v;
        return;
    }

    vehicle *temp = *head;
    while (temp->next)
        temp = temp->next;

    temp->next = v;
}
void add_vehicle(Parking *p)
{
    vehicle *v = create_vehicle();
    if (!v)
        return;

    if (exists(p->vip, v->number) ||
        exists(p->f1, v->number) ||
        exists(p->f2, v->number) ||
        exists(p->f3, v->number))
    {
        printf("Vehicle already exists!\n");
        free(v);
        return;
    }

    printf("Is VIP? (y/n): ");
    scanf(" %c", &v->is_vip);

    if (v->is_vip == 'y' || v->is_vip == 'Y')
        insert_end(&p->vip, v);
    else
        insert_end(&p->f1, v);

    printf("Vehicle added successfully!\n");
}
void display(vehicle *head)
{
    if (!head)
    {
        printf("Empty.\n");
        return;
    }

    int i = 1;

    while (head)
    {
        printf("%d) Car: %d | VIP: %c | Time: %02d:%02d\n",
               i,
               head->number,
               head->is_vip,
               head->entry_time.hour,
               head->entry_time.min);

        head = head->next;
        i++;
    }
}
vehicle *search_vehicle(vehicle *head, int number, vehicle **prev)
{
    *prev = NULL;

    while (head)
    {
        if (head->number == number)
            return head;

        *prev = head;
        head = head->next;
    }

    return NULL;
}
void pay_fee(Parking *p)
{
    int num;
    int hour, min;
    float fee;

    printf("Enter vehicle number: ");
    scanf("%d", &num);

    vehicle *prev = NULL;
    vehicle *v = search_vehicle(p->vip, num, &prev);
    int in_vip = 1;

    if (!v)
    {
        v = search_vehicle(p->f1, num, &prev);
        in_vip = 0;
    }

    if (!v)
    {
        printf("Vehicle not found!\n");
        return;
    }

    printf("Enter current time:\n");

    do
    {
        printf("Hour: ");
        scanf("%d", &hour);
    } while (hour < 0 || hour > 23);

    do
    {
        printf("Minute: ");
        scanf("%d", &min);
    } while (min < 0 || min > 59);

    int entry = v->entry_time.hour * 60 + v->entry_time.min;
    int now = hour * 60 + min;

    int duration = now - entry;

    if (duration < 0)
    {
        printf("Invalid time!\n");
        return;
    }

    if (v->is_vip == 'y' || v->is_vip == 'Y')
        fee = duration * 2.0;
    else
        fee = duration * 1.5;

    printf("Total Fee: %.2f DA\n", fee);

    p->income += fee;

    vehicle **list = in_vip ? &p->vip : &p->f1;

    if (prev == NULL)
        *list = v->next;
    else
        prev->next = v->next;

    free(v);
}
int main()
{
    Parking p;
    init_parking(&p);

    int choice;

    while (1)
    {
        printf("\n==== SMART PARKING SYSTEM ====\n");
        printf("1. Add Vehicle\n");
        printf("2. Display VIP\n");
        printf("3. Display Floor 1\n");
        printf("4. Display All\n");
        printf("5. Pay Fee & Exit\n");
        printf("0. Exit\n");

        printf("Choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            add_vehicle(&p);
            break;

        case 2:
            display(p.vip);
            break;

        case 3:
            display(p.f1);
            break;

        case 4:
            printf("\nVIP:\n");
            display(p.vip);
            printf("\nF1:\n");
            display(p.f1);
            printf("\nF2:\n");
            display(p.f2);
            printf("\nF3:\n");
            display(p.f3);
            break;

        case 5:
            pay_fee(&p);
            break;

        case 0:
            printf("Total income: %.2f DA\n", p.income);
            return 0;

        default:
            printf("Invalid choice!\n");
        }
    }
}