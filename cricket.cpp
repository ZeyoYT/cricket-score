#include<iostream>
#include<cstdlib>
#include<ctime>
#include<string>
#include<map>
#include<set>
#include<list>
#include<vector>
#include<iomanip>

using namespace std;


class Players {

    private:
        // k: Name, v: Score
        map<string, map<int, int>> players;
        int teamScore = 0;
        int extraScore = 0;

    public:

        // gives list of names in players map
        list<string> playerNameList() {
            
            list<string> playerNames;

            for(auto it = players.begin(); it != players.end(); it++) {
                playerNames.push_back(it->first);
            }

            return playerNames;
        }

        // create a player with all types of scores
        void player(string name) {
            players[name] = map<int, int> {
                {1, 0},
                {2, 0},
                {3, 0},
                {4, 0},
                {6, 0},
            };
        }

        // update a players score
        void player(string name, int score) {
            if(players.find(name) == players.end()) {
                player(name);
            }

            for(auto it = players[name].begin(); it != players[name].end(); it++) {
                if(it->first == score) {
                    it->second++;
                }
            }
        }

        void clearPlayerScores() {
            for(auto it = players.begin(); it != players.end(); it++) {
                for(auto it2 = it->second.begin(); it2 != it->second.end(); it2++) {
                    it2->second = 0;
                }
            }

            teamScore = 0;
        }

        void incrementExtraScore(int score) {
            extraScore += score;
        }

        int getTeamScore() {
            return teamScore + extraScore;
        }

        void generateScoreTable(bool print = false) {

            int hyphens = 94;

            if (print) {
                cout << "Player Name\t1\t2\t3\t4\t6\tTotal Runs\tTeam Runs\n";
                cout << setw(hyphens) << setfill('-') << "\n\n";
            }

            teamScore = 0;

            // loop over players, and print the score based on the player and what they scored
            for(auto it = players.begin(); it != players.end(); it++) {
                int playerScore = 0;

                // Print the player name
                if (print) {
                    cout << it->first << "\t\t";
                }

                for(auto it2 = it->second.begin(); it2 != it->second.end(); it2++) {
                    if (print) {
                        cout << it2->second << "\t";
                    }
                    playerScore += it2->first * it2->second;
                }

                teamScore += playerScore;

                // Print the total score of the player and the team
                if (print) {
                    cout << playerScore << "\t\t" << teamScore << "\n";
                }
            }

            // Print the total team score
            if (print) {
                cout << setw(hyphens) << setfill('-') << "\n\n";
                cout << "Total Runs: " << teamScore << " + " << extraScore << " : " << getTeamScore() << "\n";
            }
        }

};

class CricketTeam : public Players {

    private:
        string teamName;
        bool isBatting; 

    public:

        CricketTeam(string teamName) {
            this->teamName = teamName;
        }

        bool setIsBatting(bool val) {
            isBatting = val;
        }

        string getTeamName() {
            return teamName;
        }

};

class Cricket {

    private:
        
        vector<string> player_names = {
            "John", "Michael", "David", "Chris", "James", "Robert", "Daniel", 
            "William", "Joseph", "Kevin", "Paul", "Mark", "Charles", "Andrew", 
            "Thomas", "Steven", "George", "Patrick", "Brian", "Edward", 
            "Richard", "Anthony"
        };

        string getRandomCricketValue() {

            struct Outcome {
                string value;
                double probability;  // Between 0 and 1
            };

            Outcome outcomes[] = {
                {"1", 0.30},  // Highest chance
                {"2", 0.20},  // High chance
                {"3", 0.05},  // Low chance
                {"4", 0.10},  // Mid chance
                {"6", 0.10},  // Mid chance
                {"W", 0.15},  // High chance
                {"WB", 0.10}, // Lower chance
                {"NB", 0.10}  // Lower chance
            };

            double randomValue = (double) rand() / RAND_MAX;
            double sumOfProbability = 0.0;

            for (const Outcome& outcome : outcomes) {
                sumOfProbability += outcome.probability;

                if (randomValue <= sumOfProbability) {
                    return outcome.value;
                }
            }

            return "1";
        }

        string getRandomPlayerName() {
            
            string selected_name;

            int random_index = rand() % player_names.size();
            selected_name = player_names[random_index];

            player_names.erase(player_names.begin() + random_index);

            return selected_name;
        }

    public:

        CricketTeam& t1;
        CricketTeam& t2;

        Cricket(CricketTeam& t1, CricketTeam& t2) : t1(t1), t2(t2) {};

        CricketTeam play(int overs) {
            
            int tempCounter = 1;
            t1.clearPlayerScores();
            t2.clearPlayerScores();

            if(t1.playerNameList().size() != 11 && t2.playerNameList().size() != 11 ) {
            
                t1.playerNameList().clear();
                t2.playerNameList().clear();
            
                while(tempCounter <= 11) {

                    t1.player(getRandomPlayerName());  
                    t2.player(getRandomPlayerName());  

                    tempCounter++;
                }
            }

            simulateInnings(t1, overs);
            cout << endl;
            simulateInnings(t2, overs);
            cout << endl;

            cout << "Team Scores : " << endl;
            cout << t1.getTeamName() << " : " << t1.getTeamScore() << endl;
            cout << t2.getTeamName() << " : " << t2.getTeamScore() << endl;

            return t1.getTeamScore() > t2.getTeamScore() ? t1 : t2;

        }

        void simulateInnings(CricketTeam& team, int overs) {
            
            int ballsPerOver = 6;
            int currentOvers = 0;
            int validBallsInCurrentOver = 0;
            bool isWicket = false;

            list<string> playerNames = team.playerNameList();

            while (currentOvers < overs) {
                if (playerNames.size() == 0) {
                    break;
                }

                string playerName = playerNames.front();

                if (isWicket) {
                    playerNames.pop_front();
                    if (playerNames.size() == 0) {
                        break;
                    }
                    playerName = playerNames.front();
                    isWicket = false;
                }

                while (validBallsInCurrentOver < ballsPerOver) {
                    string ballOutcome = getRandomCricketValue();

                    if (ballOutcome == "W") {
                        isWicket = true;
                        validBallsInCurrentOver++;
                        break;
                    } 
                    else if (ballOutcome == "NB" || ballOutcome == "WB") {
                        team.incrementExtraScore(1);
                    } 
                    else {
                        team.player(playerName, stoi(ballOutcome));
                        validBallsInCurrentOver++;
                    }
                }

                if (validBallsInCurrentOver == ballsPerOver) {
                    currentOvers++;
                    validBallsInCurrentOver = 0;
                }
            }

            team.generateScoreTable();
        }



};

void displayMenu(bool gamePlayed, string teamOneName, string teamTwoName, string winnerTeamName = "") {
    if (gamePlayed) {
        cout << "=============================\n";
        cout << "Team Won: " << winnerTeamName << "\n";
        cout << "=============================\n";
    }
    cout << "1. Play the game\n";
    cout << "2. Print score of " << teamOneName << "\n";
    cout << "3. Print score of " << teamTwoName << "\n";
    cout << "4. Exit\n";
    cout << "Enter your choice: ";
}

int main() {

    // Seed the random number generator with time
    srand(std::time(0));

    string team1Name, team2Name;
    cout << "Enter name for Team 1: ";
    cin >> team1Name;
    cout << "Enter name for Team 2: ";
    cin >> team2Name;
    cout << endl;

    CricketTeam t1 = CricketTeam(team1Name);
    CricketTeam t2 = CricketTeam(team2Name);

    bool gamePlayed = false;
    string winnerTeamName;
    int choice;

    do {
        displayMenu(gamePlayed, team1Name, team2Name, winnerTeamName);
        cin >> choice;
        cout << endl;

        switch (choice) {
            case 1: {
                int overs = 0;

                cout << "Enter number of overs to play: ";
                cin >> overs;

                Cricket c = Cricket(t1, t2);
                CricketTeam winner = c.play(overs);

                winnerTeamName = winner.getTeamName();
                gamePlayed = true;
                
                cout << endl;
                break;
            }
            case 2:
                t1.generateScoreTable(true);
                cout << endl;
                break;
            case 3:
                t2.generateScoreTable(true);
                cout << endl;
                break;
            case 4:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}
