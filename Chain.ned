network Chain
{
    parameters:
        int totalNodes = default(3);
	submodules:
	    server: Server{
	        tn = totalNodes;
	    }
	    node[totalNodes]: Node{
	        id = index;
	    }
	connections:
	    for i=0..totalNodes-2{
	        node[i].inoutGateVector++ <--> node[i+1].inoutGateVector++;
	    }
//	    node[totalNodes-1].inoutGateVector++ <--> node[0].inoutGateVector++;
}
