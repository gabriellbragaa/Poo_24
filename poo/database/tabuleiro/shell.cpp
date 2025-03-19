#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

class Player{

private:
int label;
int pos;
int free;

public:

    Player(int label): label(label), pos(0), free(true) {}

    bool isFree()  {
        return free;
    }
    
    string toString()  {
        ostringstream oss;
        oss << "Player " << label << " | Position: " << pos << " | " 
            << (free ? "Free" : "Trapped");
        return oss.str();
    }
    int getLabel(){
        return label;
    }
    int getPos(){
        return pos;
    }
    void setPos(int pos){
        this -> pos = pos ;
    }
    void setFree(int free){
        this -> free = free ;
    }
};

class Board{

private:

vector<int> trapList;
vector<Player> players;

int boardSize;
bool gameOver;
int currentPlayer;



public:

    Board(int nPlayers, int boardSize) : trapList(), players(),  boardSize(boardSize), gameOver(false), currentPlayer(0){
        for(int i = 1; i <= nPlayers; ++i) {
            players.emplace_back(i);
            }
    }
    void addTrap(int pos){
        trapList.push_back(pos); // adiciona um ultimo elemento ao vetor // armadilha 
    }


void rollDice(int value) {
        if (gameOver) {
            cout << "game is over" << endl;
            return;
        }
        
        Player& player = players[currentPlayer];
        
        if (!player.isFree()) {
            if (value % 2 == 0) {
                player.setFree(true);
                cout << "player" << player.getLabel() << " se libertou" << endl;
            } else {
                cout << "player" << player.getLabel() << " continua preso" << endl;
            }
        } else {
            int newPos = player.getPos() + value;
            if (newPos >= boardSize) {
                cout << "player" << player.getLabel() << " ganhou" << endl;
                gameOver = true;
                return;
            }
            player.setPos(newPos);
            cout << "player" << player.getLabel() << " andou para " << newPos << endl;
            
            for (int trap : trapList) {
                if (newPos == trap) {
                    player.setFree(false);
                    cout << "player" << player.getLabel() << " caiu em uma armadilha" << endl;
                    break;
                }
            }
        }
        
        currentPlayer = (currentPlayer + 1) % players.size();
    }
    void ponto(string& board) {
    // Verifica se o último caractere da string é válido
    if (board.size() <= static_cast<size_t>(boardSize) && board.back() != 'x' && (board.back() < '1' || board.back() > '9')) {
        board += '.'; // Adiciona um ponto extra se necessário
    }
}

    void show()  {
    vector<string> playerBoards(players.size(), string(boardSize, '.'));
    string trapBoard(boardSize, '.');

    // Posiciona os jogadores nos seus respectivos tabuleiros
    for ( auto& player : players) {
        if (player.getPos() < boardSize) {
            playerBoards[player.getLabel() - 1][player.getPos()] = '0' + player.getLabel();
        }
    }

    // Posiciona as armadilhas
    for (int trap : trapList) {
        if (trap < boardSize) {
            trapBoard[trap] = 'x';
        }
    }
  

       // Imprime os tabuleiros dos jogadores
    for (size_t i = 0; i < players.size(); i++) {
        if ( i < players.size()){}
            ponto(playerBoards[i]);
            cout << "player" << i + 1 << ": " << playerBoards[i]  << endl;
            
}
         ponto(trapBoard);  // Passa o boardSize
            cout << "traps__: " << trapBoard << endl;
                

    }



};


int main() {

    Board board(2,10);
    while(true) {
        string line, cmd;
        getline(cin, line);
        cout << "$" << line << endl;

        stringstream ss(line);
        ss >> cmd;

        if (cmd == "end") {
            break;
        } else if (cmd == "init") {
             int nPlayers, size;
             ss >> nPlayers >> size;
             board = Board(nPlayers, size);
        } else if (cmd == "addTrap") {
             int pos;
             ss >> pos;
            board.addTrap(pos);
        } else if (cmd == "roll") {
             int value;
             ss >> value;
             board.rollDice(value);
        } else if (cmd == "show") {
            board.show();
        } else {
            cout << "fail: command not found" << endl;
        }

    }
}
