#include <iostream>
#include "stdc++.h"

using namespace std;


class ISubscriber {
public:
    virtual bool sendNotification(string message) = 0;
};

class TextMessage:public ISubscriber {
public:
    bool sendNotification(string msg){
        cout<<"In Text Message"<<endl;
        return true;
    }
};

class PushNotification:public ISubscriber {
public:
    bool sendNotification(string msg){
        cout<<"In push notification"<<endl;
        return true;
    }
};

class Notification {
private:
    string message;
public:
    Notification(string msg){
        message = msg;
    }
    string getMessage(){
        return message;
    }
};

class MessageTopic{
private:
    string topicName;
    queue<Notification*> messages;
    vector<ISubscriber*> subscribers;
public:
    MessageTopic(string topic){
        topicName = topic;
    }

    string getTopicName(){
        return topicName;
    }

    void addMessage(string message){
        messages.push(new Notification(message));
    }
    void addSubscriber(ISubscriber* s){
        subscribers.push_back(s);
    }

    bool isNextMessage(){
        return !messages.empty();
    }

    bool processMessage(){
        if(!messages.empty()){
            Notification* n = messages.front();
            messages.pop();
            for(auto subs: subscribers){
                subs->sendNotification(n->getMessage());
            }
        }
        return true;
    }
};


class NotificationSystem{
private:
    vector<MessageTopic*> topics;

    MessageTopic* getTopic(string topicName){
        for(auto i:topics){
            if(i->getTopicName()==topicName){
                return i;
            }
        }
        return NULL;
    }

public:
    bool publishNotification(string message,string topicName){
        MessageTopic* topic = getTopic(topicName);
        topic->addMessage(message);
    }
    void sendNotification(){
        for(auto topic: topics){
            if(topic->isNextMessage()){
                topic->processMessage();
            }
        }
    }
};


int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}