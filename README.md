[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/7RAFczHS)
# Project 4 - HashTable

Project description can be found [in the repo](Project4_HashTable.pdf)

Place your complexity analysis below.

---
insert(key, value)

Average Case: O(1) — Inserting a key typically requires checking only a few buckets before finding an empty slot or detecting a duplicate.
Worst Case: O(n) — In the case of high load factors or clustering, the algorithm may need to probe every bucket.

remove(key)

Average Case: O(1) — Most keys can be found quickly using pseudo-random probing.
Worst Case: O(n) — If the key is not present or the table is nearly full, all buckets may need to be probed.

contains(key)

Average Case: O(1) — Similar to get, most keys are found after probing only a few positions.
Worst Case: O(n) — If the key is absent and collisions have forced long probe sequences.

get(key)

Average Case: O(1) — Accessing a value via a key requires only a small number of probes in a reasonably filled table.
Worst Case: O(n) — In the unlikely event that the key is missing and the probe sequence traverses the entire table.

operator[](key)

Average Case: O(1) — Similar to get, accessing the value by reference requires probing a small number of buckets.
Worst Case: O(n) — If the key is absent, the behavior is undefined, but a search could require probing all buckets.

keys()

Time Complexity: O(n) — Iterates through all buckets to collect the occupied keys.

alpha()

Time Complexity: O(1) — Returns the ratio size / capacity.

size()

Time Complexity: O(1) — Returns the number of stored key-value pairs.

capacity()

Time Complexity: O(1) — Returns the total number of buckets.