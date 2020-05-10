network Network2
{
    parameters:
        int totalNodes = default(3);
	submodules:
	    server: Server;
	    node[totalNodes]: Node{
	        id = index;
	    }
	connections:
		node[0].inoutGateVector++ <--> node[1].inoutGateVector++;
		node[1].inoutGateVector++ <--> node[2].inoutGateVector++;
		node[2].inoutGateVector++ <--> node[3].inoutGateVector++;
		node[2].inoutGateVector++ <--> node[4].inoutGateVector++;
		node[2].inoutGateVector++ <--> node[0].inoutGateVector++;
		node[2].inoutGateVector++ <--> node[5].inoutGateVector++;
		node[0].inoutGateVector++ <--> node[4].inoutGateVector++;
		node[1].inoutGateVector++ <--> node[4].inoutGateVector++;
}
