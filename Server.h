#ifndef __PROSPATHIAA_SERVER_H_
#define __PROSPATHIAA_SERVER_H_

#include <omnetpp.h>

using namespace omnetpp;

/**
 * TODO - Generated class
 */
class Server : public cSimpleModule
{
  protected:
    int totalFrames;
    int netType;
    int totalNodes;
    double connectedness;
    int data;
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void finish();
};

#endif
