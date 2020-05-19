# Meep : Binary Heap + Hash Map

## Introduction
Meep is a combined data structure (Binary Heap + Hash map) made to replace C++'s ordinary priority queue. I first heard of this data structure from [Tushar Roy](https://www.linkedin.com/in/tushar-roy-4351091a/) in his [tutorial](https://www.youtube.com/watch?v=oP2-8ysT3QQ&list=PLrmLmBdmIlpu2f2g8ltqaaCZiq6GJvl1j&index=4) about Prim's minimal spanning tree.

I implemented the data structure because 

- Having a library devoted to graph algorithms is convenient. 
- C++'s priority queue doesn't have decrease operation, which sucks.
- I hate having naked separate data structures and then call it a combined one. I prefer having it inside the implementation files so the users doesn't know what's behind the scene.
## Usage 
Right now,  Meep supports
 
 - Constructor taking _n_ as 
 ```C++
Meep<char,int> mp(10); // takes n=10 to construct a 10 elements Meep
// and takes keys type of char and values type of integer
// default sorting for heap: ascending

```
 - Insertion - O(log n)
```C++
mp.insert('A',10); // insert key 'A' of value 10;
mp.insert('B',3); // insert key 'B' of value 3;
```
 - empty(), full() - O(1)
 ```C++
 if(!mp.empty()) { // do sth }
 if(mp.full()) { // do sth }
 ```
 - searchValue - O(1) 
 ```C++
 std::cout << mp.searchValue('A') << std::endl;
 // prints out 10
```
 - searchIndex - O(1)
 ```C++
 std::cout << mp.searchIndex('B') << std::endl; // B has index 1
 std::cout << mp.searchIndex('A') << std::endl; // A has index 2
```
 - Increase in priority: change() - O(log n)
 ```C++
 mp.change('A',-1);
 std::cout << mp.searchIndex('A') << std::endl; // now A has index 1
 std::cout << mp.searchIndex('B') << std::endl; // and B has index 2
 ```
 - check if Meep contains a key : has() - O(1)
 ```C++
if(mp.has('A')) { std::cout << "YES" << std::endl; }
// prints out "YES"
if(!mp.has('C')) { std::cout << "YES" << std::endl; }
// prints out "YES"
```
 - pop() - O(log n)
 ```C++
 // get and pop the minimum value 
 mp.pop();
 if(mp.has('A') { std::cout << "YES"<< std::endl; }
 // doesnt print out "YES" because 'A' is popped off
 ```
## Implementation details
Meep consists of two different data structures:

- A binary heap used as a priority queue.
- A hash map that stores the index of elements in binary heap.

The binary heap I implemented was from Robert Sedgewick's textbook Algorithm's in C++.
I use C++'s vector as the container for the binary heap since I wanted Meep to be dynamic, not static.
At first I wanted to change the indexing from 1 to 0 because I didn't want to waste any space, turns out I was wrong.


- I would have to recreate every method of a binary heap with 0-indexed, which is terrible.
- The method has() relies on the fact that if something is not in the hash map, hash_map[key] will return 0, so in order to not clash with the first element of the binary heap, I choose to use 1-indexed binary heap. 
-- Of course you can develop tricks to keep going as a 0-indexed but it is not needed since we have a perfect data structure implementation from the Robert Sedgewick himself.

The hash map is the unordered_map from C++ STL

- I chose it over C++'s map because unordered_map has faster average insertion and retrieval time.
## Trivial
The name Meep comes from a game character in Dota and Dota 2 named Meepo. Since Meap (Map+Heap) and Meep sounds alike, I prefer the name Meep because simply I'm a fan of Dota 2.


## Resources
Algorithms in C++ by Robert Sedgewick

Prim's minimal spanning tree by Tushar Roy
