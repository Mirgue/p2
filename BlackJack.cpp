#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;
double add(int num);
int getCard(bool wash);
int printCard(int card);
int player();
void computer(int result);

int win_num = 0, lose_num = 0, even_num = 0;

int main()
{
    srand(time(NULL));
    char YorN; int result;
    while (true){
        cout << "\nWant to play a game(Y/N)?"; //ask whether to play the game.
        cin >> YorN; cin.sync();
        getCard(true); //wash cards.
        if (YorN == 'N' || YorN == 'n'){
            cout << "Your play " << win_num+lose_num+even_num
                 << " game(s), win " << win_num
                 << " game(s), lose " << lose_num << " game(s)." << endl;
            break;}
        if (YorN == 'Y' || YorN == 'y'){
            result = player(); //player's playing.
            if (result>0) computer(result);}} //computer's playing.
    return 0;
}

double add(int num) //calculate the value of a card.
{
    num = num % 13 + 1;
    if (num <= 10) return num;
    else return 0.5;
}

int getCard(bool wash = false) //if (wash == false), wash cards. Otherwise, get a card(just a random number).
{
    int j; bool flag = true;
    static int cardArray[52] = {0}, i = -1;
    if (!wash){
	    i++;
	    do{
	        flag = true;
	        cardArray[i] = rand() % 52;
	        for (j=0; j<i; j++){
	            if (cardArray[j] == cardArray[i]){
                    flag = false; break;}}
	    } while (!flag); // get a card which differs from those gotten before.
	    return cardArray[i];}
    else{
		for (j=0; j<52;j++) cardArray[j] = 0;
		i = -1;
        return 0;}
}

int printCard(int card) //print the name of the card by operating the random number.
{
    int color, number;
    color = card % 4;
    number = card % 13 + 1;
    cout << "  ";
    switch(color){
        case 0: cout << "heart "; break;
        case 1: cout << "diamond "; break;
        case 2: cout << "spade "; break;
        default: cout << "club "; break;}
    if (number >= 2 && number <= 10) cout << number;
    else{
        switch(number){
            case 1: cout << 'A'; break;
            case 11: cout << 'J'; break;
            case 12: cout << 'Q'; break;
            default: cout << 'K'; break;}}
    cout << "  ";
}

int player() //what player does.
{
    int player[11], time = 1, i; double total = 0.0; char flag;
    cout << "\nYour turn:" << endl;
    player[0] = getCard(); printCard(player[0]); total += add(player[0]);
    player[1] = getCard(); printCard(player[1]); total += add(player[1]); // get the beginning two cards.
    while (true){
        cout << endl << " Want another card(Y/N)?" ;
        cin >> flag; cin.sync();
        if (flag == 'N' || flag == 'n') break;
        if (flag == 'Y' || flag == 'y'){//if yes, get another card.
            time++;
            player[time] = getCard();
            for (i = 0; i<= time; i++) printCard(player[i]);
            total += add(player[time]);
            if (total > 21){
                cout << "\nYou lose!" << endl; //if total > 21, lose the game.
                total = 0; time = 0;
                lose_num++;
                break;}}}
    return (total * 100 + time);
}

void computer(int result) // what computer dose.
{
    int player[11], time = 1, i; double total = 0.0;
    cout << "\nComputer's turn:" << endl;
    player[0] = getCard(); printCard(player[0]); total += add(player[0]);
    player[1] = getCard(); printCard(player[1]); total += add(player[1]); //get the beginning two cards.
    while (true){
        time++;
        if (total*100+time > result){
            cout << "\nYou lose!" << endl; //if the value > result, lose the game.
            lose_num++;
            break;}
        else if (total == 21 && total*100+time > result ){
                cout << "\nEVEN!";
                even_num++;}
            else{
                cout << endl;
                player[time] = getCard(); //if not, get another card.
                for (i = 0; i<= time; i++) printCard(player[i]);
                total += add(player[time]);
                if (total > 21){ //if total > 21, win the game.
                    cout << "\nYou win!" << endl;
                    win_num++;
                    break;}}}
}
