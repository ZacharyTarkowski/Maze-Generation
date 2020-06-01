#include "Graph.h"

using namespace std;

int main()
{
	Graph x(300,100); 
	//x.flipWall(0, 0);
	x.generateMaze(13); //random enough, will come back to hashing/keying later
	//x.flipWall(2,1); 
	
	//x.testList();
	
	x.display(cout); //the start is literally just the first tile
	

	//x.testStack();
	//one generate maze has a key one doesnt
	//just send the function a number

	return 0;
}