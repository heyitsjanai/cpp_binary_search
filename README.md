# SNHU CS 305 
# Data Analysis & Design
Portfolio submission for Data Analysis &amp; Design
For this class, we had to create an analysis of the run-time and memory for different data structures.
Our client was a university (ABCU) that needed help sorting and displaying course information in order of prerequisites.
First, I analyzed three different data structures, vectors, hash tables, and binary search trees. 
By completing an analysis on the pros and cons of each and creating pseudocode of each,
I was able to recommend the most efficient data structure for this client, the binary search tree. 

The binary search tree was the data structure I chose to implement because it sorted the classes by prerequisites
and kept them sorted, even if classes were added or deleted. When a student requested to see the classes in order 
of which they should take them, the tree easily handles this request without having to do any resorting.

I had trouble using the pre-coded CSV parser and header files. I need to refactor this code to implement my final code design. At this point, the CSV file is not loading in properly, and I do need to fix this. I hope to figure out and fully understand why it isn't correctly loading here.

This project allowed us to create a database from nothing and load in our own data. This is absolutely useful, and while in the real world we may just be asked to maintain databases, it is very good practice to know how to create from scratch!

This project helped expand my knowledge of C++, especially how to arrange files within an application design. CSV files should also be parsed and read correctly, otherwise none of it will work.
