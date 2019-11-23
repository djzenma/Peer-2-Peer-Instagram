//#include<iostream>


#include <string>
#include "../headers/Thread.h"


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

    cout << getIp("4")<<endl <<getPort("4")<<endl ;

//
//
//    if(argc > 1 &&strcmp(argv[1], "dos") == 0)
//    {// DoS
//        /*
//         * argv[1] = Auth Port, argv[2] = Login Port, argv[3] = IP
//         */
//        /*
//        const char* auth_port = argv[1];
//        const char* login_port = argv[2];
//        const char* ip = argv[3];
//
//
//        bool client_tst = true;
//        if (client_tst) {
//            auto com = new Communication();
//            com->sendMsg(ip, stoi(auth_port), "Mazen/123");
//            com->sendMsg(ip, stoi(login_port), "Mazen/123");
//        }
//        else {
//            auto dos = new DoS(ip, stoi(auth_port), stoi(login_port));
//            dos->runAuthThread();
//            dos->runLoginThread();
//            dos->join();
//        }*/
//    } else
//    {
//        int reqNum = -1 ;
//        string serverName;
//        int image_id;
//        srand(time(0));
//        int r = rand()%((65535 - 4040) + 1) + 4040;
//        Thread * thrd = new Thread(false , true ,  reqNum ,image_id,  serverName,r ,  toConnectIp , toConnectPort ); //server thread
//        string toConnectPort , toConnectIp ;
//        while (1)
//        {
//            reqNum = -1 ;
//            bool cli = false ;
//            string h , p ;
//
//
//            cout << "Do You want a Client Thread? ";
//            cin >> cli;
//            if (cli == true) {
//
//                cout <<"Enter Request Number";
//                cin >> reqNum ;
//                if (reqNum == 2 ||reqNum == 3 ) {
//                    cout << "Which Picture would you like to view ? ";
//                    cin >> image_id;
//                }
//                else {
//                    cout << "Enter User Requested ";
//                    cin >> serverName;
//                }
//                cout << getIp("4")<<endl <<getPort("4")<<endl ; //if reqNum = 1 or 2
//                Thread * thrd = new Thread(true , false ,  reqNum , image_id ,  serverName,4040 , toConnectIp , toConnectPort  ); //client thread
//
//            }
//
//        }
//
//    }
    return 0;
}

