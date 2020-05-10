simple Server
{
    parameters:
        int netType = default(-1); // network type
        int tn = default(-1); // totalNodes
        double c = default(1); //connectedness
        int h = default(-1); //height
	gates:
	    input inGate @directIn;
}
