# STL Compatible Tree Container

### Summary:

The purpose of this repository is to contain a bunch of custom-made tree-related C++11 STL compatible tree containers.

Currently this repository contains partly finished 'binary_tree' container (tree with left and right children) and 'tree_blueprint' to conveniently store common bare-bone interface of tree like structures to aid with making custom and future tree containers.

Future plans include: 'multi_tree' (tree with multiple children), 'BST' and 'family_tree' (tree with 2 parents per node).

---

### Concept:

The idea of this project was to create C++ STL compatible tree containers, and to learn some implementation details of STL containers along the way.
Initially my plan was to create Java/C# style tree containers, heavily based on inheritance, to minimize the amount of code/repetition.
After working and fighting with this idea in practise for some time, I finally decided that this is not a good idea.
Java/C# style inheritance based containers just does not work well in C++ and overly complicates, bloats and slows down code, which is all due to the way templates work in C++.

Given this, I still recognised that to make several similar tree containers, I would have to write quite a bit of duplicate code.
Hence I decided to keep this inheritance structure in principle, even if I would not use concrete inheritance.
This lead me to create separate 'tree_blueprint' class to simply allow me to create & copy-paste what I would consider to be mostly common code for most trees.
This includes common methods, variables and structure.
Granted, this approach is quite archaic, but in my opinion works quite well for the purpose it is needed.

---

### Contains:

* binary_tree:
  * Common tree structure, where each node has up to 2 children (left & right).
  * Mostly finished state (not properly tested yet):
    * STL compliant bidirectional iterator.
    * Most of the common STL methods can be found. (insert, emplace, erase, find, etc.)
    * Basic print functionality included as functions in 'tree_container' namespace.
  * Based on unique_ptr.
  * NOT THREAD SAFE!
* tree_blueprint:
  * Interface style common blueprint for tree like structures (copy-paste-style)

---

### How to use:

Minimum C++ version required: C++11.

The easiest way to use one of the tree classes, is to simply copy class header '.h' with its template implementation '.tpp' into your project.
For example, to use 'binary_tree', copy 'binary_tree.h' and 'binary_tree.tpp' into your project.

Alternatively, you can use this library as part of your own CMake project as you desire.

---

### Version History:

#### Version 1.0.0:

* Renamed:
  * 'BinaryTree' to 'binary_tree' and
  * 'BlueprintTree' to 'tree_blueprint' (to bring them to same naming convention as std containers).
* Modified CMake files and overall project structure.
* Changed file naming convention from 'PascalCase' to 'snake_case'.
* Moved everything into 'tree_container' namespace.
* Removed 'googletest' submodule in favour of GoogleTest's automated configure time build.
* Slightly prettified 'binary_tree_examples.cpp' and added screenshot of its print to preliminarily showcase this library.

#### Version 0.8.1:

* Started testing BinaryTree properly in '/tests/BinaryTree_Test.cpp'.
* Made some minor fixes/changes.

#### Version 0.8.0:

* Added use instructions to 'README.md'.
* Added/changed all insertion and emplacement methods to BinaryTree:
	* Added 'insert_child' and 'insert_at' (and their left and right variants eg. insert_child_left) methods. (Original 'insert_at' method is now 'insert_child'.)
	* Added emplacement versions of all insertion methods. (In fact, all insertion methods just forward their arguments to corresponding emplace equivalents.)
	* Added erasure methods.

#### Version 0.7.1:

* Added 'emplace' and changed 'insert' in BinaryTree.
* Fixed error in 'CMakeLists.txt' to make sure gtesting can actually be done. (testing not properly started yet)

#### Version 0.7.0:

* Changed project from Visual Studio solution to static CMake library.
* Added googletest to get started with proper testing.
* Previous main function (preliminary tests) can now be found in: examples/BinaryTree_Examples.cpp . (to be turned into proper tests)


#### Version 0.6.0:

* Added 'swap', 'height', 'subtreeSize' and bunch of assignments/constructors for BinaryTree.
* Added couple constructors and 'subtreeSize' method for BinaryTree::TreeNode.
* Cleaned up code slightly.

#### Version 0.5.5:

Added presentable printing functionality for BinaryTree.

#### Version 0.5.0:

Initial version of BinaryTree and BlueprintTree.
Basic functionality of BinaryTree mostly in working condition ('iterator', 'find' and 'insert' seem to work, not properly tested).

BlueprintTree is mostly completed blueprint to quickly start the work on future tree structures, as planned, when done with BinaryTree.

---

### Fixes and features left to consider/implement:

* Finish 'binary_tree'.
	* methods using initializer_list or inputIterator range
* Add more to 'tree_blueprint' if it makes sense (or consider removing it completely).
* Add 'multi_tree' (tree with multiple children).
* Add BST (Binary Search Tree).
* Add 'family_tree' (tree with 2 parents per node).
* Write more tests.

---

### Screenshot:

#### Version 1.0.0 output of 'binary_tree_examples':  
![v1.0.0 output of 'binary_tree_examples'](/screenshots/tree-container_binary-tree_example.JPG "v1.0.0 output of 'binary_tree_examples'")