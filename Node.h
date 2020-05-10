#ifndef __PROSPATHIAA_NODE_H_
#define __PROSPATHIAA_NODE_H_

#include <omnetpp.h>
#include "Server.h"

using namespace omnetpp;

/**
 * TODO - Generated class
 */
class Node : public cSimpleModule
{
  protected:
    int id;
    int totalNodes;
    int NeighborsCount;
    int receivedArray[150];
    int receivedCount;
    bool isRoot;
    int parent[150];
    int parentCounter;
    Server* server = nullptr;

    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
};

#endif
