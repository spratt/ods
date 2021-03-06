/*
 * main.cpp
 *
 *  Created on: 2011-11-23
 *      Author: morin
 */
#include <cmath>
#include <cassert>
#include <ctime>
#include <cstdlib>

#include <iostream>
using namespace std;

#include "ArrayStack.h"
#include "FastArrayStack.h"
#include "ArrayDeque.h"
#include "DualArrayDeque.h"
#include "RootishArrayStack.h"
#include "DLList.h"
#include "SEList.h"
#include "SkiplistList.h"

#include "FastSqrt.h"

#include "SkiplistSSet.h"
#include "BinarySearchTree.h"
#include "Treap.h"
#include "ScapegoatTree.h"
#include "RedBlackTree.h"

#include "BinaryHeap.h"
#include "MeldableHeap.h"

#include "BinaryTree.h"

#include "Algorithms.h"

using namespace ods;

#ifndef CLOCKS_PER_SEC
#define CLOCKS_PER_SEC 1000
#endif

const unsigned RA=0x0001;   // random access
const unsigned FM=0x0002;   // front modifications

void sqrtTests() {
	int n = 1 << 30;
	clock_t start, stop;

	cout << "Initializing sqrt tables " << n << " inputs...";
	cout.flush();
	start = clock();
	FastSqrt::init();
	stop = clock();
	cout << "done (" << ((double)(stop-start))/CLOCKS_PER_SEC << "s)" << endl;

/*
	cout << "Testing correctness of " << n << " inputs...";
	cout.flush();
	start = clock();
	for (int t = 1; t < n; t++) {
		if ((t & 0xfffff) == 0xfffff)
			cout << "."; cout.flush();
		int x = t;
		int logx = FastSqrt::log(x);
		assert(((1 << logx) & x) != 0);
		assert((((1 << (logx + 1)) - 1) & x) == x);
		double ms = sqrt(x);
		double fss = FastSqrt::sqrt(x);
		assert (fabs(ms - fss) <= 2.0);
	}
	stop = clock();
	cout << "passed!" << endl;
*/

	n = 1 << 27;

	cout << "Computing " << n << " sqrt roots...";
	cout.flush();
	start = clock();
	for (int i = 0; i < n; i++) {
		sqrt(i);
	}
	stop = clock();
	cout << "done (" << ((double)(stop-start))/CLOCKS_PER_SEC << "s)" << endl;

	cout << "Computing " << n << " FastSqrt::sqrt roots...";
	cout.flush();
	start = clock();
	for (int i = 0; i < n; i++) {
		FastSqrt::sqrt(i);
	}
	stop = clock();
	cout << "done (" << ((double)(stop-start))/CLOCKS_PER_SEC << "s)" << endl;
}

template<class Tree>
void btTests(Tree &t) {
	t.size();
	t.size2();
	t.height();
	t.bfTraverse();
	t.traverse();
	t.traverse2();
}

template<class Heap>
void heapTests(Heap &h, int n) {
	clock_t start, stop;
	cout << "Adding " << n << " elements...";
	cout.flush();
	start = clock();
	for (int i = 0; i < n; i++) {
		h.add(rand()%100);
	}
	stop = clock();
	cout << "done (" << ((double)(stop-start))/CLOCKS_PER_SEC << "s)" << endl;

	cout << "Removing " << n << " elements...";
	cout.flush();
	start = clock();
	int p = h.remove();
	for (int i = 1; i < n; i++) {
		assert(h.size() == n-i);
		int q = h.remove();
		assert(p <= q);
		p = q;
	}
	stop = clock();
	cout << "done (" << ((double)(stop-start))/CLOCKS_PER_SEC << "s)" << endl;
}

template <class SortedSet>
void ssetTests(SortedSet &ss, int n, unsigned flags) {
	clock_t start, stop;
	cout << "Adding " << n << " elements...";
	cout.flush();
	start = clock();
	for (int i = 0; i < n; i++) {
		ss.add(rand());
	}
	stop = clock();
	cout << "done (" << ((double)(stop-start))/CLOCKS_PER_SEC << "s)" << endl;

	cout << "Finding " << n << " elements...";
	cout.flush();
	start = clock();
	for (int i = 0; i < n; i++) {
		int z = rand();
		int y = ss.find(z);
		if (i % 300000 == 0) {
			cout << "[" << z << "=>" << y << "]";
		}
	}
	stop = clock();
	cout << "done (" << ((double)(stop-start))/CLOCKS_PER_SEC << "s)" << endl;

	cout << "Running binary tree tests...";
	cout.flush();
	start = clock();
	btTests(ss);
	stop = clock();
	cout << "done (" << ((double)(stop-start))/CLOCKS_PER_SEC << "s)" << endl;

	cout << "Removing " << n << " elements...";
	cout.flush();
	start = clock();
	for (int i = 0; i < n; i++) {
		ss.remove(rand());
	}
	stop = clock();
	cout << "done (" << ((double)(stop-start))/CLOCKS_PER_SEC << "s)" << endl;

	cout << "Final size is " << ss.size() << endl;

	cout << "Clearing " << ss.size() << " elements...";
	cout.flush();
	start = clock();
	ss.clear();
	stop = clock();
	cout << "done (" << ((double)(stop-start))/CLOCKS_PER_SEC << "s)" << endl;
}

template <class List>
void listTests(List &ell, int n, unsigned flags)
{
	cout.setf(ios::fixed,ios::floatfield);
	cout.precision(5);

	ell.clear();

	clock_t start, stop;
	cout << "Adding " << n << " elements...";
	cout.flush();
	start = clock();
	for (int i = 0; i < n; i++)
		ell.add(ell.size(), i);
	stop = clock();
	cout << "done (" << ((double)(stop-start))/CLOCKS_PER_SEC << "s)" << endl;

	if (flags & RA) {
		cout << "Reading " << n << " elements...";
		cout.flush();
		start = clock();
		for (int i = 0; i < n; i++)
			assert(ell.get(i) == i);
		stop = clock();
		cout << "done (" << ((double)(stop-start))/CLOCKS_PER_SEC << "s)" << endl;

		cout << "Setting " << n << " elements...";
		cout.flush();
		start = clock();
		for (int i = 0; i < n; i++)
			ell.set(i, 2*i);
		stop = clock();
		cout << "done (" << ((double)(stop-start))/CLOCKS_PER_SEC << "s)" << endl;
	} else {
		cout << "Reading 2log(" << n << ") elements...";
		cout.flush();
		start = clock();
		for (int i = 1; i < n; i*=2) {
			assert(ell.get(i) == i);
			assert(ell.get(n-i-1) == n-i-1);
		}
		stop = clock();
		cout << "done (" << ((double)(stop-start))/CLOCKS_PER_SEC << "s)" << endl;

		cout << "Setting 2log(" << n << ") elements...";
		cout.flush();
		start = clock();
		for (int i = 1; i < n; i*=2) {
			ell.set(i, 2*i);
			ell.set(n-i-1, 2*(n-i-1));
		}
		stop = clock();
		cout << "done (" << ((double)(stop-start))/CLOCKS_PER_SEC << "s)" << endl;

	}

	if (flags & FM) {
		cout << "Adding " << n << " elements at front...";
		cout.flush();
		start = clock();
		for (int i = 0; i < n; i++)
			ell.add(0, i);
		stop = clock();
		cout << "done (" << ((double)(stop-start))/CLOCKS_PER_SEC << "s)" << endl;

		cout << "Removing " << n << " elements at front...";
		cout.flush();
		start = clock();
		for (int i = 0; i < n; i++)
			ell.remove(0);
		stop = clock();
		cout << "done (" << ((double)(stop-start))/CLOCKS_PER_SEC << "s)" << endl;
	} else {
		cout << "Adding log(" << n << ") elements at front...";
		cout.flush();
		start = clock();
		for (int i = 1; i < n; i*=2)
			ell.add(0, i);
		stop = clock();
		cout << "done (" << ((double)(stop-start))/CLOCKS_PER_SEC << "s)" << endl;

		cout << "Removing log(" << n << ") elements at front...";
		cout.flush();
		start = clock();
		for (int i = 1; i < n; i*=2)
			ell.remove(0);
		stop = clock();
		cout << "done (" << ((double)(stop-start))/CLOCKS_PER_SEC << "s)" << endl;
	}

	cout << "Removing " << n << " elements...";
	cout.flush();
	start = clock();
	for (int i = 0; i < n; i++)
		ell.remove(ell.size()-1);
	stop = clock();
	cout << "done (" << ((double)(stop-start))/CLOCKS_PER_SEC << "s)" << endl;
}

void sortTests(int n) {
	clock_t start, stop;
	array<int> a(n);

	for (int i = 0; i < n; i++)
		a[i] = rand();
	cout << "Sorting " << n << " elements using quickSort...";
	cout.flush();
	start = clock();
	quickSort(a);
	stop = clock();
	cout << "done (" << ((double)(stop-start))/CLOCKS_PER_SEC << "s)" << endl;
	for (int i = 1; i < n; i++)
		assert(a[i-1] <= a[i]);

	for (int i = 0; i < n; i++)
		a[i] = rand();
	cout << "Sorting " << n << " elements using heapSort...";
	cout.flush();
	start = clock();
	heapSort(a);
	stop = clock();
	cout << "done (" << ((double)(stop-start))/CLOCKS_PER_SEC << "s)" << endl;
	for (int i = 1; i < n; i++)
		assert(a[i-1] <= a[i]);

	for (int i = 0; i < n; i++)
		a[i] = rand();
	cout << "Sorting " << n << " elements using mergeSort...";
	cout.flush();
	start = clock();
	mergeSort(a);
	stop = clock();
	cout << "done (" << ((double)(stop-start))/CLOCKS_PER_SEC << "s)" << endl;
	for (int i = 1; i < n; i++)
		assert(a[i-1] <= a[i]);

}


int main(int argc, char **argv)
{
	int n = 1000000;

	sortTests(n);

	{
		cout << endl << "BinaryTree:" << endl;
		BinaryTree<BTNode1> t;
		btTests(t);
	}


	{
		cout << endl << "BinaryHeap<int>:" << endl;
		BinaryHeap<int> h;
		heapTests(h, n);
	}

	{
		cout << endl << "MeldableHeap<int>:" << endl;
		MeldableHeap1<int> h;
		heapTests(h, n);
	}

	{
		cout << endl << "RedBlackTree<int>:" << endl;
		RedBlackTree1<int> t;
		btTests(t);
		ssetTests(t, n, 0x0);
	}

	{
		cout << endl << "ScapegoatTree<int>:" << endl;
		ScapegoatTree1<int> t;
		btTests(t);
		ssetTests(t, n, 0x0);
	}

	{
		cout << endl << "BinarySearchTree<int>:" << endl;
		BinarySearchTree1<int> t;
		btTests(t);
		ssetTests(t, n, 0x0);
	}

	{
		cout << endl << "Treap<int>:" << endl;
		Treap1<int> t;
		btTests(t);
		ssetTests(t, n, 0x0);
	}


/*
	{
		cout << endl << "SkiplistSet<int>:" << endl;
		SkiplistSSet<int> s;
		ssetTests(s, n, 0x0);
	}
*/

	{
		BinarySearchTree<BSTNode1<int>,int> s;
		ssetTests(s, n, 0x0);
	}

	// sqrtTests();

	cout << endl << "ArrayStack<int>:" << endl;
	ArrayStack<int> as;
	listTests(as, n, RA);

	cout << endl << "FastArrayStack<int>:" << endl;
	FastArrayStack<int> fas;
	listTests(fas, n, RA);

	cout << endl << "ArrayDeque<int>:" << endl;
	ArrayDeque<int> ad;
	listTests(ad, n, RA|FM);

	cout << endl << "DualArrayDeque<int>:" << endl;
	DualArrayDeque<int> dad;
	listTests(dad, n, RA|FM);

	cout << endl << "RootishArrayStack<int>:" << endl;
	RootishArrayStack<int> ras;
	listTests(ras, n, RA);

	cout << endl << "DLList<int>:" << endl;
	DLList<int> dll;
	listTests(dll, n, FM);

	{
	cout << endl << "SEList<int>:" << endl;
	SEList<int> sel(50);
	listTests(sel, n, FM);
	}

	{
	cout << endl << "SkiplistList<int>:" << endl;
	SkiplistList<int> sel;
	listTests(sel, n, RA|FM);
	}

	return 0;
}

