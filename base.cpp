/*
A simulated game of baseball between Home and Away teams.
Outputs the box score when complete.

Trevor Bonner-Dewitt
*/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <Windows.h>
#include <iomanip>

using namespace std;

bool home = false;
int runsHome = 0;
int runsAway = 0;
int hitsHome = 0;
int hitsAway = 0;
int abHome = 0;
int abAway = 0;
int w = 0;
int l = 0;
int gs = 0;
int sing = 0;
int doub = 0;
int trip = 0;
int hr = 0;
int totRuns = 0;
int dp = 0;
int walk = 0;

struct pa
{
	int balls;
	int strikes;
	int pitch;
	int pitchguess;
	pa()
	{
		balls = 0; strikes = 0; pitch = 0; pitchguess = 0;
	}
};

struct diamond
{
	bool first;
	bool second;
	bool third;
	diamond()
	{
		first = false; second = false; third = false;
	}
	void advance(int basenum)
	{
		int xtra = rand() % 100;
		int scorer = 0;

		if(basenum >= 1)
			if (home)
				hitsHome++;
			else
				hitsAway++;

		switch (basenum)
		{
		case -1:  //if dp, no outs
			if (third)
			{
				scorer++;
				third = false;
			}

			if (second)
			{
				second = false;
				third = true;
			}

			first = false;

			if (home)
				runsHome += scorer;
			else
				runsAway += scorer;

			if (scorer)
				cout << scorer << " runs score!\n";
			break;
		case 0:
			if (first == false)
				first = true;
			else if (second == false)
				second = true;
			else if (third == false)
				third = true;
			else
			{
				if (home)
					runsHome++;
				else
					runsAway++;
				cout << "They walk in a run!\n";
			}
			break;
		case 1:
			if (third == true)
			{
				scorer++;

				third = false;
			}

			if (second == true)
			{
				scorer++;

				second = false;
			}

			if (first == true)
			{
				if (xtra > 49)
					third = true;
				else
					second = true;
			}
			else
				first = true;
			if (home)
				runsHome += scorer;
			else
				runsAway += scorer;

			if(scorer)
				cout << scorer << " runs score!\n";
			break;
		case 2:
			if (first)
				scorer++;
			if (second)
				scorer++;
			if (third)
				scorer++;
			
			first = false;
			second = true;
			third = false;

			if (home)
				runsHome += scorer;
			else
				runsAway += scorer;

			if(scorer)
				cout << scorer << " runs score!\n";
			break;
		case 3:
			if (first)
				scorer++;
			if (second)
				scorer++;
			if (third)
				scorer++;

			first = false;
			second = false;
			third = true;

			if (home)
				runsHome += scorer;
			else
				runsAway += scorer;

			if(scorer)
				cout << scorer << " runs score!\n";
			break;
		case 4:
			scorer++;

			if (first)
				scorer++;
			if (second)
				scorer++;
			if (third)
				scorer++;

			if (first)
				if (second)
					if (third)
						gs++;

			first = false;
			second = false;
			third = false;

			if (home)
				runsHome += (scorer);
			else
				runsAway += (scorer);
			
			cout << scorer << " runs score!\n";
			break;
			}
	}
};


int
contact()
{

/*
returns an integer which signify different outcomes

0 - foul
1 - single
2 - double
3 - triple
4 - home run
5 - flyout
6 - groundout

*/
	
	int fair, type, base;
	fair = rand() % 100;
	type = rand() % 100; //Line Drive, Ground Ball, or Fly Ball
	base = rand() % 100; //type of base hit

	if (fair < 3)
	{
		cout << " it's in foul territory and CAUGHT!\n";
		return 5;
	}
	else if (fair < 33)
	{
		cout << " fouls it out of play.\n";
		return 0;
	}
	else if (fair >= 33)
	{
		cout << " that's a fair ball!\n";
		if (type < 20)
		{
			cout << "A line drive";
		}
		else if (type >= 20 && type <= 55)
		{
			cout << "A fly ball";
		}
		else if (type > 55)
		{
			cout << "A ground ball";
		}

		if (fair > 65)
		{
			if (type <= 55)
			{
				cout << " that is caught.\n";
				return 5;
			}
			else if (type > 55)
			{
				cout << " in the infield.\n";
				return 6;
			}
				
		}
		else if (fair <= 65)
		{
			if (base < 29 || type > 55)
			{
				cout << " base hit.\n";
				sing++;
				return 1;
			}
			else if (base >= 29 && base <= 67)
			{
				cout << " double";
				doub++;
				if (base >= 29 && base <= 49)
				{
					cout << " to the";
					if (base <= 39)
						cout << " left";
					else
						cout << " right";
					cout << " field gap!\n";
				}
				else
				{
					cout << " down the";
					if (base <= 59)
						cout << " left";
					else
						cout << " right";
					cout << " field line!\n";
				}
				return 2;
			}
			else if (base > 67 && base <= 71)
			{
				cout << " triple to the";
				trip++;
				if (base >= 70)
					cout << " left";
				else
					cout << " right";
				cout << " field gap!\n";
				return 3;
			}
			else if (base > 71)
			{
				cout << " DEEP and that is OUTTA HERE!\n";
				hr++;
				return 4;
			}
		}
	}
};

int
atbat(diamond &a)
{
	/* 
	returns result according to key:

	-1 - double play
	0 - strike out
	1 - contact out
	2 - walk
	3 - single
	4 - double
	5 - triple
	6 - HR

	*/

	pa *count;
	count = new pa;

	diamond basepath;
	basepath = a;

	int out, hit, hbp;
	hbp = rand() % 240;
	count->pitch = 0; count->balls = 0; out = 0;
	count->strikes = 0; count->pitchguess = 0; hit = 0;

	if (basepath.first == true || basepath.second == true || basepath.third == true)
	{
		if (basepath.first == true && basepath.second == true && basepath.third == true)
			cout << "Bases loaded!\n";
		else if (basepath.first == true && basepath.second == true && basepath.third == false)
			cout << "Runners on first and second.\n";
		else if (basepath.first == false && basepath.second == true && basepath.third == true)
			cout << "Runners on second and third.\n";
		else if (basepath.first == true && basepath.second == false && basepath.third == true)
			cout << "Runners on the corners.\n";
		else if (basepath.third)
			cout << "Runner on third.\n";
		else if (basepath.second)
			cout << "Runner on second.\n";
		else if (basepath.first)
			cout << "Runner on first.\n";
	}
	else if (basepath.first == false && basepath.second == false && basepath.third == false)
		cout << "Bases empty.\n";
	else
		cout << "Error\n";

	while (count->strikes < 3 && count->balls < 4)
	{
		cout << count->balls << " and " << count->strikes << "." << endl;
		count->pitch = rand() % 100;
		count->pitchguess = rand() % 100;
		count->pitchguess = abs(count->pitchguess - count->pitch);

		if (hbp == 239)
		{
			cout << "The batter was hit by the pitch! ";
			return 2;
		}
		else if (count->pitchguess > 59)
		{
			count->strikes++;
			cout << "Swing and a miss, ";
			if (count->strikes == 3)
				return 0;
		}
		else if (count->pitch > 57)
		{
			count->balls++;
			cout << "Ball. ";
			if (count->balls == 4)
			{
				cout << "Ball four. ";
				return 2;
			}	
		}
		else if (count->pitch <= 57 && count->pitchguess < 20)
		{
			cout << "He swings, and";
			hit = contact();
			if (hit == 5 || (hit == 6 && basepath.first == false))
				return 1; //out
			else if (hit == 6 && basepath.first == true)
				return -1; //dp
			else if (hit == 1)
				return 3; //single
			else if (hit == 2)
				return 4; //double
			else if (hit == 3)
				return 5; //triple
			else if (hit == 4)
				return 6; //homer
			else if (!hit)
				if (count->strikes < 2)
					count->strikes++;
		}
		else if (count->pitch <= 57 && count->pitchguess >= 20)
		{
			count->strikes++;
			cout << "Strike! ";
			if (count->strikes == 3)
				return 0;
		}
		else
			cout << "\nError\n\n" << "pitch: " << count->pitch << "\n guess: " << count->pitchguess << endl;
	}
}

int
inning(int inn)
{
	int out, batter, oldRuns, newRuns;
	out = 0; batter = 0;

	diamond *basepath;
	basepath = new diamond;

	oldRuns = runsHome + runsAway;
	
	while ((out < 3 && inn < 18) ||
		   (out < 3 && (inn >= 18 && inn % 2 == 0 && runsAway >= runsHome)) ||
		   (out < 3 && (inn >=18 && (inn % 2 == 1))))
	{
		batter = atbat(*basepath);

		if (home)
			abHome++;
		else
			abAway++;

		switch (batter) {
		case -1:
			if (out < 2)
			{
				out += 2;
				cout << "And the defense turns two! Double play!\n";
				if (out == 2)
					basepath->advance(-1);
				dp++;
			}
			else
				out++;
			cout << out << " Out.\n";
			break;
		case 0:
			cout << "Strike three! He's out!\n";
			out++;
			cout << out << " Out.\n";
			break;
		case 1:
			cout << "Routine play.\n";
			out++;
			cout << out << " Out.\n";
			break;
		case 2:
			cout << "Take your base.\n";
			basepath->advance(0);
			cout << out << " Out.\n";
			walk++;
			if (home)
				abHome--;
			else
				abAway--;
			break;
		case 3:
			basepath->advance(1);
			cout << out << " Out.\n";
			break;
		case 4:
			basepath->advance(2);
			cout << out << " Out.\n";
			break;
		case 5:
			basepath->advance(3);
			cout << out << " Out.\n";
			break;
		case 6:
			basepath->advance(4);
			cout << out << " Out.\n";
			break;
		}
	}
	newRuns = (runsHome + runsAway) - oldRuns;

	return newRuns;
}

int
main()
{
	srand(time(0));
	int games = 0;
	int inn = 1; //equivalent to one half-inning of batting
	int maxinn = 0;
	int score = 0;
	int board[20] = {};

	float battingH, battingA, onbaseH, onbaseA;

		while (inn < 18 || (inn >= 18 && runsHome == runsAway) || (inn >= 18 && runsAway >= runsHome && inn % 2 == 0))
		{
			//system("cls");

			if (inn % 2 == 0)
			{
				cout << "\n\nBOT " << (inn / 2) << endl;
				home = true;
			}
			else
			{
				cout << "\n\nTOP " << (inn / 2) + 1 << endl;
				home = false;
			}

			score = inning(inn);

			if (inn <= 18)
				board[inn - 1] = score;
			else if (inn > 18 && inn % 2 == 1)
				board[18] += score;
			else if (inn > 18 && inn % 2 == 0)
				board[19] += score;
			else
				cout << "\nSCOREBOARD ERROR\n";

			inn++;
			if (inn > maxinn)
				maxinn = inn;
		}

		if (runsHome > runsAway)
			w++;
		else if (runsAway > runsHome)
			l++;
		
		cout << "\nScore:\n\n";

		for (int j = 1; j < (maxinn/2)+1; j++)
		{
			//inning number
			if(j < 11)
				cout << setw(4) << j;
		}

		cout << setw(4) << "R" << setw(4) << "H" << setw(5) << "E" << endl;


		for (int k = 1; k < maxinn; k++)
		{
			//away team score
			if (k % 2 == 1 && k < 21)
				cout <<  setw(4) << board[k-1];
		}

		cout << setw(4) << runsAway << setw(4) << hitsAway << setw(5) << "0" << endl;

		for (int m = 1; m < maxinn+1; m++)
		{
			//home team score
			if (maxinn == 18 && m < 22)
				board[17] = 0;
			if (m % 2 == 0 && m < 22)
				cout << setw(4) << board[m-1];
		}

		cout << setw(4) << runsHome << setw(4) << hitsHome << setw(5) << "0" << endl;

	games++;
	totRuns += runsHome + runsAway;
	
	battingA = float(hitsAway) / float(abAway);
	onbaseA = (float(hitsAway) + float(walk)) / float(abAway);
	battingH = float(hitsHome) / float(abHome);
	onbaseH = (float(hitsHome) + float(walk)) / float(abHome);

	
	cout << setprecision(3) << fixed << "\nAway Batting Avg: " << battingA << endl;
	cout << setprecision(3) << fixed << "Away On Base Avg: " << onbaseA << endl;
	cout << setprecision(3) << fixed << "\n\nHome Batting Avg: " << battingH << endl;
	cout << setprecision(3) << fixed << "Home On Base Avg: " << onbaseH << endl;
	cout << "\nTotal Runs: " << totRuns << endl;
	cout << "Max inning: " << maxinn/2 << endl;
	cout << "Double plays: " << dp << endl;
	cout << "Walks: " << walk << endl;
	cout << "Singles: " << sing << endl;
	cout << "Doubles: " << doub << endl;
	cout << "Triples: " << trip << endl;
	cout << "Home Runs: " << hr << endl;
	cout << "Grand Slams: " << gs << endl;

	system("pause");
}