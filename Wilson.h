#pragma once
#include <iostream>
#include <math.h>
#include <time.h>

/////////////////////I HAVE GIVEN UP ON WILSONS ALGORITHM

using namespace std;
class Wilson
{
public:
	Wilson();
	Wilson(int r, int c);
	~Wilson();
	void testList();
	void generateMaze(); //wilsons algorithm 
	void display(ostream& out);
	

private:

	int row;
	int col;

	class node
	{
	public:
		node()
		{
			left = right = up = down = 0;
			wall = true;
			visited = false;
			
			partofwalk = false;
		}

		node(node* l, node* r, node* u, node* d, bool w)
		{
			left = l;
			right = r;
			up = u;
			down = d;
			wall = w;
		}

		node* left;
		node* right;
		node* up;
		node* down;
		bool wall;
		bool visited;
		
		bool partofwalk;
	};
	class List
	{
	public:
		int length;

		class  embnode
		{
		public:
			node* data;
			embnode* next;

			embnode(node* d, embnode* n)
			{
				data = d;
				next = n;
			}
		};

		embnode* head;

		List()
		{
			head = 0;
			length = 0;
		}

		~List()
		{
			embnode* walkingstick = head;
			while (walkingstick != 0)
			{
				embnode* temp;
				temp = walkingstick;
				walkingstick = walkingstick->next;
				delete temp;
			}
		}

		bool empty()
		{
			return (head == 0);
		}

		void insert(node* dat) //should be fine for this algorithm
		{
			//cout << "length is " << length << endl; //tester
			head = new embnode(dat, head);
			dat->partofwalk = true;
			length++;

		}

		void clearto(node* dat)
		{
			embnode* currptr = head;
			embnode* temp;
			bool cont = true;;
			while (currptr != 0 && cont)
			{
				if (currptr->data == dat)
				{
					cont = false;
					head = currptr->next;
					delete currptr;
				}
				else
				{
					
					temp = currptr;
					currptr->data->partofwalk = false;
					currptr = currptr->next;
					head = currptr;
					delete temp;
					//cout << "deleting" << endl;
				}
			}
		}

		void addtomaze()//makes all not walls, makes all sides visited, clear the list
		{
			embnode* currptr = head;
			embnode* temp;

			while (currptr != 0)
			{
				temp = currptr;
				currptr->data->wall = false;
				currptr->data->partofwalk = false;
				currptr->data->visited = true;
				visitwalls(currptr->data);
				currptr = currptr->next;
				delete temp;
			}
			head = 0;
		}

		void visitwalls(node* n)
		{
			if (n->right != 0)
			{
				n->right->visited = true;
			}
			if (n->left != 0)
			{
				n->left->visited = true;
			}
			if (n->up != 0)
			{
				n->up->visited = true;
			}
			if (n->down != 0)
			{
				n->down->visited = true;
			}
		}

		

	};

	node* topleft;
	
	List currentwalk; //current node in the random walk needs to be checked against this
					  //also needs a random walk? or can i do that in the algorithm
	//List maze; dont need a list of maze elements, know if its in the maze based on wall/not wall
	void direction(node** n); //helper function
};

