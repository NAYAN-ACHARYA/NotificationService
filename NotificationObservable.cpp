
#include <bits/stdc++.h>
#include "./NotificationDecorator.cpp"
#include "./NotificationStrategy.cpp"
using namespace std;
class INotificationObserver {
   public:
    virtual void update() = 0;
};
class INotificationObservable {
    protected:
    set<INotificationObserver*>observers;
   public:
    virtual void add(INotificationObserver* obs)=0;
    virtual void remove(INotificationObserver* obs)=0;
    virtual void notify()=0;
    virtual INotification* getNotification()=0;
    virtual void setNotification(INotification* notif)=0;
};

class NotificationObservable:public INotificationObservable{
    private:
    INotification* notification;
    public:
    void add(INotificationObserver* obs) override{
        observers.insert(obs);
    }
    void remove(INotificationObserver* obs) override{
        if(observers.find(obs)!=observers.end()){
            observers.erase(obs);
        }
    }
    void setNotification(INotification* notification){
        this->notification=notification;
        notify();
    }
    void notify() override{
        for(INotificationObserver* obs:observers){
            obs->update();
        }
    }
    INotification* getNotification(){
        return notification;
    }
};

class NotificationEngine:public INotificationObserver{
    private:
    INotificationObservable* observable;
    set<INotificationStrategy*>strategies;
    public:
    NotificationEngine(INotificationObservable* observable){
        this->observable=observable;
        observable->add(this);
    }
    void setStrategy(INotificationStrategy* strategy) {
        strategies.insert(strategy);
    }
    void update() override{
        INotification* notif=observable->getNotification();
        cout<<notif->getContent();
        for(INotificationStrategy* strategy:strategies){
            strategy->sendNotification();
        }
    }
};
int main(){
    INotificationObservable* observable=new NotificationObservable();
    NotificationEngine* obs1=new NotificationEngine(observable);
    NotificationEngine* obs2=new NotificationEngine(observable);
    obs1->setStrategy(new EmailStrategy());
    obs1->setStrategy(new SMSStrategy());
    obs2->setStrategy(new SMSStrategy());
    INotification* notif=new simpleNotification("base_txt");
    notif=new TimestampDecorator(notif);
    observable->setNotification(notif);
    return 0;
}
