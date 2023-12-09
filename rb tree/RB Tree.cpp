#include <iostream>
#include "RB tree.h"
#include "List.h"

int main(){
	tree_elem_generic<int>* nullnode_int = null_init_generic<int>();
	tree_elem_generic<int>* yearTree = root_init_generic(nullnode_int);
	insert(yearTree, nullnode_int, 10);
	insert(yearTree, nullnode_int, 10);
	insert(yearTree, nullnode_int, 9);
	insert(yearTree, nullnode_int, 11);
	insert(yearTree, nullnode_int, 10);
	insert(yearTree, nullnode_int, 10);
	print(yearTree, nullnode_int, 4, 1);
	erase(yearTree, nullnode_int, 10);
	print(yearTree, nullnode_int, 4, 1);
	
}