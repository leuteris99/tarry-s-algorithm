network FullGraph
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
		for i=0..totalNodes-1,for j=i+1..totalNodes-1{
            node[i].inoutGateVector++ <--> node[j].inoutGateVector++;
        }
}
