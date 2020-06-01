#include "Graph.h"

Graph::Graph(int r, int c)
{
	row = r; //do -1 for both if wanting no 0 row/col - the -1 is probably better at the row making
	col = c;

	topleft = new node(); 
	node* prevptr = topleft;
	node* upptr = topleft;
	node* endptr = topleft;
	node* currptr;

	//first row
	for (int i = 0; i < col-1; i++)
	{
		currptr = new node();
		prevptr->right = currptr;
		currptr->left = prevptr;
		prevptr = currptr;
	}
	
	for (int j = 0; j < row-1; j++)
	{
		//new row operation prep
		currptr = new node(); 
		endptr->down = currptr;
		currptr->up = endptr;
		upptr = endptr->right;
		endptr = currptr;
		prevptr = currptr;

		for (int i = 0; i < col-1; i++) //if we get an error from upptr try adjusting the row lengths?
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

Graph::~Graph()
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


void Graph::display(ostream& out)
{
	node* godown = topleft;
	node* walkingstick;
	int i = 0;
	int j = 0;

	while (godown!=0)
	{
		walkingstick = godown;
		godown = godown->down;
		j = 0;

		while (walkingstick!=0)
		{
			if (walkingstick->wall)
			{
				out << "W ";
			}
			else
			{
				out << "  ";
			}

			walkingstick = walkingstick->right;
			j++;
		}
		out << endl;
		i++;
	}
}

bool Graph::flipWall(int r,int c)
{
	if (c > col || r > row) //checks that the given position is actually in the board
	{
		return false;
	}

	node* walkingstick = topleft;
	int i = 0;
	int j = 0;
	while (i < c)
	{
		walkingstick = walkingstick->right;
		i++;
	}
	while (j < r)
	{
		walkingstick = walkingstick->down;
		j++;
	}

	walkingstick->wall = false;
	return true;
}

void Graph::testList()
{
	List test;
	node* walkingstick = topleft;
	/*
	while (walkingstick != 0)
	{
		test.insert(walkingstick);
		walkingstick = walkingstick->right;
	}*/

	for (int j = 0; j < col; j++)
	{
		test.insert(walkingstick);
		walkingstick = walkingstick->right;

	}

	for (int i = 0; i < col; i++)
	{
		
		test.take(&walkingstick, 5);
		cout << "got it, i = " << i;
	}
}

//need a function to find a random wall - check it against the cell list
//need a function to find a random cell from the beginning

void Graph::generateMaze(int unsigned key)
{
	//use the key for the srand function?
	//dont even need rand? is this a good enough hash??
	int rand_row = key % row;
	int rand_col = key % col;
	
	
	node* currwall = topleft;
	int i = 0;

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

	currwall->wall = false;//first cell

	//add walls of currwall to the wall list
	addwalls(currwall);

	//main algorithm

	while (!wall_list.empty())
	{
		wall_list.take(&currwall, key); //takes a random wall from the wall list
		//test if eligible to be passage - only one nonwall
		//if so wall=false, add neighboring walls ~ no need for a different function than the other, shouldnt add parts of the passage
		//doubly added walls to the wall list resolve themselves in the elegibility test

		if (eligible(currwall))
		{
			addwalls(currwall);
			currwall->wall = false;
		}
	}
	
	//for algorithm, gonna need an opposite function
	//display gonna need to show those
	

}

void Graph::addwalls(node* n)
{
	if (n->right != 0)
	{
		if (n->right->wall == true)
		{
			wall_list.insert(n->right);
		}
	}
	if (n->left != 0)
	{
		if (n->left->wall == true)
		{
			wall_list.insert(n->left);
		}
	}
	if (n->up != 0)
	{
		if (n->up->wall == true)
		{
			wall_list.insert(n->up);
		}
	}
	if (n->down != 0)
	{
		if (n->down->wall == true)
		{
			wall_list.insert(n->down);
		}
	}
}

bool Graph::eligible(node* n)
{
	int non_walls = 0;

	if (n->right != 0)
	{
		if (n->right->wall == false)
		{
			non_walls++;
		}
	}
	if (n->left != 0)
	{
		if (n->left->wall == false)
		{
			non_walls++;
		}
	}
	if (n->up != 0)
	{
		if (n->up->wall == false)
		{
			non_walls++;
		}
	}
	if (n->down != 0)
	{
		if (n->down->wall == false)
		{
			non_walls++;
		}
	}

	if (non_walls == 1)
	{
		return true;
	}

	return false;

}