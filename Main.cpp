#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>
//#include <dirent.h>
//#include <unistd.h>
#include <sys/stat.h>
#include <Tchar.h>
#include <ctype.h>
void xclear(void);//somthing like system ("Cls");
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
void makedir(char name[]);
void makefile(char filename[],char txt[]);
void printfile(char filename[]);
int removedir(const char *path);
void removefile(char filename[]);
void cd(char address[]);
void copyfile(char from[],char to[]);
char current[250]="\\home";
char root[250]="C:\\Users\\ozhanT\\Desktop\\directory";
void cp(char from[], char to[]);
int ls(void);
void pwd(void);
void writefile1(char filename[],char txt[]);
void writefile2(char filename[],char txt[]);
void copyfile1(char from[],char to[]);
void movefile(char from[], char to[]);
#define BOARD_SIZE 6
#define TRUE 0
#define FALSE 1


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
    }
    else
       i = chdir(address);
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


