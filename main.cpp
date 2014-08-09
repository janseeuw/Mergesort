//
//  Created by Jonas Anseeuw
//  Copyright (c) 2014 Jonas Anseeuw. All rights reserved.
//

#include <iostream>
#include <vector>
#include "math.h"

using namespace std;

template<typename T>
class MergeSort{
public:
	void operator() (vector<T> & v) const{
		vector<T> h(v.size());
		mergesort(v, 0, v.size()-1, h);
	}
private:
	void merge(vector<T> &v, int l, int m, int r, vector<T> &h) const{
		int i, j;
		for(i = m+1; i>l; i--) h[i-1] = v[i-1];
		for(j=m; j<r; j++) h[r+m-j] = v[j+1];
		for(int k = l; k<= r; k++){
			if (h[j]<h[i]){
				v[k] = h[j--];
			}else{
				v[k] = h[i++];
			}
		}
	}
	void mergesort(vector<T>&v, int l, int r, vector<T>&h) const{
		if(l < r){
			int m =l+(r-l)/2; // safer than (l+r)/2
			mergesort(v, l, m, h);
			mergesort(v, m+1, r, h);
			merge(v, l, m, r, h);
		}
	}
};

template<typename T>
class MergeSortBottomUp{
public:
	void operator() (vector<T> & v) const{
		mergesort(v, 0, v.size()-1);
	}
private:
	int min(int a, int b) const{
		return (a<b)? a:b;
	}
	void merge(vector<T> &v, int l, int m, int r) const{
		int i, j;
		vector<T>h(v.size());
		for(i = m+1; i>l; i--) h[i-1] = v[i-1];
		for(j=m; j<r; j++) h[r+m-j] = v[j+1];
		for(int k = l; k<= r; k++){
			if (h[j]<h[i]){
				v[k] = h[j--];
			}else{
				v[k] = h[i++];
			}
		}
	}
	void mergesort(vector<T>&v, int l, int r) const{
		for(int m = 1; m <= r-l; m = m+m)
			for(int i=l; i<= r-m; i+=m+m)
				merge(v, i, i+m-1, min(i+m+m-1,r));
	}
};

int main(int argc, const char * argv[])
{
	int temp[] = {16,2,77,29, 6, 19, 15, 88};
	vector<int> array (temp, temp + sizeof(temp) / sizeof(int) );
	
	MergeSort<int> mergeSort;
	mergeSort(array);
	
	cout << "Sorted array is \n";
	for(int i=0; i<array.size(); i++){
		cout<<array[i]<<" ";
	}
	
    return 0;
}

