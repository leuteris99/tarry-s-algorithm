#include "Server.h"
#include <string>

Define_Module(Server);

void Server::initialize()
{
    totalFrames = 0; // to sinolo ton paketon pou stalthikan sto diktio
    totalNodes = par("tn"); // to sinilo ton kombon tou diktiou
    connectedness = par("c"); // proeretiko: pithanotita dimiourgias edge metaksi kombon
    netType = par("netType"); // to eidos tou diktiou (chain, circle, binary...)
    if(netType == 5){
        data = par("h"); // mono gia binary to ipsos tou dentrou
    }
}

void Server::handleMessage(cMessage *msg)
{
    // kathe fora pou lamvano 1 paketo simeni pos exei stalthi 1 msg sto diktio
    totalFrames++; // ara kathe fora pou perno paketo afksano to counter ton frames
    delete msg;
}

void Server::finish()
{
    FILE* file = fopen("result.txt","a"); // anoigo to result file
    std::string str;
    switch(netType){ // epilego eidikevmeni morfi apothikefsis ton dedomenon analoga tou diktiou
    case 1:
        str = "Five Node Example";
        break;
    case 2:
        str = "Six Node Example";
        break;
    case 7:
        str = "Seven Node Example";
        break;
    case 3:
        str = "Chain, TotalNodes: " + std::to_string(totalNodes);
        break;
    case 4:
        str = "Circle, TotalNodes: " + std::to_string(totalNodes);
        break;
    case 5:
        str = "Binary Tree, Height: " + std::to_string(data);
        break;
    case 6:
        str = "Random Graph, TotalNodes: "+ std::to_string(totalNodes) + ", Connectedness: " + std::to_string(connectedness);
        break;
    case 8:
        str = "Full Graph, TotalNodes: " + std::to_string(totalNodes);
        break;
    default:
        str = "Unknown";
    }
    fprintf(file,"Network: %s, TotalFrames: %d\n",str.c_str(),totalFrames); // grafo sto arxio ta apotelesmata
    fclose(file);
}
