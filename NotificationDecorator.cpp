#include<bits/stdc++.h>
#pragma once
using namespace std;

class INotification{
    public:
    virtual string getContent()=0;
};

class simpleNotification:public INotification{
    private:
    string txt;
    public:
    simpleNotification(string txt){
        this->txt=txt;
    }
    string getContent()override{
         return txt;
    }
};

class INotificationDecorator:public INotification{
    protected:
    INotification* notification;
    public:
    INotificationDecorator(INotification* notification){
        this->notification=notification;
    }
};

class TimestampDecorator:public INotificationDecorator{
    public:
    TimestampDecorator(INotification* notification): INotificationDecorator(notification){}
    string getContent(){
        time_t t=time(0);
        char* dt=ctime(&t);
        return notification->getContent()+"\n"+dt;
    }
};

class SignatureDecorator:public INotificationDecorator{
    private:
    string sign;
    public:
    SignatureDecorator(INotification* notification,string sign):INotificationDecorator(notification){
        this->sign=sign;
    }
    string getContent(){
        return notification->getContent()+sign+"\n";
    }
};

