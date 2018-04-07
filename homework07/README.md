Homework 07
===========

# Activity 2 - Questions

1. Describe how the `symbol` is stored in the `Node` **struct** by diagramming
   the memory layout of the following `Node` structure:

        Node *n = node_create('\n', 2, NULL, NULL);

        |  count  |stack (4 bytes)
        |         |
        |  Left   |heap (16 bytes total - 8 bytes for both pointes)
        |  Right  |
        | symbol  |data (8 bytes b/c char and int64_t are both 8 bytes but only save one at a time in memory)
        |         |code (0 bytes)

        total bytes in Node struct: 28 bytes

    Be sure to indicate how much memory each `Node` structure occupies and how
    much is allocated for each attribute in the struct.

    1. Explain what the code `assert(n->string.letter == '\n')` would result in?
      We checked for characters that needed to be escaped when we set our symbol (including the new line character) so this assert would be true and do nothing.

    1. Given that `symbol` is a **union** type, is it ever possible for both the
      `letter` and `string` of the symbol `\n` to co-exist (that is, the
      `string` doesn't clobber the `letter`)?
          If they are stored in a union, they can't both store values because the way a union works is it only allocates memory large enough for the largest data type. It then saves all the attributes of the union in that allocated place in memory. Therefore once an attribute is defined, if a different attribute is defined, it is stored over the first. However if a struct was used, each value could be saved at the same time because structs allocate memory for all its attributes.

2. To construct the Huffman code, you had to utilize both a **priority queue**
   (aka. **min-heap**) and a **Huffman Tree**, both of which were binary trees.
   For the former, you used an **array** representation while for the later you
   used a **linked node** representation.  With this in mind, answer the
   following questions:

    1. Would it have been easier to implement the **priority queue** with a
      **linked node** representation?  Explain why this would be better or
      worse than the **array** representation.

      It would be not be easier because we conducted multiple swaps of data and it is a lot more difficult to swap pointers than it is to swap in an array since it's index based. We also wouldn't have the indexes to access the children/parents of each node so we'd have to build a tree before we could do these types of calculations if we had used a linked list.

    2. Would it have been easier to implement the **Huffman Tree** with an
      **array** representation?  Explain why this would be better or worse
      than the **linked node** representation.

      This would not have been easier because it is much more difficult to traverse a tree when it is in array form. When a tree is built with a linked list, recursion can be used for many different operations like traversing and inserting.

3. Analyze the results of your experiements with you `huff.py` Python script.
   What sort of compression ratios were you able to achieve?  How does this
   compare to standard utilities such as `gzip`, `bzip2`, and `xz`?

    |        FILE        | OLD SIZE | NEW SIZE |   RATIO   |
    |--------------------|----------|----------|-----------|
    |     data/1342-0.txt|   5712512|   3238771|     56.70%|
    |      data/219-0.txt|   1866312|   1065343|     57.08%|
    |       data/84-0.txt|   3579736|   2005500|     56.02%|
    |        data/844.txt|   1139056|    672349|     59.03%|
    |       data/98-0.txt|   6298288|   3575868|     56.78%|
    |       data/data.txt|       328|       127|     38.72%|
    |      data/ideas.txt|      8360|      4934|     59.02%|
