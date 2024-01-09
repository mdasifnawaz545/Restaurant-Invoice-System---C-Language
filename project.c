#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct item
{
    char name[100];
    int qty;
    float price;
};
struct order
{
    char customer[100];
    char date[20];
    int noOfItems;
    struct item items[];
};
void header(char name[100], char date[15]);
void footer(float total);
void billBody(char itemName[100], int qty, float price);
int main()
{
    FILE *fp;
    char findName[100];
    int choice;
    float total = 0;
    struct order ord;
    struct order ordering;
    printf("\n");
    printf("---__---__--- :|  Al-Makkah Restaurant  |: ---__---__---\n");
    printf("\n");
    while (1)
    {
        printf("1. New Invoice\n");
        printf("2. All Invoices\n");
        printf("3. Find Invoice\n");
        printf("4. Exit\n");
        printf("\n");
        printf("Enter Your Choice : ");
        scanf("%d", &choice);
        fgetc(stdin); // Why we are taken this here ?. (as far as i know it is for taking the input as an standard).
        int n;
        char save, ch;
        switch (choice)
        {
        case 1:
            system("clear"); // It is used to clear all the previous code of the same program in order to give a better code readability.
            printf("Customer Name : ");
            fgets(ord.customer, 100, stdin);            // 1. Did'nt understood why we had used this fgets instead of puts and scanf also.
            ord.customer[strlen(ord.customer) - 1] = 0; // 2. It is used to find the end of the string and assign ord.customer to ord.customer[0] in order to take the things in a new line because by default it is not doing the same thing.
            strcpy(ord.date, __DATE__);                 // 3. It is used to copy string from a variable to the another variable. instead of this can we directly assign it as (ord.date=__DATE__;)?
            printf("No. of Items : ");
            scanf("%d", &n);
            for (int i = 0; i < n; i++)
            {
                fgetc(stdin); // Why ?
                printf("\n");
                printf("Item %d Name : ", i + 1);
                fgets(ord.items[i].name, 30, stdin);
                ord.items[i].name[strlen(ord.items[i].name) - 1] = 0; // Refer to problem serial number 2.
                printf("Quantity : ");
                scanf("%d", &ord.items[i].qty);
                printf("Price : ");
                scanf("%f", &ord.items[i].price);
                total = total + ord.items[i].price * ord.items[i].qty;
            }
            ord.noOfItems = n;
            header(ord.customer, ord.date);
            for (int i = 0; i < ord.noOfItems; i++)
            {
                billBody(ord.items[i].name, ord.items[i].qty, ord.items[i].price);
            }
            footer(total);
            printf("\n");
            printf("Do you want to save this Invoice [y/n] : ");
            scanf("%s", &save);
            if (save == 'y')
            {
                fp = fopen("Restaurant_Invoice.txt", "a+");
                fwrite(&ord, sizeof(struct order), 1, fp);
                if (fwrite != 0) // it is used to check whether the file has been save or not.
                {
                    printf("Saved Sucessfully !!\n");
                }
                else
                {
                    printf("Error While Saving...!\n");
                }
                fclose(fp);
            }
            break;
        case 2:
            fp = fopen("Restaurant_Invoice.txt", "r");
            printf("*****__All Invoices__*****\n");
            while (fread(&ordering, sizeof(struct order), 1, fp))
            {
                float invoiceTotal = 0;
                header(ordering.customer, ordering.date);
                for (int i = 0; i < ordering.noOfItems; i++)
                {
                    billBody(ordering.items[i].name, ordering.items[i].qty, ordering.items[i].price);
                    invoiceTotal = invoiceTotal + ordering.items[i].price * ordering.items[i].qty;
                }
                footer(invoiceTotal);
            }
            fclose(fp);
            break;
        case 3:
            printf("Enter the Name of the Customer : ");
            fgetc(stdin); // why ?
            fgets(findName, 100, stdin);
            fp = fopen("Restaurant_Invoice.txt", "r");
            while (fread(&ordering, sizeof(struct order), 1, fp))
            {

                float invTotal = 0;
                if (!strcmp(ordering.customer, findName)) // we are using logical not operator because if both the given string in the strcmp is same then it will returns 0.
                {                                         // How is the strcmp inbuilt function is working ?.
                    printf("*****__Invoice of : %s\n", findName);
                    header(ordering.customer, ordering.date);
                    for (int i = 0; i < ordering.noOfItems; i++)
                    {
                        billBody(ordering.items[i].name, ordering.items[i].qty, ordering.items[i].price);
                        invTotal = invTotal + ordering.items[i].price * ordering.items[i].qty;
                    }
                    footer(invTotal);
                }
                else
                {
                    printf("Invoice Not Found...!\n");
                }
            }
            fclose(fp);
            break;
        case 4:
            printf("Thanks For Choosing this Platform !! :) ZAZAKALLAH KHAIR :)");
            exit(1);
            break;
        default:
            printf("Invalid Choice\n");
            break;
        }
    }
    return 0;
}
void header(char name[100], char date[15])
{
    printf("\n");
    printf("   ---__---__--- :|  Al-Makkah Restaurant  |: ---__---__---\n");
    printf("\n");
    printf("Customer Name : %s\n", name);
    printf("Date : %s\n", date);
    printf("_______________________________________________________________\n");
    printf("Items\t\tQuantity\t\tPrice\t\tTotal\n");
    printf("_______________________________________________________________\n");
}
void billBody(char itemName[100], int qty, float price)
{
    printf("%s\t\t   ", itemName);
    printf("%d\t\t\t", qty);
    printf("%.2f\t\t", price);
    printf("%.2f", qty * price);
    printf("\n");
}
void footer(float total)
{
    printf("_______________________________________________________________\n");
    printf("Sub Total\t\t\t\t\t\t%.2f\n", total);
    // printf("Discount @5%%\t\t\t\t\t");
    float discountCalulation = 0.05 * total; // Why this discount has not been calculated.
    printf("Discount @%%5  \t\t\t\t\t\t%.2f\n", discountCalulation);
    float netTotal = total - discountCalulation;
    printf("Net Total\t\t\t\t\t\t%.2f\n", netTotal);
    float cgst = 0.09 * netTotal;
    printf("CGST @9%%\t\t\t\t\t\t%.2f\n", cgst); // how to use percent in coding -: Answer is = (%%)
    printf("SGST @9%%\t\t\t\t\t\t%.2f\n", cgst);
    printf("_______________________________________________________________\n");
    float grandTotal = netTotal + (2 * cgst);
    printf("Grand Total\t\t\t\t\t\t%.2f\n", grandTotal);
    printf("\n");
}