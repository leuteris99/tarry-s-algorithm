network RandomGraph
{
    parameters:
    	int totalNodes = default(5); 			//To plithos twn komvwn. Arxikopoieitai apo to omnetpp.ini arxeio.
		double connectedness = default(0.5);	//Analoga me authn thn pithanothta tha dhmiourgeitai h oxi syndesi anamesa se dyo komvous.
    
    
    submodules:
        server: Server{
            c = connectedness;
            tn = totalNodes;
        }
        node[totalNodes]: Node{					//Dhlwnoume vector apo Node me megethos oso h prohgoymenh parametros.
	        id = index;
	    }
        
    connections:
        for i=0..totalNodes-2{
            node[i].inoutGateVector++ <--> node[i+1].inoutGateVector++;
        }
        for i=0..totalNodes-1,for j=i+2..totalNodes-1{
            node[i].inoutGateVector++ <--> node[j].inoutGateVector++ if uniform(0,1)<connectedness;
        }
        
        
//		for i = 0..totalNodes-1, for j = i+1..totalNodes-1	//Gia kathe dynato zeugari komvwn tou diktyou
//		{
//			node[i].inoutGateVector++ <--> node[j].inoutGateVector++ if uniform(0,1)<connectedness; //na ginei syndesi symfwna me thn synthiki pou dhlwnetai sto if
//		}
}
