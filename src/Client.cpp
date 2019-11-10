#include "../headers/Client.h"

Client::Client(const char * listen_hostname, const char * listen_port){
    buffer = new char [buff_size];
    this->port = listen_port ;
    this->hostname = listen_hostname ;
    std::string serverIp = hostname_to_ip((char *)listen_hostname);
    reqReply = new RequestReply(listen_port,  serverIp.c_str(), true, 1024);
}


void Client::executePrompt() {

    if (!requestNumber (0))
        perror("Error Sending Request Number");
    for (int i=1 ;i<4  ;i++) {
        std::string s= "/Users/owner/CLionProjects/Distributed-Client/imag"+ std::to_string(i) + ".jpg" ;
        if (!requestSamples(s) )
            perror("Error Requesting Samples from Server");
    }

}
int Client :: requestNumber (int req)
{
    printf("\nSending a Request of index: %i\n", req);
    return reqReply->sendReq(req); //sends request number to server
}

int Client :: requestSamples (std::string s )
{

    printf("Receiving Samples ...\n");
    return reqReply->getRequest( s ) ; // receives photo
    //reqReply->shutDownFD();
}


int Client::execute(char *msg){
        /*int replyStatus, requestStatus;
        std::strcpy(buffer, msg);
        requestStatus = reqReply->doOperation(buffer);
        std::cout << requestStatus << std::endl;
        if (requestStatus >= 0){
                if((replyStatus = reqReply->getReply(buffer)) >= 0){
                        printf("%s \n", buffer); //reply from server
                }
        }
        return replyStatus;*/
}

bool Client::req_photo(int photoid, const char *hostname, const char *port)
{
    /*Message m((void *)"",(size_t)0);
    m.setMessageType(Request);
    std::strcpy(buffer,(char*) m);
    */
    int requestStatus, replyStatus;
    List::entry e;
    e.port= (char*)port;
    e.hostname=(char*)hostname;
    e.photoid=photoid;
    int val = 0;
    if(!lookup_table.search(e))  //define search function as well the undefined crap if needed
    {

        lookup_table.insertFirst(e,val);  //could be a table of pic/needs to expand
    }

    requestStatus= reqReply->doOperation(buffer); //what to put
    /*if (requestStatus >= 0){
            if((replyStatus = reqReply->getReply(buffer)) >= 0){

            }
            }*/
}


Client::~Client(){
     reqReply->shutDownFD();
}
