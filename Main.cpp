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
time_t st;//starting time for a user for using in time limit 
//Variables



//Functions
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
		
	
}

int gesfun()
{

return 0 ; 
}

int timeminus(char *un , char *num)
{
	int tim,t,vaz =0 ;
	char *string,us[21];
	char username[21],password[17];
	strcpy(us , un );
	tim = strtod (num,&string);
	FILE *file , *temp1;
	temp1 = fopen ("temp.txt","w");
	file = fopen ("user.txt","r");
	//printf("%s\n%d",un,tim);
	while (!feof(file))
	{
		fscanf(file,"%20s%16s%d",username,password,&t);
		if ( strcmp(username,us))
		{
			fprintf(temp1,"%s %s %d\n",username,password,t);
		}
		else
		{
			vaz = 1 ;
			t = tim;
			if ( t < 0 ) { t = 0 ;}
			fprintf(temp1,"%s %s %d\n",username,password,t);
		}
	}
	if ( vaz ==  0 ) 
	{
		printf("No Such User\n");
	}

	fclose(temp1);
	fclose(file);
	temp1 = fopen ("temp.txt","r");
	file = fopen ("user.txt","w");
	while ( !feof(temp1))
	{
		fscanf(temp1,"%s%s%d",username,password,&t);
		fprintf(file,"%s %s %d\n",username,password,t);
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
	if ( strcmp (newpass1,newpass2))
	{
		printf("Confirmation doesn't match the password\n");
		return 0 ;
	}
	
		file = fopen ("user.txt","r");
		temp1 = fopen ("temp.txt","w");
		while (!feof(file))
		{
			fscanf(file,"%s%s%d\n",usname,pasword,&t);
			if ( strcmp(usname,username))
			{
				fprintf(temp1,"%s %s %d\n",usname,pasword,t);
			}
			else
			{
				vaz  = 1 ;
				fprintf(temp1,"%s %s %d\n",usname,newpass1,t);
			}
		}
		if (vaz == 0 ) 
		{
			printf("Username is Invalid\n");
		}
	fclose(file);
	fclose(temp1);
	file = fopen ("user.txt","w");
	temp1 = fopen ("temp.txt","r");
	while ( !feof(temp1))
	{
		fscanf(temp1,"%s%s%d",usname,pasword,&t);
		fprintf(file,"%s %s %d\n",usname,pasword,t);
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
	upf = fopen ("user.txt","r");
	if (!(strcmp(username,"admin")) && !(strcmp(password,"admin")))
	{
		strcpy(user , "admin");
		um =1 ; 
		xclear(); 
		adfun();
	}
	while ( !feof(upf))
	{
		fscanf(upf,"%s %s %d",fun,fpw,&rt);
		if (!(strcmp(fun,username)))
		{
			if (!(strcmp(fpw,password)))
			{
				if ( rt )
				{
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
	upf = fopen ("user.txt","r");
	if ( upf == NULL ) printf("l;jkdaf");
	while ( !feof(upf))
	{
		fscanf(upf,"%20s%16s%d",fun,fpw,&rt);
		if (!(strcmp(fun,username)))
		{
			if (!(strcmp(fpw,password)))
			{
				if ( rt )
				{
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
   const char s[2] = " ";
   char *token;
   char *part[6];
   int tem = 0 ; 
   while ( (command[tem] = getchar()) != '\n'){tem++;}
   command[tem] = '\0';
   token = strtok(command, s);
   part[0] = token;
   tem = 0 ; 
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

    else if ( ! ( strcmp (part[0] , "su")))
	{
		chguse(part[1]);
	}
	//cheking whether su was typed

	else if ( ! ( strcmp ( part[0] , "exit")))
	{
		exit(1);
	}
	//:| :| :|

	else if ( ! ( strcmp ( part[0] , "calendar"))) 
	{
		finalcal();
	}
	//using for calling calendar function

	else if ( ! ( strcmp (part[0] , "clear")))
	{
		xclear();
	}
	//:| :| :|

	else if ( ! ( strcmp (part[0] , "passwd")))
		{
			if ( ! ( strcmp ( part[1] , "-l")))
			{
				if (part[2] == NULL || part[3] == NULL ){
				printf("Wrong Command\n");
				continue;
				}
				timeminus(part[3] , part[2]);
			}
			else
			{
				adminpasschg(part[1]);
			}
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
	int tim;
	scanf("%d",&tim);
	getchar();
	pf = fopen ("user.txt","r");
	if (!(strcmp(username,"admin"))) {
		printf("***\tUsername can't be admin.\t*** \n"); 
		fclose(pf); 
		return 0 ; }
	while ( !feof(pf))
	{
		fscanf(pf,"%20s%16s%d",fun ,fpw,&rm);
		if (!strcmp (username,fun ))
		{
			printf("Username is Invalid\n");
			fclose (pf);
			return 0 ;
		}
	}
	fclose(pf);
	pf = fopen ("user.txt","a");
	fprintf(pf,"%s %s %d\n",username,password,tim);
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