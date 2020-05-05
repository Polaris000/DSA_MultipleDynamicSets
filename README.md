## RAM

As part of our Data Structures and Algorithms course at BITS Pilani, Pilani campus, we were asked to implement a simple abstraction of a computer's RAM using multiple dynamic sets.

Put simply, the project entailed using dynamic arrays with the funtionality of doubly linked lists. Though computer memory can have heterogenous objects, the project assumes homogenous objects.

Each object had three attributes: a key, a pointer to the next object in the list and one to the previous object.

```
object
    - prev
    - key
    - next
```

### Allocating and Freeing objects
Since each object has three attributes, which are in essence, integers, storing `n` logical objects would require a space of `3 * n`.

At a given point of time, our RAM with a capacity of, say, `m` objects, would be partially populated. The remaining space of `m - n` objects would be considered as free.

Free objects would be maintained as another doubly linked list, but their `prev` fields would be `NULL`. The allocating and freeing of objects from RAM would follow the properties of a stack -- the next object allocated would be the last one freed.


### Defragmentation
Since there is only one memory, the object lists and the free list would become convoluted, with patches of free memory between allocated memory.

Defragmentation would, as expected, move all allocated memory to one side, separating the free memory from the object lists.


### Usage
```
$ make
gcc -c utils.c list.c
gcc -o run_code driver.c utils.o list.c 
./run_code
Select an option:  
1. Create a new list  
2. Insert a new element in a given list in sorted order   
3. Delete an element from a given list   
4. Count total elements excluding free list  
5. Count total elements of a list  
6. Display all lists  
7. Display free list  
8. Perform defragmentation  
9. Press 0 to exit  
 ****************** 
Select an option between 0 and 8: 
```
After creating and adding some random elements to a list using options 1 and 2, we can view the allocated memory using option 6.
```
Select an option between 0 and 8: 6
 
Elements of list-1 are: 
key      next    prev 
2        991    NIL 
4        994    997 
10       988    997 
12       NIL    994 
 
         ****************** 
```
Currently, the allocated space in our memory is contiguous, so defragmenation would have no impact. Lets delete the element 4 from our list.

```
Select an option between 0 and 8: 3
 
List you want to delete from: 1
Enter the key value: 4
SUCCESS: ELEMENT DELETED
```

Lets check the updated list.
```
Select an option between 0 and 8: 6
 
Elements of list-1 are: 
key      next    prev 
2        991    NIL 
10       988    997 
12       NIL    991 
```

Since we free a middle element, its location was added to the end of the free list. Thus, our memory has allocated space (2) followed by a free space followed by 10 and 12. The rest is, of course, free space.

Lets defragment the list with option 8 and then view it.
```
Select an option between 0 and 8: 8
 
SUCCESS: RAM DEFRAGMENTED 
```

```
Select an option between 0 and 8: 6
 
Elements of list-1 are: 
key      next    prev 
2        991    NIL 
10       994    997 
12       NIL    991 
```

Notice how the next and prev values for 10 and 12 change. Now, all of the allocated space in our memory is contiguous.