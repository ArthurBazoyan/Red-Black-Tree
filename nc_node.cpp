#include "RBtree.h"

/* functions for the nested class node start here */

// add functions start here

void c_RBtree::nc_node::add_left(int info)
{
	nc_node* temp = new nc_node(info);
	temp->set_parent(this);
	left = temp;
}


void c_RBtree::nc_node::add_right(int info)
{
	nc_node* temp = new nc_node(info);
	temp->set_parent(this);
	right = temp;
}

//add functions end here

//set functions start here

void c_RBtree::nc_node::set_parent(nc_node* par)
{
	parent = par;
}

void c_RBtree::nc_node::set_right(nc_node* child)
{
	right = child;
}


void c_RBtree::nc_node::set_left(nc_node* child)
{
	left = child;
}

void c_RBtree::nc_node::set_children(nc_node * child)
{
	set_right(child);
	set_left(child);
}


void c_RBtree::nc_node::set_data(int info)
{
	value = info;
}

void c_RBtree::nc_node::set_color(color_ paint)
{
	// 1 is red, 0 is black
	color = paint;
}

// set functions end here

// get functions start here


typename c_RBtree::nc_node* c_RBtree::nc_node::get_parent() const
{
	return parent;
}

c_RBtree::nc_node* c_RBtree::nc_node::get_child() const
{
	if (left->get_data() == NULL && right->get_data() == NULL)
		return nullptr;
	if (left->get_data() != NULL && right->get_data() == NULL)
		return left;
	if (left->get_data() == NULL && right->get_data() != NULL)
		return right;
}


typename c_RBtree::nc_node* c_RBtree::nc_node::get_right() const
{
	return right;
}


typename c_RBtree::nc_node* c_RBtree::nc_node::get_left() const
{
	return left;
}


typename c_RBtree::nc_node* c_RBtree::nc_node::get_sibling() const
{
	if (is_left())
		return parent->right;
	return parent->left;
}

c_RBtree::nc_node* c_RBtree::nc_node::get_uncle() const
{
	return parent->get_sibling();
}


c_RBtree::nc_node* c_RBtree::nc_node::get_grandparent() const
{
	return parent->get_parent();
}


int c_RBtree::nc_node::get_data() const
{
	return value;
}


enum c_RBtree::color_
	c_RBtree::nc_node::get_color() const
{
	return color;
}


int c_RBtree::nc_node::get_height() const
{
	if ( value == NULL)
		throw("c_RBtree::nc_node::get_height - Node is non existent!");
	int left_height = left->get_height();
	int right_height = right->get_height();

	return std::max(left_height, right_height);
}


int c_RBtree::nc_node::get_black_height() const
{
	int height = 0;
	if ( value == NULL)
		return 1;
	if (color == BLACK)
		height += 1;
	height += left->get_black_height();
	return (height - 1);
}

	// get functions end here

	//additional functions start here


bool c_RBtree::nc_node::is_left() const
{
	if (parent == nullptr)
		return false;
	if (parent->left == this)
		return true;
	return false;
}

bool c_RBtree::nc_node::has_children() const
{
	if (left->get_data() != NULL && right->get_data() != NULL)
		return true;
	return false;
}

bool c_RBtree::nc_node::has_child() const
{
	if (left->get_data() != NULL || right->get_data() != NULL)
		return true;
	return false;
}

bool c_RBtree::nc_node::has_red_child() const
{
	if (left->get_color() == RED || right->get_color() == RED)
		return true;
	return false;
}

bool c_RBtree::nc_node::is_leaf() const
{
	if (left->get_data() == NULL && right->get_data() == NULL)
		return true;
	return false;
}


// additional functions end here

/* functions for the nested class node end here */
