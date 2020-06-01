#pragma once
#include <iostream>

using namespace std;

//change the name of graph to mazegraph


class Graph
{
public:
	Graph();
	Graph(int r, int c);
	~Graph();

	bool flipWall(int r, int c); // helper function for maze generation

	void testList();

	void generateMaze(int unsigned key); //prims algorithm
	
	void display(ostream &out);
	

private:
	//made them static so I can use them in the hash
	int row;
	int col;

	class node
	{
	public:
		node()
		{
			left = right = up = down = 0;
			wall = true;
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

		void insert(node* dat)
		{
			//cout << "length is " << length << endl; //tester
			head = new embnode(dat, head);
			length++;
			
		}

		void take(node** link, unsigned int key)
		{
			if (!empty())
			{
				int i = 0;
				embnode* currptr = head;
				embnode* prevptr = head;

				while (i < (key) % (length)) //can probably implement in a way outside this function, but good enough
				{ 
					prevptr = currptr;
					currptr = currptr->next;
					i++;
				}

				if (key % length == 0)
				{
					prevptr = currptr;
					currptr = currptr->next;

					if (length == 1)
					{
						currptr = prevptr;
					}
				}

				*link = currptr->data;
				//cout << "position is: " << i << "length is " << length << endl;//tester
				prevptr->next = currptr->next;

				if (length == 1) //if the head was being popped it would trigger a breakpoint, this keeps the head but sets it to null so that the list is empty
				{
					head = 0;
				}
				else
				{
				delete currptr;
				}

				length--;
			}
		}
	
	};

	node* topleft;
	List wall_list;

	//private helper functions
	void addwalls(node* n);
	bool eligible(node* n);
	
};

