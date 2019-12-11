#include <string>
#include <ostream>
#include <fstream>

#include "../headers/Peer.h"
#include "../headers/Message.h"
#include "../headers/Image.h"

using namespace std;

void getimageInfo(string stego_image, int & num_views , string & owner_ip , string & owner_name)
{
    std::string extracted_path = "../images/stego/temp/scratch.jpg";
    std::string hidden_text = stega_decode(stego_image, extracted_path, true);
    std::vector<std::string> parsed = parseHidden(hidden_text);
    num_views = atoi(parsed[0].c_str());
    owner_ip = parsed[1];
    owner_name = parsed[2];
}


void getSampleInfo(string sample_image, string & owner_ip , string & owner_name)
{
    std::string extracted_path = "../images/stego/temp/scratch.jpg";
    std::string hidden_text = stega_decode(sample_image, extracted_path, true);
    std::vector<std::string> parsed = parseHidden(hidden_text);
    owner_name = parsed[0];
    owner_ip = parsed[1];
}

int main(int argc,char **argv){
    int n= 0;

    if(strcmp(argv[1], "Server")==0){
        Peer p("10.40.56.37", "Manar", "127.0.0.1");
        sleep(6);
        std::vector<Message> pending = p.getPending();
        for (int i=0; i< pending.size(); i++){
            cout << "Rejecting request: " << pending[i].getRequestId() << std::endl;
            n= n+1;
            p.Accept(pending[i].getRequestId());
        }
        sleep(500);
        perror("Updating VIEWS \n");
        //p.updateViewsForPeer(4,0, "Bassant", "10.40.56.37" );
        //        sleep(10);

        pending = p.getPending();
        for (int i=0; i< pending.size(); i++){
            cout << "Rejecting request: " << pending[i].getRequestId() << std::endl;
            n= n+1;
            p.Accept(pending[i].getRequestId());
        }
        while(true){
            pending = p.getPending();
            for (int i=0; i< pending.size(); i++){
                cout << "Rejecting request: " << pending[i].getRequestId() << std::endl;
                n= n+1;
                p.Accept(pending[i].getRequestId());
            }
        }
    } else {
        Peer p("10.40.56.37", "Manar", "127.0.0.1");
        Message imgMsg;
        //p.requestImageFromPeer( 4, "10.40.32.170"); //DONE!!
        //        int  num_views ;
        //        string  owner_ip ;
        //        string  owner_name;
        //        getimageInfo("./../images/requested/images/Manar/4.jpg", num_views ,  owner_ip , owner_name);
        //        cout << num_views << " "<< owner_ip << " "<< owner_name <<endl ;
         //p.viewImage(4, "Manar"); //DONE!!
        //p.requestProfileFromPeer("10.40.32.170"); //DONE!!
        //sleep(500);
    }

    return 0;
}
