#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include <assert.h>

#define MAXCOLS  256
#define MAXROWS  256


/* Data type: Labyrinth - ASCII map, costs, direction */

typedef struct labyrinth
{
   char lab[MAXCOLS+2][MAXROWS];
   long costs[MAXCOLS][MAXROWS];
   long bestx[MAXCOLS][MAXROWS];
   long besty[MAXCOLS][MAXROWS];
   int maxrow;
   int startx;
   int starty;
   int treasurex;
   int treasurey;
   bool fehler;
}LabCell, *Lab_p;

LabCell labeinlesen(char dateiname [MAXCOLS+1], LabCell lab_pointer);
void labauslesen(LabCell lab);
int loeslaby(LabCell lab, int x, int y);
void labyrinthloesen(LabCell lab);


int main ()
{
	LabCell labyrinth;
	char dateiname [MAXCOLS];
	/*printf("Welche Datei soll eingelesen werden?\n");
	fgets(dateiname, MAXCOLS, stdin);
	fflush(stdin);
	printf("%s", dateiname);*/
	strcpy(dateiname, "C:\\Users\\FREWERTB\\Documents\\lab.txt");
	
	labyrinth = labeinlesen(dateiname, labyrinth);
	printf("%c", labyrinth.lab[0][0]);
	labauslesen(labyrinth);
	labauslesen(labyrinth);
	labyrinthloesen(labyrinth);
}


LabCell labeinlesen(char dateiname [MAXCOLS+1], LabCell lab)
{
	FILE *datei = fopen(dateiname,"r");
	char buffer[MAXCOLS+1];
	int i = 0;
	int j = 0;
	bool startda;
	bool zielda;
	while(!feof(datei))
	{
		fgets( buffer, MAXCOLS+1, datei);
		j = 0;
		while (j < MAXCOLS && buffer[j] != '\n')
		{
			lab.lab[i][j] = buffer[j];
			if(lab.lab[i][j] == 'S')
			{
				if(startda == false)
				{
					lab.startx = i;
					lab.starty = j;
					startda == true;
				}
				else{
					lab.fehler = true;
				}
			}
			else{
				if(lab.lab[i][j] == 'X')
				{
					if(zielda == false)
					{
						lab.treasurex = i;
						lab.treasurey = j;
						zielda == true;
					}
					else{
						lab.fehler = true;
					}
				}
			}
			j++;
		}
		i++;
	}
	return lab;
}


void labauslesen(LabCell lab)
{
	int i = 0;
	int j = 0;
	while(i < MAXCOLS && lab.lab[i][0] != 0)
	{
		j = 0;
		while(j < MAXCOLS && lab.lab[i][j] != 0)
		{
			printf("%c", lab.lab[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}


void labyrinthloesen(LabCell lab)
{
	int x = lab.startx;
	int y = lab.starty;
	/*
	if(loeslaby(lab, x, y) == 1)
	{
		printf("Das Labyrinth konnte gelöst werden!\n");
	}
	else{
		printf("Das Labyrinth konnte NICHT gelöst werden!\n");
	}*/
}

int loeslaby(LabCell lab, int x, int y)
{
	labauslesen(lab);
	if(lab.lab[x][y] == 'X')
	{
		return 1;
	}
	if(lab.lab[x][y] == '#' || lab.lab[x][y] == '.')
	{
		return -1;
	}
	else{
		lab.lab[x][y] = '.';
		if(loeslaby(lab,x+1, y) == 1)
		{
			return 1;
		}
		else{
			if(loeslaby(lab, x, y+1) == 1)
			{
				return 1;
			}
			else{
				if(loeslaby(lab, x-1, y) == 1)
				{
					return 1;
				}
				else{
					if(loeslaby(lab, x, y-1))
					{
						return 1;
					}
					else{
						return -2;
					}
				}
			}
		}
	}
}
