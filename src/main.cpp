

#include<iostream>

#include "../headers/Thread.h"
#include "../headers/Peer.h"
#include "../headers/DoS.h"

using namespace std;

int main(int argc, char **argv){

    if(argc > 1 &&strcmp(argv[2], "dos") == 0) {// DoS
        /*
         * argv[1] = DOS_IP
         */
        const char* ip = argv[1];


        bool client_tst = true;
        if (client_tst) {
            auto peer = new Peer("127.0.0.2", "Mazen");
            peer->authenticate("Mazen", "123", ip);

            /*
            auto com = new Communication();
            com->sendMsg(ip, AUTH_PORT, "Mazen/123");
            com->sendMsg(ip, LOGIN_PORT, "Mazen/123");*/

        }
        else {
            auto dos = new DoS(ip);
            dos->runAuthThread();
            //dos->runLoginThread();
            dos->join();
        }
    }
        /*
    else {
        int reqNum = -1 ;
        string serverName;
        int image_id;

        Thread * thrd = new Thread(false , true ,  reqNum ,image_id,  serverName); //server thread

        while (1)
        {
            reqNum = -1 ;
            bool cli = false ;
            string h , p ;


            cout << "Do You want a Client Thread? ";
            cin >> cli;
            if (cli == true) {

                cout <<"Enter Request Number";
                cin >> reqNum ;
                if (reqNum == 2 ||reqNum == 3 ) {
                    cout << "Which Picture would you like to view ? ";
                    cin >> image_id;
                }
                else {
                    cout << "Enter User Requested ";
                    cin >> serverName;
                }
                Thread * thrd = new Thread(true , false ,  reqNum , image_id ,  serverName ); //client thread

            }

        }

    }
         */
    return 0;
}

