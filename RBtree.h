#pragma once

#include <iostream>
#include <algorithm>
#define COUNT 10

class c_RBtree
{
	enum color_ { RED = 1, BLACK = 0 };
public:
	class nc_node
	{
	public:
		nc_node(int info)
		{
			right = nullptr;
			left = nullptr;
			parent = nullptr;
			value = info;
			color = RED;
		};
		~nc_node()
		{
			destroy();
		};


		// add functions
		void add_left(int info);
		void add_right(int info);
		// set functions
		void set_parent(nc_node* par);
		void set_right(nc_node* child);
		void set_left(nc_node* child);
		void set_children(nc_node* child);
		void set_data(int info);
		void set_color(enum color_ paint);
		// get functions
		nc_node* get_parent() const;
		nc_node* get_child() const;
		nc_node* get_right() const;
		nc_node* get_left() const;
		nc_node* get_sibling() const;
		nc_node* get_uncle() const;
		nc_node* get_grandparent() const;
		int get_data() const;
		enum color_ get_color() const;
		int get_height() const;
		int get_black_height() const;
		//additional functions
		bool is_left() const;
		bool has_children() const;
		bool has_child() const;
		bool has_red_child() const;
		bool is_leaf() const; 

	private:

		void destroy()
		{
			if( left != nullptr)
				delete left;
			if( right != nullptr)
				delete right;
		}

		nc_node* left;
		nc_node* right;
		nc_node* parent;
		int value;
		color_ color;
	};

	c_RBtree();
	~c_RBtree();

public:

	void add_node(int info);
	void add_node_fixup(nc_node* current);
	void remove_node(int info);
	nc_node* get_root() const;
	void left_rotate(nc_node* current);
	void right_rotate(nc_node* current);
	void recolor(nc_node* current);
	bool search( int key );
	nc_node* get_node(int key);
	void print();


private:

	void remove_node_fixup(nc_node* current);
	void destroy(nc_node* current);
	void print2DUtil(nc_node* root, int space);
	void do_right_rotate(nc_node* current);
	void do_left_rotate(nc_node* current);

	nc_node* nil_node;
	nc_node* root;

};