#include "singly_linked_list.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TRACK_TITLE_SIZE 60

#define PLAYLIST_IN_PATH "playlist.txt"
#define PLAYLIST_OUT_PATH "playlist-out.txt"
// To avoid unnecessary complexity, we fix the filenames instead of getting them
// through runtime parameters.

typedef char Data[TRACK_TITLE_SIZE];
Node *playlist;

/// Removes trailing newline from the line, if it exists.
char *remove_newline_if_exists(char *line) {
  // YOUR CODE HERE
  size_t len = strlen(line);

  if (len > 0 && line[len - 1] == '\n') {
    line[len - 1] = '\0';
  }
  return line;
}

/// Reads lines from at `filename`, creates a node for each line and inserts
/// nodes to `list`.
Node **load_file(const char *filename, Node **list) {
  // Open the file and assign to stream `f`
  // YOUR CODE HERE
  FILE *f = fopen(filename, "r");

  if (!f) {
    perror(PLAYLIST_IN_PATH);
    exit(EXIT_FAILURE);
  }
  char line[TRACK_TITLE_SIZE];

  while (
      // Read one line from the stream
      // YOUR CODE HERE
      fgets(line, TRACK_TITLE_SIZE, f)) {
    remove_newline_if_exists(line);

    Node *new_node = (Node *)malloc(sizeof(Node));
    // ^ CHANGED from "auto new_node" → explicit pointer type (C23
    // compatibility)

    new_node->next = NULL;
    // ^ CHANGED from "nullptr" → "NULL" (nullptr is C++ only)

    Data *data = (Data *)malloc(sizeof(Data));
    // ^ CHANGED from "auto data" → explicit pointer type (C23 compatibility)

    new_node->data = data;

    // Copy line to `new_node` and append `new_node` to `list`
    // YOUR CODE HERE
    strcpy((char *)new_node->data, line);

    if (*list == NULL) {
      *list = new_node;
    } else {
      Node *last = *list;
      while (last->next != NULL) {
        last = last->next;
      }
      last->next = new_node;
    }
  }
  fclose(f);
  return list;
}

/// Saves `list` contents to the file at `filename`.
void save_file(const char *filename, Node *list) {
  // Open file
  // YOUR CODE HERE
  FILE *f = fopen(filename, "w");

  // Move through the list and save the tracks to the file
  // Note: You have to cast the data to print the track to the file as follows:
  // (char *)current->data
  // Because current->data is a pointer to everything (void*).
  Node *current = list;
  // ^ CHANGED from "auto current" → explicit pointer type (C23 compatibility)
  // YOUR CODE HERE
  size_t i = 1;
  while (current != NULL) {
    fprintf(f, "%zu %s\n", i, (char *)current->data);
    current = current->next;
    i++;
  }
  fclose(f);
}

void print_tracks(const Node *const playlist) {
  Node *current = (Node *)playlist;
  // ^ CHANGED from "auto current" → explicit pointer type (C23 compatibility)
  //   Cast added because 'playlist' is const

  for (size_t i = 1; current; i++, current = current->next)
    printf("%2zu: %s\n", i, (char *)current->data);
}

int main() {
  load_file(PLAYLIST_IN_PATH, &playlist);
  print_tracks(playlist);

  // Deletion
  size_t node_index_to_del = 4;
  free(delete_at(&playlist, node_index_to_del));

  // Insertion
  Node node = {.data = "Tarkan – Şımarık 💋", .next = NULL};
  // ^ CHANGED from ".next = nullptr" → ".next = NULL" (nullptr is C++ only)

  insert_at(&playlist, 3, &node);

  save_file(PLAYLIST_OUT_PATH, playlist);
}
