//816000026 - Tevin Achong
//Please run console in full-screen

#include <iostream>
#include <fstream>
#include <cstring>
#include <ctime>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>


using namespace std; 
struct Player{
	char fname[50];
	char lname[50];
	bool bowl;
	int runs;
	int wickets;
	bool batted;
	bool bowled;
	bool out;
	char outMethod[20];
	int oversBowled;
};

bool isLetter (char ch){
	return ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'));
}

int numBowlers (Player arr[], int size){
	int numB = 0;
	for (int i = 0; i < size; i++){
		if (arr[i].bowl)
			numB++;
	}
	return numB;
}

Player getBowler (Player arr[], int size){
	Player currBowl;
	
	int numBowl = numBowlers(arr, size);
	
	int bowler = rand()%numBowl + 1;
	int check = 0;
	int i = 0;
	while (check != bowler && i < size){
		if (arr[i].bowl){
			check++;
		}
		
		if (check == bowler){
			currBowl = arr[i];
		}
		
		i++;
	}
	
	return currBowl;
}

void printName(Player p){
	int i = 0; 
	while (p.fname[i] != '\0'){
		cout<<p.fname[i];
		i++;
	}
	cout<<" ";
	
	int j = 0;
	while (p.lname[j] != '\0'){
		cout<<p.lname[j];
		j++;
	}
	
	j = 0;
	i = 0;
}

int findPlayerLocation (Player arr[], int size, char fname[], char lname[]){
	for (int i = 0; i < size; i++){
		if ((strcmp (fname, arr[i].fname) == 0) && (strcmp (lname, arr[i].lname)==0))
			return i;
	}
	cout<<"Player not found!"<<endl;
	return -1; 
}

void swapPlayers (Player * p1, Player * p2){
	Player temp;
	temp = *p1;
	*p1 = *p2;
	*p2 = temp;
}


int main(){
	srand (time(NULL));
	
	int overs;
	int ballDelay; 
	int overDelay;
	int innDelay; 
	
	char coinChoice;  
	
	cout<<"Enter the number of overs each team will have to bat: ";
	cin>>overs;
	
	cout<<"Enter the time delay (in seconds) between balls: ";
	cin>>ballDelay; 
	
	cout<<"Enter the time delay (in seconds) between overs: ";
	cin>>overDelay;
	
	cout<<"Enter the time delay (in seconds) between innings: ";
	cin>>innDelay; 
	
	
	cout<<endl;
	cout<<"Choose heads or tails ('h' for heads, 't' for tails): ";
	cin>>coinChoice; 
	
	while (coinChoice != 'h' && coinChoice != 'H' && coinChoice != 't' && coinChoice != 'T'){
		cout<<"Please enter either ''h', 'H', 't' or 'T': ";
		cin>>coinChoice;
	}
		
	int coinToss = rand()%2 + 1; 
	
	char teamPos;
	
	if (coinToss == 1){
		cout<<endl;
		cout<<"HEADS"<<endl;
		if (coinChoice == 'h' || coinChoice == 'H'){
			cout<<"Congratulations! You chose heads and won the coin toss!"<<endl<<endl;
			 
			cout<<"Would you like to bat or field?"<<endl;
			cout<<"Enter 'b' or 'B' to bat. Enter 'f' or 'F' to field: ";
			cin>>teamPos;
			
			while (teamPos != 'b' && teamPos != 'B' && teamPos != 'f' && teamPos != 'F'){
				cout<<"Please enter either 'b', 'B', 'f' or 'F': ";
				cin>>teamPos;
			} 
		}
		else {
			cout<<"Sorry! You lost the coin toss!"<<endl;
			int numPos = rand()%2 + 1;
			if (numPos == 1){
				teamPos = 'b';
				cout<<"Your opponent's team has chosen to field first!"<<endl;
			}
			else if (numPos == 2){
				teamPos = 'f';
				cout<<"Your opponent's team has chosen to bat first!"<<endl;
			}
		}
	}
	
	else if (coinToss == 2){
		cout<<endl;
		cout<<"TAILS"<<endl;
		if (coinChoice == 't' || coinChoice == 'T'){
			cout<<"Congratulations! You chose tails and won the coin toss!"<<endl<<endl;
			 
			cout<<"Would you like to bat or field?"<<endl;
			cout<<"Enter 'b' or 'B' to bat. Enter 'f' or 'F' to field: ";
			cin>>teamPos;
			
			while (teamPos != 'b' && teamPos != 'B' && teamPos != 'f' && teamPos != 'F'){
				cout<<"Please enter either 'b', 'B', 'f' or 'F': ";
				cin>>teamPos;
			} 
		}
		else {
			cout<<"Sorry! You lost the coin toss!"<<endl;
			int numPos = rand()%2 + 1;
			sleep(3);
			if (numPos == 1){
				teamPos = 'b';
				cout<<"Your opponent's team has chosen to field first!"<<endl;
			}
			else if (numPos == 2){
				teamPos = 'f';
				cout<<"Your opponent's team has chosen to bat first!"<<endl;
			}
		}
	}
	
	ifstream fin; 
	fin.open("teams.txt");
	
	if (!fin.is_open()){
		cout<<"Could not open file!"<<endl; 
	}
	
	else{ 
		char largeArr[1000];
		Player p; 
		Player teamOne[11];
		Player teamTwo[11];
		int playerCount = 1, teamOneCount=0, teamTwoCount=0; 
		while (!fin.eof()){
			fin.getline(largeArr, 1000);
			int i = 0, j = 0;
			while (isLetter(largeArr[i]) || largeArr[i] == '-'){
				p.fname[i] = largeArr[i];
				i++;
			}
			p.fname[i] = '\0';
			
			while (!isLetter(largeArr[i])){
				i++; 
			} 
			
			while (isLetter(largeArr[i]) || largeArr[i] == '-'){
				p.lname[j] = largeArr[i];
				i++; 
				j++;
			}
			p.lname[j] = '\0';
			
			while (!isLetter(largeArr[i])){
				i++; 
			}
			
			if (largeArr[i] == 'N' && largeArr[i+1] == 'o' && largeArr[i+2] == 't'){
				p.bowl = false; 
			}
			
			else{
				p.bowl = true;
			}
			
			if (playerCount <= 11){
				teamOne[teamOneCount] = p;
				teamOneCount++; 
				playerCount++;
			}
			else if (playerCount > 11){
				teamTwo[teamTwoCount] = p;
				teamTwoCount++;
				playerCount++;
			}
		}
		
		cout<<endl;
		cout<<"YOU PLAY AS TEAM ONE: "<<endl; 
		int x = 0; 
		while (x < 11){
			sleep(1);
			int i = 0;
			while (teamOne[x].fname[i] != '\0'){
				cout<<teamOne[x].fname[i];
				i++; 
			}
			cout<<" ";
			
			i = 0; 
			while (teamOne[x].lname[i] != '\0'){
				cout<<teamOne[x].lname[i]; 
				i++; 
			}
			cout<<" ";			
			
			if (teamOne[x].bowl){
				cout<<"(bowler)"<<endl;
			}
			else {
				cout<<"(non-bowler)"<<endl;
			}
			x++;
		}
		
		cout<<endl;
		cout<<"YOU WILL PLAY AGAINST TEAM TWO: "<<endl;
		int y = 0; 
		while (y < 11){
			sleep(1);
			int i = 0;
			while (teamTwo[y].fname[i] != '\0'){
				cout<<teamTwo[y].fname[i];
				i++; 
			}
			cout<<" ";
			
			i = 0; 
			while (teamTwo[y].lname[i] != '\0'){
				cout<<teamTwo[y].lname[i]; 
				i++; 
			}
			cout<<" ";			
			
			if (teamTwo[y].bowl){
				cout<<"(bowler)"<<endl;
			}
			else {
				cout<<"(non-bowler)"<<endl;
			}
			y++;
		}
		cout<<endl;
		
		cout<<"EACH TEAM WILL HAVE " << overs << " OVERS TO SCORE AS MUCH RUNS AS POSSIBLE!"<<endl;
		cout<<"LET'S BEGIN!"<<endl<<endl;
		
 
		if (teamPos == 'b' || teamPos == 'B'){
			
			int playerNum = 0;
			for (int set=0; set<11; set++){
				teamOne[set].runs = 0;
				teamOne[set].batted = false;
				teamOne[set].out = false;
				teamOne[set].wickets = 0;
				teamOne[set].bowled = false;
				teamOne[set].oversBowled = 0;
			}
		
			for (int set=0; set<11; set++){
				teamTwo[set].wickets = 0;
				teamTwo[set].bowled = false;
				teamTwo[set].batted = false;
				teamTwo[set].runs = 0;
				teamTwo[set].out = false;
				teamTwo[set].oversBowled = 0;
			}
			
			Player battingEnd = teamOne[1];
			playerNum++;
			Player bowlingEnd = teamOne[0];
			Player temp = teamOne[playerNum];
		
			Player currBowler = getBowler(teamTwo, 11);
		
			int teamOneRuns = 0;
		
			int currOver = 1;
			
			int outCount = 0;
			
			int extraRuns = 0;
			
			
			while (currOver <= overs && outCount < 10){
				cout<<"OVER No.	BALL No.	BATTING END BATSMAN	BOWLING END BATSMAN	BOWLER				RESULT"<<endl;
				int currBall = 1;
				
				swapPlayers(&battingEnd, &bowlingEnd);
				
				currBowler.bowled = true;
				currBowler.oversBowled += 1;
				while (currBall <= 8 && outCount < 10){
					
					battingEnd.batted = true;
					
					cout<<currOver<<"		";
					cout<<currBall<<"		";
					printName(battingEnd);
					cout<<"		";
					printName(bowlingEnd);
					cout<<"		";
					printName(currBowler);
					cout<<"		";
					
					int goodOrBad = rand()%100 + 1; 
					
					if (goodOrBad >= 1 && goodOrBad <= 6){
						cout<<"No Ball (+2 runs)"<<endl;
						teamOneRuns += 2;
						extraRuns += 2;
					}
					
					else if (goodOrBad >= 7 && goodOrBad <= 10){
						cout<<"Wide Ball (+2 runs)"<<endl;
						teamOneRuns += 2;
						extraRuns += 2;
					}
					
					else if (goodOrBad >= 11 && goodOrBad <= 100){
						int ballResult = rand()%100 + 1;
						
						if (ballResult >= 1 && ballResult <= 17){
							cout<<"Six!! (+6 runs)"<<endl;
						
							battingEnd.runs += 6;
							teamOneRuns += 6;
						}
						
						else if (ballResult >= 18 && ballResult <= 20){
							cout<<"Five Runs Scored (+5 runs)"<<endl; 
							
							battingEnd.runs += 5;
							teamOneRuns += 5;
							swapPlayers(&battingEnd, &bowlingEnd);
						}
						
						else if (ballResult >= 21 && ballResult <= 48){
							cout<<"Four Runs Scored (+4 runs)"<<endl;
						
							battingEnd.runs += 4;
							teamOneRuns += 4;
						}
						
						else if (ballResult >= 49 && ballResult <= 56){
							cout<<"Three Runs Scored (+3 runs)"<<endl;
							
							battingEnd.runs += 3;
							teamOneRuns += 3;
							swapPlayers(&battingEnd, &bowlingEnd);
						}
						
						else if (ballResult >= 57 && ballResult <= 68){
							cout<<"Two Runs Scored (+2 runs)"<<endl;
							
							battingEnd.runs += 2;
							teamOneRuns += 2;
						}
						
						else if (ballResult >= 69 && ballResult <= 76){
							cout<<"One Run Scored (+1 run)"<<endl;
							
							battingEnd.runs += 1;
							teamOneRuns += 1;
							swapPlayers(&battingEnd, &bowlingEnd);
						}
						
						else if (ballResult >= 77 && ballResult <= 83){
							cout<<"Zero Runs Scored"<<endl;
						}
						
						else if (ballResult >= 84 && ballResult <= 100){
							cout<<"OUT!!"<<endl;
							outCount++;
							battingEnd.out = true;
							currBowler.wickets += 1;
							int loc = findPlayerLocation(teamOne, 11, battingEnd.fname, battingEnd.lname);
							teamOne[loc] = battingEnd;
							if (outCount < 10){
								playerNum++; 
								battingEnd = teamOne[playerNum];
							}
						}
					}
					cout<<endl<<"==========SCORE: "<<teamOneRuns<<" - "<<outCount<<"=========="<<endl;
					sleep(ballDelay);
					currBall += 1;
				}
				cout<<endl<<endl<<"THE OVER HAS ENDED"<<endl;
				cout<<"SCORE: "<<teamOneRuns<<" - "<<outCount<<endl<<endl;
				
				
				
				Player tempBowler = getBowler(teamTwo, 11);
				while ((strcmp(tempBowler.fname, currBowler.fname)==0) && (strcmp(tempBowler.lname, currBowler.lname)==0)){
					tempBowler = getBowler(teamTwo, 11);
				}
				int bowlLoc = findPlayerLocation(teamTwo, 11, currBowler.fname, currBowler.lname);
				teamTwo[bowlLoc] = currBowler;
				currBowler = tempBowler;
				
				sleep(overDelay);
				currOver += 1;
			}
			
			int batLoc = findPlayerLocation(teamOne, 11, battingEnd.fname, battingEnd.lname);
			teamOne[batLoc] = battingEnd;
			teamOne[batLoc].batted = true;
			
			int batLoc2 = findPlayerLocation(teamOne, 11, bowlingEnd.fname, bowlingEnd.lname);
			teamOne[batLoc2] = bowlingEnd;
			
			cout<<"Team One Scored "<<teamOneRuns<<" runs"<<endl;
			
			cout<<"END OF INNINGS"<<endl;
			sleep(innDelay);
			
			int playerNum2 = 0;
				
			Player battingEnd2 = teamTwo[1];
			playerNum2++;
			Player bowlingEnd2 = teamTwo[0];
			Player temp2 = teamTwo[playerNum2];
		
			Player currBowler2 = getBowler(teamOne, 11);
		
			int teamTwoRuns = 0;
		
			int currOver2 = 1;
			
			int outCount2 = 0;
			
			int extraRuns2 = 0;
			
			
			while (currOver2 <= overs && outCount2 < 10 && teamTwoRuns <= teamOneRuns){
				cout<<"OVER No.	BALL No.	BATTING END BATSMAN	BOWLING END BATSMAN	BOWLER				RESULT"<<endl;
				int currBall2 = 1;
				
				swapPlayers(&battingEnd2, &bowlingEnd2);
				
				currBowler2.bowled = true;
				currBowler2.oversBowled += 1;
				while (currBall2 <= 8 && outCount2 < 10 && teamTwoRuns <= teamOneRuns){
					
					battingEnd2.batted = true;
					
					cout<<currOver2<<"		";
					cout<<currBall2<<"		";
					printName(battingEnd2);
					cout<<"		";
					printName(bowlingEnd2);
					cout<<"		";
					printName(currBowler2);
					cout<<"		";
					
					int goodOrBad = rand()%100 + 1; 
					
					if (goodOrBad >= 1 && goodOrBad <= 6){
						cout<<"No Ball (+2 runs)"<<endl;
						teamTwoRuns += 2;
						extraRuns2 += 2;
					}
					
					else if (goodOrBad >= 7 && goodOrBad <= 10){
						cout<<"Wide Ball (+2 runs)"<<endl;
						teamTwoRuns += 2;
						extraRuns2 += 2;
					}
					
					else if (goodOrBad >= 11 && goodOrBad <= 100){
						int ballResult = rand()%100 + 1;
						
						if (ballResult >= 1 && ballResult <= 17){
							cout<<"Six!! (+6 runs)"<<endl;
							battingEnd2.runs += 6;
							teamTwoRuns += 6;
						}
						
						else if (ballResult >= 18 && ballResult <= 20){
							cout<<"Five Runs Scored (+5 runs)"<<endl; 
							battingEnd2.runs += 5;
							teamTwoRuns += 5;
							swapPlayers(&battingEnd2, &bowlingEnd2);
						}
						
						else if (ballResult >= 21 && ballResult <= 48){
							cout<<"Four Runs Scored (+4 runs)"<<endl;
							battingEnd2.runs += 4;
							teamTwoRuns += 4;
						}
						
						else if (ballResult >= 49 && ballResult <= 56){
							cout<<"Three Runs Scored (+3 runs)"<<endl;
							battingEnd2.runs += 3;
							teamTwoRuns += 3;
							swapPlayers(&battingEnd2, &bowlingEnd2);
						}
						
						else if (ballResult >= 57 && ballResult <= 68){
							cout<<"Two Runs Scored (+2 runs)"<<endl;
							battingEnd2.runs += 2;
							teamTwoRuns += 2;
						}
						
						else if (ballResult >= 69 && ballResult <= 76){
							cout<<"One Run Scored (+1 run)"<<endl;
							battingEnd2.runs += 1;
							teamTwoRuns += 1;
							swapPlayers(&battingEnd2, &bowlingEnd2);
						}
						
						else if (ballResult >= 77 && ballResult <= 83){
							cout<<"Zero Runs Scored"<<endl;
						}
						
						else if (ballResult >= 84 && ballResult <= 100){
							cout<<"OUT!!"<<endl;
							outCount2++;
							battingEnd2.out = true;
							currBowler2.wickets += 1;
							int loc = findPlayerLocation(teamTwo, 11, battingEnd2.fname, battingEnd2.lname);
							teamTwo[loc] = battingEnd2;
							if (outCount2 < 10){
								playerNum2++; 
								battingEnd2 = teamTwo[playerNum2];
							}
						}
						
					}
					cout<<endl<<"==========SCORE: "<<teamTwoRuns<<" - "<<outCount2<<"=========="<<endl;
					sleep(ballDelay);
					currBall2 += 1;
				}
				cout<<endl<<endl<<"THE OVER HAS ENDED"<<endl;
				cout<<"SCORE: "<<teamTwoRuns<<" - "<<outCount2<<endl<<endl;
				
				
				
				Player tempBowler2 = getBowler(teamOne, 11);
				while ((strcmp(tempBowler2.fname, currBowler2.fname)==0) && (strcmp(tempBowler2.lname, currBowler2.lname)==0)){
					tempBowler2 = getBowler(teamOne, 11);
				}
				int bowlLoc2 = findPlayerLocation(teamOne, 11, currBowler2.fname, currBowler2.lname);
				teamOne[bowlLoc2] = currBowler2;
				currBowler2 = tempBowler2;
				
				sleep(overDelay);
				currOver2 += 1;
			}
			
			int batLoc2One = findPlayerLocation(teamTwo, 11, battingEnd2.fname, battingEnd2.lname);
			teamTwo[batLoc2One] = battingEnd2;
			teamTwo[batLoc2One].batted = true;
			
			int batLoc2Two = findPlayerLocation(teamTwo, 11, bowlingEnd2.fname, bowlingEnd2.lname);
			teamTwo[batLoc2Two] = bowlingEnd2;
			
			cout<<"Team Two Scored "<<teamTwoRuns<<" runs"<<endl;
			sleep(innDelay);
			cout<<endl<<endl;
			if (teamOneRuns > teamTwoRuns){
				cout<<"YOUR TEAM WON!!"<<endl;
			}
		
			else if (teamTwoRuns > teamOneRuns){
				cout<<"YOUR TEAM LOST!!"<<endl;
			}
		
			cout<<"Your Team: "<<teamOneRuns<<" - "<<outCount<<"			Opponent's Team: "<<teamTwoRuns<<" - "<<outCount2<<endl;
			cout<<"						FINAL SCOREBOARD"<<endl;
			cout<<"FIRST INNING: Your Team Batting"<<endl;
			for (int c=0; c<11; c++){
				
				if (teamOne[c].batted){
					printName(teamOne[c]);
					if (teamOne[c].out){
						cout<<"				"<<teamOne[c].runs<<" runs";
						int outStyle = rand()%5  + 1;
						if (outStyle == 1)
							cout<<" (bowled out)"<<endl;
						else if (outStyle == 2)
							cout<<" (caught out)"<<endl;
						else if (outStyle == 3)
							cout<<" (LBW)"<<endl;
						else if (outStyle == 4)
							cout<<" (hit wicket)"<<endl;
						else if (outStyle == 5)
							cout<<" (stumped)"<<endl;
					}
					else	
						cout<<"			"<<teamOne[c].runs<<" (not out)"<<endl;
				}
			}
			cout<<"Extra Runs: "<<extraRuns<<endl;
			
			cout<<endl<<"Opponent Team Fielding: "<<endl;
			
			for (int c=0; c<11; c++){
				
				if (teamTwo[c].bowled){
					printName(teamTwo[c]);
					cout<<"					"<<teamTwo[c].oversBowled;
					if (teamTwo[c].oversBowled == 1)
						cout<<" over bowled";
					else
						cout<<" overs bowled";
					cout<<"				"<<teamTwo[c].wickets;
					if (teamTwo[c].wickets == 1)
						cout<<" wicket taken"<<endl;
					else
						cout<<" wickets taken"<<endl;
				}
			}
			cout<<endl;
			
			cout<<"SECOND INNING: Opponent Team Batting"<<endl;
			for (int c=0; c<11; c++){
				
				if (teamTwo[c].batted){
					printName(teamTwo[c]);
					if (teamTwo[c].out){
						cout<<"			"<<teamTwo[c].runs<<" runs";
						int outStyle = rand()%5  + 1;
						if (outStyle == 1)
							cout<<" (bowled out)"<<endl;
						else if (outStyle == 2)
							cout<<" (caught out)"<<endl;
						else if (outStyle == 3)
							cout<<" (LBW)"<<endl;
						else if (outStyle == 4)
							cout<<" (hit wicket)"<<endl;
						else if (outStyle == 5)
							cout<<" (stumped)"<<endl;
					}
					else	
						cout<<"			"<<teamTwo[c].runs<<" (not out)"<<endl;
				}
			}
			cout<<"Extra Runs: "<<extraRuns2<<endl;
			
			cout<<endl<<"Your Team Fielding: "<<endl;
			
			for (int c=0; c<11; c++){
				
				if (teamOne[c].bowled){
					printName(teamOne[c]);
					cout<<"			"<<teamOne[c].oversBowled;
					if (teamOne[c].oversBowled == 1)
						cout<<" over bowled";
					else
						cout<<" overs bowled";
					cout<<"			"<<teamOne[c].wickets;
					if (teamOne[c].wickets == 1)
						cout<<" wicket taken"<<endl;
					else
						cout<<" wickets taken"<<endl;
				}
			}	
		}
		
		else if (teamPos == 'f' || teamPos == 'F'){
			int playerNum2 = 0;
			for (int set=0; set<11; set++){
				teamOne[set].runs = 0;
				teamOne[set].batted = false;
				teamOne[set].out = false;
				teamOne[set].wickets = 0;
				teamOne[set].bowled = false;
				teamOne[set].oversBowled = 0;
			}
		
			for (int set=0; set<11; set++){
				teamTwo[set].wickets = 0;
				teamTwo[set].bowled = false;
				teamTwo[set].batted = false;
				teamTwo[set].runs = 0;
				teamTwo[set].out = false;
				teamTwo[set].oversBowled = 0;
			}
				
			Player battingEnd2 = teamTwo[1];
			playerNum2++;
			Player bowlingEnd2 = teamTwo[0];
			Player temp2 = teamTwo[playerNum2];
		
			Player currBowler2 = getBowler(teamOne, 11);
		
			int teamTwoRuns = 0;
		
			int currOver2 = 1;
			
			int outCount2 = 0;
			
			int extraRuns2 = 0;
			
			
			while (currOver2 <= overs && outCount2 < 10){
				cout<<"OVER No.	BALL No.	BATTING END BATSMAN	BOWLING END BATSMAN	BOWLER				RESULT"<<endl;
				int currBall2 = 1;
				
				swapPlayers(&battingEnd2, &bowlingEnd2);
				
				currBowler2.bowled = true;
				currBowler2.oversBowled += 1;
				while (currBall2 <= 8 && outCount2 < 10){
					
					battingEnd2.batted = true;
					
					cout<<currOver2<<"		";
					cout<<currBall2<<"		";
					printName(battingEnd2);
					cout<<"		";
					printName(bowlingEnd2);
					cout<<"		";
					printName(currBowler2);
					cout<<"		";
					
					int goodOrBad = rand()%100 + 1; 
					
					if (goodOrBad >= 1 && goodOrBad <= 6){
						cout<<"No Ball (+2 runs)"<<endl;
						teamTwoRuns += 2;
						extraRuns2 += 2;
					}
					
					else if (goodOrBad >= 7 && goodOrBad <= 10){
						cout<<"Wide Ball (+2 runs)"<<endl;
						teamTwoRuns += 2;
						extraRuns2 += 2;
					}
					
					else if (goodOrBad >= 11 && goodOrBad <= 100){
						int ballResult = rand()%100 + 1;
						
						if (ballResult >= 1 && ballResult <= 17){
							cout<<"Six!! (+6 runs)"<<endl;
							battingEnd2.runs += 6;
							teamTwoRuns += 6;
						}
						
						else if (ballResult >= 18 && ballResult <= 20){
							cout<<"Five Runs Scored (+5 runs)"<<endl; 
							battingEnd2.runs += 5;
							teamTwoRuns += 5;
							swapPlayers(&battingEnd2, &bowlingEnd2);
						}
						
						else if (ballResult >= 21 && ballResult <= 48){
							cout<<"Four Runs Scored (+4 runs)"<<endl;
							battingEnd2.runs += 4;
							teamTwoRuns += 4;
						}
						
						else if (ballResult >= 49 && ballResult <= 56){
							cout<<"Three Runs Scored (+3 runs)"<<endl;
							battingEnd2.runs += 3;
							teamTwoRuns += 3;
							swapPlayers(&battingEnd2, &bowlingEnd2);
						}
						
						else if (ballResult >= 57 && ballResult <= 68){
							cout<<"Two Runs Scored (+2 runs)"<<endl;
							battingEnd2.runs += 2;
							teamTwoRuns += 2;
						}
						
						else if (ballResult >= 69 && ballResult <= 76){
							cout<<"One Run Scored (+1 run)"<<endl;
							battingEnd2.runs += 1;
							teamTwoRuns += 1;
							swapPlayers(&battingEnd2, &bowlingEnd2);
						}
						
						else if (ballResult >= 77 && ballResult <= 83){
							cout<<"Zero Runs Scored"<<endl;
						}
						
						else if (ballResult >= 84 && ballResult <= 100){
							cout<<"OUT!!"<<endl;
							outCount2++;
							battingEnd2.out = true;
							currBowler2.wickets += 1;
							int loc = findPlayerLocation(teamTwo, 11, battingEnd2.fname, battingEnd2.lname);
							teamTwo[loc] = battingEnd2;
							if (outCount2 < 10){
								playerNum2++; 
								battingEnd2 = teamTwo[playerNum2];
							}
						}
						
					}
					cout<<endl<<"==========SCORE: "<<teamTwoRuns<<" - "<<outCount2<<"=========="<<endl;
					sleep(ballDelay);
					currBall2 += 1;
				}
				cout<<endl<<endl<<"THE OVER HAS ENDED"<<endl;
				cout<<"SCORE: "<<teamTwoRuns<<" - "<<outCount2<<endl<<endl;
				
				
				
				Player tempBowler2 = getBowler(teamOne, 11);
				while ((strcmp(tempBowler2.fname, currBowler2.fname)==0) && (strcmp(tempBowler2.lname, currBowler2.lname)==0)){
					tempBowler2 = getBowler(teamOne, 11);
				}
				int bowlLoc2 = findPlayerLocation(teamOne, 11, currBowler2.fname, currBowler2.lname);
				teamOne[bowlLoc2] = currBowler2;
				currBowler2 = tempBowler2;
				
				sleep(overDelay);
				currOver2 += 1;
			}
			
			int batLoc2One = findPlayerLocation(teamTwo, 11, battingEnd2.fname, battingEnd2.lname);
			teamTwo[batLoc2One] = battingEnd2;
			teamTwo[batLoc2One].batted = true;
			
			int batLoc2Two = findPlayerLocation(teamTwo, 11, bowlingEnd2.fname, bowlingEnd2.lname);
			teamTwo[batLoc2Two] = bowlingEnd2;
			
			cout<<"Team Two Scored "<<teamTwoRuns<<" runs"<<endl;
			
			cout<<endl<<"END OF INNINGS"<<endl;
			sleep(innDelay);
			cout<<endl<<endl<<endl;
			
			int playerNum = 0;
			
			Player battingEnd = teamOne[1];
			playerNum++;
			Player bowlingEnd = teamOne[0];
			Player temp = teamOne[playerNum];
		
			Player currBowler = getBowler(teamTwo, 11);
		
			int teamOneRuns = 0;
		
			int currOver = 1;
			
			int outCount = 0;
			
			int score;
			
			int extraRuns = 0;
			
			
			while (currOver <= overs && outCount < 10 && teamOneRuns <= teamTwoRuns){
				cout<<"OVER No.	BALL No.	BATTING END BATSMAN	BOWLING END BATSMAN	BOWLER				RESULT"<<endl;
				int currBall = 1;
				
				swapPlayers(&battingEnd, &bowlingEnd);
				
				currBowler.bowled = true;
				currBowler.oversBowled += 1;
				while (currBall <= 8 && outCount < 10 && teamOneRuns <= teamTwoRuns){
					
					battingEnd.batted = true;
					
					cout<<currOver<<"		";
					cout<<currBall<<"		";
					printName(battingEnd);
					cout<<"		";
					printName(bowlingEnd);
					cout<<"		";
					printName(currBowler);
					cout<<"		";
					
					int goodOrBad = rand()%100 + 1; 
					
					if (goodOrBad >= 1 && goodOrBad <= 6){
						cout<<"No Ball (+2 runs)"<<endl;
						teamOneRuns += 2;
						extraRuns += 2;
					}
					
					else if (goodOrBad >= 7 && goodOrBad <= 10){
						cout<<"Wide Ball (+2 runs)"<<endl;
						teamOneRuns += 2;
						extraRuns += 2;
					}
					
					else if (goodOrBad >= 11 && goodOrBad <= 100){
						int ballResult = rand()%100 + 1;
						
						if (ballResult >= 1 && ballResult <= 17){
							cout<<"Six!! (+6 runs)"<<endl;
							score = 6;
							battingEnd.runs += 6;
							teamOneRuns += 6;
						}
						
						else if (ballResult >= 18 && ballResult <= 20){
							cout<<"Five Runs Scored (+5 runs)"<<endl; 
							score = 5;
							battingEnd.runs += 5;
							teamOneRuns += 5;
							swapPlayers(&battingEnd, &bowlingEnd);
						}
						
						else if (ballResult >= 21 && ballResult <= 48){
							cout<<"Four Runs Scored (+4 runs)"<<endl;
							score = 4;
							battingEnd.runs += 4;
							teamOneRuns += 4;
						}
						
						else if (ballResult >= 49 && ballResult <= 56){
							cout<<"Three Runs Scored (+3 runs)"<<endl;
							score = 3;
							battingEnd.runs += 3;
							teamOneRuns += 3;
							swapPlayers(&battingEnd, &bowlingEnd);
						}
						
						else if (ballResult >= 57 && ballResult <= 68){
							cout<<"Two Runs Scored (+2 runs)"<<endl;
							score = 2;
							battingEnd.runs += 2;
							teamOneRuns += 2;
						}
						
						else if (ballResult >= 69 && ballResult <= 76){
							cout<<"One Run Scored (+1 run)"<<endl;
							score = 1;
							battingEnd.runs += 1;
							teamOneRuns += 1;
							swapPlayers(&battingEnd, &bowlingEnd);
						}
						
						else if (ballResult >= 77 && ballResult <= 83){
							cout<<"Zero Runs Scored"<<endl;
						}
						
						else if (ballResult >= 84 && ballResult <= 100){
							cout<<"OUT!!"<<endl;
							outCount++;
							battingEnd.out = true;
							currBowler.wickets += 1;
							int loc = findPlayerLocation(teamOne, 11, battingEnd.fname, battingEnd.lname);
							teamOne[loc] = battingEnd;
							if (outCount < 10){
								playerNum++; 
								battingEnd = teamOne[playerNum];
							}
						}
						
					}
					cout<<endl<<"==========SCORE: "<<teamTwoRuns<<" - "<<outCount<<"=========="<<endl;
					sleep(ballDelay);
					currBall += 1;
				}
				cout<<endl<<endl<<"THE OVER HAS ENDED"<<endl;
				cout<<"SCORE: "<<teamOneRuns<<" - "<<outCount<<endl<<endl;
				
				
				
				Player tempBowler = getBowler(teamTwo, 11);
				while ((strcmp(tempBowler.fname, currBowler.fname)==0) && (strcmp(tempBowler.lname, currBowler.lname)==0)){
					tempBowler = getBowler(teamTwo, 11);
				}
				int bowlLoc = findPlayerLocation(teamTwo, 11, currBowler.fname, currBowler.lname);
				teamTwo[bowlLoc] = currBowler;
				currBowler = tempBowler;
				
				sleep(overDelay);
				currOver += 1;
			}
			
			int batLoc = findPlayerLocation(teamOne, 11, battingEnd.fname, battingEnd.lname);
			teamOne[batLoc] = battingEnd;
			teamOne[batLoc].batted = true;
			
			int batLoc2 = findPlayerLocation(teamOne, 11, bowlingEnd.fname, bowlingEnd.lname);
			teamOne[batLoc2] = bowlingEnd;
			
			cout<<"Team One Scored "<<teamOneRuns<<" runs"<<endl;
			
			sleep(innDelay);
			
			cout<<endl<<endl;
			if (teamOneRuns > teamTwoRuns){
				cout<<"YOUR TEAM WON!!"<<endl;
			}
		
			else if (teamTwoRuns > teamOneRuns){
				cout<<"YOUR TEAM LOST!!"<<endl;
			}
		
			cout<<"Your Team: "<<teamOneRuns<<" - "<<outCount<<"			Opponent's Team: "<<teamTwoRuns<<" - "<<outCount2<<endl<<endl;
			cout<<"						FINAL SCOREBOARD"<<endl;
			cout<<"FIRST INNING: Opponent Team Batting"<<endl;
			for (int c=0; c<11; c++){
				
				if (teamTwo[c].batted){
					printName(teamTwo[c]);
					if (teamTwo[c].out){
						cout<<"				"<<teamTwo[c].runs<<" runs";
						int outStyle = rand()%5  + 1;
						if (outStyle == 1)
							cout<<" (bowled out)"<<endl;
						else if (outStyle == 2)
							cout<<" (caught out)"<<endl;
						else if (outStyle == 3)
							cout<<" (LBW)"<<endl;
						else if (outStyle == 4)
							cout<<" (hit wicket)"<<endl;
						else if (outStyle == 5)
							cout<<" (stumped)"<<endl;
					}
					else	
						cout<<"			"<<teamTwo[c].runs<<" (not out)"<<endl;
				}
			}
			cout<<"Extra Runs: "<<extraRuns2<<endl;
			
			cout<<endl<<"Your Team Fielding: "<<endl;
			
			for (int c=0; c<11; c++){
				
				if (teamOne[c].bowled){
					printName(teamOne[c]);
					cout<<"					"<<teamOne[c].oversBowled;
					if (teamOne[c].oversBowled == 1)
						cout<<" over bowled";
					else
						cout<<" overs bowled";
					cout<<"				"<<teamOne[c].wickets;
					if (teamOne[c].wickets == 1)
						cout<<" wicket taken"<<endl;
					else
						cout<<" wickets taken"<<endl;
				}
			}
			cout<<endl;
			
			cout<<"SECOND INNING: Your Team Batting"<<endl;
			for (int c=0; c<11; c++){
				
				if (teamOne[c].batted){
					printName(teamOne[c]);
					if (teamOne[c].out){
						cout<<"			"<<teamOne[c].runs<<" runs";
						int outStyle = rand()%5  + 1;
						if (outStyle == 1)
							cout<<" (bowled out)"<<endl;
						else if (outStyle == 2)
							cout<<" (caught out)"<<endl;
						else if (outStyle == 3)
							cout<<" (LBW)"<<endl;
						else if (outStyle == 4)
							cout<<" (hit wicket)"<<endl;
						else if (outStyle == 5)
							cout<<" (stumped)"<<endl;
					}
					else	
						cout<<"			"<<teamOne[c].runs<<" (not out)"<<endl;
				}
			}
			cout<<"Extra Runs: "<<extraRuns<<endl;
			
			cout<<endl<<"Opponent Team Fielding: "<<endl;
			
			for (int c=0; c<11; c++){
				
				if (teamTwo[c].bowled){
					printName(teamTwo[c]);
					cout<<"			"<<teamTwo[c].oversBowled;
					if (teamTwo[c].oversBowled == 1)
						cout<<" over bowled";
					else
						cout<<" overs bowled";
					cout<<"			"<<teamTwo[c].wickets;
					if (teamTwo[c].wickets == 1)
						cout<<" wicket taken"<<endl;
					else
						cout<<" wickets taken"<<endl;
				}
			}
		}
			
	}
	
	return 0; 
	
}
