#include <stdio.h>
#include <string.h>

//Author: Ramazantk3
int currentaccountid;
int carcount = 5;

struct cars {
  char name[25];
  int  price;
  char color[15];
  int sold;
  char owner[25];
};

struct accounts {
  char name[25];
  char password[25];
  int  money;
  int  ownedcarcount;
  struct cars ownedcar[20];
};

struct cars car[10];
struct accounts account[10];
void searchcar(struct accounts account0);
char buycar(struct accounts *account0, struct cars *car0);


int main(){
   int accountcount = 0;
   int created_userid;
   struct cars *carptr;
   struct accounts *accountptr;
    // Initialization of car variables.

    char carnames[10][25] = {"Ford","BMW","Lamborghini","Renault","Tesla"};
    char color[10][15] = {"Red","Blue","Green","Red","Green"};
    int price[10] ={1000,10000,15000,5000,7500};

 for(int i=0; i<=4; i++){
    strcpy(car[i].name , carnames[i]);
    car[i].price = price[i];
    strcpy(car[i].color , color[i]);
    car[i].sold = 0;
  }
    //

  //Main Menu
   account[0].money = 12500;
   strcpy(account[0].password,"1234");
   strcpy(account[0].name,"admin");
   char logininfo;

   printf("Welcome to the Car Trading App!\n");
   Main_menu: 
   printf("Please type \nL: To Login\nC: To Create an Account\n");
   scanf(" %c",&logininfo);
  //

   //Login Screen
   if (logininfo =='L'){

     char password[25];
     int  id,idcar;
     printf("Id:");
     scanf("%d",&id);
     printf("Password:");
     scanf("%s",password);
     printf("%s",password);
     if (strcmp(account[id].password, password)== 0){
     printf("\n\nLogin Successful!\nHello %s \n",account[id].name);
     currentaccountid = id;
     account[0].money = 12500;
     //Actions Screen
     char action_info;
     char cancel_info;
     Actions_menu:

     printf("What would you like to do?\nPlease type \nB: To Buy Cars\nC: To See the Cars You Own\nM: For Monetary Transactions\nX: To Sign Out\n");
     scanf(" %c",&action_info);
     //Buy Car
     if (action_info =='B'){
      search_car:
      searchcar(account[currentaccountid]);
      printf("Please enter X to go back, enter any other letter or number to proceed.\n");
      scanf(" %c",&cancel_info);
      if(cancel_info == 'X'){
        printf("Action canceled. Now you are redirected to Actions Menu...\n");
        goto Actions_menu;
      }else{
      printf("Please Enter the Id the of the Car You Want to Buy.\n");
      scanf("%d",&idcar);
      }
      char moneycheck;
      accountptr = &account[currentaccountid];
      carptr = &car[idcar];
      moneycheck = buycar(accountptr,carptr);
      if(moneycheck =='!'){
        goto search_car;
      }else{
        goto Actions_menu;
      }
    // Check the cars user own
    } else if(action_info == 'C'){
      printf("The List Of the Cars You Own\n");
      printf("Id  Name             Color            Price\n");
      for(int k=0; k< account[currentaccountid].ownedcarcount; k++){
      printf("%-*d: %-*s: %-*s: %d\n", 2,k  ,15,account[currentaccountid].ownedcar[k].name  ,15,account[currentaccountid].ownedcar[k].color ,account[currentaccountid].ownedcar[k].price);
      }
      printf("\n");
      goto Actions_menu;
    
    //Monetary Transactions
    } else if(action_info == 'M'){
      char money_info;
      int changemoney;
      mispress:
      printf("Your Money: %d\n",account[currentaccountid].money);
      printf("Please type \nA: To Add Money\nW: To Withdraw Money\n");
      scanf(" %c",&money_info);
      if(money_info =='A'){
        printf("Please enter the amount of money you want to add(please use integers):\n");
        scanf("%d",&changemoney);
        account[currentaccountid].money += changemoney;
        printf("Money added successfully...\n");
        printf("Your Money is Now:%d\n",account[currentaccountid].money);
        goto Actions_menu;
      } else if(money_info =='W'){
        printf("Please enter the amount of money you want to withdraw(please use integers):\n");
        scanf("%d",&changemoney);
        account[currentaccountid].money -= changemoney;
        printf("Money withdrew successfully...\n");
        printf("Your Money is Now:%d\n",account[currentaccountid].money);
        goto Actions_menu;
      }else
      goto mispress;

    }else if(action_info == 'X'){
    goto Main_menu;
  } 
  }
  //Login Failed
    else {
      printf("\nPlease Try Again...\n");
      goto Main_menu;
    }
   } else if (logininfo =='C'){
// Create Account Screen
    char name[25], password[25];
    int money;

    printf("Enter your name:");
    scanf("%s",&name);
    strcpy(account[accountcount].name,name);
    printf("Enter your password:");
    scanf("%s",&password);
    strcpy(account[accountcount].password,password);
    printf("Enter your money(Please use integers):");
    scanf("%d",&money);
    account[accountcount].money = money;
    account[accountcount].ownedcarcount = 0;

    printf("Account created successfully...\nYour id is %d please do remember this. Now you are redirected to main menu...\n",accountcount);
    accountcount++;
    goto Main_menu;
    }else
    goto Main_menu;
  return(0);
}

void searchcar(struct accounts account0){
   printf("Please type\n1: To See The List\n2: To Search Cars by Color\n");
   int a;
   scanf("%d",&a);
    if(a==1){
      printf("Id  Name             Color            Price\n");
      for(int k=0; k< carcount; k++){
      printf("%-*d: %-*s: %-*s: %d\n",2,k ,15,car[k].name ,15,car[k].color ,car[k].price);
      }
    }
      printf("Your Money: %d\n",account0.money);

}

char buycar (struct accounts *account0, struct cars *car0){
  char confirm;
  struct cars carx;
  carx = *car0;
  if(car0->price <= account0->money){
  printf("You have enough money to buy this car. Do you confirm buying?\nPlease type Y to confirm, N to cancel.\n");
  }else{
    printf("You don't have enough money to buy this car.");
    return('!');//only this used
  }
  scanf(" %c",&confirm);
   if(confirm == 'Y'){
   strcpy(car0->owner, account0->name);
   account0->money = account0->money - car0->price;
   account0->ownedcar[account0->ownedcarcount] = carx;
   account0->ownedcarcount++;
   printf("Buying successful... Now you own the %s car.\nYou are now redirected to actions menu...\n",car0->name);
   return('V'); //unused
   }else{
    printf("Buying canceled. Now you are redirected to actions menu...\n");
    return('V');//unused
   }
  }