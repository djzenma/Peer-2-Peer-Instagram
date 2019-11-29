//#include<iostream>


#include <string>
#include "../headers/Thread.h"
#include "../headers/DoS.h"
#include "../headers/Peer.h"


using namespace std;


string getIp(std::string imageId){
    string image = "/Users/owner/CLionProjects/Distributed-Client/images/requested/"+imageId+".jpg";
    std::string output = stega_decode(image);
    stringstream ss(output);
    string  token [3];
    int i =0 ;
    while (getline(ss, token[i], ',')) {
        i++ ;
    }
    int numViews = stoi(token[0]);
    std::string senderPort= token[1];
    std::string senderIp= token[2];
    return senderIp;

}

string getPort(std::string imageId){
    string image = "/Users/owner/CLionProjects/Distributed-Client/images/requested/"+imageId+".jpg";
    std::string output = stega_decode(image);
    stringstream ss(output);
    string  token [3];
    int i =0 ;
    while (getline(ss, token[i], ',')) {
        i++ ;
    }
    int numViews = stoi(token[0]);
    std::string senderPort= token[1];
    std::string senderIp= token[2];
    return senderPort;

}

int main(int argc,char **argv){


    if(argc > 1 && strcmp(argv[2], "dos") == 0)
    {// DoS
        /*
         * argv[1] = Auth Port, argv[2] = Login Port, argv[3] = IP
         */
        const char* dosIp = argv[1];
        bool client_tst = true;
        if (client_tst) {
            auto peer = new Peer("127.0.0.1", "Mazen", dosIp);
            peer->authenticate("Mazen", "123");
        }
        else {
            auto dos = new DoS(dosIp);
            dos->runAuthThread();
            //dos->runLoginThread();
            dos->join();
        }
    }

    /*else
    {
        int reqNum = -1 ;
        string serverName;
        int image_id;
        string toConnectIp = "127.0.0.1" ;
        string toConnectPort = "4040" ;
        int num_views = 0;


        Thread * thrd = new Thread(false , true ,  reqNum ,image_id,true,4040 ,  toConnectIp , toConnectPort , 0); //server thread

        while (1)
        {
            reqNum = -1 ;
            bool cli = false ;

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
                    cout << "Which Picture would you like to update views for ? ";
                    cin >> image_id;
                    cout << "Enter Number of views: ";
                    cin >> num_views;
                }
                Thread * thrd = new Thread(true , false ,  reqNum , image_id ,false,4040 ,  toConnectIp , toConnectPort , num_views); //client thread

            }

        }

    }*/
    return 0;
}