## A doubly-linked list and its iterator

*Learning purposes only. =D*

In a doubly-linked list, each node has two links. The first link points to the previous node in the list, and the second link points to the next node in the list. 

<p align="center">
    <img src="resources/diagram.png?raw=true" alt="Diagram">
</p>

This implementation covers a set of operations, such as:

**Insertion**

- `insert_front()` – Inserts a new node as the first node. **Complexity:** `O(1)`.
- `insert_back()` – Inserts a new node at the end as the last node (it's a push operation). **Complexity:** `O(1)`.
- `insert_before()` – Given a node, inserts a new node before it. **Complexity:** `O(n)`.
- `insert_after()` – Given a node, inserts a new node after it. **Complexity:** `O(n)`.

**Deletion**

- Delete the first node – Deletes the first node in the list. **Complexity:** `O(1)`.
- Delete the last node – Deletes the last node in the list. **Complexity:** `O(1)`.
- Delete a node by its data – Given the data, the operation matches it with the node data in the linked list and deletes that node. **Complexity:** `O(n)`.

**Reverse**

Reverses the nodes, so the last one becomes the first one.

**Search**

 - `list_search()` - Used to search for a particular node in the list. **Complexity:** `O(n)`.

### Running tests

This project uses [Meson](https://mesonbuild.com/Quick-guide.html).

After cloning:

```bash
$ meson builddir
```

It will generate the `buildir`, then you can run the tests:

```bash
$ meson test -C builddir/ -v 
```

Testing using Valgrind (a tool to find memory leaks):

```bash
$ meson test -C builddir/ -v --wrap=valgrind
```

### Contributing

Feel free to send a PR. =D
