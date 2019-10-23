#include "experiment.h"

void varyLoad(Client * c, int num_reqs){
    char  msg [] = "Hello";
    int count = 0;
    int status; 
    do {
       status = c->execute(msg);
       count = (status <= 0)? count : count + 1;
    } while (--num_reqs !=0);

    std::cout << "Successful requests: " << count << std::endl;
}

void varyBuffSize(Server * s, int buff_size){
    s->setBufferSize(buff_size);
    s->serveRequest();
}