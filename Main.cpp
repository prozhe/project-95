// Libraries
#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>
//#include <dirent.h>
//#include <unistd.h>
#include <sys/stat.h>
#include <Tchar.h>
#include <stdarg.h>
//Libraries



//Colours
#define RED     "\x1b[31m"  
#define GREEN   "\x1b[32m"	
#define YELLOW  "\x1b[33m"	
#define BLUE    "\x1b[34m"	
#define MAGENTA "\x1b[35m"	
#define CYAN    "\x1b[36m"	
#define RESET   "\x1b[0m"	
//Colours



//Variables
int um =0 ;//user status    checking if user is admin or not 
int rt;//reaming time that user can use the program
char user[21];//for showing username in the programm all the time 
time_t st,t1;//starting time for a user for using in time limit 
int access = 0 ; // access point
FILE *history ; 
//Variables



//Functions
int tim();//showing time 
void xclear(void);//somthing like system ("Cls");
int checking_users(char username[21],char password[17]);//cheking whether the username and password is correct or not
int adfun();//function that runs when admin is using the programm
int crtur();//function for creating user by admin
int chguse(char *p);//function for changing user by 
int gesfun();//functionn that runs when user is geust
int isLeapYear( int year );// True if leap year 
int leapYears( int year );// The number of leap year 
int todayOf( int y, int m, int d);// The number of days since the beginning of the year 
long days( int y, int m, int d);// Total number of days 
void calendar(int y, int m);// display calendar at m y 
int finalcal();// function for initializing calendar
int timeminus(char *un , char *num); // function for cutting time of one user
int adminpasschg(char *un);// function for changing password for admin
int passchg();//function for changing one's password
int gesfun();//function for doing geust command
int timecheck();//checking if user time is finished or not 
int clear();//just Clear screen screen
int crttm();//changing user by a geust 
int histor(char *tempr);//history function
int h();//showing history
//Functions



int main ()
{
	
	char username[21],password[17];
	while (1){
		printf("................................\n................................\n");
		printf("Please Enter Your Username and Password\n	Username :");
		scanf("	%20s",username);
		printf("	Password :");
		scanf("%16s",password);
		if (!(strcmp(username , "admin"))) 
		{
			if (!(strcmp(password,"admin")))
			{
				strcpy(user , "admin");
				um = 1  ;
				break;
			}
		}
	
		if (checking_users(username,password)) break;

	}//getting username and password till get a correct username and password
	getchar();	
	xclear();//should be replaced with xclear 
			if (um == 1) 
	{
		// if user is admin this function will be called 
		adfun();
		
	}
			if (um == 0 )
			{
				gesfun();
			}
		
	
}

int h ()
{
	history = fopen (".history.txt","r");
	char you[42];
	while (!feof(history))
	{
		fscanf(history,"%s",you);
		printf("%s\n",you);
	}
	fclose(history);
	return 0 ;
}

int timecheck()
{	
				char username[21],password[17];

	t1 = time(NULL);
	if (t1-st > rt)
		{
			clear();
			printf("User time is Finished\nLogin as another user\n");
	while (1){
		printf("................................\n................................\n");
		printf("Please Enter Your Username and Password\n	Username :");
		scanf("	%20s",username);
		printf("	Password :");
		scanf("%16s",password);
		if (!(strcmp(username , "admin"))) 
		{
			if (!(strcmp(password,"admin")))
			{
				strcpy(user , "admin");
				um = 1  ;
				access = 1;
				break;
			}
		}
	
		if (checking_users(username,password)) break;

	}//getting username and password till get a correct username and password
	getchar();	
	xclear();
		}
	return 0 ;
}

int crttm()
{
	t1 = time (NULL);
	int tim = rt - (t1 - st ),t,vaz =0,a ;
	char *string,us[21];
	char username[21],password[17];
	FILE *file , *temp1;
	temp1 = fopen (".temp.txt","w");
	file = fopen (".user.txt","r");
	while (!feof(file))
	{
		fscanf(file,"%20s%16s%d%d",username,password,&t,&a);
		if ( strcmp(username,user))
		{
			fprintf(temp1,"%s %s %d %d\n",username,password,t,a);
		}
		else
		{
			vaz = 1 ;
			t = tim;
			if ( t < 0 ) { t = 0 ;}
			fprintf(temp1,"%s %s %d %d\n",username,password,t,a);
		}
	}
	if ( vaz ==  0 ) 
	{
		printf("No Such User\n");
	}

	fclose(temp1);
	fclose(file);
	temp1 = fopen (".temp.txt","r");
	file = fopen (".user.txt","w");
	while ( !feof(temp1))
	{
		fscanf(temp1,"%s%s%d%d",username,password,&t,&a);
		fprintf(file,"%s %s %d %d\n",username,password,t,a);
	}
	if ( vaz == 1 ) 
	{
		//printf("Action is Done\n");
	}
	fclose(temp1);
	fclose(file);
	return 0 ; 

}
int histor(char *tempr)
{
		history = fopen (".history.txt","a");
	fprintf(history,"%s",tempr);
	fclose(history);
	return 0 ;
}
int gesfun()
{

	while(1){
			timecheck();
			printf("Enter Your Command Please:\t");
   char command[40] ;
   char tempr[41];
   const char s[2] = " ";
   char *token;
   char *part[6];
   int tem = 0 ; 
   while ( (command[tem] = getchar()) != '\n'){tem++; timecheck();}
   command[tem] = '\0';
   strcpy(tempr,command);
   token = strtok(command, s);
   part[0] = token;
   tem = 0 ; 
   while( token != NULL ) 
   {
	    
	    token = strtok(NULL, s);
		part[++tem] = token ;
   }
   //till now we have seperated command by space 
   
	if ( ! ( strcmp (part[0] , "su")))
	{
		histor(tempr);
		crttm();
		chguse(part[1]);
	}
	//cheking whether su was typed

	else if ( ! ( strcmp ( part[0] , "exit")))
	{
				histor(tempr);
		crttm();
		exit(1);
	}
	//:| :| :|

	else if ( ! ( strcmp ( part[0] , "calendar"))) 
	{
				histor(tempr);
		timecheck();

		finalcal();
	}
	//using for calling calendar function

	else if ( ! ( strcmp (part[0] , "clear")))
	{	timecheck();
				histor(tempr);
		xclear();
	}
	//:| :| :|
	else if ( ! ( strcmp (part[0] , "passwd")))
		{		histor(tempr);
			timecheck();

			passchg();
		}		
	else if (!(strcmp(part[0] , "history")))
	{
		h();
	}
	else if (!(strcmp(part[0] , "time")))
	{
		histor(tempr);
		tim();
	}
	else
	{
		printf("Wrong Command");
	}
		}
	

return 0 ; 
}

int timeminus(char *un , char *num)
{
	int tim,t,vaz =0 ,a;
	char *string,us[21];
	char username[21],password[17];
	strcpy(us , un );
	tim = strtod (num,&string);
	FILE *file , *temp1;
	temp1 = fopen (".temp.txt","w");
	file = fopen (".user.txt","r");
	//printf("%s\n%d",un,tim);
	while (!feof(file))
	{
		fscanf(file,"%20s%16s%d%d",username,password,&t,&a);
		if ( strcmp(username,us))
		{
			fprintf(temp1,"%s %s %d %d\n",username,password,t,a);
		}
		else
		{
			vaz = 1 ;
			t = tim;
			if ( t < 0 ) { t = 0 ;}
			fprintf(temp1,"%s %s %d %d\n",username,password,t,a);
		}
	}
	if ( vaz ==  0 ) 
	{
		printf("No Such User\n");
	}

	fclose(temp1);
	fclose(file);
	temp1 = fopen (".temp.txt","r");
	file = fopen (".user.txt","w");
	while ( !feof(temp1))
	{
		fscanf(temp1,"%s%s%d%d",username,password,&t,&a);
		fprintf(file,"%s %s %d %d\n",username,password,t,a);
	}
	if ( vaz == 1 ) 
	{
		printf("Action is Done\n");
	}
	fclose(temp1);
	fclose(file);
	return 0 ; 
}

int adminpasschg(char *un)
{
	char username[21];
	char usname[21],pasword[17];
	int t,vaz=0;
	char newpass1[17],newpass2[17];
	strcpy(username,un);
	FILE *temp1,*file;
	printf("Enter New Password:\t");
	scanf("%s",newpass1);
	printf("Confirm Password:\t");
	scanf("%s",newpass2);
	getchar();
	int a;
	if ( strcmp (newpass1,newpass2))
	{
		printf("Confirmation doesn't match the password\n");
		return 0 ;
	}
	
		file = fopen (".user.txt","r");
		temp1 = fopen (".temp.txt","w");
		while (!feof(file))
		{
			fscanf(file,"%s%s%d%d\n",usname,pasword,&t,&a);
			if ( strcmp(usname,username))
			{
				fprintf(temp1,"%s %s %d %d\n",usname,pasword,t,a);
			}
			else
			{
				vaz  = 1 ;
				fprintf(temp1,"%s %s %d %d\n",usname,newpass1,t,a);
			}
		}
		if (vaz == 0 ) 
		{
			printf("Username is Invalid\n");
		}
	fclose(file);
	fclose(temp1);
	file = fopen (".user.txt","w");
	temp1 = fopen (".temp.txt","r");
	while ( !feof(temp1))
	{
		fscanf(temp1,"%s%s%d%d",usname,pasword,&t,&a);
		fprintf(file,"%s %s %d %d\n",usname,pasword,t,a);
	}
	fclose(file);
	fclose(temp1);
	if(vaz == 1 )
	{
	printf("Action is Done\n");
	}
	return 0 ;
}

int passchg()
{
	int l,ta;
	char usename[21],pasword[17];
	char newpass1[17],newpass2[17];
	FILE *temp1,*file;
	printf("Enter New Password:\t");
	scanf("%s",newpass1);
	printf("Confirm Password:\t");
	scanf("%s",newpass2);
	getchar();
	if (strcmp(newpass1,newpass2))
	{
		printf("Confirmation doesn't match the password\n");
		return 0 ;
	}
	file = fopen (".user.txt","r");
	temp1 = fopen(".temp.txt","w");
	while (!feof(file))
	{
		fscanf(file,"%s%s%d%d\n",usename,pasword,&l,&ta);
		if (strcmp(user,usename))
		{
			fprintf(temp1,"%s %s %d %d\n",usename,pasword,l,ta);
		}
		else
		{
			fprintf(temp1,"%s %s %d %d\n",usename,newpass1,l,ta);
		}
	}
	fclose(file);
	fclose(temp1);
	file = fopen (".user.txt","w");
	temp1 = fopen (".temp.txt","r");
	while (!feof(temp1))
	{
		fscanf(temp1,"%s%s%d%d\n",usename,pasword,&l,&ta);
		fprintf(file,"%s %s %d %d\n",usename,pasword,l,ta);
	}
	printf("Action is Done\n");
	return 0 ; 
}

int chguse(char *p)
{
	FILE *upf;//username and password file
	char fun[21],fpw[17];//file username and file password
	char username[21],password[17];
	strcpy(username, p);
	printf("Please Enter Password :");
	scanf("%16s",password);
	getchar();
	upf = fopen (".user.txt","r");
	if (!(strcmp(username,"admin")) && !(strcmp(password,"admin")))
	{
		strcpy(user , "admin");
		um =1 ; 
		xclear(); 
		adfun();
	}
	while ( !feof(upf))
	{
		fscanf(upf,"%s %s %d %d",fun,fpw,&rt,&access);
		if (!(strcmp(fun,username)))
		{
			if (!(strcmp(fpw,password)))
			{
				if ( rt )
				{
					rt = rt ; 
					strcpy(user,username);
					fclose(upf);
					st = time(NULL);
					xclear();
					gesfun();
					return 1;
				}
				printf("Account has Been Dismissed\n");
				fclose(upf);
				return 0 ;
			}
		}
	}
	fclose(upf);
	printf("Wrong Username or Password\n" );
	
	return 0 ;	


}

int checking_users(char username[21] , char password[17])
{
	FILE *upf;//username and password file
	char fun[21],fpw[17];//file username and file password
	upf = fopen (".user.txt","r");
	if ( upf == NULL ) printf("l;jkdaf");
	while ( !feof(upf))
	{
		fscanf(upf,"%20s%16s%d%d",fun,fpw,&rt,&access);
		if (!(strcmp(fun,username)))
		{
			if (!(strcmp(fpw,password)))
			{
				if ( rt )
				{
					rt = rt;
					strcpy(user,username);
					fclose(upf);
					st = time(NULL);
					return 1;
				}
				printf("Account has Been Dismissed\n");
				fclose(upf);
				return 0 ;
			}
		}
	}
	fclose(upf);
	printf("Wrong Username or Password\n");
	
	return 0 ;	
}

int adfun ()
{
   while ( 1 ){
   printf("Enter Your Command Please:\t");
   char command[40] ;
   char tempr[41];
   const char s[2] = " ";
   char *token;
   char *part[6];
   int tem = 0 ; 
   while ( (command[tem] = getchar()) != '\n'){tem++;}
   command[tem] = '\0';
   token = strtok(command, s);
   part[0] = token;
   tem = 0 ; 
   strcpy(tempr,command);
   while( token != NULL ) 
   {
	    
	    token = strtok(NULL, s);
		part[++tem] = token ;
   }
   //till now we have seperated command by space 
	if ( !(strcmp (part[0], "create")))
		{
			if ( !(strcmp(part[1],"user")))
			{
				crtur();
			}
			else
			{
				printf("Wrong Command\n");
				continue;
			}
		}
	// checking whether Create user was typed
	else if (!(strcmp(part[0] , "time")))
	{
		histor(tempr);
		tim();
	}

    else if ( ! ( strcmp (part[0] , "su")))
	{
		histor(tempr);
		chguse(part[1]);
	}
	//cheking whether su was typed

	else if ( ! ( strcmp ( part[0] , "exit")))
	{
		histor(tempr);
		exit(1);
	}
	//:| :| :|

	else if ( ! ( strcmp ( part[0] , "calendar"))) 
	{histor(tempr);
		finalcal();
	}
	//using for calling calendar function

	else if ( ! ( strcmp (part[0] , "clear")))
	{histor(tempr);
		xclear();
	}
	//:| :| :|

	else if ( ! ( strcmp (part[0] , "passwd")))
		{
			if ( ! ( strcmp ( part[1] , "-l")))
			{histor(tempr);
				if (part[2] == NULL || part[3] == NULL ){
				printf("Wrong Command\n");
				continue;
				}
				timeminus(part[3] , part[2]);
			}
			else
			{histor(tempr);
				adminpasschg(part[1]);
			}
	}
	else if ( !strcmp(part[0] , "history"))
	{
		h();
	}
	else { 
		printf("Wrong Command\n");
	}
   }
	
   return 0 ;
}

int crtur()
{
	printf("***\tPlease Enter The Name of the New User You Want to Add\t\***\n\tUsername :");
	char fun[21],fpw[17];
	char username[21], password[17];
	FILE *pf;
	int rm;
	scanf("%20s",username);
	printf("\tPassword :");
	scanf("%16s",password);
	printf("The Time You Want to Give to this Account (Minutes) :");
	int tim ,a ,ta;
	scanf("%d",&tim);
	printf("Access Level Please ( 1 Or 0) :");
	scanf("%d",&a);
	while(a != 1 && a!= 0)
	{
		printf("God damn it you F***er. Don't you Understand 1 Or 0\n ");
		printf("Access Level Please ( 1 Or 0) :) ");
		scanf("%d",&a);
	}
	getchar();
	pf = fopen (".user.txt","r");
	if (!(strcmp(username,"admin"))) {
		printf("***\tUsername can't be admin.\t*** \n"); 
		fclose(pf); 
		return 0 ; }
	while ( !feof(pf))
	{
		fscanf(pf,"%20s%16s%d%d",fun ,fpw,&rm,&ta);
		if (!strcmp (username,fun ))
		{
			printf("Username is Invalid\n");
			fclose (pf);
			return 0 ;
		}
	}
	fclose(pf);
	pf = fopen (".user.txt","a");
	fprintf(pf,"%s %s %d %d\n",username,password,tim*60,a);
	fclose(pf);
	printf("Action is Done\n");
return 0 ;
}

void xclear(void)
{
	int x = 0, y = 0; char ch;

	CONSOLE_SCREEN_BUFFER_INFO coninfo;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsole, &coninfo);
	coninfo.dwCursorPosition.Y = 0;
	coninfo.dwCursorPosition.X = 0;
	SetConsoleCursorPosition(hConsole, coninfo.dwCursorPosition);

	int counter, i;

	for (counter = 0; counter < 2000; counter++)
	{
		GetConsoleScreenBufferInfo(hConsole, &coninfo);
		coninfo.dwCursorPosition.Y = y;
		coninfo.dwCursorPosition.X = x;
		SetConsoleCursorPosition(hConsole, coninfo.dwCursorPosition);
jump:
			if (ch = fgetc(stdout) == '\n')
		{
			printf("%c", NULL);
			x = 0;
			y++;
		}
		else
		{ 
			printf("%c", NULL);
			x++;
		}
	}

	GetConsoleScreenBufferInfo(hConsole, &coninfo);
	coninfo.dwCursorPosition.Y = 0;
	coninfo.dwCursorPosition.X = 0;
	SetConsoleCursorPosition(hConsole, coninfo.dwCursorPosition);
	printf("***\t%s is Using the Programm\t***\n\n",user);

}
int tim()
{
		time_t theTime = time(NULL);
struct tm *aTime = localtime(&theTime);
int day = aTime->tm_mday;
int month = aTime->tm_mon + 1; // Month is 0 – 11, add 1 to get a jan-dec 1-12 concept
int year = aTime->tm_year + 1900; // Year is # years since 1900
int hour=aTime->tm_hour;
int min=aTime->tm_min;
printf("\t%d : %d\n\n",hour,min);
return 0 ;
}
int clear()
{
	
	int x = 0, y = 0; char ch;

	CONSOLE_SCREEN_BUFFER_INFO coninfo;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsole, &coninfo);
	coninfo.dwCursorPosition.Y = 0;
	coninfo.dwCursorPosition.X = 0;
	SetConsoleCursorPosition(hConsole, coninfo.dwCursorPosition);

	int counter, i;

	for (counter = 0; counter < 2000; counter++)
	{
		GetConsoleScreenBufferInfo(hConsole, &coninfo);
		coninfo.dwCursorPosition.Y = y;
		coninfo.dwCursorPosition.X = x;
		SetConsoleCursorPosition(hConsole, coninfo.dwCursorPosition);
jump:
			if (ch = fgetc(stdout) == '\n')
		{
			printf("%c", NULL);
			x = 0;
			y++;
		}
		else
		{ 
			printf("%c", NULL);
			x++;
		}
	}

	GetConsoleScreenBufferInfo(hConsole, &coninfo);
	coninfo.dwCursorPosition.Y = 0;
	coninfo.dwCursorPosition.X = 0;
	SetConsoleCursorPosition(hConsole, coninfo.dwCursorPosition);
	return 0 ;
}

int finalcal(){
    int year,month;

    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    char s[64];
    char o[64];
    strftime(s, sizeof(s), "%m", tm);
    char *stringPtr;
    char *date = s;
    int d,c;
    d = strtod( date, &stringPtr );
    strftime(o, sizeof(o), "%Y", tm);
    char *yea = o;
    c = strtod( yea, &stringPtr );

    calendar(c, d);
    return 0;
}

int isLeapYear( int y ) /* True if leap year */
{
    return(y % 400 == 0) || ((y % 4 == 0) && (y % 100 != 0));
}

int leapYears( int y ) /* The number of leap year */
{
    return y/4 - y/100 + y/400;
}

int todayOf( int y, int m, int d) /* The number of days since the beginning of the year */
{
    static int DayOfMonth[] =
        { -1/*dummy*/,0,31,59,90,120,151,181,212,243,273,304,334};

    return DayOfMonth[m] + d + ((m>2 && isLeapYear(y))? 1 : 0);
}

long days( int y, int m, int d) /* Total number of days */
{
    int lastYear;

    lastYear = y - 1;

    return 365L * lastYear + leapYears(lastYear) + todayOf(y,m,d);
}

void calendar(int y, int m) /* display calendar at m y */
{
    const char *NameOfMonth[] = { NULL/*dummp*/,
        "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"
    };
    char Week[] = "Su Mo Tu We Th Fr Sa";
    int DayOfMonth[] =
        { -1/*dummy*/,31,28,31,30,31,30,31,31,30,31,30,31 };
    int weekOfTopDay;
    int i,day;

    weekOfTopDay = days(y, m, 1) % 7;
    if(isLeapYear(y))
        DayOfMonth[2] = 29;
    printf("\n     %s %d\n%s\n", NameOfMonth[m], y, Week);

    for(i=0;i<weekOfTopDay;i++)
        printf("   ");
    for(i=weekOfTopDay,day=1;day <= DayOfMonth[m];i++,day++){
        printf("%2d ",day);
        if(i % 7 == 6)
            printf("\n");
    }
    printf("\n");
}