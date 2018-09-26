COMP9319 Assignment1
Student Id z5124945
Zhao Wang


About the Huffman tree.
First I scan the whole file and count the numbers of all chars, then create a node with the char and its frequency.
Then I use the Priority Queue find the smallest two char and construct a trie  ( a new node with the total frequency of its subnodes) with two subNodes, and push the new node into the pQueue, until there is only one trie which is the root. Finally, from the root to the leaves, we can create the Haffman code by give the left subtree with 0s and right tree with 1s recrusively.
