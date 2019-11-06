# STL Compatible Tree Container -- work in progress --

### Summary:

The purpose of this repository is to contain a bunch of custom-made tree-related C++11 STL compatible tree containers.
Currently the repository contains partly finished BinaryTree container (tree with left and right children) and BlueprintTree to conveniently store common bare-bone interface of tree like structures to aid with making custom and future tree containers.
Future plans include: MultiTree(tree with multiple children), BST and FamilyTree(tree with 2 parents per node).

---

### Concept:

The idea of this project was to create C++ STL compatible tree containers, and to learn some inner workings of STL containers along the way.
Initially my plan was to create Java/C# style tree containers, heavily based on inheritance, to minimize the amount of code/repetition.
After working and fighting with this idea in practise for some time, I finally decided that this is not a good idea.
Java/C# style inheritance based containers just does not work well in C++ and overly complicates, bloats and slows down code, which is all due to the way templates work in C++.

Given this, I still recognised that to make several similar tree containers, I would have to write quite a bit of duplicate code.
Hence I decided to keep this inheritance structure in principle, even if I would not use concrete inheritance.
This lead me to create separate BlueprintTree class to simply allow me to create & copy-paste what I would consider to be mostly common code for most trees.
This includes common methods, variables and structure.
Granted, this approach is quite archaic, but in my opinion works quite well for the purpose I need it.

---

### Contains:

* BinaryTree:
  * Common tree structure, where each node has up to 2 children (left & right).
  * Partly finished state:
    * Mostly working STL compliant bidirectional iterator (not properly tested).
    * Working basic insertion and find operations.
	* Working print functionality.
  * Based on unique_ptr.
  * NOT THREAD SAFE!
* BlueprintTree:
  * Interface style common blueprint for tree like structures (copy-paste-style)

---

### How to use:

Minimum C++ version required: C++11.

The easiest way to use one of the tree classes, is to simply copy class header '.h' with its template implementation '.tpp' (and possibly '.cpp' too, if it is not empty) into your project.
For example, to use BinaryTree; copy 'BinaryTree.h' and 'BinaryTree.tpp' into your project. ('BinaryTree.cpp' is empty for now)

If you want to clone this git repository, use 'git clone --recurse-submodules --remote-submodules https://github.com/TimiMakkonen/TreeContainer.git' or something similar to make sure that 'googletest' submodule gets cloned properly.

---

### Version History:

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

* Finish BinaryTree.
	* methods using initializer_list or inputIterator range
* Add more to BlueprintTree if it makes sense (or consider removing it completely).
* Add Multitree(tree with multiple children).
* Add BST(Binary Search Tree).
* Add FamilyTree(tree with 2 parents per node).
* Continue testing.