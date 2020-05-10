network BinaryTree
{
    parameters:
        int height = default(2);			//to ypsos tou dentrou tha dinetai ws parametros sto omnetpp.ini
        int totalNodes = 2^(height+1)-1;	//to plithos tha ypologizetai apo to ypsos
        									//ara den vazoume default() gia na mhn ginetai override apo to omnetpp.ini
        
	submodules:
	    server: Server{
	        h = height;
	    }
	    node[totalNodes]: Node{
	        id = index;
	    }
	connections:
		for i=0..2^height-2					//Gia osous komvous den einai fylla
		{
			node[i].inoutGateVector++ <--> node[2*i+1].inoutGateVector++; //nea syndesh me to aristero paidi
			node[i].inoutGateVector++ <--> node[2*i+2].inoutGateVector++; //nea syndesh me to deksi paidi
		}
}
