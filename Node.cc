#include "Node.h"

Define_Module(Node);

void Node::initialize()
{
    id = par("id"); // id tou kombou
    totalNodes = par("totalNodes"); // o sinolikos arithmos ton kombon tou diktiou
    NeighborsCount = gateSize("inoutGateVector"); // o arithmos ton gitonikon kombon aftou tou kombou
    parentCounter = 0; // counter pou metra se posous parent exei na apadisi me finish o kombos
    receivedCount = 0; // o arithmos ton minimaton pou elabe (h estile) apo kathe kombo (metra mono thn 1h fora gia kathe kombo)
    for(int i=0; i<=totalNodes-1; i++){ // arxikopoiisi tou pinaka
        receivedArray[i] = -1; // pinakas pou apothikevi to index apo ta gate pou elabe (i estile) minima (metra mono thn 1h fora)
    }
    isRoot = false; // an o kombos einai h riza

    cModule* temp = this->getParentModule();
    temp = temp->getSubmodule("server");
    server = ((Server*)temp); // apothikevo to instance tou server gia na boro na tou stelno asirmata

    if(id == 0){ // ksekinai o algorithmos stelnodas start o komvos me id=0 ston eafto tou
        scheduleAt(simTime()+0.1,new cMessage("start"));
    }
}

void Node::handleMessage(cMessage *msg)
{
    std::string msgContent = msg->getName(); // apothikefsi tou msg
    int msgGateIndex = 0;
    if (msgContent != "start"){ // stelno sto server msg gia na afksisi to counter ton paketon pou stalthikan sto diktio
        msgGateIndex = gate(msg->getArrivalGateId())->getIndex(); // apothikebo prosorina to index tou gate apo opou elaba to msg
        cMessage *serv = new cMessage("send");
        sendDirect(serv->dup(),server->gate("inGate"));
        delete serv;
    }

    if(msgContent == "start"){
        bubble("Start");
        isRoot = true;
        receivedArray[receivedCount++] = 0; // simiono oti stelno msg sto gate  me index 0

        cMessage *helloMsg = new cMessage("hello");
        send(helloMsg->dup(),gate("inoutGateVector$o",0)); // ksekina o algoritmos
        delete helloMsg;
    }
    if(msgContent == "hello"){
        bubble("hello");

        parent[parentCounter++] = msgGateIndex; // simiono to index apo opou elaba to msg os parent

        bool msgExist=false;
        for(int i=0; i<receivedCount; i++){ // checkaro an yparxei allo msg apo afto to gate
            if(receivedArray[i] == msgGateIndex){
                msgExist=true;
                break;
            }
        }
        if(!msgExist){ // an den yparxei allo msg apo afto to gate tote simiono oti exo epikoinonisi me afto to gate
            receivedArray[receivedCount] = msgGateIndex;
            receivedCount++;
        }
        if(receivedCount<NeighborsCount){ // oso yparxoun komboi pou den exo stili-pari hello

            int index = 0;
            for(int i=0; i<=NeighborsCount-1; i++){                         // TODO: AN SPASI BGALE TO =
                for(int j=0;j<=NeighborsCount-1;j++){                       // TODO: AN SPASI BGALE TO =
                    if(receivedArray[j] == index){
                        index++; // ypologizo to index tou epomenou gate pou exo na stilo hello
                    }
                }
            }
//            EV<<id<<" "<<index<<endl;
            receivedArray[receivedCount]=index; // prostheto to gate sti lista me ta gate pou exo epikoinonisi
            cMessage *helloMsg = new cMessage("hello");
            send(helloMsg->dup(),gate("inoutGateVector$o",index)); // stelno hello sto gate
            receivedCount++;
            delete helloMsg;
        }else{ // an den exo na stilo allo hello
            if(parentCounter == 0){ // an den yparxei kapios parent termatizo
                return;
            }
            //alios stelno finish ston telefteo stin lista parent kai ton afero apo afti
            cMessage *finishMsg = new cMessage("finish");
            send(finishMsg->dup(),gate("inoutGateVector$o",parent[--parentCounter]));
            delete finishMsg;
        }
    }
    if(msgContent == "finish"){
        bubble("finish received!");
        if(receivedCount<NeighborsCount){ // oso yparxoun komboi pou den exo stili-pari hello
            int index = 0;
            for(int i=0; i<=NeighborsCount-1; i++){                         // TODO: AN SPASI BGALE TO =
                for(int j=0; j<= NeighborsCount-1;j++){                     // TODO: AN SPASI BGALE TO =
                    if(receivedArray[j] == index){
                        index++; // ypologizo to index tou epomenou gate pou exo na stilo hello
                    }
                }
            }
            receivedArray[receivedCount]=index; // prostheto to gate sti lista me ta gate pou exo epikoinonisi
            cMessage *helloMsg = new cMessage("hello");
            send(helloMsg->dup(),gate("inoutGateVector$o",index)); // stelno hello sto gate
            receivedCount++;
            delete helloMsg;
        }else{ // an den exo na stilo allo hello
            if(parentCounter == 0){ // an den yparxei kapios parent termatizo
                return;
            }
            //alios stelno finish ston telefteo stin lista parent kai ton afero apo afti
            cMessage *finishMsg = new cMessage("finish");
            send(finishMsg->dup(),gate("inoutGateVector$o",parent[--parentCounter]));
            delete finishMsg;
        }
    }
    delete msg;
}
