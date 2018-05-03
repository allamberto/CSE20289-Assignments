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
      This could would be false because the \n isn't escaped like we do when we assign symbol in our set symbol function so it will return a newline.

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

3. Analyze the results of your experiments with you `huff.py` Python script.
   What sort of compression ratios were you able to achieve?  How does this
   compare to standard utilities such as `gzip`, `bzip2`, and `xz`?

   According to online research, gzip, bzip2, and xz have compression ratios range from 20 to thirty. Mine are twice as larger as that, making them less efficient than standard utilities.

   | FILE                | OLD SIZE     | NEW SIZE     | RATIO        |
   |---------------------|--------------|--------------|--------------|
   | alice.txt           |       1316256|        762209|        57.91%|
   | heart_dark.txt      |       1866304|       1065323|        57.08%|
   | pride_pred.txt      |       5712504|       3238750|        56.70%|
   | wilde.txt           |       1139048|        672330|        59.03%|
   | grime.txt           |       4357080|       2433257|        55.85%|
