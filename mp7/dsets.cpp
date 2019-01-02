/* Your code here! */
#include "dsets.h"


void DisjointSets::addelements (int num){
	int i;
	for (i = 0; i < num; i++){s.push_back(-1);} 
}

int DisjointSets::find (int elem){
	if(s[elem] < 0){return elem;}
	return find(s[elem]);

}

void DisjointSets::setunion (int a, int b){

	int sum = s[find(a)] + s[find(b)];
	if(find(a) == find(b)){return;}
	
	if(s[find(a)] <= s[find(b)]){
		s[find(b)] = find(a);
		s[find(b)] = sum;
	}
	else{
		s[find(a)] = find(b);
		s[find(b)] = sum;
	}
	return;
}

