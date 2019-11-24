//#include<iostream>


#include <string>
#include "../headers/Thread.h"


using namespace std;

int main(int argc,char **argv){


    if(argc > 1 &&strcmp(argv[1], "dos") == 0)
    {// DoS
        /*
         * argv[1] = Auth Port, argv[2] = Login Port, argv[3] = IP
         */
        /*
        const char* auth_port = argv[1];
        const char* login_port = argv[2];
        const char* ip = argv[3];


        bool client_tst = true;
        if (client_tst) {
            auto com = new Communication();
            com->sendMsg(ip, stoi(auth_port), "Mazen/123");
            com->sendMsg(ip, stoi(login_port), "Mazen/123");
        }
        else {
            auto dos = new DoS(ip, stoi(auth_port), stoi(login_port));
            dos->runAuthThread();
            dos->runLoginThread();
            dos->join();
        }*/
    } else
    {
        int reqNum = -1 ;
        string serverName;
        int image_id;
        //srand(time(0));
        //int r = rand()%((65535 - 4040) + 1) + 4040;

        Thread * thrd = new Thread(false , true ,  reqNum ,image_id,  serverName,true,4040); //server thread

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
                Thread * thrd = new Thread(true , false ,  reqNum , image_id ,  serverName,false,4040 ); //client thread

            }

        }

    }
    return 0;
}

