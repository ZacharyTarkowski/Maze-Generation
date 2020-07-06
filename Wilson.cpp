#include "Wilson.h"
//functions:
//regular graph
//display
//generate maze
//randomwalk: randomly selects the next tile/node

Wilson::Wilson(int r, int c)
{
	row = r; //do -1 for both if wanting no 0 row/col - the -1 is probably better at the row making
	col = c;

	topleft = new node();
	node* prevptr = topleft;
	node* upptr = topleft;
	node* endptr = topleft;
	node* currptr;

	//first row
	for (int i = 0; i < col - 1; i++)
	{
		currptr = new node();
		prevptr->right = currptr;
		currptr->left = prevptr;
		prevptr = currptr;
	}

	for (int j = 0; j < row - 1; j++)
	{
		//new row operation prep
		currptr = new node();
		endptr->down = currptr;
		currptr->up = endptr;
		upptr = endptr->right;
		endptr = currptr;
		prevptr = currptr;

		for (int i = 0; i < col - 1; i++) //if we get an error from upptr try adjusting the row lengths?
		{
			//new row, linking with old
			currptr = new node();
			prevptr->right = currptr;
			currptr->left = prevptr;
			upptr->down = currptr;
			currptr->up = upptr;
			prevptr = currptr;
			upptr = upptr->right;
		}
	}
}

Wilson::~Wilson()
{
	node* followdown;
	node* totheright = topleft;
	node* temp;

	while (totheright != 0)
	{
		followdown = totheright;
		totheright = totheright->right;

		while (followdown != 0)
		{
			temp = followdown;
			followdown = followdown->down;
			delete temp;
		}


	}


}


void Wilson::display(ostream& out)
{
	node* godown = topleft;
	node* walkingstick;
	int i = 0;
	int j = 0;

	while (godown != 0)
	{
		walkingstick = godown;
		godown = godown->down;

		while (walkingstick != 0)
		{
			
			 if (walkingstick->wall)
			{
				out << "O ";
			}
			else
			{
				out << " test ";
			}

			walkingstick = walkingstick->right;
			j++;
		}
		out << endl;
		i++;
	}
}

void Wilson::testList()
{
	node* walkingstick = topleft;
	/*
	while (walkingstick != 0)
	{
		test.insert(walkingstick);
		walkingstick = walkingstick->right;
	}*/
	node* test = topleft;
	for (int j = 0; j < col; j++)
	{
		currentwalk.insert(walkingstick);
		walkingstick = walkingstick->right;
		if (j == 5) { test = walkingstick; }

	}
		//currentwalk.clearto(0);
		currentwalk.addtomaze();
		cout << "cleared";
}

void Wilson::generateMaze() //might have to start each time in the maze, but maybe not. certainly would be faster?
{
	int limit = (row + col) / 2;
	int limtest = 0;
	srand(time(NULL));
	int rand_row;
	int rand_col;
	node* currwall;
	int i = 0;
	bool walk = true;
	

	//main loop
	while (limtest <= limit)
	{
		//all outdated, need to make a maze list to pick from
		//overhaul?
		rand_row = rand() % row;
		rand_col = rand() % col;
		currwall = topleft;
		i = 0;

		while (i < rand_col)
		{
			currwall = currwall->right;
			i++;
		}
		i = 0;
		while (i < rand_row)
		{
			currwall = currwall->down;
			i++;
		}

		if (currwall->visited) //wont let it try 
		{
			limtest++;
		}

		else
		{
			walk = true;
			limtest = 0;
			while (walk)
			{
				currentwalk.insert(currwall);
				direction(&currwall);

				if (currwall->wall == false)
				{
					currentwalk.addtomaze();
					walk = false; // go select a different node
				}
				else if (currwall->partofwalk == true)
				{
					currentwalk.clearto(currwall); 
				}

			}
		}

	}

	//secondary loop to finish out
}

void Wilson::direction(node** n)
{
	
	int dir;
	node* temp = *n;

	dir = rand() % 4;
	
	switch (dir)
	{
	case 0:
		*n = temp->right;
		if (*n != 0) { break; }
	case 1:
		*n = temp->left; 
		if (*n != 0) { break; }
	case 2:
		*n = temp->up; 
		if (*n != 0) { break; }
	case 3:
		*n = temp->down;
		if (*n != 0) { break; }
	default:
		cerr << "Somethings wrong" << endl;
	}
	
}