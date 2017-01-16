#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>
#include <stdarg.h>
#include<conio.h>
#include<process.h>
//#include <dirent.h>
//#include <unistd.h>
#include <sys/stat.h>
#include <Tchar.h>

//cool color start
#define BLUE 9
#define GREEN 10
#define CYAN 11
#define RED 12
#define PURPLE 13
#define YELLOW 14
#define WHITE 15
//cool color end

int i, j, ec, fg, ec2;
char fn[20], e, c;
FILE *file_temp, *file_user, *file_func;

void xclear(void);//somthing like system ("Cls");
void xcprintf(int x,const char *format, ...);//colorful printf
int um =0 ;//user status    checking if user is admin or not 
char user[21];//for showing username in the programm all the time 
int rt;//reaming time that user can use the program
int checking_users(char username[21],char password[17]);//cheking whether the username and password is correct or not
time_t st;//starting time for a user for using in time limit 
int adfun();//function that runs when admin is using the programm
int crtur();//function for creating user by admin
int chguse(char *p);//function for changing user by 
int gesfun();//functionn that runs when user is geust
int isLeapYear( int year );        /* True if leap year */
int leapYears( int year );         /* The number of leap year */
int todayOf( int y, int m, int d); /* The number of days since the beginning of the year */
long days( int y, int m, int d);   /* Total number of days */
void calendar(int y, int m);       /* display calendar at m y */
int finalcal();// function for initializing calendar
void Create();
void Delete();
void Display(char *ss);
void myeditor(char *ss);
void xxclear();
void Find();
void Save();
void Exit();
void xcopyfile(FILE *copyFrom, FILE *copyTo);

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
   char *part[4];
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
    else if ( ! ( strcmp (part[0] , "su")))
	{
		chguse(part[1]);
	}
	else if ( ! ( strcmp ( part[0] , "exit")))
	{
		exit(1);
	}
	else if ( ! ( strcmp ( part[0] , "calendar"))) 
	{
		finalcal();
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

void xcprintf(int x,const char *format, ...)
{
	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, x);//change color

	va_list arg;
	va_start(arg, format);
	vfprintf(stdout, format, arg);
	va_end(arg);

	SetConsoleTextAttribute(hConsole, 7);//reset color
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
	printf("***\t%s is Using the Programm\t***\n",user);

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
void myeditor(char *ss)
{
	if (ss != NULL)
		Display(ss);
	char ch;
	do {
		xxclear();
		xcprintf(GREEN, "\n\t**** xxx *****  TEXT EDITOR  ***** xxx ****");
		xcprintf(CYAN, "\n\n\tMENU:\n\t-----\n ");
		xcprintf(CYAN, "\n\t1.CREATE\n\t2.DISPLAY and EDIT\n\t3.DELETE\n\t4.EXIT\n");
		xcprintf(CYAN, "\n\tEnter your choice: ");
		ch = _getch();
		switch (ch)
		{
		case '1':
			Create();
			break;
		case '2':
			Display(NULL);
			break;
		case '3':
			Delete();
			break;
		case '4':
			exit(0);
		}
	} while (1);
}
void Create()
{
	xxclear();
	xcprintf(GREEN, "\n\t**** xxx *****  TEXT EDITOR  ***** xxx ****");
	xcprintf(CYAN, "\n\n\t1.CREATE:\n\t x\n\t x\n\t x");
	file_temp = fopen("temp.txt", "w");
	xcprintf(CYAN, "\n\tEnter the text and press 'Ctrl+S' to save\n\n\t");
	while (1)
	{
		c = _getch();

		if (c == 19)
		{
			fclose(file_temp);
			xcprintf(CYAN, "\n\tEnter then new filename: ");
			scanf("%s", fn);
			file_temp = fopen("temp.txt", "r");
			file_func = fopen(fn, "w");
			while (!feof(file_temp))
			{
				c = getc(file_temp);
				putc(c, file_func);
			}
			fclose(file_func);
			break;
		}
		else
			if(c == 13)
			{
				c = '\n';
				putchar(c);
				fputc(c, file_temp);
				printf("\t");
			}
			else
				if (c == 8)
				{
					printf("\b \b");
					fputc(c, file_temp);
				}
				else
				{
					putchar(c);
					fputc(c, file_temp);
				}
	}
}
void Delete()
{
	xxclear();
	xcprintf(GREEN, "\n\t**** xxx *****  TEXT EDITOR  ***** xxx ****");
	xcprintf(CYAN, "\n\n\t3.DELETE:\n\t x\n\t x\n\t x");
	xcprintf(CYAN, "\n\tEnter the file name: ");
	scanf("%s", fn);
	file_temp = fopen(fn, "r");
	if (file_temp == NULL)
	{
		xcprintf(RED, "\n\tFile not found!");
		xcprintf(CYAN, "\n\n\tPress any key to continue...");
		_getch();
		myeditor(NULL);
	}
	fclose(file_temp);
	if (remove(fn) == 0)
	{
		xcprintf(GREEN, "\n\n\tFile has been deleted successfully!");
		xcprintf(CYAN, "\n\n\tPress any key to continue...");
		_getch();
		myeditor(NULL);
	}
	else
		xcprintf(RED, "\n\tError!\n");
	xcprintf(CYAN, "\n\n\tPress any key to continue...");
	_getch();
}
void Display(char *ss)
{
	xxclear();
	xcprintf(GREEN, "\n\t**** xxx *****  TEXT EDITOR  ***** xxx ****");
	xcprintf(CYAN, "\n\n\t2.DISPLAY and EDIT:\n\t x\n\t x\n\t x\n\t");
	if (ss == NULL)
	{
		xcprintf(CYAN, "Enter the file name:\n\t ");
		scanf("%s", fn);
		file_temp = fopen(fn, "r");
	}
	else
	{
		file_temp = fopen(ss, "r");
		if (file_temp == NULL)
		{
			file_temp = fopen(ss, "w");
			fclose(file_temp);
			file_temp = fopen(ss, "r");
		}
	}
	if (file_temp == NULL)
	{
		xcprintf(RED, "\n\tFile not found!");
		_getch();
		myeditor(NULL);
	}
	while (!feof(file_temp))
	{
		c = getc(file_temp);
		printf("%c", c);
		if (c == '\n')
			printf("\t");
	}
	fclose(file_temp);
	xcprintf(CYAN, "\n\tType the text and press 'Ctrl+S' to append and 'Ctrl+x' to exit.\n\t");
	file_temp = fopen(fn, "a");
	while (1)
	{
		c = _getch();
		if (c == 19)
		{
			fclose(file_temp);
			_getch();
			myeditor(NULL);
		}
		if (c == 13)
		{
			c = '\n';
			putchar(c);
			fputc(c, file_temp);
			printf("\t");
		}
		else
			if (c == 8)
			{
				printf("\b \b");
				fputc(c, file_temp);
			}
			else
				if (c == 24)
				{
					Exit();
				}
				else
				{
					putchar(c);
					fputc(c, file_temp);
				}
	}
	fclose(file_temp);
	_getch();
}

void xxclear()
{
	DWORD n;
	DWORD size;
	COORD coord = { 0 };
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(h, &csbi);
	size = csbi.dwSize.X * csbi.dwSize.Y;
	FillConsoleOutputCharacter(h, TEXT(' '), size, coord, &n);
	GetConsoleScreenBufferInfo(h, &csbi);
	FillConsoleOutputAttribute(h, csbi.wAttributes, size, coord, &n);
	SetConsoleCursorPosition(h, coord);
}
void Find()
{

}
void Save()
{

}
void Exit()
{
	myeditor(NULL);
}
void xcopyfile(FILE *copyFrom,FILE *copyTo)
{
	for (;;) {
		int caractereActuel = fgetc(copyFrom);
		if (caractereActuel != EOF) {
			fputc(caractereActuel, copyTo);
		}
		else {
			break;
		}
	}
	fclose(copyFrom);
	fclose(copyTo);
}