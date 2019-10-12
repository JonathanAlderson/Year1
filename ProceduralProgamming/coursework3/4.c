#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

// gloabl variables  /////////////////////////
#define universeHeight 30   // This is used in a define statement to avoid use of magic numbers and avoid the runtime error of not using the define statement
#define universeWidth 60
int i,j;
char frameBuffer[universeHeight][universeWidth]; // creating the frame buffer array
/////////////////////////////////////////////////

// global varaibles for the tier 2
int numberOfPlanets;
int starLifeTime; // Measured in billions of years (average being 10)
int planetSafeZone; // The distance away from a star a planet can be before it dies

// global varaibles for the tier 3
int planetSurvivalRate[universeHeight][universeWidth] = {0}; // this shows the total length of time each planet space survives for over the whole simulatiosn.

// shooting stars travel at 130 km/s, for simplicity we will say 100 km/s
// light travels at 300 km/s

// therefore the stars will travel 1 light year in 3 years.

// It will be difficult to estimate a frame size, since there will be billions of years between the stars dying, but only a hundred or so, for the shooting star to beam across the galaxy.

// I might solve this my doing part of the simulation and then saying things like  800,000 years later.
// Then showing the next shooting star.


// Structures /////////////////////////
typedef struct
{
	int starNumber;
	struct {double x; double y;}Point;
	char starSize;
  char name[100];
	int direction; // This is used to indicate which direction they will travel in once they have turned into shooting stars, starting with an invalid direction so that they do not move
	int age; // a random number in billions of years between, somewhere between 0 and 20 billion years. (Yes I know that this isn't very sciency)
}Star;

typedef struct
{
	int planetNumber;
	struct{double x;double y;}Point;
	char planetSize;
}Planet;

typedef struct
{
	int id1;
	int id2;
  double distance;
}Pair;

Star MakeStar(int identifier, double x, double y)
{
	Star temp; // creates a new star and assigns the correct variables to it
	temp.starNumber = identifier;
	temp.Point.x = x; // uses the random number function named above to create a new place for the star to be
	temp.Point.y = y; // But is called externally so as not to produce duplicate stars
	temp.starSize = '.'; // sets the default to be a '.', which will be change dwhen it's made into a pair
	temp.age = rand() % 20; // creates a random age between 0 and 20;
	temp.direction = -1;
	return temp;

}

Pair MakePair(int id1,int id2,double distance)
{
	Pair temp; // creates a new pair to assign the parameters of the function to it
	temp.id1 = id1;
	temp.id2 = id2;
	temp.distance = distance;
	return temp; // Returns this temporary struct so that it can be used in the starPairs array countaining all of the paris of stars in the universe.
}

Planet MakePlanet(int identifier, double x, double y)
{
	Planet temp;
	temp.planetNumber = identifier; // creates a planet with the parameters passed to it.
	temp.Point.x = x;
	temp.Point.y = y;
	temp.planetSize	= '@'; // '@' is used for an alive planet and 'X' for a dead planet.
	return temp;
}

Star starArray[universeWidth*universeHeight]; // Makes an arrray of stars which is the length of the maximum possible stars that could be contained in the universe, this is good as if the universe changed size, there wouldn't be any more varaibles to change so that the game would work.
Pair starPairs[universeWidth*universeHeight]; // Makes an array to contain all the pairs of stars, the aray length is the maximum number of pairs that can be
Planet planetArray[universeWidth*universeHeight];
int numberOfStars = 0;
int numberOfPairs = 0;


///////////////////////////////////////////


// Sleep function
void sleepMS(int ms) // A small function that is used to add short delays so that the simulator can be seen in action.
{
    long delay;
    clock_t time1,time2;

    delay = ms*(CLOCKS_PER_SEC/1000);
    time1 = clock();
    time2 = clock();
    while( (time1-time2) <= delay )
        time1 = clock();
}


void displayWelcomeMessage()
{
  printf("\e[1;1H\e[2J"); // This makes sure that the terminal is clear.
  printf("\n  ____  _         ____                       _____ _                 _       _             ");
  printf("\n |  _ \\(_)       |  _ \\                     / ____(_)               | |     | |            ");
  printf("\n | |_) |_  __ _  | |_) | __ _ _ __   __ _  | (___  _ _ __ ___  _   _| | __ _| |_ ___  _ __");
  printf("\n |  _ <| |/ _` | |  _ < / _` | '_ \\ / _` |  \\___ \\| | '_ ` _ \\| | | | |/ _` | __/ _ \\| '__|");
  printf("\n | |_) | | (_| | | |_) | (_| | | | | (_| |  ____) | | | | | | | |_| | | (_| | || (_) | |  ");
  printf("\n |____/|_|\\__, | |____/ \\__,_|_| |_|\\__, | |_____/|_|_| |_| |_|\\__,_|_|\\__,_|\\__\\___/|_|  ");
  printf("\n           __/ |                     __/ |                                            ");
  printf("\n          |___/                     |___/                                         ");
	printf("\n                                                              T i e r  3\n\n\nNote: For tier two, to call bang with planets, please use 'bigBang' without arguments.\n");

}

void shootingStar()
{
	printf("\n\t\t★彡\n\nSee you again soon...\n\n\n"); // prints a shooting star and an exit message
}


double DistanceBetweenStar(Star a,Star b)
{
	return(sqrt(pow(a.Point.x - b.Point.x,2)+pow(a.Point.y - b.Point.y,2))); // pythagarus
}

Pair findClosestPairOfStars(Star starArray[],int lenghtOfArray)
{
	Pair a;
	a.distance = -1; // initially is set to an invalid amount, therefore, if it returns -1, we know that there are no more pairs left.
	bool valid;
	int i,j,k;
	double closestDistance = 999999999999; // set to a large number, so that a smaller one can be found.

	for(i=0;i<lenghtOfArray;i++)
	{
		for(j=0;j<lenghtOfArray;j++)
		{
			if(j!=i)
			{
				valid = true;
				for(k = 0 ; k<numberOfPairs;k++) // check that star has not already been used in a pair
				{
					if(starPairs[k].id1 == i || starPairs[k].id1 == j || starPairs[k].id2 == i || starPairs[k].id2 == j ) // None of the current stars can be in any of the current pairs
						valid = false; // this pair is invalid
				}
				if (DistanceBetweenStar(starArray[i],starArray[j]) < closestDistance)
				{
					if(valid)
					{
						closestDistance = (DistanceBetweenStar(starArray[i],starArray[j]));
						a.id1 = i;
						a.id2 = j;
						a.distance = closestDistance;
					}

				}
			}

		}
  }
	return(a);

}


void clear()// clear (erase) the whole frame buffer by filling it with white space (ASCII 32)
{
  for(i=0;i<universeHeight;i++)
  {
    for(j=0;j<universeWidth;j++)
    {
      frameBuffer[i][j] = ' '; // sets all to blank space
    }
  }
}

void plot(int x, int y, char c)
{
  frameBuffer[y][x] = c; // draws to the frame buffer
}

void writeAt(int x,int y, char str[])
{
  int stringLength = strlen(str);
  int i;
  for(i = 0; i < (stringLength-1); i++) // must be -1 since the strings accidently end witha "\n" which was causing some trouble.
	{
    frameBuffer[y][x+i] = str[i]; // writes onto the frame buffer sequentially
	}

}

void refresh()
{
  displayWelcomeMessage();
	int i;
  for(i=0;i<universeHeight;i++)
  {
    printf("\n");
    for(j=0;j<universeWidth;j++)
    {
      if(frameBuffer[i][j] == '\0') // For some reason in C the char of ' ', turns into a '\0' and will not print anything on the screen, so this check is needed.
          printf(" ");
      else
        printf("%c",frameBuffer[i][j]);
    }
  }
	printf("\n");
}


void draw()
{
	int i;
	for(i = 0;i<numberOfStars;i++)
	{
		if(starArray[i].Point.x > -1 && starArray[i].Point.x < universeWidth && starArray[i].Point.y > -1 && starArray[i].Point.y < universeHeight) // The star must be inside the univese to draw it.
			plot(starArray[i].Point.x, starArray[i].Point.y,starArray[i].starSize);
	}

	for(i = 0;i<numberOfPlanets;i++)
		plot(planetArray[i].Point.x, planetArray[i].Point.y,planetArray[i].planetSize);
	refresh(); // I'm not sure what else needs to be done on this function.
}

void load()
{
	FILE *write_ptr;
	write_ptr = fopen("universe.bin","rb");
	int i;
	fread(&numberOfStars,sizeof(int),1,write_ptr); // reads the first int
	fread(&numberOfPairs,sizeof(int),1,write_ptr); // reads the second int
	printf("\t\tNumber of stars to load: %i\n\t\tNumber of pairs to load: %i\n",numberOfStars,numberOfPairs); // this just informs the user about the file they are currently loading
	for(i=0;i<numberOfStars;i++)
		fread(&starArray[i],sizeof(Star),1,write_ptr); // reads the correct amount of stars and planets
	for(i=0;i<numberOfPairs;i++)
		fread(&starPairs[i],sizeof(Pair),1,write_ptr);
  printf("\nCongratulations, your saved universe was restored!"); // congratulations message to the user
}

void save()
{
	FILE *write_ptr;
	write_ptr = fopen("universe.bin","wb"); // opens the file containing the entire universe
	int i;
	fwrite(&numberOfStars,sizeof(int),1,write_ptr); // writes the first int
	fwrite(&numberOfPairs,sizeof(int),1,write_ptr); // writes the second int
	for(i=0;i<numberOfStars;i++)
		fwrite(&starArray[i],sizeof(Star),1,write_ptr);
	for(i=0;i<numberOfPairs;i++)
		fwrite(&starPairs[i],sizeof(Pair),1,write_ptr);
	fclose(write_ptr);
  printf("\nThanks, you have saved the universe!");
}

void show()
{
	printf("\nEnter your full name:");
	int i;
	char targetName[100];
	bool found = false;
	getchar();
	fgets(targetName,100,stdin); // get's a maximum of 100 characters from the input buffer
	for(i=0;i<numberOfPairs;i++)
	{
		if(strcmp(starArray[starPairs[i].id1].name,targetName) == 0 || strcmp(starArray[starPairs[i].id2].name,targetName) == 0)
		{
			draw();
			found = true; // used in a boolean check later on
			if(starArray[starPairs[i].id1].Point.x > (universeWidth / 2)) // the star is on the left hand side of the screen
				writeAt(starArray[starPairs[i].id1].Point.x - strlen(starArray[starPairs[i].id1].name) +1,starArray[starPairs[i].id1].Point.y,starArray[starPairs[i].id1].name); // so write the name on the right hand side of the screen
			else
				writeAt(starArray[starPairs[i].id1].Point.x + 2,starArray[starPairs[i].id1].Point.y,starArray[starPairs[i].id1].name); // else, write it on the left hand side of the screen

			if(starArray[starPairs[i].id2].Point.x > (universeWidth / 2))  // Same with this, just for the second name :)
				writeAt(starArray[starPairs[i].id2].Point.x - strlen(starArray[starPairs[i].id2].name) +1,starArray[starPairs[i].id2].Point.y,starArray[starPairs[i].id2].name);
			else
				writeAt(starArray[starPairs[i].id2].Point.x + 2,starArray[starPairs[i].id2].Point.y,starArray[starPairs[i].id2].name);
			refresh(); // First time draw() call may allow star names to be overwritten by other stars, this refresh makes sure that this is not the case.
		}
	}
	if(found)
	{

		clear(); // Removes the names, so that they will not be visible for the next time.
		printf("\nYour star pair has been found!");
	}
	else
		printf("\nI'm sorry, your star pair was not found, try looking in another universe...");
}

void pairs()
{
  int i;
	for(i=0;i<numberOfPairs;i++)
		printf("\nPair %i:\ndistance: %lf\nstar %i\nname: %s\ncoords: (%.3lf,%.3lf)\nstar %i\nname: %s\ncoords: (%.3lf,%.3lf)\n**************************",i,starPairs[i].distance,starPairs[i].id1,starArray[starPairs[i].id1].name,starArray[starPairs[i].id1].Point.x,starArray[starPairs[i].id1].Point.y,starPairs[i].id2,starArray[starPairs[i].id2].name,starArray[starPairs[i].id2].Point.x,starArray[starPairs[i].id2].Point.y);
	if(numberOfPairs == 0)
		printf("\nSorry, there are no pairs to show.");
	getchar(); // if you enter 5 letters the print statement is skipped over

}

void name()
{
	Pair closestPair = findClosestPairOfStars(starArray,numberOfStars);
	if(closestPair.distance == -1)
	{
		printf("\nSorry, no pairs were found!\nWish you a better luck in the next universe.");
		getchar(); // this makes sure that the message is shown on screen, since otherwise it is not swallowed by the next scan f
	}
	else
	{
  printf("\n\nThe closest pair of stars are no. %i and %i\nThey are %lf light years apart.\nWould you like to name this pair (y/n)?",closestPair.id1,closestPair.id2,closestPair.distance);
	char firstName[100],secondName[100],answer;
	getchar();
	answer = getchar();
	if(answer == 'y')
	{
		printf("\nEnter your full name: ");
		getchar();
		fgets(firstName,100,stdin);

		printf("\nEnter your spouses full name: ");
		fgets(secondName,100,stdin);
		printf("\nCongratulations, a pair of stars has been named after you and your spouse");
		strcpy(starArray[closestPair.id1].name,firstName); // sets the value of the star arrays to the names
		strcpy(starArray[closestPair.id2].name,secondName);
	}

	starArray[closestPair.id1].starSize = '*'; // sets the stars to be the larger ones representing a couple
	starArray[closestPair.id2].starSize = '*';

	starPairs[numberOfPairs] = closestPair;
	numberOfPairs++;
	}
}

void list()
{
  int i;
	for(i=0;i<numberOfStars;i++)
	{
		printf("star %i\ncoords: (%.2lf,%.2lf)\n",i+1,starArray[i].Point.x,starArray[i].Point.y); // rounding is used for nice formatting
	}
}



void bang(int n)
{
	clear();
	numberOfStars = n; // this variable is important for use in the drawing function so it knows how far to iterate through the array of stars.
	numberOfPairs = 0;
	numberOfPlanets = 0;
  int i = 0,j=0;
	double randomX,randomY;
	bool usedCoordinate;

  while(i < n)
  {
		usedCoordinate = false;
    randomX = rand() % universeWidth; // Makes a random set of numbers inside the universe boundries
    randomY = rand() % universeHeight;
    for(j=0;j<i;j++) // iterates j through how ever many i's there are so far
    {
			if(starArray[j].Point.x == randomX && starArray[j].Point.y == randomY) // this checks to see ifthe star has already been used.
			{
				usedCoordinate = true;
			}
		}
		if(! usedCoordinate)
		{
			starArray[i] = MakeStar(i+1,randomX,randomY); // Just so stars are not zero indexed, since nobody starts counting at 0 these days, only cool computer scientists. But not other folk.
	    i++; // a star has been successfully created
		}


  }
	draw();
}

void howToPlay()
{
	// Just a really long print statement about how to play the game;
	printf("\n\nYou are now starting the big bang game!\n\nYour only objective is to try and survive\nStarting by entering a number of stars you would like (the more stars the harder)\nThe number of planets (the more the easier)\nYou will then be given the choice of which Planet to select\nthe one which you think has the highest chance of survival.\nFinally you pick a how many billion years you think the star will survie for.\n\nOnce everything has been chosen\nall the stars on the screen will begin to die out\nbecoming shooting stars\nif any of the stars come too close to the planet\nit will explode and you will lose.\n\nGood luck.\n\n\n\tPress enter to continue...");
	getchar();getchar();getchar();getchar();getchar(); // this swallows the last three characters from bigbang. Since our read function only looks at the first 4 items.
	displayWelcomeMessage(); // clears the previous text from the screen
}


void bigBang()
{
	clear();
	howToPlay();
	printf("\nNumber of stars:");
	scanf("%i",&numberOfStars);
	printf("\nNumber of planets:");
	scanf("%i",&numberOfPlanets);
	numberOfPairs = 0;

  int i = 0,j=0;
	double randomX,randomY;
	bool usedCoordinate;

  while(i < (numberOfStars+numberOfPlanets))
  {
		usedCoordinate = false;
    randomX = rand() % universeWidth; // Makes a random set of numbers inside the universe boundries
    randomY = rand() % universeHeight;
    for(j=0;j<i;j++) // iterates j through how ever many i's there are so far
    {
			if((starArray[j].Point.x == randomX && starArray[j].Point.y == randomY)  || ( planetArray[j].Point.x == randomX && planetArray[j].Point.y == randomY)) // this checks to see ifthe star has already been used.
			{
				usedCoordinate = true;
			}
		}
		if(! usedCoordinate)
		{
			if(i < numberOfStars)
				starArray[i] = MakeStar(i+1,randomX,randomY); // Just so stars are not zero indexed, since nobody starts counting at 0 these days, only cool computer scientists. But not other folk.
			else
				planetArray[i-numberOfStars] = MakePlanet(i-numberOfStars+1,randomX,randomY); // Just so planets are also 0 indexed
	    i++; // a star has been successfully created
		}


  }
	draw();
}

void simulate()
{
	int i,j,k,billionsOfYears;
	int chosenPlanet;
	getchar();
	printf("\n\nYou will now select which star you think will survive for the longest.\nThe planets will now be displayed with their planet ID's.\nYour chosen planet will be identified with '#'\n\tPress enter to continue...");
	getchar();
	draw();
	for(i=0;i<numberOfPlanets;i++)
	{
		frameBuffer[(int)planetArray[i].Point.y][(int)planetArray[i].Point.x + 1] = '=';
		char planetIDString[4];
		sprintf(planetIDString,"%d",i+1);
		for(j=0;j<strlen(planetIDString);j++)
			frameBuffer[(int)planetArray[i].Point.y][(int)planetArray[i].Point.x + 2 + j] = planetIDString[j];
	}
	refresh(); // this second refresh is so that the planet id numbers are not overwritten by rouge stars.
	clear();
	printf("\n\nPlease enter the planet ID you would like to nominate:");
	scanf("%i",&chosenPlanet);
	planetArray[chosenPlanet-1].planetSize = '#'; // the '#' means this is the planet you want to survive.
	draw();
	getchar();
	printf("\n\nHow many billion years do you think your planet will survive for:");
	scanf("%i",&billionsOfYears);
	printf("\n\tPress enter to continue...");
	getchar();

	// The simulation now goes through a loop and decreases one from every star age
	for(j=0;j<billionsOfYears;j++)
	{
			printf("\nj = %i",j);
			for(i=0;i<numberOfStars;i++)
			{
				if(starArray[i].age == 0)
				{
					starArray[i].direction = rand() % 8; // Gives each star a random direction to travel to on death
				}
				starArray[i].age --; // every star gets a little older

				// straight lines
				if(starArray[i].direction == 0) // straight up;
					starArray[i].Point.y --;
				if(starArray[i].direction == 2) // right
					starArray[i].Point.x ++;
				if(starArray[i].direction == 4) // down
					starArray[i].Point.y ++;
				if(starArray[i].direction == 6) // left
					starArray[i].Point.x --;

				// diagonals
				if(starArray[i].direction == 1) // north east
				{starArray[i].Point.y--;starArray[i].Point.x++;}
				if(starArray[i].direction == 3)//south east
				{starArray[i].Point.y++;starArray[i].Point.x++;}
				if(starArray[i].direction == 5)//south west
				{starArray[i].Point.y++;starArray[i].Point.x--;}
				if(starArray[i].direction == 7) // north west
				{starArray[i].Point.y--;starArray[i].Point.x--;}
			}
			draw();
			clear();
			sleepMS(100); // sleeps for half a second.

			for(i=0;i<numberOfPlanets;i++) // checks if any of the plaents are hit into by a star
			{
				// Loops through all the stars and compares the x,y locations of any of the planets, to check if they are too close.
				for(k=0;k<numberOfStars;k++)
				{
					// Checks if the star is in the surrounding 9 squares of the planet
					if((planetArray[i].Point.x > starArray[k].Point.x -2) && (planetArray[i].Point.x < starArray[k].Point.x +2) && (planetArray[i].Point.y > starArray[k].Point.y -2) &&  (planetArray[i].Point.y < starArray[k].Point.y +2))
					{
						planetArray[i].planetSize = 'x';
					}
				}
			}
	}

	if(planetArray[chosenPlanet-1].planetSize == '#')
		printf("\n\nCongratulations, you've won!\nYour planet was safe from the shooting stars!");
	else
		printf("\n\nUnfortunately, your planet was destroyed by a shooting star!\nWhy not try again.");

}


void autoBigBang(int numberOfStars) // a version of the big bang function that takes paramets and runs without any printf statements.
{
	// this version of the function will now just create as many stars as there are inputted.
	clear();
  int i = 0,j=0;
	double randomX,randomY;
	bool usedCoordinate;

  while(i < (numberOfStars))
  {
		usedCoordinate = false;
    randomX = rand() % universeWidth; // Makes a random set of numbers inside the universe boundries
    randomY = rand() % universeHeight;
    for(j=0;j<i;j++) // iterates j through how ever many i's there are so far
    {
			if((starArray[j].Point.x == randomX && starArray[j].Point.y == randomY)) // this checks to see ifthe star has already been used.
			{
				usedCoordinate = true;
			}
		}
		if(! usedCoordinate)
		{
			if(i < numberOfStars)
				starArray[i] = MakeStar(i+1,randomX,randomY); // Just so stars are not zero indexed, since nobody starts counting at 0 these days, only cool computer scientists. But not other folk.
	    i++; // a star has been successfully created
		}
  }
}

void autoSim(int numberOfStars) // autoSim is a version of simulate which takes parameters and runs instantly instead of querying the player for information.
{
	// the planetSurvivalRate array tells us how long every planet has lived for
	int i,j,k,l;
	bool planetsStillAlive[universeHeight][universeWidth]; // this array tells us if the planet has been hit by a star yet.
	for(i=0;i<universeHeight;i++)
	{
		for(j=0;j<universeWidth;j++)
		{
			planetsStillAlive[i][j] = true; // sets every value in the array to be true; they can later be set to false once hit by a star.
		}
	}

	//clear();
	// The simulation now goes through a loop and decreases one from every star age
	for(j=0;j<(80);j++) // the reason 80 has been chosen is because it is the maximum length of  time that will matter. since the oldest a star can be is 20, and the longest it can travel is 60, assuming worst case scenario
	{

			for(k=0;k<universeHeight;k++) // This two for loops will increase the age of any stars that are still living
			{
				for(l=0;l<universeWidth;l++)
				{
					if(planetsStillAlive[k][l] == true) // if the planets are still alive, increase it's survival rate.
						planetSurvivalRate[k][l]++;

				}
			}

			for(i=0;i<numberOfStars;i++)
			{
				if((int)starArray[i].Point.y > -1 && (int)starArray[i].Point.y < universeHeight && (int)starArray[i].Point.x > -1 && (int)starArray[i].Point.x < universeWidth) // this does a small check to make sure that the star is still in range.
					planetsStillAlive[(int)starArray[i].Point.y][(int)starArray[i].Point.x] = false; // The star's current position would be above a hypothetical planet, if it were in that spot.


				if(starArray[i].age == 0)
				{
					starArray[i].direction = rand() % 8; // Gives each star a random direction to travel to on death
				}
				starArray[i].age --; // every star gets a little older

				// straight lines
				//if(starArray[i].direction == 0) // straight up;
				//	{starArray[i].Point.y --;}
				if(starArray[i].direction == 0) // straight up;
					starArray[i].Point.y --;
				if(starArray[i].direction == 2) // right
					{starArray[i].Point.x ++;}

				if(starArray[i].direction == 4) // down
					starArray[i].Point.y ++;
				if(starArray[i].direction == 6) // left
					starArray[i].Point.x --;

				// diagonals
				if(starArray[i].direction == 1) // north east
				{starArray[i].Point.y--;starArray[i].Point.x++;}
				if(starArray[i].direction == 3)//south east
				{starArray[i].Point.y++;starArray[i].Point.x++;}
				if(starArray[i].direction == 5)//south west
				{starArray[i].Point.y++;starArray[i].Point.x--;}
				if(starArray[i].direction == 7) // north west
				{starArray[i].Point.y--;starArray[i].Point.x--;}

			}



	}




}

void prove()
{
	printf("\n\nThe prove function will now begin to run.");
	getchar();getchar(); // swallows the extra spaces that need to be swallowed by the program.

	int numberOfStars = 0;

	printf("\n\nHow many stars do you want to run the simulation with:");
	scanf("%i",&numberOfStars);

	int i,j,numberOfSimulations = 1000;
	for(i=0;i<numberOfSimulations;i++)
	{
		//time_t t;
		//srand((unsigned) time(&t));
		printf("\nSimulation %i",i);
		autoBigBang(numberOfStars);
		autoSim(numberOfStars);
	}
	displayWelcomeMessage();
	printf("\n\nSimulations Complete:\n\n\nHere is the heat map from %i simulations with %i stars.\n\n",numberOfSimulations,numberOfStars);

	for(i=0;i<universeHeight;i++)
	{
		printf("\n");
		for(j=0;j<universeWidth;j++)
		{
			printf("%.2f,",(float)((float)planetSurvivalRate[i][j] / numberOfSimulations));
		}
	}
	getchar(); // swallows the previous newline.
}




void commandLineInterface()
{
	char c;
	displayWelcomeMessage(); // Displays a lovely welcome message
  printf("\n\n>>>");
  char command[5] = {' ',' ',' ',' ','\0'};
  int argument = -1;
  int i = 0;
  for(i = 0;i<4;i++)
    command[i] = getchar();
  if(command[3] == 'g')
  {
    scanf("%i",&argument);
    printf(""); // This allows for the 'press enter to continue message' to work for the bang command.
                // The printf clears whatever was there before (their integer parameter for the function) and so clears anything that would stop getchar() working.
  }
  if(strcmp(command,"load") == 0)
    {load();getchar();} // Some functions need an extra netline swalloing but others do not.
  if(strcmp(command,"save") == 0)
    {save();getchar();}
  if(strcmp(command,"show") == 0)
		show();
  if(strcmp(command,"pair") == 0)
    {pairs();getchar();} // Since pairs is 5 letters instead of the others only being 4; an extra getchar() is needed to swallow the extra character.
  if(strcmp(command,"name") == 0)
    name();
  if(strcmp(command,"list") == 0)
		{list();getchar();} // Needs an extra newline taken care of.
	if(strcmp(command,"draw") == 0)
		{draw();getchar();}
	if(strcmp(command,"quit") == 0)
		{shootingStar();exit(1);}
  if(strcmp(command,"bang") == 0) // extra getchars() are needed depending on the length of the number used, one extra for the spaves then one for each power of ten in the number;
    {bang(argument);getchar();} // Need to sort out a problem where whenever bang is called, it skips the getchar() command, not sure how to fix atm;
	if(strcmp(command,"bigB") == 0)
		{bigBang();simulate();}
	if(strcmp(command,"prov") == 0)
		{prove();}
	printf("\n\n\n\n\tPress enter to continue..."); // Displays a message to tell the user to press enter
	while ((c = getchar()) != '\n' && c != EOF) {} // Clears all of the characters from the input buffer
}

int main()
{
	displayWelcomeMessage();
	printf("\n\nThis version of the program is used to prove that stars towards the edge of the system have a higher survival rate.\nPlease use 'prove' to run the simulation of the simulations.\n\n\tPress enter to continue...");
	getchar();
  // Seeds the random number generator
  time_t t;
  srand((unsigned) time(&t));
  while(1<2)
    commandLineInterface();
}
