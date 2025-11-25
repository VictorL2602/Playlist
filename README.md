# Playlist Manager
A C program that reads a playlist from a text file, stores the songs in a singly linked list, modifies the list, and writes the result to a new file.

## What it does
- Reads songs from playlist.txt
- Stores them in a linked list
- Deletes the song at index 4
- Inserts a new song at index 3
- Saves the result to playlist-out.txt

## Extra
C++ language from the template was replaced with similar C23 functions. (For example auto)

auto new_node = (Node *)malloc(sizeof(Node));
auto data = (Data *)malloc(sizeof(Data));
auto current = playlist;

Replaced with:
Node *new_node = (Node *)malloc(sizeof(Node));
Data *data = (Data *)malloc(sizeof(Data));
Node *current = list;

and:

new_node->next = nullptr;
Node node = {.data = "…", .next = nullptr};

replaced with:
new_node->next = NULL;
Node node = {.data = "…", .next = NULL};
