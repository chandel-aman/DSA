#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct tree_node
{
	int val;
	struct tree_node* left;
	struct tree_node* right;
}node;

typedef struct tree
{
	node* root;
	int size;
}tree;

bool sanity_check (void* ptr)
{
	if (ptr)
		return true;
	else
	{
		perror ("MEM ALLOC FAIL\n");
		return false;
	}
}

tree* plant_a_tree ()
{
	//initialize the tree
	tree* ptr = (tree*) malloc (sizeof (tree));
	if (sanity_check (ptr))
	{
		ptr->root = NULL;
		ptr->size = 0;
	}
	printf ("\tTREE PLANTED\n");
	return ptr;
}

node* grow_a_leaf (int val)
{
	node* ptr = (node*) malloc (sizeof (node));
	if (sanity_check (ptr))
	{
		ptr -> val = val;
		ptr -> left = NULL;
		ptr -> right = NULL;
	}
	return ptr;
}

bool add (node* ptr, int val)
{
	if (ptr -> val == val)
	{
		printf ("\tVAL EXISTS\n");
		return false;
	}
	else if (ptr -> val > val)
	{
		if (ptr -> left)
			return add (ptr -> left, val);
		ptr -> left = grow_a_leaf (val);
	}
	else
	{
		if (ptr -> right)
			return add (ptr -> right, val);
		ptr -> right = grow_a_leaf (val);
	}
	return true;
}

bool add_node (tree* root, int val)
{
	if (root)
	{
		if (root -> root)
		{	
			if (add (root -> root, val))
			{
				root -> size ++;
				return true;
			}
			else
				return false;
		}
		else
		{
			root -> root = grow_a_leaf (val);
			if (root -> root == NULL)
				return false;
			else
			{
				root -> size = 1;
				return true;
			}
		}
	}
	else
	{
		printf ("\tPLANT A TREE FIRST\n");
		return false;
	}
}

//returns the parentp node of the searched value
node* search (node* ptr, int val, node* parent = NULL)
{
	if (ptr)
	{
		if (ptr -> val == val)
		{
			printf ("\tFOUND.\n");
			return parent;
		}
		else if ( ptr -> val > val)
			return search (ptr -> left, val, ptr);
		else
			return search (ptr -> right, val, ptr);
	}
	else
	{
		printf ("\tNO SUCH VAL.\n");
		return NULL;
	}
}

bool find (tree* root, int val)
{
	if (root)
		if ((root -> root -> val == val) || search (root -> root, val))
			return true;
		else 
			return false;
	else
		return false;
}

bool remove_node (tree *root, int val)
{
	node *tmp, *ptmp, *to_del;
	bool flag;
	if (root)
	{
		if (root -> root -> val == val)
		{
			to_del = root -> root;
			
			if (to_del -> right == NULL)
				root -> root = to_del -> left;
			else if (to_del -> right -> left == NULL)
			{
				to_del -> right -> left = to_del -> left;
				root -> root = to_del -> right;
			}
			else
			{
				//find the in-order successor
				tmp = to_del -> right;
				ptmp = to_del;
				while (tmp -> left)
				{
					ptmp = tmp;
					tmp = ptmp -> left;
				}
				ptmp -> left = tmp -> right;
				tmp -> left = to_del -> left;
				tmp -> right = to_del -> right;
				root -> root = tmp;
			}
			free (to_del);
			return true;
		}
		else	
		{
			node* parent = search (root -> root, val);
			if (parent)
			{
				if (parent -> left && parent -> left -> val == val)
				{
					to_del = parent -> left;
					flag = true;
				}
				else 
				{
					to_del = parent -> right;
					flag = false;
				}

				if (to_del -> right == NULL)
				{
					if (flag)
						parent -> left = to_del -> left;
					else
						parent -> right = to_del -> left;
				}
				else if (to_del -> right -> left == NULL)
				{
					to_del -> right -> left = to_del -> left;
					if (flag)
						parent -> left = to_del -> right;
					else
						parent -> right = to_del -> right;
				}
				else
				{
					//find the in-order successor
					tmp = to_del -> right;
					ptmp = to_del;
					while (tmp -> left)
					{
						ptmp = tmp;
						tmp = ptmp -> left;
					}
					ptmp -> left = tmp -> right;
					tmp -> left = to_del -> left;
					tmp -> right = to_del -> right;
					if (flag)
						parent -> left = tmp;
					else
						parent -> right = tmp;
				}

				free (to_del);
				return true;
			}
			else
				return false;
		}
	}
	else
	{
		printf ("\tPLANT A TREE FIRST\n");
		return false;
	}
}
 
int h (node* ptr)
{
	int hl, hr;
	if (ptr == NULL)
		return 0;

	hl = h (ptr -> left);
	hr = h (ptr -> right);
	return hl > hr ? hl + 1: hr + 1;
}

int height (tree *root)
{
	if (root && root -> root)
		return h (root->root);
	else
		return 0;
}

void display_in_order (node* ptr)
{
	if (ptr)
	{
		display_in_order (ptr -> left);
		printf ("%d ", ptr -> val);
		display_in_order (ptr -> right);
	}
}

void display_pre_order (node* ptr)
{
	if (ptr)
	{
		printf ("%d ", ptr -> val);
		display_pre_order (ptr -> left);
		display_pre_order (ptr -> right);
	}
}

void display_post_order (node* ptr)
{
	if (ptr)
	{
		display_post_order (ptr -> left);
		display_post_order (ptr -> right);
		printf ("%d ", ptr -> val);
	}
}

void printLevel (node* ptr, int level)
{
	if (ptr)
	{
		if (level == 1)
			printf ("%d\t", ptr -> val);
		else
		{
			printLevel (ptr -> left, level - 1);
			printLevel (ptr -> right, level - 1);
		}
	}
}

void display_level_order (node* ptr, int h)
{
	for (int i = 1; i <= h; i ++)
	{  
		printf ("\tLevel %d ::\t", i);
		printLevel(ptr, i);
		printf ("\n");
	}
}

void display_graphical (node* ptr, FILE* fp)
{
	if (ptr)
	{
		if (ptr -> left)
		{
			fprintf (fp, "%d -- %d;", ptr -> val, ptr -> left -> val);
			display_graphical (ptr -> left, fp);
		}
		if (ptr -> right)
		{
			fprintf (fp, "%d -- %d;", ptr-> val, ptr -> right -> val);
			display_graphical (ptr -> right, fp);
		}
	}
}

void display (tree* root, int choice = 100)
{
	FILE *fp;
	int hh;
	if (!root)
	{
		printf ("\tPLANT A TREE FIRST\n");
		return;
	}
	switch (choice)
	{
		case 1:
			printf ("\tPRE ORDER:: ");
			display_pre_order (root -> root);
			printf ("\n");
			return;
		case 2:
			printf ("\tIN ORDER:: ");
			display_in_order (root -> root);
			printf ("\n");
			return;
		case 3:
			printf ("\tPOST ORDER:: ");
			display_post_order (root -> root);
			printf ("\n");
			return;
		case 4: 
			fp = fopen ("tmp.dot", "w");
			if (root -> root)
				fprintf (fp, "strict graph{ %d;", root -> root -> val);
			else
			{
				printf ("TREE EMPTY\n");
				break;
			}
			display_graphical (root -> root, fp);
			fprintf (fp, "}");
			fclose (fp);
			printf ("dot file with name tmp.dot created, run the command --> `dot -Tpng tmp.dot > graph.png` to generate png image\n");
			system ("dot -Tpng tmp.dot > graph.png");
		default:
			printf ("\tLEVEL ORDER:: \n");
			hh = height (root);
			display_level_order (root -> root, hh);
	}
}


void destroy (node* ptr)
{
	if (ptr)
	{
		destroy (ptr -> left);
		destroy (ptr -> right);
		free (ptr);
	}
}

bool clear (tree* root)
{
	if (root)
	{
		destroy (root -> root);
		root -> root = NULL;
		free (root);
		return true;
	}
	else
		return false;
}

bool tree_planted (tree *root)
{
	if (root == NULL)
	{
		printf ("\tPLANT A TREE FIRST\n");
		return false;
	}
	else
		return true;
}

void  cs ()
{
	char ch;
	while (ch = getchar ())
		if (ch == '\n')
			break;
}

int main ()
{
	tree* root = NULL;
	int ch, val;

	while (true)
	{
		//take user preference
		printf ("\n1:: Add\n2:: Del\n3:: Search\n4:: Traverse\n5:: Display Graphical\n6:: Display\n7:: Uproot the tree\n8:: Plant a Tree\n9:: Exit\n\tEnter Choice--> ");
		scanf ("%d", &ch);
		
		switch (ch)
		{
			case 1:
				if (tree_planted (root))
				{
					printf ("Enter value to insert:: ");
					scanf ("%d", &val);
					if (add_node (root, val))
						printf ("\t...Success.\n");
					else
						printf ("\t...Failure.\n");
				}
				break;
			case 2:
				if (tree_planted (root))
				{
					printf ("Enter value to remove:: ");
					scanf ("%d", &val);
					if (remove_node (root, val))
						printf ("\t...Success.\n");
					else
						printf ("\t...Failure.\n");
				}
				break;
			case 3:
				if (tree_planted (root))
				{
					printf ("Enter value to search:: ");
					scanf ("%d", &val);
					if (find (root, val))
						printf ("\t...Success.\n");
					else
						printf ("\t...Failure.\n");
				}
				break;
			case 4:
				if (tree_planted (root))
				{
					printf ("Enter \n\t1 for Pre-order\n\t2 for In-order\n\t3 for Post-order\n\t\t\tchoice--> ");
					scanf ("%d", &val);
					display (root, val);
				}
				break;
			case 5:
				if (tree_planted (root))
				{
					display (root, 4);
				}
				break;
			case 6:
				if (tree_planted (root))
				{
					display (root);
				}
				break;
			case 7:
				if (tree_planted (root))
				{
					clear (root);
					printf ("\tTREE UPROOTED.\n");
					root = NULL;
				}
				break;
			case 8:
				clear (root);
				root = plant_a_tree ();
				break;
			default:
				clear (root);
				root = NULL;
				exit (0);
		}
		cs ();
	}
	
}
