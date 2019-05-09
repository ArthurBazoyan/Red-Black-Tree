#include "RBtree.h"

/* functions for the main c_RBtree class start here */

// public functions start here

c_RBtree::c_RBtree()
{
	nil_node = new nc_node(NULL);
	nil_node->set_color(BLACK);
	root = nil_node;
	root->set_parent(nil_node);
};

c_RBtree::~c_RBtree()
{
	destroy(root);
	delete nil_node;
};


void c_RBtree::add_node(int info)
{
	if (root == nil_node)
	{
		nc_node* node = new nc_node(info);
		node->set_right(nil_node);
		node->set_left(nil_node);
		root = node;
		root->set_parent(nil_node);
		add_node_fixup(root);
	}
	else
	{
		nc_node* temp = root;
		nc_node* temp_par = nil_node;
		while (temp != nil_node)
		{
			temp_par = temp;
			if (info > temp->get_data())
			{
				temp = temp->get_right();
				continue;
			}
			else
			{
				temp = temp->get_left();
				continue;
			}
		}
		if (info >= temp_par->get_data())
		{
			temp_par->add_right(info);
			temp_par->get_right()->set_children(nil_node);
			add_node_fixup(temp_par->get_right());
		}
		else
		{
			temp_par->add_left(info);
			temp_par->get_left()->set_children(nil_node);
			add_node_fixup(temp_par->get_left());
		}
	}
}


void c_RBtree::add_node_fixup(nc_node* current)
{
	// case: current is root
	if (current == root)
	{
		root->set_color(BLACK);
		return;
	}
	// case: current parent is not BLACK
	if (current->get_parent()->get_color() != BLACK)
	{
		// case: parent is RED, uncle is RED
		if (current->get_uncle()->get_color() == RED)
		{
			// paint parent and uncle BLACK, grandparent RED call the fixup function on grandparent
			current->get_parent()->set_color(BLACK);
			current->get_uncle()->set_color(BLACK);
			current->get_grandparent()->set_color(RED);
			add_node_fixup(current->get_grandparent());
			return;
		}
		// case: parent is RED, uncle is BLACK
		else
		{
			// case: left left
			if (current->get_parent()->is_left() && current->is_left())
			{
				recolor(current->get_grandparent());
				recolor(current->get_parent());
				right_rotate(current->get_grandparent());
				return;
			}

			// case: left right, 
			if (current->get_parent()->is_left() && !current->is_left())
			{
				left_rotate(current->get_parent());
				add_node_fixup(current->get_left());
				return;
			}

			// case: right right
			if (!current->get_parent()->is_left() && !current->is_left())
			{
				recolor(current->get_parent());
				recolor(current->get_grandparent());
				left_rotate(current->get_grandparent());
				return;
			}

			// case: right left
			if (!current->get_parent()->is_left() && current->is_left())
			{
				right_rotate(current->get_parent());
				add_node_fixup(current->get_right());
				return;
			}
		}
	}
}


void c_RBtree::remove_node(int info)
{
	if (!search(info))
		std::cout << "Key Not Found! Try Again!" << std::endl;
	nc_node* node_to_delete = get_node(info);
	if (node_to_delete->has_children())
	{
		//throw("Cannot delete a Node which has 2 children - c_RBtree::remove_node ");
		std::cout << "Cannot delete a Node with 2 children" << std::endl;
		return;
	}
		
	if (node_to_delete == root && node_to_delete->is_leaf())
	{
		node_to_delete->set_right(nullptr);
		node_to_delete->set_left(nullptr);
		delete node_to_delete;
		root = nil_node;
		return;
	}
	if (node_to_delete == root && node_to_delete->has_child())
	{
		nc_node* child = node_to_delete->get_child();
		if (child->is_left())
		{
			right_rotate(node_to_delete);
			root->set_right(nil_node);
		}
		else
		{
			left_rotate(node_to_delete);
			root->set_left(nil_node);
		}
		root->set_color(BLACK);
		node_to_delete->set_right(nullptr);
		node_to_delete->set_left(nullptr);
		delete node_to_delete;

		return;
	}
	// case where is leaf and is red,
	if (node_to_delete->get_color() == RED && node_to_delete->is_leaf())
	{
		node_to_delete->set_right(nullptr);
		node_to_delete->set_left(nullptr);
		if (node_to_delete->is_left())
			node_to_delete->get_parent()->set_left(nil_node);
		else
			node_to_delete->get_parent()->set_right(nil_node);
		delete node_to_delete;
		return;
	}

	if (node_to_delete->has_child() && node_to_delete->get_child()->get_color() == RED)
	{
		// recolor the child
		recolor(node_to_delete->get_child());
		node_to_delete->get_child()->set_parent(node_to_delete->get_parent());
		if (node_to_delete->is_left())
			node_to_delete->get_parent()->set_left(node_to_delete->get_child());
		else
			node_to_delete->get_parent()->set_right(node_to_delete->get_child());

		node_to_delete->set_right(nullptr);
		node_to_delete->set_left(nullptr);
		delete node_to_delete;
		return;
	}

	nc_node* child = node_to_delete->get_child();
	color_ child_color;
	if (child != nullptr)
		child_color = child->get_color();
	else
		child_color = BLACK;


	nc_node* parent = node_to_delete->get_parent();
	if (child_color == RED || node_to_delete->get_color() == RED)
	{
		if (child != nullptr)	//if it has a child switch the positions then delete the node 
		{
			if (node_to_delete->is_left())
			{
				parent->set_left(child);
				child->set_parent(parent);
			}
			else
			{
				parent->set_right(child);
				child->set_parent(parent);
			}
		}
		else        // if doesnt have a child, delete the node 
		{
			if (node_to_delete->is_left())
				node_to_delete->get_parent()->set_left(nil_node);
			else
				node_to_delete->get_parent()->set_right(nil_node);
			node_to_delete->set_right(nullptr);
			node_to_delete->set_left(nullptr);
			delete node_to_delete;
			return;
		}

	}

	if (child_color == BLACK && node_to_delete->get_color() == BLACK)
	{
		if (child != nullptr)
		{
			if (node_to_delete->is_left())
			{
				parent->set_left(child);
				child->set_parent(parent);
				// now child is double black
				remove_node_fixup(child);
			}
			else
			{
				parent->set_right(child);
				child->set_parent(parent);
				// now child is double black
				remove_node_fixup(child);
			}
		}
		else
		{
			remove_node_fixup(node_to_delete);
		}
	}	
	if (node_to_delete->is_left())
		node_to_delete->get_parent()->set_left(nil_node);
	else
		node_to_delete->get_parent()->set_right(nil_node);
	node_to_delete->set_right(nullptr);
	node_to_delete->set_left(nullptr);
	delete node_to_delete;
}

void c_RBtree::remove_node_fixup(nc_node * current)
{
	if (current == root)
		return;
	nc_node* sibling = current->get_sibling();
	if (sibling->get_color() == BLACK)
	{
		if (sibling->has_children())
		{
			if (!sibling->is_left())
			{
				// right right case
				if (sibling->get_right()->get_color() == RED || (sibling->get_right()->get_color() == RED && sibling->get_left()->get_color() == RED))
				{
					if (sibling->get_parent()->get_color() == RED)
						sibling->get_parent()->set_color(BLACK);
					sibling->set_color(sibling->get_parent()->get_color());
					sibling->get_right()->set_color(BLACK);
					sibling->get_parent()->set_color(BLACK);
					left_rotate(sibling->get_parent());
					return;
				}
				//right left case
				if (sibling->get_left()->get_color() == RED)
				{
					recolor(sibling);
					recolor(sibling->get_left());
					right_rotate(sibling);
					remove_node_fixup(current);
				}
			}
			else
			{
				//left left case
				if (sibling->get_left()->get_color() == RED || (sibling->get_right()->get_color() == RED && sibling->get_left()->get_color() == RED))
				{
					if (sibling->get_parent()->get_color() == RED)
						sibling->get_parent()->set_color(BLACK);
					sibling->set_color(sibling->get_parent()->get_color());
					sibling->get_left()->set_color(BLACK);
					sibling->get_parent()->set_color(BLACK);
					right_rotate(sibling->get_parent());
					return;
				}
				// left right case
				if (sibling->get_right()->get_color() == RED)
				{
					recolor(sibling);
					recolor(sibling->get_right());
					left_rotate(sibling);
					remove_node_fixup(current);
				}
			}
		}
		// sibling has 1 child and sibling is black
		else if (sibling->has_child())
		{
			nc_node* child = sibling->get_child();
			if (child->get_color() == RED)
			{
				if (!sibling->is_left())
				{
					// right right case
					if (!child->is_left())
					{
						sibling->set_color(sibling->get_parent()->get_color());
						sibling->get_right()->set_color(BLACK);
						sibling->get_parent()->set_color(BLACK);
						left_rotate(sibling->get_parent());
						return;
					}
					//right left case
					else if (child->is_left())
					{
						recolor(sibling);
						recolor(child);
						right_rotate(sibling);
						remove_node_fixup(current);
						return;
					}
				}
				else
				{
					// left right case
					if (!child->is_left())
					{
						recolor(sibling);
						recolor(child);
						left_rotate(sibling);
						remove_node_fixup(current);
						return;
					}
					//left left case
					else if (child->is_left())
					{
						sibling->set_color(sibling->get_parent()->get_color());
						sibling->get_left()->set_color(BLACK);
						sibling->get_parent()->set_color(BLACK);
						right_rotate(sibling->get_parent());
						return;
					}
				}
			}
		}
		// sibling doesnt have children or both are black
		if( !sibling->has_children() || (sibling->get_right()->get_color() == BLACK && sibling->get_left()->get_color() == BLACK) )
		{
			sibling->set_color(RED);
			if (sibling->get_parent()->get_color() == BLACK)
				remove_node_fixup(sibling->get_parent());
			else
				sibling->get_parent()->set_color(BLACK);
		}
	}
	// sibling is RED
	else
	{
		if (sibling->is_left())
		{
			recolor(sibling);
			recolor(current->get_parent());
			right_rotate(current->get_parent());
			remove_node_fixup(current);
			return;
		}
		else
		{
			recolor(sibling);
			recolor(current->get_parent());
			left_rotate(current->get_parent());
			remove_node_fixup(current);
			return;
		}
	}
}


c_RBtree::nc_node* c_RBtree::get_root() const
{
	return root;
}


void c_RBtree::left_rotate(nc_node* current)
{
	do_left_rotate(current);
}


void c_RBtree::right_rotate(nc_node* current)
{
	do_right_rotate(current);
}

void c_RBtree::recolor(nc_node* current)
{
	if(current == root)
		current->set_color(BLACK);
	if ( current == nil_node)
		return;
	if (current->get_color() == RED)
	{
		current->set_color(BLACK);
		return;
	}
	current->set_color(RED);
	return;
}

bool c_RBtree::search( int value)
{
	nc_node* temp = root;

	while (temp != nil_node)
	{
		if (temp->get_data() == value)
			return true;
		if (temp->get_data() > value)
		{
			temp = temp->get_left();
			continue;
		}
		else
		{
			temp = temp->get_right();
			continue;
		}
	}
	return false;
}

c_RBtree::nc_node* c_RBtree::get_node(int key)
{
	if (!search(key))
		return nullptr;
	nc_node* temp = root;
	while (temp->get_data() != key)
	{
		if (temp->get_data() > key)
		{
			temp = temp->get_left();
			continue;
		}
		else 
		{
			temp = temp->get_right();
			continue;
		}
	}
	return temp;
}

void c_RBtree::print()
{
	if (root == nil_node)
	{
		std::cout << "Tree doesn't exist!" << std::endl;
		return;
	}
	std::cout << " 0 is black, 1 is red " << std::endl;
	print2DUtil(root, 0);
}

// public functions end here

//private functitons start here

void c_RBtree::destroy(nc_node* current)
{
	if (current->get_left() != nil_node)
		destroy(current->get_left());
	if (current->get_right() != nil_node)
		destroy(current->get_right());
	
	current->set_left(nullptr);
	current->set_right(nullptr);
	delete current;
}

void c_RBtree::print2DUtil(nc_node* current, int space)
{

	if (current == nil_node)
		return;

	space += COUNT;

	print2DUtil(current->get_right(), space);

	std::cout << std::endl;
	for (int i = COUNT; i < space; i++)
		std::cout << " ";
	std::cout << current->get_data() << ":" << current->get_color() << "\n";

	print2DUtil(current->get_left(), space);
}


void c_RBtree::do_right_rotate(nc_node* current)
{
	nc_node* y = current->get_left();
	current->set_left(y->get_right());
	if (y->get_right() != nil_node)
		y->get_right()->set_parent(current);
	y->set_parent(current->get_parent());
	if (current->get_parent() == nil_node)
		root = y;
	else if (current->is_left())
		current->get_parent()->set_left(y);
	else
		current->get_parent()->set_right(y);
	y->set_right(current);
	current->set_parent(y);
}


void c_RBtree::do_left_rotate(nc_node* current)
{
	nc_node* y = current->get_right();
	current->set_right(y->get_left());
	if (y->get_left() != nil_node)
		y->get_left()->set_parent(current);
	y->set_parent(current->get_parent());
	if (current->get_parent() == nil_node)
		root = y;
	else if (current->is_left())
		current->get_parent()->set_left(y);
	else
		current->get_parent()->set_right(y);
	y->set_left(current);
	current->set_parent(y);
}

//private functions end here

/* functions for the main c_RBtree class end here */