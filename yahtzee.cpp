#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <cstdlib>
#include <ctime>
#include <algorithm>

std::array<int, 5> SortDicesDescending(std::array<int, 5> d_array){
    std::array<int, 5> new_dices;
    int place = 0;

    for(int biggest_int = 6; biggest_int > 0; --biggest_int){ 
        for(int i = 0; i < 5; ++i){
            if(biggest_int == d_array[i]){
                new_dices[place] = d_array[i];
                ++place;
            }
        }
    }
    return new_dices;
}
//puts -1 to scoreboard to mark that value used
int markNotEmpty(int& v){
    if(v == 0)
        return -1;
    else
        return v;
}

struct Score{
    std::array<int, 17> score_array = {};
    std::array<std::string, 17> score_string = {"Aces", "Twos", "Threes", "Fours", 
                    "Fives", "Sixes", "Upper bonus", "One pair", "Two pairs", 
                    "Three of a kind", "Four of a kind", "Small straight", "Large straight",
                    "Full house", "Change", "Yatzy", "Total points"};

    int checkAces(std::array<int, 5>& dice_array){
        int value = 0;
        for(int i = 0; i < 5; ++i){
            if(dice_array[i] == 1){
                value += dice_array[i];
            }
        }
        value = markNotEmpty(value);
        return value;
    }
    int checkTwos(std::array<int, 5>& dice_array){
        int value = 0;
        for(int i = 0; i < 5; ++i){
            if(dice_array[i] == 2){
                value += dice_array[i];
            }
        }
        value = markNotEmpty(value);
        return value;
    }
    int checkThrees(std::array<int, 5>& dice_array){
        int value = 0;
        for(int i = 0; i < 5; ++i){
            if(dice_array[i] == 3){
                value += dice_array[i];
            }
        }
        value = markNotEmpty(value);
        return value;
    }
    int checkFours(std::array<int, 5>& dice_array){
        int value = 0;
        for(int i = 0; i < 5; ++i){
            if(dice_array[i] == 4){
                value += dice_array[i];
            }
        }
        value = markNotEmpty(value);
        return value;
    }
    int checkFives(std::array<int, 5>& dice_array){
        int value = 0;
        for(int i = 0; i < 5; ++i){
            if(dice_array[i] == 5){
                value += dice_array[i];
            }
        }
        value = markNotEmpty(value);
        return value;
    }
    int checkSixes(std::array<int, 5>& dice_array){
        int value = 0;
        for(int i = 0; i < 5; ++i){
            if(dice_array[i] == 6){
                value += dice_array[i];
            }
        }
        value = markNotEmpty(value);
        return value;
    }
    int checkTotalUpperSection(){
        int upper_section = 0;

        for(int i = 0; i < 6; ++i){
            if(score_array[i] > 0){
                upper_section += score_array[i];
            }
        }

        if(upper_section >= 63){
            return 50;
        }else{
            return 0;
        }
    }

    int checkPair(std::array<int, 5>& dice_array){
        int value = 0;
        int first_number = 0;
        int second_number = 0;

        dice_array = SortDicesDescending(dice_array);

        for(int i = 0; i < 5; ++i){
            first_number = dice_array[i];
            if(dice_array[i+1] == first_number){
                second_number = dice_array[i+1];
                break;
            }
        }
        //jälkitarkastus jotta aina asetettava first_number ei mene tulokseen
        if(first_number == second_number){
            value = first_number + second_number;
        }
        value = markNotEmpty(value);
        return value;
    }

    int checkTwoPairs(std::array<int, 5> dice_array){
        int value = 0;
        int first_number = 0;
        int second_number = 0;
        int third_number = 0;
        int fourth_number = 0;
        int number_place;

        dice_array = SortDicesDescending(dice_array);
        //eka pari
        for(int i = 0; i < 5; ++i){
            first_number = dice_array[i];
            if(dice_array[i+1] == first_number){
                second_number = dice_array[i+1];
                number_place = i+1; //plus 1 että hypätään seuraavaan arrayssa
                break;
            }
        }
        //toka pari
        for(int i = number_place; i < 5; ++i){
            third_number = dice_array[i];
            if(dice_array[i+1] == third_number){
                fourth_number = dice_array[i+1];
                break;
            }
        }
        //lopputarkastus ettei hyväksytä esim. 22422
        if( first_number == second_number && 
            third_number == fourth_number &&
            first_number != fourth_number){
                value = first_number + second_number + third_number + fourth_number;
            }
        value = markNotEmpty(value);
        return value;
    }

    int checkThreeOfK(std::array<int, 5>& dice_array){
        int value = 0;
        int first_number = 0, second_number = 0, third_number = 0;
    
        dice_array = SortDicesDescending(dice_array);

        for(int i = 0; i < 5; ++i){
            first_number = dice_array[i];
            if( dice_array[i+1] == first_number && 
                dice_array[i+2] == first_number){
                second_number = dice_array[i+1];
                third_number = dice_array[i+2];
                break;
            }
        }
        if( first_number == second_number && 
            first_number == third_number){
            value = 3 * first_number;
        }
        value = markNotEmpty(value);
        return value;
    }

    int checkFourOfK(std::array<int, 5> dice_array){
        int value = 0;

        dice_array = SortDicesDescending(dice_array);

        if( dice_array[0] == dice_array[1] &&
            dice_array[0] == dice_array[2] &&
            dice_array[0] == dice_array[3]){
                value = dice_array[0] * 4;
        }
        if( dice_array[4] == dice_array[1] &&
            dice_array[4] == dice_array[2] &&
            dice_array[4] == dice_array[3]){
                value = dice_array[4] * 4;
        }
        value = markNotEmpty(value);
        return value;
    }

    int checkSmallStraight(std::array<int, 5> dice_array){
        int value = 0;

        dice_array = SortDicesDescending(dice_array);

        if( dice_array[4] == 1 &&
            dice_array[3] == 2 &&
            dice_array[2] == 3 &&
            dice_array[1] == 4 &&
            dice_array[0] == 5){
                value = 1+2+3+4+5;
        }
        value = markNotEmpty(value);
        return value;
    }

    int checkLargeStraight(std::array<int, 5> dice_array){
        int value = 0;

        dice_array = SortDicesDescending(dice_array);

        if( dice_array[4] == 2 &&
            dice_array[3] == 3 &&
            dice_array[2] == 4 &&
            dice_array[1] == 5 &&
            dice_array[0] == 6){
                value = 2+3+4+5+6;
        }
        value = markNotEmpty(value);
        return value;
    }

    int checkFullHouse(std::array<int, 5> dice_array){
        int value = 0;

        dice_array = SortDicesDescending(dice_array);

        if( dice_array[0] == dice_array[1] &&
            dice_array[0] == dice_array[2] &&
            dice_array[4] == dice_array[3] &&
            dice_array[0] != dice_array[4]){
                for(int i = 0; i < 5; ++i){
                    value += dice_array[i];
                }
            }
        if( dice_array[0] == dice_array[1] &&
            dice_array[4] == dice_array[2] &&
            dice_array[4] == dice_array[3] &&
            dice_array[0] != dice_array[4]){
                for(int i = 0; i < 5; ++i){
                    value += dice_array[i];
                }
            }
        value = markNotEmpty(value);
        return value;
    }
    
    int checkChange(std::array<int, 5> dice_array){
        int value = 0;

        for(int i = 0; i < 5; ++i){
            value += dice_array[i];
        }
        value = markNotEmpty(value);
        return value;
    }

    int checkYatzy(std::array<int, 5> dice_array){
        int value = 0;

        if( dice_array[0] == dice_array[1] &&
            dice_array[0] == dice_array[2] &&
            dice_array[0] == dice_array[3] &&
            dice_array[0] == dice_array[4]){
                value = 50;
            }
        value = markNotEmpty(value);
        return value;
    }
    int calcTotalScore(){
        int total = 0;
        for(int i = 0; i < 16; ++i){
            //jätetään -1 arvot huomioimatta tulostaulusta
            if(score_array[i] > 0){
                total += score_array[i];
            }
        }
        return total;
    }
};

struct Player : Score{
    std::string name;
    int id;/*
    int total_score = 0;

    void print(){
        std::cout << "Player " << id << " - " << name << "'s score: ";
        std::cout << total_score << "\n";
    }*/
};

int getPlayerCount(){
    std::cout << "How many players play (max = 8): ";
    int player_count;
    std::cin >> player_count;

    if(player_count > 0 && player_count < 9)
    {
        return player_count;
    }else{
        getPlayerCount();
    }    
}

Player* makePlayer(int i){
    Player* p;
    p->id = i;

    do{
        std::cout << "Give 1-7 character name for player " << i << ": ";
        std::cin >> p->name;
        
        if(p->name.size() > 7){
            std::cout << "Name is over 7 characters!\n";
        }
    }while(p->name.size() > 7);

    return p;
}

class Dices{
    public:        
        std::array<int, 5> dice_array;

        Dices(){
            int rand();
            srand(time(NULL));
        }

        int rollDice(){            
            int value = rand() % 6 + 1;
            return value;
        }

        void throwAll(){
            for(int i = 0; i < 5; ++i){
                int num = rand() % 6 + 1;
                dice_array[i] = num;                
            }
        }

        void printDices(){            
            std::cout << "Dices: ";

            for(int i = 0; i < 5; ++i){
                std::cout << dice_array[i];
            }
            std::cout << "\n";
        }

        std::string lockDices(){
            std::string word = "";
            std::string lock_word = "";
            bool no_bad_chars = true;

            std::cout << "Keep:  ";
            std::cin >> word;

            if(word == "a" || word == "A"){
                word = "KKKKK";
            }

            //muutetaan kaikki kirjaimet isoiksi
            for(int i = 0; i < word.size(); ++i){
                lock_word += toupper(word[i]);
            }

            //tarkastetaan Keep ja Roll
            for(int i = 0; i < lock_word.size(); ++i){
                if(lock_word[i] != 'K' && lock_word[i] != 'R'){
                    no_bad_chars = false;
                }
            }

            if(lock_word.size() == 5 && no_bad_chars){
                return lock_word;
            }else{
                std::cout << "Error! Choose dices again.\n";
                lockDices();
            }
        }

        int rollDices(std::string lock_word){
            for(int i = 0; i < 5; ++i){
                if(lock_word[i] == 'R'){
                    dice_array[i] = rollDice();
                }
            }
            //jos kaikki nopat on lukittu ei enää heitetä seuraavalla vuorolla
            if(lock_word == "KKKKK"){
                return 2;
            }
            return 1;
        }

        ~Dices(){}
    protected:
        //std::array<int, 5> dice_array;
};

void PlayerTurn(std::vector<Player*> p, Dices dices, int i){
    std::cout << "Write K/k to keep and R/r to roll again, example. \"krrkr\"\n";
    std::cout << "or just A/a to keep all dices.\n\n";
    std::cout << p[i]->name << "'s turn\n";

    dices.throwAll();
    dices.printDices();

    int rolls_left = 2;
    while(rolls_left > 0){
        rolls_left -= dices.rollDices(dices.lockDices());
        dices.printDices();
    }
/*  
    dices.rollDices(dices.lockDices());
    dices.printDices();

    dices.rollDices(dices.lockDices());
    dices.printDices();
*/
    int chosen;

    //tarkastetaan ettei tulospaikkaa ole jo täytetty
    while(true){        
        std::cout << "Choose 1-16 where points go: ";
        std::cin >> chosen;
        --chosen;
        if(chosen >= 0 && chosen <= 15 && chosen != 6){
            if(p[i]->score_array[chosen] == 0){
                break;
            }else{
                std::cout << "Place " << chosen + 1 << " is already filled!\n";
            }
        }        
    }

    switch(chosen){
        case 0:                             
            p[i]->score_array[chosen] = p[i]->checkAces(dices.dice_array);
            break;
        case 1:
            p[i]->score_array[chosen] = p[i]->checkTwos(dices.dice_array);
            break;
        case 2:
            p[i]->score_array[chosen] = p[i]->checkThrees(dices.dice_array);
            break;
        case 3:
            p[i]->score_array[chosen] = p[i]->checkFours(dices.dice_array);
            break;
        case 4:
            p[i]->score_array[chosen] = p[i]->checkFives(dices.dice_array);
            break;
        case 5:
            p[i]->score_array[chosen] = p[i]->checkSixes(dices.dice_array);
            break;
        case 6:
            std::cout << "meh\n";
            break;
        case 7:
            p[i]->score_array[chosen] = p[i]->checkPair(dices.dice_array);
            break;
        case 8:
            p[i]->score_array[chosen] = p[i]->checkTwoPairs(dices.dice_array);
            break;
        case 9:
            p[i]->score_array[chosen] = p[i]->checkThreeOfK(dices.dice_array);
            break;
        case 10:
            p[i]->score_array[chosen] = p[i]->checkFourOfK(dices.dice_array);
            break;
        case 11:
            p[i]->score_array[chosen] = p[i]->checkSmallStraight(dices.dice_array);
            break;
        case 12:
            p[i]->score_array[chosen] = p[i]->checkLargeStraight(dices.dice_array);
            break;
        case 13:
            p[i]->score_array[chosen] = p[i]->checkFullHouse(dices.dice_array);
            break;
        case 14:
            p[i]->score_array[chosen] = p[i]->checkChange(dices.dice_array);
            break;
        case 15:
            p[i]->score_array[chosen] = p[i]->checkYatzy(dices.dice_array);
            break;
    }

    //tarkastetaan aina vuoron lopussa yläpuolen bonuspisteet
    p[i]->score_array[6] = p[i]->checkTotalUpperSection();
}

void printScoreBoard(std::vector<Player*> p){
    std::system("clear");
    std::cout << "\t\t\t";    
    for(int i = 0; i < p.size(); ++i){
        std::cout << p[i]->name << "\t";
    }
    std::cout << "\n";

    //tulostetaan sanat
    for(int j = 0; j < 17; ++j){
        if(j != 6 && j != 16){
            //tasataan miinusmerkki yksinumeroisiin
            if(j < 9){
                std::cout << j+1 << "  - " << p[0]->score_string[j] << "\t"; 
            }else{            
                std::cout << j+1 << " - " << p[0]->score_string[j] << "\t";
            }
            //ylimääränen tabulaattori alle 8 kirjaimen stringeille
            if(((p[0]->score_string[j]).size() +3) < 15){
                std::cout << "\t";
            }
        }else{
            //std::cout << "    " << p[0]->score_string[j] << "\t\t";
            std::cout << p[0]->score_string[j] << "\t\t";
        }        

        //tulostaa luvun
        for(int i = 0; i < p.size(); ++i){
            if(p[i]->score_array[j] == 0){
                //std::cout << "" << "\t";
                std::cout << "\t";
            }else if(p[i]->score_array[j] < 0){
                std::cout << "-" << "\t";            
            }else{
                std::cout << p[i]->score_array[j] << "\t";
            }
        }
        std::cout << "|\n";
    }

    //tulostaulun alareuna erikseen
    std::cout << "------------------------";
    for(int i = 0; i < p.size(); ++i){
        std::cout << "--------";
    }
    std::cout << "-\n";
}

void calcTotalPoints(std::vector<Player*> p){
    for(int i = 0; i < p.size(); ++i){
        p[i]->score_array[16] = p[i]->calcTotalScore();
    }
}

void showWinner(std::vector<Player*> p){
    int biggest = p[0]->score_array[16];

    //haetaan suurimmat loppupisteet
    for(int i = 0; i < p.size(); ++i){
        if(p[i]->score_array[16] > biggest){
            biggest = p[i]->score_array[16];
        }
    }
    //verrataan parasta lopputulosta kaikkiin kaksois- tai kolmoisvoiton varalta
    int winner_count = 0;
    std::cout << "CONGURATULATIONS TO ";
    for(int i = 0; i < p.size(); ++i){
        if(p[i]->score_array[16] == biggest){
            if(winner_count > 0){
                std::cout << " & ";
            }
            std::cout << p[i]->name;
            ++winner_count;
        }
    }
    std::cout << "!!!!!!\n";
}

void printMenu(){
    std::cout << "--------------------------------------------------------------\n";
    std::cout << "|                                                            |\n";
    std::cout << "|       Welcome to scandinavian version of Yahtzee.          |\n";
    std::cout << "|                                                            |\n";
    std::cout << "| Diffence to normal version is that if upperpart (one's,    |\n";
    std::cout << "| two's, three's, etc.) sum is over 63, that player will     |\n";
    std::cout << "| get 50 points for free and game gets little more tactical. |\n";
    std::cout << "|                                                            |\n";
    std::cout << "| How to play:                                               |\n";
    std::cout << "| 1. Write how many player's play                            |\n";
    std::cout << "| 2. Write names of each player                              |\n";
    std::cout << "| 3. Play!                                                   |\n";
    std::cout << "|                                                            |\n";
    std::cout << "--------------------------------------------------------------\n";
}

int main()
{
    printMenu();

    Dices dices;
    std::vector<Player*> players = {};

    int player_count = getPlayerCount();
    int turn_max = 15;
    int turn = 0;

    for(int i = 1; i <= player_count; ++i){
        Player* p = new Player;
        p = makePlayer(i);
        players.push_back(p);
    }

    //pääluuppi
    for(turn = 0; turn < turn_max; ++turn){
        for(int i = 0; i < player_count; ++i){
            printScoreBoard(players);
            PlayerTurn(players, dices, i);
        }
    }    
    
    calcTotalPoints(players);
    printScoreBoard(players);
    showWinner(players);

    return 0;
}