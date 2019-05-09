#include <iostream>
#include "RBtree.h"


int main()
{
	int size = 0;
	int node;
	int node_to_delete;
	c_RBtree myTree;

	int i = 1;
	while(true)
	{
		std::cout << "Type '" << -1 << "' if you want to stop adding nodes . . . " << std::endl;
		std::cout << "Please input the node number: " << i << std::endl;
		std::cin >> node;
		if (node == -1)
			break;
		if (myTree.search(node))
		{
			std::cout << "Node already exists!, please insert another one . . . " << std::endl;
			continue;
		}
		myTree.add_node(node);
		myTree.print();
		i++;
	}

	int answer = 0;
	std::cout << std::endl;
	std::cout << "If you wish to delete Nodes type 1 if not type 0 ";
	std::cin >> answer;

	if (answer == 1)
	{
		while ( i != 0)
		{
			std::cout << "Type '" << -1 << "' if you want to stop deleting nodes . . . " << std::endl;
			std::cout << "Please input the node to be deleted: " << std::endl;
			std::cin >> node_to_delete;
			if (!myTree.search(node_to_delete))
			{
				std::cout << "Node doesn't exist! Try another node!";
				continue;
			}
			myTree.remove_node(node_to_delete);
			myTree.print();
			i--;
		}
	}

	system("pause");
	return 0;
}