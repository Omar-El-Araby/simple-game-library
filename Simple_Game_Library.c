#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <unistd.h>
#define data "Data.txt"

typedef struct game 
{
	char name[30];
	char genre[20];
	char nplayers[12];
	float price;
} game;

void readFile(const char src[], game lib[], int *n);
void writeFile(const char src[], game lib[], int n);
void displaybeg();
void display(game lib[], int start, int end);
void displayend();
void gread(game lib[], int start, int n);
void gminName(game lib[], int start, int n, int *minpos);
void gminGenre(game lib[], int start, int n, int *minpos);
void gminNplayers(game lib[], int start, int n, int *minpos);
void gsortName(game lib[], int n);
void gsortGenre(game lib[], int n);
void gsortNplayers(game lib[], int n);
void gsearchName(game lib[], int n, char target[]);
void gsearchGenre(game lib[], int n, char target[]);
void gsearchNplayers(game lib[], int n, char target[]);
void gminPrice(game lib[], int start, int n, int *minpos);
void gsortPrice(game lib[], int n);
void gsearchPrice(game lib[], int n, float target);
void storer(char str[]);
void spacer(char str[]);
void searcher(char str[]);
void sampler(game lib[], int *n);
float power(int a, int b);
float str_flt(char x[]);
int chr_int(char x);
int str_int(char x[]);
char *strlwr(char *str);

int main()
{
	game lib[1000] = {}; 
	char input[10], field[10], target[30];
	int qcounter = 0, qcounter2 = 0, index, n, appender;
	float ptarget = 0;
	printf("Hello and welcome to Game Library 5000, Omar El Araby's interactive\nassignment/project!\n"
	"This is a virtual game library, containing a list of games\nas well as their genres, prices, and whether they are singleplayer\nor multiplayer.\n"
	"Enter \"help\" to receive a list of valid commands!\nIf this is your first time running this program, please enter \"setup\".\n");
	while(true)
	{
		if(access(data, F_OK ) == 0) //Check that Data.txt exists.
			readFile(data, lib, &n); //If the file exists, use it to fill the array.
		printf("@>>");
		fgets(input, 40, stdin);
		input[strcspn(input, "\n")] = 0;
		searcher(input);
		if(strcmp(input, "help") == 0) //Print the help message.
		{
			printf("help    - receive a list of commands\nclr     - clears the console display\n"
			"sample  - reset the library to its original size (5) and fill it with sample game titles\n"
			"read    - input your own game titles\nsort    - sort the library\nsearch  - search the library for a specific term\n"
			"display - display the current library\ncredits - gives credit where it's due\n"
			"info    - gives my personal information\nappend  - adds one record\n"
			"append+ - adds more than one record\nquit/q  - exit the program\n");
			qcounter = 0;
		}
		else if(strcmp(input, "clr") == 0) system("cls"); //Clear the screen.
		else if(strcmp(input, "setup") == 0) //Make Data.txt.
		{
			sampler(lib, &n);
			printf("\"Data.txt\" has been created. Setup complete!\n");
			qcounter = 0;
		}
		else if(strcmp(input, "sample") == 0) //Input sample.
		{
			sampler(lib, &n);
			printf("Sample has been inputted.\n");
			qcounter = 0;
		}
		else if(strcmp(input, "read") == 0) //Let user manually change records.
		{
			while(true)
			{
				index = -1;
				printf("Please enter a number from 1 to %d to choose which record to alter.\n"
				"Enter -1 to input all %d values from the start, or 0 to go back to the main menu.\n", n, n);
				scanf("%d", &index);
				getchar();
				if(index == 0) break;
				else if(index > 0 && index < 1000) 
				{
					for(int i=0; i<n; ++i)
					{
						if(index == i+1)
						{
							gread(lib, i, i+1);
							printf("Entered successfully!\n");
						}		
					}
					writeFile(data, lib, n);
				}
				else if(index == -1) 
				{
					gread(lib, 0, n);
					writeFile(data, lib, n);
					break;
				}
				else 
				{
					printf("Incorrect input.\n");
					++qcounter2;
					if(qcounter2 == 3) 
					{
						printf("Too many incorrect inputs. Returning to main menu.\n");
						qcounter2 = 0;
						break;
					}
				}
			}
			qcounter = 0;
		}
		else if(strcmp(input, "sort") == 0) //Sort.
		{
			int x = 0;
			printf("Please enter which field you wish to sort by.\nThe available fields are \"Name\", \"Genre\", \"Single/Multi\"(or \"sm\" for short),\nand \"Price\".\n");
			fgets(field, 40, stdin);
			field[strcspn(field, "\n")] = 0;
			searcher(field);
			if(strcmp(field, "name") == 0) gsortName(lib, n);
			else if(strcmp(field, "genre") == 0) gsortGenre(lib, n);
			else if(strcmp(field, "single/multi") == 0 || strcmp(field, "sm") == 0) gsortNplayers(lib, n);
			else if(strcmp(field, "price") == 0) gsortPrice(lib, n);
			else 
			{
				printf("Invalid input. Returning to main menu.\n");
				++x;
			}
			if(x == 0) printf("Sorting complete!\n");
			writeFile(data, lib, n);
			qcounter = 0;
		}
		else if(strcmp(input, "search") == 0) //Let user find a specific record.
		{
			printf("Please enter which field you wish to search in.\nThe available fields are \"Name\", \"Genre\", \"Single/Multi\"(or \"sm\" for short),\nand \"Price\".\n");
			fgets(field, 40, stdin);
			field[strcspn(field, "\n")] = 0;
			int newflag = 0;
			searcher(field);
			if(strcmp(field, "name") == 0); else if(strcmp(field, "genre") == 0);
			else if(strcmp(field, "single/multi") == 0 || strcmp(field, "sm") == 0); else if(strcmp(field, "price") == 0);
			else newflag = 1;
			if(newflag == 0) 
			{
				printf("Please enter the term you'd like to search for:\n");
				if(strcmp(field, "Price") == 0 || strcmp(field, "price") == 0) 
				{
					scanf("%f", &ptarget);
					getchar();
				}
				else 
				{
					fgets(target, 40, stdin);
					target[strcspn(target, "\n")] = 0;
				}
			}
			if(strcmp(field, "name") == 0) gsearchName(lib, n, target);
			else if(strcmp(field, "genre") == 0) gsearchGenre(lib, n, target);
			else if(strcmp(field, "single/multi") == 0 || strcmp(field, "sm") == 0) gsearchNplayers(lib, n, target);
			else if(strcmp(field, "price") == 0) gsearchPrice(lib, n, ptarget);
			else printf("Invalid input. Returning to main menu.\n");
			qcounter = 0;
		}
		else if(strcmp(input, "append") == 0) //Add a new record.
		{
			++n;
			gread(lib, n-1, n);
			writeFile(data, lib, n);
			qcounter = 0;
		}
		else if(strcmp(input, "append+") == 0) //Add several new records.
		{
			printf("Enter the number of records you wish to add:\n");
			scanf("%d", &appender);
			getchar();
			n += appender;
			appender = n - appender;
			gread(lib, appender, n);
			writeFile(data, lib, n);
			qcounter = 0;
		}
		else if(strcmp(input, "credits") == 0) //Print credits message.
		{
			printf("\nBelow is a list of the people I'd like to thank, for this project would\nnot exist without them.\n"
			"Dr. Marwa El Shenawy - For being the person\nwho requested this in the first place\n"
			"Eng. Heba Ibrahim - For always giving me way too many things to do\n"
			"My Family - For generally being supportive and nice\n"
			"Abdelrahman Hussein - For taking the whole workload with the art project\n"
			"Abdelrahman Yosri - For generally just being a bro\n"
			"Ahmed Saeed - For being the person who\ninspired me to make an interactive assignment\n"
			"Ahmed Gawish - For being super creepy and making me look good by comparison\n"
			"Hamed Mohamed Najeeb - For being super nice and positive all the time\n"
			"Mahmoud Saeed - For saying \"Yes\" sometimes\n"
			"Mohamed Komsany - For occasionally not being an idiot\n"
			"Shady - For being the guy who Saeed hates\n"
			"Shehab Badawy - For always having a story to tell\n"
			"Walid Kamal - For consistently being able to make me panic over nothing\n\n");
			qcounter = 0;
		}
		else if(strcmp(input, "info") == 0) //Print info message.
		{
			printf("Name: Omar Mostafa Morsi Mostafa El Araby\nRegistration Number: 18100410\n"
			"Term: 3\nClass: E\nLikes:\n"
			"Chocolate. All food, actually, because I don't discriminate, but mainly chocolate.\n"
			"I also like video games, if that hasn't already been made apparent by this whole project in general.\n"
			"Finally, free will. I like doing what I want, how I want it. As long as it doesn't impose on others, that is.\nDislikes:\n"
			"I hate feeling constrained or limited, for one. I also quite hate judgemental people. People in general, actually.\n"
			"No I'm just joking. I hate some people, but not all of them. There are good people out there.\n"
			"I especially hate the fact that while I'm marketing this as a game library that can go as\n"
			"big as its user needs it to be, it does technically have a limit of 1000, and my code has no indicator to show that.\n"
			"Still, it should be fine. Honestly, if you actually go through the effort of inputting 995 records\n"
			"just to spite me, I'm only going to be impressed.\nHobbies:\n"
			"I honestly quite enjoy writing code. It's not my favourite thing in the world but it's fun enough,\n"
			"and I have to do a whole lot of it anyways.\nI also like gaming, because you clearly didn't already know that from the game themed project,\n"
			"and finally I like watching movies and TV shows. Only if they're good though.\n");
			qcounter = 0;
		}
		else if(strcmp(input, "display") == 0) //Display everything.
		{
			displaybeg();
			display(lib, 0, n);
			displayend();
			qcounter = 0;
		}
		else if(strcmp(input, "quit") == 0 || strcmp(input, "q") == 0) break; //Exit.
		else 
		{
			++qcounter;				//Quit counter incremends with every invalid input and resets with every valid input.
			if(qcounter == 3) break;	//Once it reaches 3 invalid inputs the program stops.
			printf("Invalid input. Enter \"help\" to receive a list of commands.\n");
		}
		if(qcounter == 2) printf("WARNING!! One more invalid input will cause the program to shut down!\n");	//Warning.
	}
	return 0;
}

void gread(game lib[],int start, int n)
{
	for(int i=start; i<n; ++i)
	{
		char tprice[10];
		printf("Record #%d. Please enter the game's name, genre, price,\nand whether it's singleplayer or multiplayer:\n", i+1);
		printf("Name: "); fgets(lib[i].name, 40, stdin); 
		lib[i].name[strcspn(lib[i].name, "\n")] = 0;
		printf("Genre: "); fgets(lib[i].genre, 40, stdin); 
		lib[i].genre[strcspn(lib[i].genre, "\n")] = 0;
		printf("Single/Multi: "); fgets(lib[i].nplayers, 40, stdin);
		lib[i].nplayers[strcspn(lib[i].nplayers, "\n")] = 0;
		printf("Price: "); fgets(tprice, 40, stdin);
		tprice[strcspn(tprice, "\n")] = 0;
		lib[i].price = str_flt(tprice);
	}
}

void gminName(game lib[], int start, int n, int *minpos)
{
	char m[30];
	strcpy(m, lib[start].name);
	int mp;
	for(int i=start; i<n; ++i)
	{
		if(strcmp(m, lib[i].name) >= 0)
		{
			strcpy(m, lib[i].name);
			mp = i;
		}
	}
	*minpos = mp;
}

void gsortName(game lib[], int n)
{
	int mp;
	game t;
	for(int i=0; i<n; ++i)
	{
		gminName(lib, i, n, &mp);
		t = lib[i];
		lib[i] = lib[mp];
		lib[mp] = t;
	}
}

void gsearchName(game lib[], int n, char target[])
{
	int flag = 0;
	searcher(target);
	for(int i=0; i<n; ++i)
	{
		searcher(lib[i].name);
		if(strcmp(lib[i].name, target) == 0)
		{
			readFile(data, lib, &n);
			++flag;
			if(flag == 1) displaybeg();
			display(lib, i, i+1);
		}
	}
	if(flag == 0) printf("That game title was not found. :(\n");
	else displayend();
}

void gminGenre(game lib[], int start, int n, int *minpos)
{
	char m[20];
	strcpy(m, lib[start].genre);
	int mp;
	for(int i=start; i<n; ++i)
	{
		if(strcmp(m, lib[i].genre) >= 0)
		{
			strcpy(m, lib[i].genre);
			mp = i;
		}
	}
	*minpos = mp;
}

void gsortGenre(game lib[], int n)
{
	int mp;
	game t;
	for(int i=0; i<n; ++i)
	{
		gminGenre(lib, i, n, &mp);
		t = lib[i];
		lib[i] = lib[mp];
		lib[mp] = t;
	}
}

void gsearchGenre(game lib[], int n, char target[])
{
	int flag = 0;
	searcher(target);
	for(int i=0; i<n; ++i)
	{
		searcher(lib[i].genre);
		if(strcmp(lib[i].genre, target) == 0)
		{
			readFile(data, lib, &n);
			++flag;
			if(flag == 1) displaybeg();
			display(lib, i, i+1);
		}
	}
	if(flag == 0) printf("That genre was not found. :(\n");
	else displayend();
}

void gminNplayers(game lib[], int start, int n, int *minpos)
{
	char m[12];
	strcpy(m, lib[start].nplayers);
	int mp;
	for(int i=start; i<n; ++i)
	{
		if(strcmp(m, lib[i].nplayers) >= 0)
		{
			strcpy(m, lib[i].nplayers);
			mp = i;
		}
	}
	*minpos = mp;
}

void gsortNplayers(game lib[], int n)
{
	int mp;
	game t;
	for(int i=0; i<n; ++i)
	{
		gminNplayers(lib, i, n, &mp);
		t = lib[i];
		lib[i] = lib[mp];
		lib[mp] = t;
	}
}

void gsearchNplayers(game lib[], int n, char target[])
{
	int flag = 0;
	searcher(target);
	for(int i=0; i<n; ++i)
	{
		searcher(lib[i].nplayers);
		if(strcmp(lib[i].nplayers, target) == 0)
		{
			readFile(data, lib, &n);
			++flag;
			if(flag == 1) displaybeg();
			display(lib, i, i+1);
		}
	}
	if(flag == 0) printf("Target not found. :(\n");
	else displayend();
}

void gminPrice(game lib[], int start, int n, int *minpos)
{
	float m = lib[start].price;
	int mp;
	for(int i=start; i<n; ++i)
	{
		if(m >= lib[i].price)
		{
			m = lib[i].price;
			mp = i;
		}
	}
	*minpos = mp;
}

void gsortPrice(game lib[], int n)
{
	game t;
	int mp;
	for(int i=0; i<n; ++i)
	{
		gminPrice(lib, i, n, &mp);	
		t = lib[i];
		lib[i] = lib[mp];
		lib[mp] = t;
	}
}

void gsearchPrice(game lib[], int n, float target)
{
	int flag = 0;
	for(int i=0; i<n; ++i)
	{
		if(lib[i].price == target)
		{
			++flag;
			if(flag == 1) displaybeg();
			display(lib, i, i+1);
		}
	}
	if(flag == 0) printf("No game titles at that price were found. :(\n");
	else displayend();
}

void displaybeg()
{
	printf("------------------------------------------------------------------------------\n"
		   "|In.|%-30s|%-20s|%-12s|%-7s|\n------------------------------------------------------------------------------\n", "Name", "Genre", "Single/Multi", "Price/$");
}

void display(game lib[], int start, int end)
{
	for(int i=start; i<end; ++i) 
	{
		printf("|%-3d|%-30s|%-20s|%-12s|", i+1, lib[i].name, lib[i].genre, lib[i].nplayers);
		if(lib[i].price == 0) printf("%-7s|\n", "Free");
		else printf("%-7.2f|\n", lib[i].price);
	}
}

void displayend()
{
	printf("------------------------------------------------------------------------------\n");
}

void readFile(const char src[], game lib[], int *n)
{
	FILE *f = fopen(src, "r");
	fscanf(f, "%d", n);
	for(int i=0; i<*n; ++i) 
	{
		fscanf(f, "%s%s%s%f", lib[i].name, lib[i].genre, lib[i].nplayers, &lib[i].price);
		spacer(lib[i].name); spacer(lib[i].genre); spacer(lib[i].nplayers);
	}
	fclose(f);
}

void writeFile(const char src[], game lib[], int n)
{
	FILE *f = fopen(src, "w");
	fprintf(f, "%d\n", n);
	for(int i=0; i<n; ++i) 
	{
		storer(lib[i].name); storer(lib[i].genre); storer(lib[i].nplayers);
		fprintf(f, "%s\n%s\n%s\n%f\n", lib[i].name, lib[i].genre, lib[i].nplayers, lib[i].price);
	}
	fclose(f);
}

void storer(char str[])
{
	for(int i=0; i<30; ++i) if(str[i]==' ') str[i] = '^';
}

void spacer(char str[])
{
	for(int i=0; i<30; ++i) if(str[i]=='^') str[i] = ' ';
}

void searcher(char str[])
{
	strlwr(str);
	for(int i=0; i<30; ++i)
	{
		if(str[i]==' ') 
		{
			for(int j=i; j<30; ++j) str[j] = str[j+1];
			--i;
		}
	}
}

void sampler(game lib[], int *n)
{
	*n = 5;
	strcpy(lib[0].name, "Counter-Strike"); strcpy(lib[0].genre, "FPS"); strcpy(lib[0].nplayers, "Multiplayer"); lib[0].price = 0;
	strcpy(lib[1].name, "Payday 2"); strcpy(lib[1].genre, "FPS"); strcpy(lib[1].nplayers, "Multiplayer"); lib[1].price = 9.99;
	strcpy(lib[2].name, "Outlast"); strcpy(lib[2].genre, "Horror"); strcpy(lib[2].nplayers, "Singleplayer"); lib[2].price = 19.99;
	strcpy(lib[3].name, "Dying Light"); strcpy(lib[3].genre, "Horror"); strcpy(lib[3].nplayers, "Multiplayer"); lib[3].price = 39.99;
	strcpy(lib[4].name, "Life Is Strange"); strcpy(lib[4].genre, "Graphic Adventure"); strcpy(lib[4].nplayers, "Singleplayer"); lib[4].price = 19.99;
	writeFile(data, lib, *n);
}

float str_flt(char x[])
{
	int point, flag = 0; float ans = 0;
	for(int i = 0; i < 10; ++i) if(x[i] == '.') 
	{
		point = i;
		flag = 1;
	}
	if(flag == 1)
	{
		for(int i = point - 1, j = 0; i >= 0; --i, ++j)
		{
			ans += power(10, j) * chr_int(x[i]);
		}
		for(int i = point+1, j = 1; i < 10; ++i, ++j)
		{
			ans += (1/(power(10,j))) * chr_int(x[i]);
		}
	}
	else return str_int(x);
	return ans;
}

int str_int(char x[])
{
	int ans = 0;
	for(int i = 0; i < strlen(x); ++i) ans += power(10, (strlen(x) - 1) - i) * chr_int(x[i]);
	return ans;
}

int chr_int(char x)
{
	switch(x)
	{
		case '1': return 1; 
		case '2': return 2; 
		case '3': return 3; 
		case '4': return 4; 
		case '5': return 5; 
		case '6': return 6; 
		case '7': return 7; 
		case '8': return 8; 
		case '9': return 9; 
		default: return 0;
	}
}

float power(int a, int b)
{
	float ans = 1;
	for(int i = 0; i < b; ++i)
	{
		ans *= a;
	}
	return ans;
}

char *strlwr(char *str)
{
  unsigned char *p = (unsigned char *)str;

  while (*p) {
     *p = tolower((unsigned char)*p);
      p++;
  }

  return str;
}
