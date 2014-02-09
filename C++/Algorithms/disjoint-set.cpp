#include <cassert>

template<typename T>
struct DisjointSet
{
	T data;
	DisjointSet* parent;
	unsigned int rank;

	DisjointSet(T d): data(d), parent(0), rank(0) {};
	DisjointSet(): parent(0), rank(0) {};
};

template<typename T>
DisjointSet<T>*
setUnion(DisjointSet<T>* x, DisjointSet<T>* y) {
	DisjointSet<T> *xRoot, *yRoot;

	xRoot = setFind(x);
	yRoot = setFind(y);
	if (xRoot == yRoot)
		return xRoot;

	if (xRoot->rank < yRoot->rank) {
		xRoot->parent = yRoot;
		return yRoot;
	}
	else if (yRoot->rank < xRoot->rank) {
		yRoot->parent = xRoot;
		return xRoot;
	}
	else {
		yRoot->parent = xRoot;
		xRoot->rank++;
		return xRoot;
	}
}

template <typename T>
DisjointSet<T>*
setFind(DisjointSet<T>* x) {
	if (x->parent == 0)
		return x;

	return x->parent = setFind(x->parent);
}

int main() {
	DisjointSet<int> a, b;

	assert(setFind(&a) == &a);
	assert(setFind(&b) == &b);

	DisjointSet<int>* c = setUnion(&a, &b);
	assert(c == &a);
}
