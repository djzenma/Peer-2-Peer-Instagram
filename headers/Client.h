#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <string>
#include <cstring>
#include <stdio.h>
#include <string.h>

#include "RequestReply.h"
#include "utils.h"
#include "Message.h"




/*class List{
public:
    struct entry{
       int photoid;
        char * hostname;
        char * port;
    };

private:
// Node Class
class node
{
public:
entry key; // key
int data; // Data
node *next; // pointer to next node
}; // end of class node declaration
typedef node * NodePointer;
NodePointer head, cursor, prev; // Pointers

public:
List()// Create an empty List
{
    NodePointer p;
  new node == p;
    head==p;
}
~List() // Class Destructor
{
  delete head;
}

bool listIsEmpty()
{
    if (head==nullptr)
        return true;
    else
        return false;
}

bool curIsEmpty()
{
    if(cursor==nullptr)
        return true;
    else
        return false;
}

void toFirst()
{
cursor=head;
}
bool atFirst()
{
 if (cursor==head)
     return true;
 else
     return false;
}
void  advance()
{
cursor=cursor->next;
}
void toEnd()
{
 while (cursor->next!=nullptr)
 {
     cursor=cursor->next;
 }
}
bool  atEnd()
{
   if (cursor->next == nullptr)
       return true;
   else
       return false;
}
int  listSize()
{
    int c=0;
    toFirst();
    while (cursor->next != nullptr)
    c++;
    return c;
}
void updateData ( int & a)
{
cursor->data=a;
}

void  retrieve (entry &a, int &b)
{
    a=cursor->key;
    b=cursor->data;
}
void  insertFirst ( entry &a,  int &b )
{
    node * p;
    toFirst();
    p=head;
    head=new node;
    head->data=b;
    head->key=a;
    head->next=p;
}
void  insertAfter ( entry &a,  int &b )
{
    node * p,*q;
    p=cursor;
    q=cursor->next;
    cursor=new node;
    cursor->data=b;
    cursor->key=a;
    cursor->next=q;
    prev=p;
}
void  insertBefore ( entry &a,  int &b )
{

    node * p;
    p=cursor;
    cursor=new node;
    cursor->data=b;
    cursor->key=a;
    cursor->next=p;

}
void insertEnd ( entry & a,  int & b )
{
    toEnd();
    NodePointer p;
    p=cursor->next;
    p=new node;
    p->data=b;
    p->key=a;
    p->next=nullptr;
}
void  deleteNode()
{

}
void deleteFirst(){}
void deleteEnd(){}
void makeListEmpty(){}
bool search ( entry & a){
    node* current = head; // Initialize current
        while (current != NULL)
        {
            if (current->key.hostname == a.hostname)  {
                if (current->key.port == a.port)  {
                    if (current->key.photoid == a.photoid)  {
                return true;  }}}
            current = current->next;
        }
          return false;
}
void orderInsert( entry &,  int & ){}
void traverse(){}
};

*/
class Client {
private:
    char * buffer;
    int buff_size = 1024;
    RequestReply* reqReply;
    const char * port;
    const char * hostname;
    std::string name ;
    int req ;
    int viewPic ;
    //Database* db;


public:
    Client(const char* hostname, const char* port);
    int execute(char * msg);
    int requestSamples(std::string s );
    int requestNumber (int req);
    int executePrompt(int req,int  image_id , std::string serverName);
    bool decrementView(std::string image);
    ~Client();
};
#endif
