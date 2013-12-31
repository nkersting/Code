// Give an O.n lg k/-time algorithm to merge k sorted lists into one sorted list,
// where n is the total number of elements in all the input lists. (Hint: Use a minheap
// for k-way merging.)


// First we construct a max-heap from the last element of each list.
// Each element of the heap is node struct.
// Extract the max, add to master list, then insert next element from the list it came from.
// Iterate.



#include<iostream>
#include<vector>
#include<queue>

using namespace std;


struct node
{
   int val;
   int index;
   node(int v, int i)
      {
         val = v;
         index = i;
      }
};


bool operator>=(const node& n1, const node& n2)
{
   if (n1.val >= n2.val) return true;
   return false;
}

bool operator<(const node& n1, const node& n2)
{
   if (n1.val < n2.val) return true;
   return false;
}



int main()
{
   vector<vector<int> > lists;
   vector<int> result;
   priority_queue<node> maxheap;

   //initialize lists
   int total_count = 0;
   for (int i = 0; i < 5; ++i)
   {
      vector<int> curr_list;
      for (int j = 10*i; j < 10*i + 10; ++j)
      {
         curr_list.push_back(j);
         total_count++;
      }
      lists.push_back(curr_list);
   }


   // print initial lists
   for (vector<vector<int> >::iterator it = lists.begin(); it != lists.end(); ++it)
   {
      for (vector<int>::iterator it2 = it->begin(); it2 != it->end(); ++it2)
      {
         cout << *it2 << " ";
      }
      cout << endl;
   }


   // construct initial heap
   int list_count = 0;
   for (vector<vector<int> >::iterator it = lists.begin(); it != lists.end(); ++it)
   {
      maxheap.push(node(it->back(), list_count));
      it->pop_back();
      list_count++;
   }


   while(result.size() < total_count)
   {
      node top(maxheap.top().val, maxheap.top().index);
      result.push_back(top.val);
      maxheap.pop();
      if (lists.at(top.index).size() > 0)
      {
         maxheap.push(node(lists.at(top.index).back(), top.index));
         lists.at(top.index).pop_back();
      }
   }

   for (vector<int>::iterator it = result.begin(); it != result.end(); ++it)
   {
      cout << *it << endl;
   }

}
