#pragma once
#include<bits/stdc++.h>

using namespace std;

class INotificationStrategy{
    public:
    virtual void sendNotification()=0;
};

class EmailStrategy:public INotificationStrategy{
    public:
    void sendNotification() override{
        cout<<"sending via email...."<<endl;
    }
};
class SMSStrategy:public INotificationStrategy{
    public:
    void sendNotification() override{
        cout<<"sending via SMS...."<<endl;
    }
};
