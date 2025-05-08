#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

struct square{
    int piece;
    bool whiteatk;
    bool blackatk;
    //0 for unoccupied, 1 white pawn, 2 white bishop, 3 white knight, 4 white rook, 5 white queen, 6 white king
    //                  7 black pawn  8               9               10            11             12 black king
};
struct node {
    int datax;
    int datay;
    node* next;
    node(int val, int val2) : datax(val),datay(val2), next(nullptr) {}
};
class adjlist {
    public:
        node* head;

        adjlist() : head(nullptr) {}
    
        // Function to insert a node at the beginning
        void insert(int valx, int valy) {
            node* newNode = new node(valx, valy);
            newNode->next = head;
            head = newNode;
        }
    

        // Function to display the linked list
        void display() {
            node* temp = head;
            while (temp != nullptr) {
                std::cout << temp->datax << " -> ";
                temp = temp->next;
            }
            std::cout << "nullptr" << std::endl;
        }
        ~adjlist()
        {
            node* current = head;
            while( current != 0 ) {
                node* next = current->next;
                delete current;
                current = next;
            }
            head = nullptr;
       }
    };

class game{
    public:
    square board[8][8];
    adjlist** moves;
    bool playerturn;
    game(){
        this->moves = new adjlist*[8];
        for(int i = 0; i < 8; i++){
            moves[i] = new adjlist[8];
        }
    }
    void displayboard(){
        system("cls");
        bool flag = true;
        cout<<"chess\n\n\n";
        cout<<" _______________\n";
        cout<<"8 |";
        for(int x = 0; x < 8; x ++){
            if(board[x][7].piece == 0){
                if(flag == true){
                    cout<<"_";
                }
                else{cout<<"#";
                }
            }
            else{cout<<board[x][7].piece;}
            flag = !flag;
        }
        cout<<"|\n";

        cout<<"7 |";
        for(int x = 0; x < 8; x ++){
            if(board[x][6].piece == 0){
                if(flag == true){
                    cout<<"_";
                }
                else{cout<<"#";
                }
            }
            else{cout<<board[x][6].piece;}
            flag = !flag;
        }
        cout<<"|\n";

        cout<<"6 |";
        for(int x = 0; x < 8; x ++){
            if(board[x][5].piece == 0){
                if(flag == true){
                    cout<<"_";
                }
                else{cout<<"#";
                }
            }
            else{cout<<board[x][5].piece;}
            flag = !flag;
        }
        cout<<"|\n";

        cout<<"5 |";
        for(int x = 0; x < 8; x ++){
            if(board[x][4].piece == 0){
                if(flag == true){
                    cout<<"_";
                }
                else{cout<<"#";
                }
            }
            else{cout<<board[x][4].piece;}
            flag = !flag;
        }
        cout<<"|\n";

        cout<<"4 |";
        for(int x = 0; x < 8; x ++){
            if(board[x][3].piece == 0){
                if(flag == true){
                    cout<<"_";
                }
                else{cout<<"#";
                }
            }
            else{cout<<board[x][3].piece;}
            flag = !flag;
        }
        cout<<"|\n";

        cout<<"3 |";
        for(int x = 0; x < 8; x ++){
            if(board[x][2].piece == 0){
                if(flag == true){
                    cout<<"_";
                }
                else{cout<<"#";
                }
            }
            else{cout<<board[x][2].piece;}
            flag = !flag;
        }
        cout<<"|\n";
        cout<<"2 |";
        for(int x = 0; x < 8; x ++){
            if(board[x][1].piece == 0){
                if(flag == true){
                    cout<<"_";
                }
                else{cout<<"#";
                }
            }
            else{cout<<board[x][1].piece;}
            flag = !flag;
        }
        cout<<"|\n";
        cout<<"1 |";
        for(int x = 0; x < 8; x ++){
            if(board[x][0].piece == 0){
                if(flag == true){
                    cout<<"_";
                }
                else{cout<<"#";
                }
            }
            else{cout<<board[x][0].piece;}
            flag = !flag;
        }
        cout<<"|\n";
        cout<<"   a b c d e f g h\n\n";
    }
    void turn(bool &whitecheck, bool &blackcheck, bool &whitecheckmate, bool &blackcheckmate){
        string location;
        int x, y, oldx, oldy;
        bool flag, outerflag;
        if(playerturn == true){
            do{
                outerflag = true;
                do{
                    flag = true;
                    cout<<"whites turn\n\n\nselect the location of the piece that you want to move: ";
                    cin>>location;
                    x = static_cast<int>(location[0]);
                    if(x < 95){x = x - 65;}
                    else{x = x - 97;}
                    if( x < -1 || x > 7){flag = false;};
                    y = static_cast<int>(location[1]);
                    y--;
                    if( y < -1 || y > 7){flag = false;};
                    if(board[x][y].piece == 0 || board[x][y].piece > 6){flag = false;}
                    if(flag == false){cout<<"incorrect input or invalid piece selected, try again";}
                }while(!flag);
                oldx = x;
                oldy = y;
                cout<<"\n\nselect where you want to move it, possible locations are:\n ";
                moves[x][y].display();
                cout<<"you may also choose to go back and choose another piece by entering 99\n\n";
                cin>>location;
                x = static_cast<int>(location[0]);
                if(x < 95){x = x - 65;}
                else{x = x - 97;}
                if( x < -1 || x > 7){outerflag = false;};
                y = static_cast<int>(location[1]);
                y--;
                if( y < -1 || y > 7){outerflag = false;};
                node *mynode = moves[x][y].head;
                outerflag = false;
                while(mynode){
                    if(x == mynode->datax && y == mynode->datay){
                        outerflag = true;
                        mynode = nullptr;
                    }
                    else{mynode = mynode->next;}
                }
                if(outerflag == false){cout<<"incorrect space selected, try again";}
            }while(!outerflag);
            board[x][y].piece = board[oldx][oldy].piece;
            board[oldx][oldy].piece = 0;
            playerturn = false;
        }
        else{
            do{
                outerflag == true;
                do{
                    flag = true;
                    cout<<"blacks turn\n\n\nselect the location of the piece that you want to move: ";
                    cin>>location;
                    x = static_cast<int>(location[0]);
                    if(x < 95){x = x - 65;}
                    else{x = x - 97;}
                    if( x < -1 || x > 7){flag = false;};
                    y = static_cast<int>(location[1]);
                    y--;
                    if( y < -1 || y > 7){flag = false;};
                    if(board[x][y].piece < 7){flag = false;}
                    if(flag == false){cout<<"incorrect input or invalid piece selected, try again";}
                }while(!flag);
                oldx = x;
                oldy = y;
                cout<<"select where you want to move it, possible locations are:\n ";
                moves[x][y].display();
                cout<<"you may also choose to go back and choose another piece by entering 99\n\n";
                cin>>location;
                x = static_cast<int>(location[0]);
                if(x < 95){x = x - 65;}
                else{x = x - 97;}
                if( x < -1 || x > 7){outerflag = false;};
                y = static_cast<int>(location[1]);
                y--;
                if( y < -1 || y > 7){outerflag = false;};
                node *mynode = moves[x][y].head;
                outerflag = false;
                while(mynode){
                    if(x == mynode->datax && y == mynode->datay){
                        outerflag = true;
                        mynode = nullptr;
                    }
                    else{mynode = mynode->next;}
                }
                if(outerflag == false){cout<<"incorrect space selected, try again";}
            }while(!outerflag);
            board[x][y].piece = board[oldx][oldy].piece;
            board[oldx][oldy].piece = 0;
            playerturn = true;
        }
    }

    void initializeboard(){
        playerturn = true; // whites turn
        for(int x = 2; x <6; x++){
            for(int y = 0; y < 8; y++){
                board[x][y].piece = 0;
            }
        }
        for(int x = 0; x < 8; x++){
            board[1][x].piece = 1;
            board[6][x].piece = 7;
            for(int y = 0; y < 8; y++){
                board[x][y].whiteatk= false;
                board[x][y].blackatk= false;
            }
        }
        board[0][0].piece = 4;
        board[0][7].piece = 4;
        board[0][1].piece = 3;
        board[0][6].piece = 3;
        board[0][2].piece = 2;
        board[0][5].piece = 2;
        board[0][3].piece = 5;
        board[0][4].piece = 6;

        board[7][0].piece = 4;
        board[7][7].piece = 4;
        board[7][1].piece = 3;
        board[7][6].piece = 3;
        board[7][2].piece = 2;
        board[7][5].piece = 2;
        board[7][3].piece = 5;
        board[7][4].piece = 6;
    }
    void adjlistupdate(bool &whitecheck, bool &blackcheck, bool &whitecheckmate, bool &blackcheckmate){
        bool flag1 , flag2 , flag3 , flag4 , flag5 , flag6 , flag7 , flag8 ;
        int wx, wy, bx, by;
        for(int x = 0; x <8; x++){
            for(int y = 0; y < 8; y++){
                board[x][y].blackatk = false;
                board[x][y].whiteatk = false;
            }
        }
        for(int i = 0; i < 8; ++i){
            delete[] moves[i];
        }
        delete[] moves;
        this->moves = new adjlist*[8];
        for(int i = 0; i < 8; i++){
            moves[i] = new adjlist[8];
        }
        for(int x = 0; x <8; x++){
            for(int y = 0; y < 8; y++){
                flag1 = true, flag2 = true, flag3 = true, flag4 = true, flag5 = true, flag6 = true, flag7 = true, flag8 = true;
                switch (board[x][y].piece){
                    case 1:
                        //white pawn
                        if(board[x+1][y].piece == 0 && x < 7){
                            moves[x][y].insert(x+1, y);
                            if(x == 1){
                                if(board[x+2][y].piece == 0){
                                    moves[x][y].insert(x+2, y);
                                }
                            }
                        }
                        if(board[x+1][y-1].piece >6){moves[x][y].insert(x+1, y-1);}
                        if(board[x+1][y+1].piece >6){moves[x][y].insert(x+1, y+1);}
                        board[x+1][y+1].whiteatk = true;
                        board[x+1][y-1].whiteatk = true;
                        break;
                    case 2:
                        // white bishop
                        while(flag1 || flag2|| flag3|| flag4){
                            int n = 1;
                            //up right
                            if(flag1){
                                if(board[x + n][y + n].piece > 0|| x + n  > 7 || y + n  > 7){
                                    flag1 = false;
                                }
                                if((board[x + n][y + n].piece == 0 || board[x + n][y + n].piece > 6)&& x + n < 8 && y + n < 8){
                                    moves[x][y].insert(x + n, y + n);
                                    board[x+n][y+n].whiteatk = true;
                                }
                            }
                            //up left
                            if(flag2){
                                if(board[x + n][y - n].piece > 0|| x + n  > 7 || y - n < 0){
                                    flag2 = false;
                                }
                                if((board[x + n][y - n].piece == 0 || board[x + n][y - n].piece > 6)&& x + n < 8 && y - n > -1){
                                    moves[x][y].insert(x + n, y - n);
                                    board[x+n][y-n].whiteatk = true;
                                }
                            }
                            //down right
                            if(flag3){
                                if(board[x - n][y + n].piece > 0|| x - n  < 0 || y + n  > 7){
                                    flag1 = false;
                                }
                                if((board[x - n][y + n].piece == 0 || board[x - n][y + n].piece > 6)&& x - n > -1 && y + n < 8){
                                    moves[x][y].insert(x - n, y + n);
                                    board[x-n][y+n].whiteatk = true;
                                }
                            }
                            //down left
                            if(flag4){
                                if(board[x - n][y - n].piece > 0|| x - n  < 0 || y - n < 0){
                                    flag2 = false;
                                }
                                if((board[x - n][y - n].piece == 0 || board[x - n][y - n].piece > 6)&& x - n > -1 && y - n > -1){
                                    moves[x][y].insert(x - n, y - n);
                                    board[x-n][y-n].whiteatk = true;
                                }
                            }
                            n++;
                        }
                        break;
                    case 3:
                        //white knight
                            if((board[x + 2][y + 1].piece > 6 || board[x + 2][y + 1].piece == 0)&&(x + 2 < 8 && y + 1 < 8)){moves[x][y].insert(x+2, y+1);
                                board[x+2][y+1].whiteatk = true;
                            }
                            if((board[x + 2][y - 1].piece > 6 || board[x + 2][y - 1].piece == 0)&&(x + 2 < 8 && y - 1 > -1)){moves[x][y].insert(x+2, y-1);
                                board[x+2][y-1].whiteatk = true;
                            }

                            if((board[x - 2][y + 1].piece > 6 || board[x - 2][y + 1].piece == 0) &&(x - 2 > -1 && y + 1 < 8)){moves[x][y].insert(x+2, y+1);
                                board[x-2][y+1].whiteatk = true;
                            }
                            if((board[x - 2][y - 1].piece > 6 || board[x - 2][y - 1].piece == 0)&&(x - 2 > -1 && y - 1 > -1)){moves[x][y].insert(x+2, y-1);
                                board[x-2][y-1].whiteatk = true;
                            }

                            if((board[x + 1][y + 2].piece > 6 || board[x + 1][y + 2].piece == 0) &&(x + 1 < 8 && y + 2 < 8)){moves[x][y].insert(x+2, y+1);
                                board[x+1][y+2].whiteatk = true;
                            }
                            if((board[x - 1][y + 2].piece > 6 || board[x - 1][y + 2].piece == 0)&&(x - 1 >-1 && y + 2 < 8)){moves[x][y].insert(x+2, y-1);
                                board[x-1][y+2].whiteatk = true;
                            }

                            if((board[x + 1][y - 2].piece > 6 || board[x + 1][y - 2].piece == 0) &&(x + 1 < 8 && y - 2 > -1)){moves[x][y].insert(x+2, y+1);
                                board[x+1][y-2].whiteatk = true;
                            }
                            if((board[x - 1][y - 2].piece > 6 || board[x - 1][y - 2].piece == 0)&&(x - 1 >-1 && y - 2 > -1)){moves[x][y].insert(x+2, y-1);
                                board[x-1][y-2].whiteatk = true;
                            }
                        break;
                    case 4:
                        //white rook

                        while(flag1 || flag2|| flag3|| flag4){
                            int n = 1;
                            //up
                            if(flag1){
                                if(board[x + n][y].piece > 0|| x + n  > 7){
                                    flag1 = false;
                                }
                                if((board[x + n][y].piece == 0 || board[x + n][y].piece > 6)&& x + n < 8){
                                    moves[x][y].insert(x + n,y);
                                    board[x + n][y].whiteatk = true;
                                }
                            }
                            //right
                            if(flag2){
                                if(board[x][y + n].piece > 0|| y + n  > 7){
                                    flag2 = false;
                                }
                                if((board[x][y + n].piece == 0 || board[x + n][y].piece > 6)&& y + n < 8){
                                    moves[x][y].insert(x,y + n);
                                    board[x][y+ n].whiteatk = true;
                                }
                            }
                            //down
                            if(flag3){
                                if(board[x - n][y].piece > 0|| x - n < 0){
                                    flag3 = false;
                                }
                                if((board[x - n][y].piece == 0 || board[x + n][y].piece > 6)&& x - n > -1){
                                    moves[x][y].insert(x - n,y);
                                    board[x - n][y].whiteatk = true;
                                }
                            }
                            //left
                            if(flag4){
                                if(board[x][y - n].piece > 0|| y - n  < 0){
                                    flag4 = false;
                                }
                                if((board[x][y + n].piece == 0 || board[x + n][y].piece > 6)&& y + n > -1){
                                    moves[x][y].insert(x,y + n);
                                    board[x][y- n].whiteatk = true;
                                }
                            }
                            n++;
                        }
                        break;
                    case 5:
                        //white queen

                        while(flag1 || flag2|| flag3|| flag4 || flag5 || flag6 || flag7 || flag8){
                            int n = 1;
                            //up right
                            if(flag1){
                                if(board[x + n][y + n].piece > 0|| x + n  > 7 || y + n  > 7){
                                    flag1 = false;
                                }
                                if((board[x + n][y + n].piece == 0 || board[x + n][y + n].piece > 6)&& x + n < 8 && y + n < 8){
                                    moves[x][y].insert(x + n, y + n);
                                    board[x + n][y + n].whiteatk = true;
                                }
                            }
                            //up left
                            if(flag2){
                                if(board[x + n][y - n].piece > 0|| x + n  > 7 || y - n < 0){
                                    flag2 = false;
                                }
                                if((board[x + n][y - n].piece == 0 || board[x + n][y - n].piece > 6)&& x + n < 8 && y - n > -1){
                                    moves[x][y].insert(x + n, y - n);
                                    board[x + n][y - n].whiteatk = true;
                                }
                            }
                            //down right
                            if(flag3){
                                if(board[x - n][y + n].piece > 0|| x - n  < 0 || y + n  > 7){
                                    flag3 = false;
                                }
                                if((board[x - n][y + n].piece == 0 || board[x - n][y + n].piece > 6)&& x - n > -1 && y + n < 8){
                                    moves[x][y].insert(x - n, y + n);
                                    board[x - n][y + n].whiteatk = true;
                                }
                            }
                            //down left
                            if(flag4){
                                if(board[x - n][y - n].piece > 0|| x - n  < 0 || y - n < 0){
                                    flag4 = false;
                                }
                                if((board[x - n][y - n].piece == 0 || board[x - n][y - n].piece > 6)&& x - n > -1 && y - n > -1){
                                    moves[x][y].insert(x - n, y - n);
                                    board[x - n][y - n].whiteatk = true;
                                }
                            }
                            if(flag5){
                                if(board[x + n][y].piece > 0|| x + n  > 7){
                                    flag5 = false;
                                }
                                if((board[x + n][y].piece == 0 || board[x + n][y].piece > 6)&& x + n < 8){
                                    moves[x][y].insert(x + n,y);
                                    board[x + n][y].whiteatk = true;
                                }
                            }
                            //right
                            if(flag6){
                                if(board[x][y + n].piece > 0|| y + n  > 7){
                                    flag6 = false;
                                }
                                if((board[x][y + n].piece == 0 || board[x][y+n].piece > 6)&& y + n < 8){
                                    moves[x][y].insert(x,y + n);
                                    board[x][y + n].whiteatk = true;
                                }
                            }
                            //down
                            if(flag7){
                                if(board[x - n][y].piece > 0|| x - n < 0){
                                    flag7 = false;
                                }
                                if((board[x - n][y].piece == 0 || board[x - n][y].piece > 6)&& x - n > -1){
                                    moves[x][y].insert(x - n,y);
                                    board[x - n][y].whiteatk = true;
                                }
                            }
                            //left
                            if(flag8){
                                if(board[x][y - n].piece > 0|| y - n  < 0){
                                    flag8 = false;
                                }
                                if((board[x][y - n].piece == 0 || board[x][y - n].piece > 6)&& y + n > -1){
                                    moves[x][y].insert(x,y + n);
                                    board[x][y - n].whiteatk = true;
                                }
                            }
                            n++;
                        }
                        break;
                    case 6:
                        //white king
                        wx = x;
                        wy = y;
                        break;
                    case 7:
                        //black pawn
                        if(board[x-1][y].piece == 0 && x >0 ){
                            moves[x][y].insert(x-1, y);
                            if(x == 6){
                                if(board[x-2][y].piece == 0){
                                    moves[x][y].insert(x-2, y);
                                }
                            }
                        }
                        if(board[x-1][y-1].piece <7){moves[x][y].insert(x-1, y-1);}
                        if(board[x-1][y+1].piece <7){moves[x][y].insert(x-1, y+1);}
                        board[x-1][y+1].blackatk = true;
                        board[x-1][y-1].blackatk = true;
                        break;
                    case 8:
                        //black bishop

                        while(flag1 || flag2|| flag3|| flag4){
                            int n = 1;
                            //up right
                            if(flag1){
                                if(board[x + n][y + n].piece > 0|| x + n  > 7 || y + n  > 7){
                                    flag1 = false;
                                }
                                if((board[x + n][y + n].piece == 0 || board[x + n][y + n].piece < 7)&& x + n < 8 && y + n < 8){
                                    moves[x][y].insert(x + n, y + n);
                                    board[x+n][y+n].blackatk = true;
                                }
                            }
                            //up left
                            if(flag2){
                                if(board[x + n][y - n].piece > 0|| x + n  > 7 || y - n  < 0){
                                    flag2 = false;
                                }
                                if((board[x + n][y - n].piece == 0 || board[x + n][y - n].piece < 7)&& x + n < 8 && y - n > -1){
                                    moves[x][y].insert(x + n, y - n);
                                    board[x+n][y-n].blackatk = true;
                                }
                            }
                            //down right
                            if(flag3){
                                if(board[x - n][y + n].piece > 0|| x - n < 0 || y + n  > 7 ){
                                    flag3 = false;
                                }
                                if((board[x - n][y + n].piece == 0 || board[x - n][y + n].piece < 7)&& x - n > 0 && y + n < 8){
                                    moves[x][y].insert(x - n, y + n);
                                    board[x-n][y+n].blackatk = true;
                                }
                            }
                            //down left
                            if(flag4){
                                if(board[x - n][y - n].piece > 0|| x - n < 0 || y - n < 0){
                                    flag4 = false;
                                }
                                if((board[x - n][y - n].piece == 0 || board[x - n][y - n].piece < 7)&& x - n > -1 && y - n > -1){
                                    moves[x][y].insert(x - n, y - n);
                                    board[x-n][y-n].blackatk = true;
                                }
                            }
                            n++;
                        }
                        break;
                    case 9:
                        //black knight
                        if(board[x + 2][y + 1].piece < 7 &&(x + 2 < 8 && y + 1 < 8)){
                            moves[x][y].insert(x+2, y+1);
                            board[x+2][y+1].blackatk = true;}
                        if(board[x + 2][y - 1].piece < 7 &&(x + 2 < 8 && y - 1 > -1)){
                            moves[x][y].insert(x+2, y-1);
                            board[x+2][y-1].blackatk = true;}

                        if(board[x - 2][y + 1].piece < 7 &&(x - 2 > -1 && y + 1 < 8)){
                            moves[x][y].insert(x+2, y+1);
                            board[x-2][y+1].blackatk = true;}
                        if(board[x - 2][y - 1].piece < 7 &&(x - 2 > -1 && y - 1 > -1)){
                            moves[x][y].insert(x+2, y-1);
                            board[x-2][y-1].blackatk = true;}

                        if(board[x + 1][y + 2].piece < 7 &&(x + 1 < 8 && y + 2 < 8)){
                            moves[x][y].insert(x+2, y+1);
                            board[x+1][y+2].blackatk = true;}
                        if(board[x - 1][y + 2].piece < 7 &&(x - 1 >-1 && y + 2 < 8)){
                            moves[x][y].insert(x+2, y-1);
                            board[x-1][y+2].blackatk = true;}

                        if(board[x + 1][y - 2].piece < 7 &&(x + 1 < 8 && y - 2 > -1)){
                            moves[x][y].insert(x+1, y-2);
                            board[x+1][y-2].blackatk = true;}
                        if(board[x - 1][y - 2].piece < 7 &&(x - 1 >-1 && y - 2 > -1)){
                            moves[x][y].insert(x-1, y-2);
                            board[x-1][y-2].blackatk = true;}
                        break;
                    case 10:
                        //black rook

                        while(flag1 || flag2|| flag3|| flag4){
                            int n = 1;
                            //up
                            if(flag1){
                                if(board[x + n][y].piece > 0|| x + n  > 7){
                                    flag1 = false;
                                }
                                if((board[x + n][y].piece == 0 || board[x + n][y].piece < 7)&& x + n < 8){
                                    moves[x][y].insert(x + n,y);
                                    board[x + n][y].blackatk = true;
                                }
                            }
                            //right
                            if(flag2){
                                if(board[x][y + n].piece > 0|| y + n  > 7){
                                    flag2 = false;
                                }
                                if((board[x][y + n].piece == 0 || board[x][y + n].piece < 7)&& y + n < 8){
                                    moves[x][y].insert(x,y + n);
                                    board[x][y + n].blackatk = true;
                                }
                            }
                            //down
                            if(flag3){
                                if(board[x - n][y].piece > 0|| x - n < 0){
                                    flag3 = false;
                                }
                                if((board[x - n][y].piece == 0 || board[x - n][y].piece < 7)&& x - n > -1){
                                    moves[x][y].insert(x - n,y);
                                    board[x - n][y].blackatk = true;
                                }
                            }
                            //left
                            if(flag4){
                                if(board[x][y - n].piece > 0|| y - n  < 0){
                                    flag4 = false;
                                }
                                if((board[x][y - n].piece == 0 || board[x][y - n].piece < 7)&& y + n > -1){
                                    moves[x][y].insert(x,y + n);
                                    board[x][y - n].blackatk = true;
                                }
                            }
                            n++;
                        
                        }
                        break;
                    case 11:
                        //black queen

                        while(flag1 || flag2|| flag3|| flag4 || flag5 || flag6 || flag7 || flag8){
                            int n = 1;
                            //up right
                            if(flag1){
                                if(board[x + n][y + n].piece > 0|| x + n  > 7 || y + n  > 7){
                                    flag1 = false;
                                }
                                if((board[x + n][y + n].piece == 0 || board[x + n][y + n].piece < 7)&& x + n < 8 && y + n < 8){
                                    moves[x][y].insert(x + n, y + n);
                                    board[x + n][y + n].blackatk = true;
                                }
                            }
                            //up left
                            if(flag2){
                                if(board[x + n][y - n].piece > 0|| x + n  > 7 || y - n < 0){
                                    flag2 = false;
                                }
                                if((board[x + n][y - n].piece == 0 || board[x + n][y - n].piece < 7)&& x + n < 8 && y - n > -1){
                                    moves[x][y].insert(x + n, y - n);
                                    board[x + n][y - n].blackatk = true;
                                }
                            }
                            //down right
                            if(flag3){
                                if(board[x - n][y + n].piece > 0|| x - n  < 0 || y + n  > 7){
                                    flag3 = false;
                                }
                                if((board[x - n][y + n].piece == 0 || board[x - n][y + n].piece < 7)&& x - n > -1 && y + n < 8){
                                    moves[x][y].insert(x - n, y + n);
                                    board[x - n][y + n].blackatk = true;
                                }
                            }
                            //down left
                            if(flag4){
                                if(board[x - n][y - n].piece > 0|| x - n  < 0 || y - n < 0){
                                    flag4 = false;
                                }
                                if((board[x - n][y - n].piece == 0 || board[x - n][y - n].piece < 7)&& x - n > -1 && y - n > -1){
                                    moves[x][y].insert(x - n, y - n);
                                    board[x - n][y - n].blackatk = true;
                                }
                            }
                            if(flag5){
                                if(board[x + n][y].piece > 0|| x + n  > 7){
                                    flag5 = false;
                                }
                                if((board[x + n][y].piece == 0 || board[x + n][y].piece < 7)&& x + n < 8){
                                    moves[x][y].insert(x + n,y);
                                    board[x + n][y].blackatk = true;
                                }
                            }
                            //right
                            if(flag6){
                                if(board[x][y + n].piece > 0|| y + n  > 7){
                                    flag6 = false;
                                }
                                if((board[x][y + n].piece == 0 || board[x][y + n].piece < 7)&& y + n < 8){
                                    moves[x][y].insert(x,y + n);
                                    board[x][y + n].blackatk = true;
                                }
                            }
                            //down
                            if(flag7){
                                if(board[x - n][y].piece > 0|| x - n < 0){
                                    flag7 = false;
                                }
                                if((board[x - n][y].piece == 0 || board[x - n][y].piece < 7)&& x - n > -1){
                                    moves[x][y].insert(x - n,y);
                                    board[x - n][y].blackatk = true;
                                }
                            }
                            //left
                            if(flag8){
                                if(board[x][y - n].piece > 0|| y - n  < 0){
                                    flag8 = false;
                                }
                                if((board[x][y + n].piece == 0 || board[x][y - n].piece < 7)&& y - n > -1){
                                    moves[x][y].insert(x,y + n);
                                    board[x][y - n].blackatk = true;
                                }
                            }
                            n++;
                        }
                        break;
                    case 12:
                        //black king
                        bx= x;
                        by = y;
                        break;
                }

            }
        }
        //white king
        if(board[wx][wy].blackatk){whitecheck = true;}
        if(board[bx][by].whiteatk){blackcheck = true;}
        if(!board[wx + 1][wy].blackatk && wx + 1 < 8){
            moves[wx][wy].insert(wx + 1,wy);
        }
        board[wx + 1][wy + 1].whiteatk = true;
        if(!board[wx + 1][wy + 1].blackatk && wx + 1 < 8 && wy + 1 < 8){
            moves[wx][wy].insert(wx + 1,wy + 1);
        }
        board[wx + 1][wy + 1].whiteatk = true;
        if(!board[wx][wy + 1].blackatk && wy + 1 < 8){
            moves[wx][wy].insert(wx,wy + 1);
        }
        board[wx][wy + 1].whiteatk = true;
        if(!board[wx - 1][wy + 1].blackatk && wx - 1 > -1 && wy + 1 < 8){
            moves[wx][wy].insert(wx - 1,wy + 1);
        }
        board[wx - 1][wy + 1].whiteatk = true;
        if(!board[wx + 1][wy].blackatk && wx - 1 < -1){
            moves[wx][wy].insert(wx + 1,wy);
        }
        board[wx + 1][wy].whiteatk = true;
        if(!board[wx - 1][wy - 1].blackatk && wx - 1 > -1 && wy -1 > -1){
            moves[wx][wy].insert(wx -1,wy -1);
        }
        board[wx - 1][wy - 1].whiteatk = true;
        if(!board[wx][wy - 1].blackatk  && wy - 1 > -1){
            moves[wx][wy].insert(wx,wy - 1);
        }
        board[wx][wy - 1].whiteatk = true;
        if(!board[wx + 1][wy - 1].blackatk && wx + 1 < 8 && wy -1 > -1){
            moves[wx][wy].insert(wx + 1,wy - 1);
        }
        board[wx + 1][wy - 1].whiteatk = true;

        //black king
        if(!board[bx + 1][by].whiteatk && bx + 1 < 8){
            moves[bx][by].insert(bx + 1,by);
        }
        board[bx + 1][by + 1].blackatk = true;
        if(!board[bx + 1][by + 1].whiteatk && bx + 1 < 8 && by + 1 < 8){
            moves[bx][by].insert(bx + 1,by + 1);
        }
        board[bx + 1][by + 1].blackatk = true;
        if(!board[bx][by + 1].whiteatk && by + 1 < 8){
            moves[bx][by].insert(bx,by + 1);
        }
        board[bx][by + 1].blackatk = true;
        if(!board[bx - 1][by + 1].whiteatk && bx - 1 > -1 && by + 1 < 8){
            moves[bx][by].insert(bx - 1,by + 1);
        }
        board[bx - 1][by + 1].blackatk = true;
        if(!board[bx + 1][by].whiteatk && bx - 1 < -1){
            moves[bx][by].insert(bx + 1,by);
        }
        board[bx + 1][by].blackatk = true;
        if(!board[bx - 1][by - 1].whiteatk && bx - 1 > -1 && by -1 > -1){
            moves[bx][by].insert(bx -1,by -1);
        }
        board[bx - 1][by - 1].blackatk = true;
        if(!board[bx][by - 1].whiteatk  && by - 1 > -1){
            moves[bx][by].insert(bx,by - 1);
        }
        board[bx][by - 1].blackatk = true;
        if(!board[bx + 1][by - 1].whiteatk && bx + 1 < 8 && by -1 > -1){
            moves[bx][by].insert(bx + 1,by - 1);
        }
        board[bx + 1][by - 1].blackatk = true;
        if(blackcheck && moves[bx][by].head == nullptr){blackcheckmate = true;}
        if(whitecheck && moves[wx][wy].head == nullptr){whitecheckmate = true;}
    }
    ~game(){
        for(int i = 0; i < 8; ++i){
            delete[] moves[i];
        }
        
        delete[] moves;
    }
};


int main(){
    game mygame;
    mygame.initializeboard();
    string x;
    bool blackcheck, whitecheck, blackcheckmate, whitecheckmate;
    cout<<"begin?";
    cin>>x;
    while(true){
        mygame.adjlistupdate(whitecheck, blackcheck, whitecheckmate, blackcheckmate);
        mygame.displayboard();
        mygame.turn(whitecheck, blackcheck, whitecheckmate, blackcheckmate);
        if(blackcheckmate){cout<<"black has been checkmated, white wins!!"; break;}
        if(whitecheckmate){cout<<"white has been checkmated, black wins!!"; break;}
    }
    return 0;
}
