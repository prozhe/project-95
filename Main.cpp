// Libraries
#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <Tchar.h>
#include <stdarg.h>
#include <process.h>
#include <conio.h>
//Libraries


//cool color start
#define BLUE 9
#define GREEN 10
#define CYAN 11
#define RED 12
#define PURPLE 13
#define YELLOW 14
#define WHITE 15
//cool color end

#define BOARD_SIZE 6
#define TRUE 0
#define FALSE 1

//Variables
int i, j, ec, fg, ec2;
char fn[20], e, c;
FILE *file_temp, *file_user, *file_func;
int um =0 ;//user status    checking if user is admin or not 
int rt;//reaming time that user can use the program
char user[21];//for showing username in the programm all the time 
time_t st,t1;//starting time for a user for using in time limit 
int access = 0 ; // access point
FILE *history ; 
//Variables



//Functions
void help (void);
void xclear(void);//somthing like system ("Cls");
void xcprintf(int x,const char *format, ...);//colorful printf
void Delete();
void Display(char *ss);
void myeditor(char *ss);
void xxclear();
void Find();
void Save();
void Exit();
void xcopyfile(FILE *copyFrom, FILE *copyTo);
void myeditor(char *ss);//text editor
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
int timecheck();//checking if user time is finished or not 
int clear();//just Clear screen screen
int crttm();//changing user by a geust 
int histor(char *tempr);//history function
int h();//showing history
void makedir(char name[]);
void makefile(char filename[],char txt[]);
void printfile(char filename[]);
int removedir(const char *path);
void removefile(char filename[]);
void cd(char address[]);
void copyfile(char from[],char to[]);
char current[250]="\\home";
char root[250]="C:\\Users\\ozhanT\\Desktop";
void cp(char from[], char to[]);
int ls(void);
void pwd(void);
void writefile(char filename[],char txt[] );
void copyfile1(char from[],char to[]);
void movefile(char from[], char to[]);
char board[BOARD_SIZE][BOARD_SIZE];
char game_board[BOARD_SIZE][BOARD_SIZE];
int lost = 0;
void display_welcome();
void build_board();
void build_gboard();
void create_mines();
void print_board();
void print_fullboard();
void start();
int play_game();
void play_again();
int check_win_game();
void check_for_mine(int, int);
int check_for_nearby_mines(int, int);
//Functions



int main ()
{
	chdir("home");

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
   char rr[250],rrr[250];
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
   part[1] = NULL;
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
		else if (! (strcmp(part[0] , "game")))
	{
		histor(tempr);
		game();
	}
		else if (!(strcmp(part[0] , "help")))
	{
		histor(tempr);
		help();
	}


	else if (!(strcmp(part[0] , "time")))
	{
		histor(tempr);
		tim();
	}
	else if ( !strcmp(part[0] , "cd"))
	{
		strcpy (rr , part[1]);
		histor(tempr);
		cd(rr);
	}
	else if ( !strcmp ( part[0] , "pwd"))
	{
		histor(tempr);
		pwd();
	}
	else if ( !strcmp( part[0],"makedir"))
	{
		strcpy(rr,part[1]);
		histor(tempr);
		makedir(rr);
	}
		else if ( !strcmp( part[0],"cat"))
	{
		strcpy(rr,part[1]);
		histor(tempr);
		printfile(rr);
	}
		else if ( !strcmp(part[0] , "rm"))
		{
			if(! strcmp(part[1] , "-r"))
			{
				strcpy(rr,part[2]);
				histor(tempr);
				removedir(rr);
			}
			else
			{
				strcpy(rr,part[1]);
				histor(tempr);
				removefile(rr);
			}
		}
		else if (!strcmp(part[0] , "cp"))
		{
			strcpy(rrr,part[2]);
				strcpy(rr,part[1]);
				histor(tempr);
				cp(rr,rrr);
		}
		else if (!strcmp(part[0] , "mv"))
		{
			strcpy(rrr,part[2]);
			strcpy(rr,part[1]);
			histor(tempr);
			movefile(rr,rrr);

		}
		else if ( ! strcmp (part[0] , "ls"))
		{
			histor(tempr);
			ls();
		}
		else if ( !strcmp(part[0] , "myeditor"))
		{
			myeditor(part[1]);
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
   char rr[250],rrr[250],tempr[41];
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
	else if (! (strcmp(part[0] , "game")))
	{
		histor(tempr);
		game();
	}

	else if (!(strcmp(part[0] , "help")))
	{
		histor(tempr);
		help();
	}

			else if ( !strcmp(part[0] , "myeditor"))
		{
			myeditor(part[1]);
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
		else if ( !strcmp(part[0] , "cd"))
	{
		strcpy (rr , part[1]);
		histor(tempr);
		cd(rr);
	}
	else if ( !strcmp ( part[0] , "pwd"))
	{
		histor(tempr);
		pwd();
	}
	else if ( !strcmp( part[0],"makedir"))
	{
		strcpy(rr,part[1]);
		histor(tempr);
		makedir(rr);
	}
		else if ( !strcmp( part[0],"cat"))
	{
		strcpy(rr,part[1]);
		histor(tempr);
		printfile(rr);
	}
		else if ( !strcmp(part[0] , "rm"))
		{
			if(! strcmp(part[1] , "-r"))
			{
				strcpy(rr,part[2]);
				histor(tempr);
				removedir(rr);
			}
			else
			{
				strcpy(rr,part[1]);
				histor(tempr);
				removefile(rr);
			}
		}
		else if (!strcmp(part[0] , "cp"))
		{
			strcpy(rrr,part[2]);
				strcpy(rr,part[1]);
				histor(tempr);
				cp(rr,rrr);
		}
		else if (!strcmp(part[0] , "mv"))
		{
			strcpy(rrr,part[2]);
			strcpy(rr,part[1]);
			histor(tempr);
			movefile(rr,rrr);

		}
		else if ( ! strcmp (part[0] , "ls"))
		{
			histor(tempr);
			ls();
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
void cd(char address[])
{

    int i;
    int n;
    if(address[0]=='\\')
    {
        char temp[250];
        strcpy(temp,root);
        strcat(temp,address);
        i = chdir(temp);
        if(i==0)
        {
            strcpy(current,temp);
        }
    }
    else{
       i = chdir(address);
       if(i==0)
       {
           strcat(current,"\\");
           strcat(current,address);
       }
    }
    if (i!=0)
            printf("Wrong address inserted if you are entering absolute address start with \\\\home \nfor example: \\\\home\\\\directory1\n");

}

void makedir(char name[])
{
    mkdir(name);
    printf("directory %s successfully created\n");
}

void makefile(char filename[],char txt[])
{
    FILE *ptr;
    ptr = fopen(filename , "a");
    fprintf(ptr,"%s",txt);
    fclose(ptr);



}

int removedir(const char *path)
{
   DIR *d = opendir(path);
   size_t path_len = strlen(path);
   int r = -1;

   if (d)
   {
      struct dirent *p;

      r = 0;

      while (!r && (p=readdir(d)))
      {
          int r2 = -1;
          char *buf;
          size_t len;

          /* Skip the names "." and ".." as we don't want to recurse on them. */
          if (!strcmp(p->d_name, ".") || !strcmp(p->d_name, ".."))
          {
             continue;
          }

          len = path_len + strlen(p->d_name) + 2;
          buf = malloc(len);

          if (buf)
          {
             struct stat statbuf;

             snprintf(buf, len, "%s/%s", path, p->d_name);

             if (!stat(buf, &statbuf))
             {
                if (S_ISDIR(statbuf.st_mode))
                {
                   r2 = removedir(buf);
                }
                else
                {
                   r2 = unlink(buf);
                }
             }

             free(buf);
          }

          r = r2;
      }

      closedir(d);
   }

   if (!r)
   {
      r = rmdir(path);
   }

   return r;
}

void printfile(char ss[])
{
  char str[999];
  FILE * file;
  file = fopen(ss, "r");
  if (file)
  {
    while (fgets(str, 100, file))
    {
      if (str[0] == EOF)
        break;
      printf("%s", str);
    }


    int counter;
    for (counter = 0; counter <= 10; counter++)
    {
      fgetc(stdout);
    }

    fclose(file);
    file = NULL;
  }
  else
  {
      printf("There is no such file to show\n");
  }
}

void removefile(char filename[])
{
    int i;
    remove(filename);
    if (i==0)
        printf("file %s successfully removed\n",filename);
    else
        printf("wrong filename inserted please try again\n");
}

void copyfile(char from[],char to[])
{
    FILE *copyFrom = fopen(from,"r");
    FILE *copyTo = fopen(to,"a");
    for (;;) {
        int caractereActuel = fgetc(copyFrom);
        if (caractereActuel != EOF) {
            fputc(caractereActuel,copyTo);
        }
        else {
            break;
        }
    }
    fclose(copyFrom);
    fclose(copyTo);
}

void cp(char from[], char to[])
{
    if(from[0]=='\\'&&from[1]=='\\')
    {
        char temp1[250]={};
        char temp2[250]={};
        strcpy(temp2,root);
        strcpy(temp1,root);
        strcat(temp1,from);
        int i = chdir(temp1);
        if(i==0)
        {
            FILE *copyFrom = fopen(from,"r");
            int j = chdir(temp2);
            if(j==0)
            {
            FILE *copyTo = fopen(to,"a");
            for (;;) {
                int caractereActuel = fgetc(copyFrom);
                if (caractereActuel != EOF) {
                    fputc(caractereActuel,copyTo);
                }
                else {
                    break;
                }
            }
            fclose(copyFrom);
            fclose(copyTo);
            }
            else
                printf("Wrong Address Inserted \n");
        }
        else
            printf("Wrong Address Inserted\n");
    }

    else
        copyfile(from,to);
}

void pwd(void)
{
    printf("%s\n",current);
}

int ls()
  {
    DIR           *d;
    struct dirent *dir;
    d = opendir(current);
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
      {
      //  for(int i=0;dir->d_name!='EOF';i++)
      //  dir->d_name=you;
         printf("%s\n", dir->d_name);
        }

    closedir(d);
      }

  }


void writefile1(char filename[],char txt[])
{
    char *ptr;
    ptr = strstr(filename,".txt");
    if (ptr==NULL)
    {
        printf("ssd\n");
        FILE *fptr;
        fptr = fopen(filename,"w");
        fprintf(fptr,"%s",txt);
        fclose(fptr);
        fptr = NULL;
    }
    else
    {
        copyfile1(filename,txt);
    }
}

void copyfile1(char from[],char to[])
{
    FILE *copyFrom = fopen(from,"a");
    FILE *copyTo = fopen(to,"w");
    for (;;) {
        int caractereActuel = fgetc(copyFrom);
        if (caractereActuel != EOF) {
            fputc(caractereActuel,copyTo);
        }
        else {
            break;
        }
    }
    fclose(copyFrom);
    fclose(copyTo);
}

void movefile(char from[],char to[])
{
    FILE *copyFrom = fopen(from,"r");
    if(copyFrom==NULL)
        printf("No such file\n");
    FILE *copyTo = fopen(to,"w");
    for (;;) {
        int caractereActuel = fgetc(copyFrom);
        if (caractereActuel != EOF) {
            fputc(caractereActuel,copyTo);
        }
        else {
            break;
        }
    }
    remove(from);
    fclose(copyFrom);
    fclose(copyTo);
}

void writefile2(char filename[],char txt[])
{
    copyfile2(filename, txt);
}

void copyfile2(char from[],char to[])
{
    FILE *copyFrom = fopen(from,"a");
    FILE *copyTo = fopen(to,"a");
    for (;;) {
        int caractereActuel = fgetc(copyFrom);
        if (caractereActuel != EOF) {
            fputc(caractereActuel,copyTo);
        }
        else {
            break;
        }
    }
    fclose(copyFrom);
    fclose(copyTo);
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
			return  ;
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



void help(void);
{
    printf("cd filename(absolute or relative): opens filename\n");
    printf("cal; prints the current month\n");
    printf("exit: closes the program\n");
    printf("history: shows the history of given commands\n");
    printf("pwd:shows current position\n");
    printf("mkdir dirname: creates a directory named dirname\n");
    printf("text>filename: puts text into filename and if text is a file name puts the texts in that file into filename\n");
    printf("cat filename: shows filename's content\n");
    printf("rm filename: removes filename if it is found in the current directory\n");
    printf("rm dirname-r: removes dirname and all the files in it\n");
    printf("cp file1 file2(or address): copies file1 in file2\n");
    printf("mv file1 file2(or address): moves file1 to file2\n");
    printf("ls; shows current directory's files\n");
    printf("create user: can only be ran by admin and its used to create a new user\n");
    printf("passwd: it's used to change password\n");
    printf("exif: shows the creator of a file and the time it was created and last changes\n");
}



void game()
{
    display_welcome();
    printf("\nAny time you're ready... Just press ENTER. :)");

    getchar();
    system("cls");

    start();


}

void build_board()
{

    int i, j;

    for(i = 0; i < BOARD_SIZE; i++)
        for(j = 0; j < BOARD_SIZE; j++)
            board[i][j] = 'o';


    create_mines();
}


void build_gboard()
{

    int i, j;
    int row, col, cur = 4;
    printf("Creating game board....\nReady..set..\nPLAY!\n\n");

    for(i = 0; i < BOARD_SIZE; i++)
        for(j = 0; j < BOARD_SIZE; j++)
            game_board[i][j] = 'o';

    for(col = 0; col < BOARD_SIZE; col++)
        printf("%d ", col + 1);

    printf("\n\n");

    for(row = 0; row < BOARD_SIZE; row++)
    {
        for(col = 0; col < BOARD_SIZE; col++)
        {
            printf("%c ", game_board[row][col]);
        }
        printf(" %d ", row + 1);
        printf("\n");
    }
}

void create_mines()
{
    int i, random;


    srand(time(0));

    for (i = 0; i < BOARD_SIZE; i++)
    {
        random = rand() % (BOARD_SIZE);
        board[random][i] = '*';
    }

}


void print_board()
{
    int row, col;

    system("cls");
    for(col = 0; col < BOARD_SIZE; col++)
        printf("%d ", col + 1);

    printf("\n\n");
        for(row = 0; row < BOARD_SIZE; row++)
    {
        for(col = 0; col < BOARD_SIZE; col++)
        {
            printf("%c ", game_board[row][col]);
        }
        printf(" %d ", row + 1);
        printf("\n");
    }
}

void print_fullboard()
{
    int row, col;

    system("cls");
    for(col = 0; col < BOARD_SIZE; col++)
        printf("%d ", col + 1);

    printf("\n\n");
        for(row = 0; row < BOARD_SIZE; row++)
    {
        for(col = 0; col < BOARD_SIZE; col++)
        {
            printf("%c ", board[row][col]);
        }
        printf(" %d ", row + 1);
        printf("\n");
    }
}

int play_game()
{
    int r_selection = 0, c_selection = 0,
        nearbymines = 0, nearbymines2 = 0,
        nearbymines3 = 0, nearbymines4 = 0,
        nearbymines5 = 0, nearbymines6 = 0,
        nearbymines7 = 0, nearbymines8 = 0,
        i = 0;


    do {
    printf("\nMake a selection (ie. row [ENTER] col): \n");
    printf("Row--> ");
    scanf("%d", &r_selection);
    printf("Col--> ");
    scanf("%d", &c_selection);

    } while(r_selection < 1 || r_selection > BOARD_SIZE || c_selection < 1 || r_selection > BOARD_SIZE);


    check_for_mine(r_selection - 1, c_selection - 1);

    if(lost == 1)
        return -1;


    nearbymines = check_for_nearby_mines(r_selection - 1, c_selection - 1);
    game_board[r_selection - 1][c_selection - 1] = (char)( ((int)'0') + nearbymines );


    if(nearbymines == 0)
    {
        if(c_selection != BOARD_SIZE)
        {
            i = 0;
            while(nearbymines == 0 && (c_selection - 1 + i) < BOARD_SIZE)
            {
                nearbymines = check_for_nearby_mines(r_selection - 1, (c_selection - 1 + i));
                if(nearbymines != -1)
                {
                game_board[r_selection - 1][(c_selection - 1) + i] = (char) ( ((int)'0') + nearbymines );
                i++;
                }
            }
                if(r_selection != 1)
                {
                    i = 0;
                    while(nearbymines5 == 0 && (c_selection - 1 + i) < BOARD_SIZE && (r_selection - 1 - i) > 0)
                    {
                        nearbymines5 = check_for_nearby_mines((r_selection - 1 - i), (c_selection - 1 + i));
                        if(nearbymines5 != -1)
                        {
                        game_board[(r_selection - 1) - i][(c_selection - 1) + i] = (char) ( ((int)'0') + nearbymines5);
                        i++;
                        }
                    }
                }
                if(r_selection != BOARD_SIZE)
                {
                    i = 0;
                    while(nearbymines6 == 0 && (r_selection - 1 + i) < BOARD_SIZE && (c_selection - 1 + i) < BOARD_SIZE )
                    {
                        nearbymines6 = check_for_nearby_mines((r_selection - 1 + i), (c_selection - 1 + i));
                        if(nearbymines != -1)
                        {
                        game_board[(r_selection - 1) + i][(c_selection - 1) + i] = (char) ( ((int)'0') + nearbymines6);
                        i++;
                        }
                    }
                }
        }

        if(r_selection != BOARD_SIZE)
        {
            i = 0;
            while(nearbymines2 == 0 && (r_selection - 1 + i) < BOARD_SIZE)
            {

                nearbymines2 = check_for_nearby_mines((r_selection - 1 + i), c_selection - 1);
                if(nearbymines2 != -1)
                {
                game_board[(r_selection - 1) + i][c_selection - 1] = (char) ( ((int)'0') + nearbymines2 );
                i++;
                }
            }

            if(c_selection != BOARD_SIZE)
            {
                i = 0;
                while(nearbymines7 == 0 && (r_selection - 1 + i) < BOARD_SIZE && (c_selection - 1 - i) > 0)
                {

                    nearbymines7 = check_for_nearby_mines((r_selection - 1 + i), (c_selection - 1 - i));
                    if(nearbymines != -1)
                    {
                    game_board[(r_selection - 1) + i][(c_selection - 1) - i] = (char) ( ((int)'0') + nearbymines7);
                    i++;
                    }
                }
            }
        }

        if(r_selection != 1)
        {
            i = 0;
            while(nearbymines3 == 0 && (r_selection - i) > 0)
            {

                nearbymines3 = check_for_nearby_mines((r_selection - 1 - i), c_selection - 1);
                if(nearbymines3 != -1)
                {
                game_board[(r_selection - 1) - i][c_selection - 1] = (char) ( ((int)'0') + nearbymines3 );
                i++;
                }
            }
            if(c_selection != BOARD_SIZE)
            {
                while(nearbymines8 == 0 && (c_selection - 1 - i) > 0 && (r_selection - 1 - i) > 0)
                {

                    nearbymines8 = check_for_nearby_mines((r_selection - 1 - i), (c_selection - 1 - i));
                    if(nearbymines8 != -1)
                    {
                    game_board[(r_selection - 1) - i][(c_selection - 1) - i] = (char) ( ((int)'0') + nearbymines8);
                    i++;
                    }
                }
            }
        }

        if(c_selection != 1)
        {
            i = 0;
            while(nearbymines4 == 0 && (c_selection - i) > 0)
            {
                nearbymines4 = check_for_nearby_mines(r_selection - 1, (c_selection - 1 - i));
                if(nearbymines4 != -1)
                {
                game_board[r_selection - 1][(c_selection - 1) - i] = (char) ( ((int)'0') + nearbymines4 );
                i++;
                }
            }
        }
    }



    if(check_win_game() == TRUE)
    {
        system("cls");
        print_fullboard();
        printf("\n\nYou've won the game!! Congrats!!\n\n");
        play_again();
    }

    return 0;
}


void check_for_mine(int r_select, int c_select)
{
    if(board[r_select][c_select] == '*')
    {
        printf("\nYou've hit a mine! You lose!\n");
        getchar(); getchar();
        lost = 1;
    }
}

int check_for_nearby_mines(int r_select, int c_select)
{
    int nearby_mine_count = 0;

    if(board[r_select][c_select] == '*')
    {
        return -1;
    }

    if(r_select < (BOARD_SIZE - 1) && c_select < (BOARD_SIZE - 1))
    {

        if(board[r_select + 1][c_select] == '*')
            nearby_mine_count++;

        if(board[r_select][c_select + 1] == '*')
            nearby_mine_count++;

        if(board[r_select + 1][c_select + 1] == '*')
            nearby_mine_count++;


        if(c_select != 0)
        {

            if(board[r_select + 1][c_select - 1] == '*')
                nearby_mine_count++;

            if(board[r_select][c_select - 1] == '*')
                nearby_mine_count++;
        }

        if(r_select != 0)
        {
            if(board[r_select - 1][c_select] == '*')
                nearby_mine_count++;

            if(board[r_select - 1][c_select + 1] == '*')
                nearby_mine_count++;

            if(c_select != 0)
            {

                if(board[r_select - 1][c_select - 1] == '*')
                    nearby_mine_count++;
            }
        }
    }

    if(r_select == (BOARD_SIZE - 1) && c_select != (BOARD_SIZE - 1))
    {

            if(board[r_select - 1][c_select] == '*')
                nearby_mine_count++;

            if(board[r_select - 1][c_select + 1] == '*')
                nearby_mine_count++;
    }

    if(c_select == (BOARD_SIZE - 1) && r_select != (BOARD_SIZE - 1))
    {

            if(board[r_select][c_select - 1] == '*')
                nearby_mine_count++;

            if(board[r_select + 1][c_select - 1] == '*')
                nearby_mine_count++;
    }

    if(r_select == (BOARD_SIZE - 1) && c_select == (BOARD_SIZE - 1))
    {

            if(board[r_select][c_select - 1] == '*')
                nearby_mine_count++;

            if(board[r_select - 1][c_select - 1] == '*')
                nearby_mine_count++;

            if(board[r_select - 1][c_select] == '*')
                nearby_mine_count++;
    }

    return nearby_mine_count;
}


int check_win_game()
{
    int row, col;

    for(row = 0; row < BOARD_SIZE; row++)
        for(col = 0; col < BOARD_SIZE; col++)
        {
            if(game_board[row][col] == 'o' && board[row][col] != '*')
                return FALSE;
        }

    return TRUE;
}

void play_again()
{
    char ans;

    printf("\n\nWould you like to play again? (y/n) --> ");
    scanf(" %c", &ans);

    if(toupper(ans) == 'Y')
    {
        system("cls");
        start();
    }

    else
    {
        printf("\n\nThanks for playing! Bye.");
        (void) getchar();
        exit(EXIT_SUCCESS);
    }
}

void display_welcome()
{
    puts("-----------------------Welcome to Minesweeper!---------------------------");
    puts("\n");
    puts("\n");
}

void start()
{
    lost = 0;
    build_board();
    build_gboard();

    do
    {
    play_game();
    print_board();
    } while(lost != 1);

    print_fullboard();
    play_again();
}

