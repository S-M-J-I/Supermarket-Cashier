/**************HOW TO USE**************************************************************
@author: S M JISHANUL ISLAM
@about: This program is a basic checkout counter program.
        >It takes any input of the items you want to check out, 
        >enters it, 
        >calculates price and 
        >if you want, makes a recepit for printing if you're using cash.
        >***TO SEE RECEIPT, A .txt FILE NAMED "Receipt.txt" WILL BE CREATED

        >if you're paying with card, enter details as the program directs
        >it will create a bill 
        >***TO SEE BILL, A .txt FILE NAME "CreditBill.txt" WILL BE CREATED
@DirectionsForUse:
        >Enter item name, price, quanitity as asked
        >Your items will be shown
        >Discount is given
        >Choose cash or card
        >Receipt for cash
        >Further details to be entered for card
***************************************************************************/
//LIBRARIES
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//STRUCT LIST
struct List{
    char ItemName[20];
    double ItemPrice;
    int quantity;
};

//STRUCT CARD
struct Card{
    char CardNum[25];
    long double CardBalance;
    int YearOfExpiry;
    char Type[15];
    int PIN;
};

//GLOBAL DECLARATIONS
int n,i;
char choice;
struct List list[50];
FILE *bill;
struct Card Customer;
double s;

//DISCOUNT FUNCTION BLOCK
double Discount(double sum){
    double Dis;
    
    if(sum>=1000 && sum<2000){Dis = 0.10;}
    else if(sum>=2000 && sum<4000){Dis = 0.20;}
    else if(sum>=4000 && sum<7000){Dis = 0.30;}
    else if(sum>=7000){Dis = 0.40;}
    else{Dis = 0;}
    
    return Dis;
}
double discount;

//FUNTION TO DISPLAY ITEMS
void PrintItems()
{
    for(i=1;i<n;i++){
        //Print items
        printf("\tItem %d: \n", i);
        printf("\tItem Name: %s\n", list[i].ItemName);
        printf("\tItem Price: %.2lf BDT\n", list[i].ItemPrice);
        printf("\tQuantity bought: %d\n", list[i].quantity);
        printf("\n");
    }
}

//FUNCTION TO PRINT RECEIPT
void printReceipt()
{
    FILE *receipt;
    receipt = fopen("Receipt.txt", "w");
    fprintf(receipt, "===============================BILL SUMMARY================================\n\n");
    fprintf(receipt, "\n");
    fprintf(receipt, "\n");
    fprintf(receipt, "Item:\t\t\t\t\t\t\tPrice:\n");
    for(i=1; i<n; i++)
    {
        fprintf(receipt, "%s x %d", list[i].ItemName, list[i].quantity);
        fprintf(receipt, "\t\t\t\t\t\t\t");
        fprintf(receipt, "%.2lf BDT", list[i].ItemPrice);
        fprintf(receipt, "\n");
    }
    fprintf(receipt, "\n\n");
    fprintf(receipt, "Total Amount: ");
    fprintf(receipt, "%.2lf BDT\n", s);
    fprintf(receipt, "%.0lf%c SURPRISE DISCOUNT OFFERED\n", (discount*100), '%');
    fprintf(receipt, "Amount to pay after Discount: %.2lf BDT\n", s - discount*s );
    fprintf(receipt, "\n\n");
    fprintf(receipt, "===========================================================================\n\n");
    fprintf(receipt, "Have a nice day! Come visit us again!\nAddress: *address*\nContact: 012345678901\n");
    fclose(receipt);
    printf("Recepit made\n\n");
}

//MAIN FUNCTION
int main()
{
    printf("\n<<<CASHING COUNTER>>>\n\nOngoing discount!!!!! Get a discount upto 40 percent !!!!!!!\n\n\n");
    n=50;
    s=0;
    //ENTER ITEMS HERE
    for(i=1;i<n;i++){
        printf("Add item? Y/N\nEnter: ");
        fflush(stdin);
        scanf("%c", &choice);
        fflush(stdout);
        if(choice=='n' || choice=='N'){
            n = i;
            break;
        }
        else if(choice=='y' || choice=='Y'){
            printf("Enter Item Name: ");
            fflush(stdin);
            gets(list[i].ItemName);
            fflush(stdout);
            reEnterPrice:
            printf("Enter Item Price: ");
            scanf("%lf", &list[i].ItemPrice);
            if(list[i].ItemPrice<=0)
            {
                printf("Invalid Price Value!\nRe-");
                goto reEnterPrice;
            }
            reEnterQuantity:
            printf("Enter quantity: ");
            scanf("%d", &list[i].quantity);
            if(list[i].quantity<=0)
            {
                printf("Invalid Quantity Value!\nRe-");
                goto reEnterQuantity;
            }
            printf("\n");
            continue;
        }
        else{
            printf("\nInavlid input. Enter again!\n");
            i--;
            continue;
        }
    }
    printf("\n");
//CALCULATE SUM
    for(i=1; i<n;i++){
        s = s + (list[i].ItemPrice*list[i].quantity);
    }
    PrintItems();
    printf("Total Amount: %.0lf BDT\n", s);//Amount w/o discount
    discount = Discount(s);    
    printf("Surprise discount given: %.0lf%c\n", (discount*100), '%' );
    printf("Amount to pay: %.2lf BDT\n", s - discount*s );
    


//IN CASE CUSMOTER FORGETS AN ITEM

    ItemDelete:
    printf("\nDelete, Add item or Continue with purchase(D/A/C)\n");
    fflush(stdin);
    scanf("%c", &choice);
    fflush(stdout);
    if(choice=='D' || choice=='d')
    {
        Again:
        printf("Enter item number: ");
        int pos;//ENTER ITEM NUMBER TO REMOVE
        scanf("%d", &pos);

        //CALCULATE NEW PRICE
        s = s - (list[pos].ItemPrice*list[pos].quantity);

        if(pos>n || pos<0)
        {
            printf("Item not found! Try again\n");
            goto Again;
        }
        else
        {
            //SHIFT ALL ELEMENTS POSITION BY -1
            for(i=pos; i<n-1; i++)
            {
                strcpy(list[i].ItemName, list[i+1].ItemName);
                list[i].ItemPrice = list[i+1].ItemPrice;
                list[i].quantity = list[i+1].quantity;
            }

        }

        //DECREASE THE ARRAY SIZE
        n--;
        
    }
    else if (choice=='A' || choice=='a')
    {
        //SHIFT ALL ELEMENTS POSITION BY +1
        for(i=n+1;i>=1;i--)
        {
            strcpy(list[i+1].ItemName, list[i].ItemName);
            list[i+1].ItemPrice=list[i].ItemPrice;
            list[i+1].quantity = list[i].quantity;
        }

        //ENTER NEW ELEMENT DETAILS, IT WILL BE PLACED AT FIRST
        printf("Enter Item Name: ");
        fflush(stdin);
        gets(list[i+1].ItemName);
        fflush(stdout);
        printf("Enter Item Price: ");
        scanf("%lf", &list[i+1].ItemPrice);
        printf("Enter quantity: ");
        scanf("%d", &list[i+1].quantity);
        //CALCULATE THE NEW PRICE
        s = s + (list[i+1].ItemPrice*list[i+1].quantity);

        //INCREASE ARRAY SIZE
        n++;

    }
    else if( choice=='C' || choice=='c' ){}//NO COND. SO LOOP EXIT
    else
    {
        printf("Incorrect input! Try again!\n");
        goto ItemDelete;//GOES BACK TO START     
    }
    PrintItems();
    printf("TOTAL : %.2lf BDT\n", s);

//DISCOUNT
    discount = Discount(s);
    printf("Surprise discount given: %.0lf%c\n", (discount*100), '%' );
    printf("Amount to pay: %.2lf BDT\n", s - discount*s );

//FINAL CHECK
    finalCheck:
    printf("\n>>Will that be all?\nY-Yes\nN-No some items are to be added/dropped\nEnter: ");
    fflush(stdin);
    scanf("%c", &choice);
    fflush(stdout);
    if(choice=='Y' || choice=='y'){}
    else if (choice=='N' || choice=='n')
    {
        goto ItemDelete;
    }
    else
    {
        printf(">>Didn't understand, invalid input!\n");
        goto finalCheck;

    }

//PRINT THE RECEIPT
    printReceipt();

//PAY OPTION    
    payOption:
    printf(">>Cash or Card?\n(1)Cash\t(2)Card\nEnter: ");
    int ch;
    scanf("%d", &ch);
    switch(ch){
        //IF PAYING WITH CASH
        case 1:
        {
            printf(">>Give cash(NOTE: ENTER ANY AMOUNT): ");
            double wallet;
            scanf("%lf", &wallet);
            double change;
            if(wallet<( s - (s*discount))){
                printf(">>Sorry, not enough cash!\nChanging Payment Method\n\n");
                goto payOption;
            }
            else if (wallet > ( s - (s*discount)) ){
                change = wallet - ( s - (s*discount) );
                printf("%.2lf BDT change returned!Thanks for paying\n", change);
            }
            else if ( wallet == ( s - (s*discount)) ){
                printf("Thanks for paying!\n");
            }
            break;
        }
        //IF PAYING WITH CARD
        case 2:
        {
            bill = fopen("CreditBill.txt", "w");
            Customer.CardBalance=100000;
            CardType:
            printf("Enter Card Name: ");
            fflush(stdin);
            gets(Customer.Type);
            fflush(stdout);
            int k=0, mark=1;
            while( Customer.Type[k] != '\0' )
            {
                if( (Customer.Type[k]>='a' && Customer.Type[k]<='z') || (Customer.Type[k]>='A' && Customer.Type[k]<='Z') || Customer.Type[k]==' ' || Customer.Type[k]=='-'  )
                {
                    mark = 1;
                }
                else
                {
                    mark = 0;
                }
                if(mark==0)
                {
                    break;
                }
                k++;
            }
            switch(mark)
            {
                case 1:
                {
                    break;
                }
                case 0:
                {
                    printf("Card not found! Re-");
                    goto CardType;
                }
            }
            CNum:
            printf("Enter card number: ");
            fflush(stdin);
            gets(Customer.CardNum);
            fflush(stdout);
            int m=0, flag=1;
            while(Customer.CardNum[m] != '\0')
            {
                if( Customer.CardNum[m] >= '0' && Customer.CardNum[m] <= '9' )
                {
                    mark = 1;
                }
                else
                {
                    mark = 0;
                }
                if(mark==0)
                {
                    break;
                }
                m++;
            }

            switch (mark)
            {
                case 1:
                {
                    break;
                }
                case 0:
                {
                    printf("Error! Re-enter ");
                    goto CNum;
                }
            }
            
            if(strlen(Customer.CardNum) == 16){}
            else
            {
                printf("Invalid Card Number. Re-enter ");
                goto CNum;
            }
            yearExpiry:
            printf("Enter Year of Expiry: ");
            scanf("%d", &Customer.YearOfExpiry);
            if( Customer.YearOfExpiry<=2019 || Customer.YearOfExpiry>=2030 )
            {
                printf("Invalid Year. Re-");
                goto yearExpiry;
            }
            pin:
            printf("Enter PIN: ");
            scanf("%d", &Customer.PIN);
            if( Customer.PIN<=0 || Customer.PIN>=10000 )
            {
                printf("Invalid PIN. Re-");
                goto pin;
            }
            if( Customer.CardBalance>= (s - (discount*s) ) )
            {
                fprintf(bill, "\t CASH RECEIPT\n=========================\n");
                fprintf(bill, "Address:\t\t*address*\n");
                fprintf(bill, "Tel:\t\t012345678901\n");
                fprintf(bill, "=====BILLING DETAILS=====\n");
                fprintf(bill, "CARD NUM. : %s\n", Customer.CardNum);
                fprintf(bill, "CARD NAME : %s\n", Customer.Type);
                fprintf(bill, "EXPY DATE : %d\n", Customer.YearOfExpiry);
                fprintf(bill, "CARD TYPE : Credit Card\n");
                fprintf(bill, "TOTAL AMOUNT : %.2lf BDT\n", (s - (s*discount)) );
                fprintf(bill, "=========================\n\n\n");
                fprintf(bill, "SIGN:____________________\n");
                fprintf(bill, "Come again!\n");
            }
            else
            {
                printf(">>NOT ENOUGH BALANCE IN CARD!\n");
                        goto payOption;
            }
                    
            fclose(bill);
            break;
        }
        default:
        {
            printf(">>Unspecified Option\nRetry\n");
            goto payOption;
        }
    }
    printf("\n\n>>CUSTOMER SERVED SUCCESSFULLY\n\n\n");

//CLOSING SYSTEM
    close:
    printf("(1)Close Counter\t(2)Next Customer\nChoice: ");
    int num;
    char key;
    scanf("%d", &num);
    if(num==1){
        printf(">>PRESS ENTER KEY TO CLOSE COUNTER\n");
        getchar();
        scanf("%c", &key);
        return 0;
    }else if(num==2){
        printf("\n\n----------------------------------------------------------------------------------------------NEXT CUSTOMER--------------------------------------------------------------------------------------------------------\n\n");
        main();
    }else{
        printf(">>NOT A VALID CHOICE\n");
        goto close;
    }


}
