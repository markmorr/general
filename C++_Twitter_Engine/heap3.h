#ifndef HEAP_H
#define HEAP_H

#include <vector>
#include <functional>
#include <utility>
#include <algorithm>
#include <stdexcept>
#include <unordered_map>
#include <iostream>
template <
         typename T,
         typename KComparator = std::equal_to<T>,
         typename PComparator = std::less<T>,
         typename Hasher = std::hash<T> >
class Heap
{
public:
    /// Constructs an m-ary heap. M should be >= 2
    Heap(int m = 2,
         const PComparator& c = PComparator(),
         const Hasher& hash = Hasher(),
         const KComparator& kcomp = KComparator()  );

    /// Destructor as needed
    ~Heap();

    /// Adds an item
    void push(const T& item);

    /// returns the element at the top of the heap
    ///  max (if max-heap) or min (if min-heap)
    T const & top() const;

    /// Removes the top element
    void pop();

    /// returns true if the heap is empty
    bool empty() const;

    /// decreaseKey - Finds key matching old object &
    /// updates its location in the heap based on the new value
    void decreaseKey(const T& old, const T& newVal);

    int size() const;

 private:
    /// Add whatever helper functions and data members you need below
  

 private:
   /// Data members - These should be sufficient
    std::vector< T > store_;
    int m_;
    void trickleUp(int loc);
    void trickleDown(int idx);
    PComparator c_;
    std::unordered_map<T, size_t, Hasher, KComparator> keyToLocation_;

};

// Complete!
template <typename T, typename KComparator, typename PComparator, typename Hasher >
Heap<T,KComparator,PComparator,Hasher>::Heap(
    int m,
    const PComparator& c,
    const Hasher& hash,
    const KComparator& kcomp ) :

    store_(),
    m_(m),
    c_(c),
    keyToLocation_(100, hash, kcomp)

{

}

// Complete!
template <typename T, typename KComparator, typename PComparator, typename Hasher >
Heap<T,KComparator,PComparator,Hasher>::~Heap()
{

}

// Incomplete!
template <typename T, typename KComparator, typename PComparator, typename Hasher >
void Heap<T,KComparator,PComparator,Hasher>::push( const T& item)
{

    store_.push_back(item); //may have to change by 1 
    keyToLocation_.insert({item,store_.size()-1});
    trickleUp(store_.size() - 1); //should place it in right location of store_ by priority
    
    //std::cout<< " yooooo" << std::endl;

}


//map and iterate over that 

// Incomplete!
template <typename T, typename KComparator, typename PComparator, typename Hasher >
void Heap<T,KComparator,PComparator,Hasher>::decreaseKey(const T& old, const T& newVal)
{
   //    std::cout << "hiii" << std::endl;
    if(c_(old,newVal)) 
    {
        std::cout << "newVal should be better than old" << std::endl; 
        return;
    }

    
    //store_[keyToLocation_[old]] = newVal;//this should give an item T
    int loc = keyToLocation_[old];
    keyToLocation_.erase(old);
    keyToLocation_.insert(std::make_pair(newVal,loc));
    store_[keyToLocation_[newVal]] = newVal;
    
    // if(old.tag == "software"){
    //     std::cout << "PRINT STUFF OUTT" << std::endl;
    //     for(int i = 0; i < size(); i++){
    //         std::cout << store_[i].tag << " " << store_[i].num << "\t";
    //         std::cout << std::endl;
    //     }
    // }
    trickleUp(keyToLocation_[newVal]);
  
    

}

// Complete!
template <typename T, typename KComparator, typename PComparator, typename Hasher >
T const & Heap<T,KComparator,PComparator,Hasher>::top() const
{
    // Here we use exceptions to handle the case of trying
    // to access the top element of an empty heap
    if(empty()) {
        throw std::logic_error("can't top an empty heap");
    }
    // If we get here we know the heap has at least 1 item
    // Add code to return the top element
    return store_[0];
}

// Incomplete!
template <typename T, typename KComparator, typename PComparator, typename Hasher >
void Heap<T,KComparator,PComparator,Hasher>::pop()
{
    //std::cout << "PRINNTTT POPPPP STATEMENTTT" << std::endl;
    if(empty()) {
        throw std::logic_error("can't pop an empty heap");
    }

    //std::cout<< "popping" << std::endl;
    keyToLocation_.erase(store_[0]);
    store_[0] = store_[size()-1]; //swap it
    store_.pop_back();//pop it from the vector
    keyToLocation_[store_[0]] = 0;
    trickleDown(0); 

    //can re-alter this guy

}

/// Complete!
template <typename T, typename KComparator, typename PComparator, typename Hasher >
bool Heap<T,KComparator,PComparator,Hasher>::empty() const
{
    return store_.empty();
}




template <typename T, typename KComparator, typename PComparator, typename Hasher >
int Heap<T,KComparator,PComparator,Hasher>::size() const
{
    return store_.size();
}



template <typename T, typename KComparator, typename PComparator, typename Hasher >
  void Heap<T,KComparator,PComparator,Hasher>::trickleDown(int idx)
  {
   
   
   //int best  = store_[smallerChild];
    int myguy = m_*idx + 1; 
    if(myguy >= size()) //checking if index is a leaf node
    {
      return;
    }

   int smallerChild = myguy; //changed this to +1 and it maaaybe fixed some stuff?
   for(int i = myguy + 1; i < myguy + m_ && i < (int) store_.size(); i++) //might need myguy+1 in loop condition changed <= to <
   {
    if (c_(store_[i], store_[smallerChild]))
    {
      smallerChild = i;
    }
   }


    if(c_(store_[smallerChild], store_[idx]) )
    {
    keyToLocation_[store_[smallerChild]] = myguy; //gonna hAVE to adjust
    keyToLocation_[store_[myguy]] = smallerChild;

     std::swap(store_[idx], store_[smallerChild]);
     trickleDown(smallerChild);
    } 

  }





template <typename T, typename KComparator, typename PComparator, typename Hasher >
void Heap<T,KComparator,PComparator,Hasher>::trickleUp(int loc)
  {
    int parent = (loc - 1)/m_; //could still change to size() - 2??
    while( parent >= 0 && c_(store_[loc], store_[parent]) )
    { 
     keyToLocation_[store_[loc]] = parent;
     keyToLocation_[store_[parent]] = loc;
    

     std::swap(store_[parent], store_[loc]);
     loc = parent; //??
     parent = (loc-1)/m_; //changed loc - 1 ??

     }
  }






#endif

