## A doubly-linked list and its iterator

*Learning purposes only. =D*

In a doubly-linked list, each node has two links. The first link points to the previous node in the list, and the second link points to the next node in the list. 

<p align="center">
    <img src="resources/diagram.png?raw=true" alt="Diagram">
</p>

This implementation covers a set of operations, such as:

**Insertion**

- `node_t *insert_front()` complexity: `O(1)` - Inserts a new node as the first node.
- `node_t *insert_back()` complexity: `O(1)` – Inserts a new node at the end as the last node (it's a push operation).
- `node_t *insert_before()` complexity: `O(1)` – Given a node, inserts a new node before it.
- `node_t *insert_after()` complexity: `O(1)` – Given a node, inserts a new node after it.

**Deletion**

- `void delete_node()` complexity: `O(1)` – Deletes the given node.
- `void delete_first_node()` complexity: `O(1)` - Delete the first node – Deletes the first node in the list.
- `void delete_last_node()` complexity: `O(1)` – Deletes the last node in the list.

**Search**

 - `node_t *list_search()` complexity: `O(n)` - Used to search for a particular node in the list.

**Reverse**

Reverses the nodes, so the last one becomes the first one.

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
