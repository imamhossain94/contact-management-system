#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<process.h>
#include <windows.h>
#include<stdlib.h>
#include<dos.h>

COORD coord = {0,0};
void gotoxy(int x,int y)
{
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}


int i,j;
int main_exit;
void menu();


struct contact
{
    int id;
    long long phone;
    char name[20],
    address[20],
    email[50],
    letter[2];
}add,check,upd,rem;

void fordelay(int j)
{   int i,k;
    for(i=0;i<j;i++)
         k=i;
}


void console(int x1,int y1,int x2,int y2);
void console(int x1,int y1,int x2,int y2)
{
    int i;
    gotoxy(x1,y1); printf("%c",201);
    for(i=x1+1;i<x2;i++)
    {
        printf("%c",205);
    }
    printf("%c",187);
    for(i=y1+1;i<y2;i++)
    {
        gotoxy(x1,i); printf("%c",186);
        gotoxy(x2,i); printf("%c",186);
    }
    gotoxy(x1,y2); printf("%c",200);

    for(i=x1+1;i<x2;i++)
    {
        printf("%c",205);
    }
    printf("%c",188);
}

void add_contact()
{
    system("cls");
    console(0,0,70,20);
    for(i=1;i<68;i++) { gotoxy(1+i,2); printf("%C",196);}
    for(i=1;i<68;i++) { gotoxy(1+i,15); printf("%C",196);}
    phone:
    gotoxy(31,1); printf("ADD CONTACT");
   // get unique phone number
    FILE *fp;
    fp=fopen("contact.dat","a+");

    gotoxy(2,5); printf("phone      :"); gotoxy(15,5); scanf("%lld",&check.phone);
    while(fscanf(fp," %lld %s %s %s",&add.phone,&add.name,&add.address,&add.email)!=EOF)
    {
        if(check.phone==add.phone)
        {
            gotoxy(14,15);printf(">> This Phone number already used!! <<");
            gotoxy(15,5); printf("              ");
            fordelay(100000000);for(i=1;i<68;i++) { gotoxy(1+i,15); printf("%C",196);}
            goto phone;
        }
    }add.phone=check.phone;

    gotoxy(2,7); printf("Name       :");
   gotoxy(15,7); scanf("%s",add.name);

    //address
    gotoxy(2,9); printf("Address    :");
    gotoxy(15,9); scanf("%s",add.address);

    //email
    gotoxy(2,11); printf("Email      :");
    gotoxy(15,11); scanf("%s",add.email);

    //saving all input document
    fprintf(fp," %lld %s %s %s",add.phone,add.name,add.address,add.email);
    fclose(fp);

    gotoxy(18,15); printf("> Contact Added Successfully <");

    add:
            gotoxy(2,16);printf("> 0 [add another contact]");
            gotoxy(2,17);printf("> 1 [main menu]");
            gotoxy(2,19);printf(">   Enter your choice: ");
            gotoxy(24,19);scanf("%d",&main_exit);
            if (main_exit==1)
                menu();
            else if(main_exit==0)
                add_contact();
            else
                {
                    MessageBox(NULL,"Invalid selection!!                                      ","Warning",MB_OK);
                    fordelay(1000000);
                    goto add;
                }

}

void view()
{
    system("cls");
    gotoxy(45,1); printf("> VIEW CONTACT <");

    int test=1;
    FILE *view;
    view=fopen("contact.dat","r");
    gotoxy(7,2);

    while(fscanf(view," %lld %s %s %s",&add.phone,&add.name,&add.address,&add.email)!=EOF)
    {
        printf("\n\t%d.\tName: %-6s \tPhone: %-12lld \tAddress: %-10s \tEmail: %s\n",test,add.name,add.phone,add.address,add.email);
        test++;
    }fclose(view);

    viewl:
            printf("\n\n\n\n\n\t1.[main menu]\t 2.[Delete]\t3.[Edit] ");
            scanf("%d",&main_exit);
            if (main_exit==1)
            {
                system("cls");
                menu();
            }
            if (main_exit==2)
            {
                system("cls");
                del();
            }
            if (main_exit==3)
            {
                system("cls");
                edit();
            }
            else
            {
                MessageBox(NULL,"Invalid selection!!                                      ","Warning",MB_OK);
                fordelay(100000000);
                goto viewl;
            }
}

void del()
{
    system("cls");
    console(0,0,70,20);
    for(i=1;i<68;i++) { gotoxy(1+i,2); printf("%C",196);}
    for(i=1;i<68;i++) { gotoxy(1+i,15); printf("%C",196);}
    gotoxy(31,1); printf("DELETE CONTACT");

    int test=0;
    FILE *fp,*ft;
    fp=fopen("contact.dat","r");
    ft=fopen("new.dat","w");

    gotoxy(2,5);printf("> Enter phone number to delete:");
    gotoxy(34,5);scanf("%lld",&check.phone);

    while(fscanf(fp," %lld %s %s %s",&add.phone,&add.name,&add.address,&add.email)!=EOF)
     {
         if(add.phone!=check.phone)
         {
            fprintf(ft," %lld %s %s %s",add.phone,add.name,add.address,add.email);
         }
        else
        {
            test++;
            gotoxy(26,14); printf("Contact deleted");
        }
     }
    fclose(fp);
    fclose(ft);
    remove("contact.dat");
    rename("new.dat","contact.dat");

    if(test==0)
    {
        gotoxy(25,14); printf("Contact not found!!");
        fordelay(10000000000); view();
    }

    dell:
            gotoxy(2,19); printf("> Enter '1' for main menu: ");
            scanf("%d",&main_exit);
            if (main_exit==1)
                    {
                        system("cls");
                        menu();
                    }
                    else
                    {
                    MessageBox(NULL,"Invalid selection!!                                      ","Warning",MB_OK);
                    fordelay(100000000);
                    goto dell;
                    }
}

void edit()
{
    system("cls");
    console(0,0,70,20);
    for(i=1;i<68;i++) { gotoxy(1+i,2); printf("%C",196);}
    for(i=1;i<68;i++) { gotoxy(1+i,15); printf("%C",196);}
    gotoxy(31,1); printf("EDIT CONTACT");

    int test=0;
    FILE *view;
    view=fopen("contact.dat","r");
    gotoxy(2,3); printf("Name:");
    gotoxy(9,3);
    while(fscanf(view," %lld %s %s %s",&add.phone,&add.name,&add.address,&add.email)!=EOF)
    {
        printf("%s-", add.name);
        test++;
    }fclose(view);
    for(i=1;i<68;i++) { gotoxy(1+i,4); printf("%C",196);}

    FILE *fp,*ft;
    fp=fopen("contact.dat","r");
    ft=fopen("new.dat","w");

    gotoxy(2,5);printf("> Enter Name to Edit:");
    gotoxy(26,5);scanf("%s",&check.name);


    while(fscanf(fp," %lld %s %s %s",&add.phone,&add.name,&add.address,&add.email)!=EOF)
     {
         if(strcmpi(add.name,check.name)==0)
        {
        test=1;
        gotoxy(2,7); printf("Name       :");   gotoxy(15,7); scanf("%s",upd.name);
        gotoxy(2,9); printf("phone      :");   gotoxy(15,9); scanf("%lld",&upd.phone);
        gotoxy(2,11); printf("Address    :");   gotoxy(15,11); scanf("%s",upd.address);
        gotoxy(2,13); printf("Email      :");   gotoxy(15,13); scanf("%s",upd.email);
        fprintf(ft," %lld %s %s %s",upd.phone,upd.name,upd.address,upd.email);
        gotoxy(25,14); printf("Save changed!!");
        }
        else fprintf(ft," %lld %s %s %s",add.phone,add.name,add.address,add.email);
     }
     fclose(fp);
     fclose(ft);
     remove("contact.dat");
     rename("new.dat","contact.dat");

      if(test!=1)
    {
        gotoxy(25,14); printf("Contact not found!!");
        fordelay(10000000000);

    }

    edit:
            gotoxy(2,19); printf("> Enter '1' for main menu: ");
            scanf("%d",&main_exit);
            if (main_exit==1)
                    {
                        system("cls");
                        menu();
                    }
                    else
                    {
                    MessageBox(NULL,"Invalid selection!!                                      ","Warning",MB_OK);
                    fordelay(100000000);
                    goto edit;
                    }

}

void search(void)
{
    system("cls");
    int choice,test=0;
    console(0,0,70,20);
    for(i=1;i<68;i++) { gotoxy(1+i,2); printf("%C",196);}
    for(i=1;i<68;i++) { gotoxy(1+i,15); printf("%C",196);}
    gotoxy(31,1); printf("SEARCH CONTACT");

    FILE *sea;
    sea=fopen("contact.dat","r");

    gotoxy(2,5); printf("> 1.Search by First Letter");
    gotoxy(2,7); printf("> 2.Search by Name");
    gotoxy(2,9); printf("> 3.Search by Number");
    gotoxy(2,11); printf("> 4.Search by Address");

    gotoxy(2,13); printf("> Enter Your choice: ");choice  = getche();
    switch(choice)
    {
	 	    case '1' :
            {
            system("cls");
            gotoxy(0,1); printf("Enter Letter: "); scanf("%s",check.letter);
            gotoxy(45,3);  printf("> SEARCH BY LETTER <\n\n");
            while(fscanf(sea," %lld %s %s %s",&add.phone,&add.name,&add.address,&add.email)!=EOF)
            {
                if(add.name[0]==check.letter[0])
                {
                    printf("\n\t%s.\tName: %-6s \tPhone: %-12lld \tAddress: %-10s \tEmail: %s\n",check.letter,add.name,add.phone,add.address,add.email);
                    test++;
                }
            }

            }break;

			case '2' :
            {
            system("cls");
            console(0,0,70,20);
            for(i=1;i<68;i++) { gotoxy(1+i,2); printf("%C",196);}
            for(i=1;i<68;i++) { gotoxy(1+i,15); printf("%C",196);}
            gotoxy(31,1); printf("SEARCH By Name");
            gotoxy(2,3); printf("Enter Name: "); scanf("%s",check.name);


            while(fscanf(sea," %lld %s %s %s",&add.phone,&add.name,&add.address,&add.email)!=EOF)
            {
                if(strcmpi(add.name,check.name)==0)
                {
                    gotoxy(2,5); printf("Name     :"); printf("%s",add.name);
                    gotoxy(2,7); printf("Phone    :"); printf("%lld",add.phone);
                    gotoxy(2,9); printf("Address  :"); printf("%s",add.address);
                    gotoxy(2,11); printf("Email    :"); printf("%s",add.email);

                }
            }
            }break;

            case '3' :
            {
            system("cls");
            console(0,0,70,20);
            for(i=1;i<68;i++) { gotoxy(1+i,2); printf("%C",196);}
            for(i=1;i<68;i++) { gotoxy(1+i,15); printf("%C",196);}
            gotoxy(31,1); printf("SEARCH BY NUMBER");
            gotoxy(2,5); printf("Enter Number: "); scanf("%lld",&check.phone);
            while(fscanf(sea," %lld %s %s %s",&add.phone,&add.name,&add.address,&add.email)!=EOF)
            {
                if(add.phone==check.phone)
                {
                    gotoxy(2,5); printf("Name     :"); printf("%s",add.name);
                    gotoxy(2,7); printf("Phone    :"); printf("%lld",add.phone);
                    gotoxy(2,9); printf("Address  :"); printf("%s",add.address);
                    gotoxy(2,11); printf("Email    :"); printf("%s",add.email);

                }
            }
            }break;

            case '4' :
            {
            system("cls");
            console(0,0,70,20);
            for(i=1;i<68;i++) { gotoxy(1+i,2); printf("%C",196);}
            for(i=1;i<68;i++) { gotoxy(1+i,15); printf("%C",196);}
            gotoxy(31,1); printf("SEARCH BY ADDRESS");
            gotoxy(2,5); printf("Enter Address: "); scanf("%s",check.address);
            while(fscanf(sea," %lld %s %s %s",&add.phone,&add.name,&add.address,&add.email)!=EOF)
            {
                if(strcmpi(add.address,check.address)==0)
                {
                    gotoxy(2,5); printf("Name     :"); printf("%s",add.name);
                    gotoxy(2,7); printf("Phone    :"); printf("%lld",add.phone);
                    gotoxy(2,9); printf("Address  :"); printf("%s",add.address);
                    gotoxy(2,11); printf("Email    :"); printf("%s",add.email);
                }
            }
            }break;
    }
}

void menu()
{
    system("cls");
    system("color 7");
    char choice;
    console(0,0,70,20);
    for(i=1;i<40;i++) { gotoxy(15+i,10); printf(" ");}
    for(i=1;i<68;i++) { gotoxy(1+i,2); printf("%C",196);}
    for(i=1;i<68;i++) { gotoxy(1+i,18); printf("%C",196);}
    gotoxy(32,1); printf("MAIN MENU");

    menu:
    gotoxy(2,4); printf("> 1. Add Contact.");
    gotoxy(2,6); printf("> 2. Delete Contact.");
    gotoxy(2,8); printf("> 3. Edit Contact.");
    gotoxy(2,10); printf("> 4. Search Contact.");
    gotoxy(2,12); printf("> 5. View Contact list.");
    gotoxy(2,14); printf("> 6. Exit().");

    gotoxy(2,19); printf("> Enter your choice:");
    gotoxy(23,19); choice  = getche();

    switch(choice)
		{
	 	    case '1' :add_contact();

			break;
			case '2' :del();

			break;
            case '3' :edit();

			break;
            case '4' :search();

			break;
            case '5' : view();

			break;
            case '6' : exit(1);

			break;


		}

}

int main()
{
    char choice;
    console(0,0,70,20);
    char g[40]="  WELCOME TO CONTACT MANAGEMENT SYSTEM  "; int n; gotoxy(16,10); for(n=0;n<40;n++){; printf("%c",g[n]); Sleep(50); }
    for(i=1;i<40;i++) { gotoxy(15+i,10); printf("%C",196);Sleep(30);}
    for(i=1;i<40;i++) { gotoxy(15+i,10); printf(" ");}
    for(i=1;i<68;i++) { gotoxy(1+i,2); printf("%C",196);}
    for(i=1;i<68;i++) { gotoxy(1+i,18); printf("%C",196);}

    menu();

}





