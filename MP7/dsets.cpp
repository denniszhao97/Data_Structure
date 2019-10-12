/* Your code here! */
#include "dsets.h"
/*
*Creates n unconnected root nodes at the end of the vector.
*/
void DisjointSets::addelements (int num){
	for(int i = 0; i < num; i++)
	{
		sets.push_back(-1);
	}
	return;
}
/*
*This function should compress paths and works as described in lecture.
*/
int DisjointSets::find (int elem){
	if(sets[elem] < 0)
		return elem;
	return sets[elem] = find(sets[elem]);
}
/*
*This function should be implemented as union-by-size.
That is, when you setunion two disjoint sets, the smaller
(in terms of number of nodes) should point at the larger. This function
works as described in lecture, except that you should not assume that the arguments
to setunion are roots of existing uptrees.
Your setunion function SHOULD find the roots of its arguments before
combining the trees. If the two sets are the same size, make the tree
containing the second argument point to the tree containing the first.
*/
void DisjointSets::setunion (int a, int b){
	int root1 = find(a);
	int root2 = find(b);
	int newSize = sets[root1] + sets[root2];
	if(sets[root1] <= sets[root2]){
		sets[root2] = root1;
		sets[root1] = newSize;
	} else{
		sets[root1] = root2;
		sets[root2] = newSize;
	}
}
/*
*Return the size of the uptree containing elem.
*/
int DisjointSets::size(int elem){

	return sets[elem];

}
