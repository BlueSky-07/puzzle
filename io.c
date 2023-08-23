#include "io.h"

char* IO_STORE_ROOT_PATH = "data/";

const char* io_action_result_string(IoActionResult result) {
  switch (result) {
    case IO_SUCCESS:
      return "SUCCESS";
    case IO_FAILURE:
      return "FAILURE";
    case IO_FAILURE_NOT_FOUND:
      return "FAILURE: NOT FOUND";
    default:
      return "UNKNOWN";
  }
}

IoActionResult io_write_binary(Binary binary, const char* path) {
  if (!path) return IO_FAILURE_NOT_FOUND;
  FILE* file = fopen(path, "w");
  if (!file) return IO_FAILURE_NOT_FOUND;

  fprintf(file, "%llu\n", binary);

  fclose(file);
  return IO_SUCCESS;
}

IoActionResult io_read_binary(const char* path, Binary* binary) {
  if (!path) return IO_FAILURE_NOT_FOUND;
  FILE* file = fopen(path, "r");
  if (!file) return IO_FAILURE_NOT_FOUND;

  fscanf(file, "%llu\n", binary);

  return IO_SUCCESS;
}

IoActionResult io_write_binary_list(BinaryListItem* list, const char* path) {
  if (!path) return IO_FAILURE_NOT_FOUND;
  FILE* file = fopen(path, "w");
  if (!file) return IO_FAILURE_NOT_FOUND;

  BinaryListItem* i = list;
  while (i) {
    if (i->binary != BINARY_INVALID) fprintf(file, "%llu\n", i->binary);
    i = i->next;
  }

  fclose(file);
  return IO_SUCCESS;
}

IoActionResult io_read_binary_list(const char* path, BinaryListItem* list) {
  if (!path) return IO_FAILURE_NOT_FOUND;
  FILE* file = fopen(path, "r");
  if (!file) return IO_FAILURE_NOT_FOUND;

  Binary binary;
  while (fscanf(file, "%llu\n", &binary) != EOF) {
    binary_list_push_unique(list, binary);
  }

  return IO_SUCCESS;
}

IoActionResult io_write_piece(Piece* piece) {
  Piece p = *piece;
  char* filename = malloc(sizeof(char) * (strlen(IO_STORE_ROOT_PATH) + 13));
  filename[0] = '\0';
  strcat(filename, IO_STORE_ROOT_PATH);
  strcat(filename, (char[]){piece->name, '\0'});
  strcat(filename, ".piece.txt");
  io_write_binary(
    binary_from_positions(p.positions, p.position_count, NULL),
    filename
  );
  free(filename);

  return IO_SUCCESS;
}

IoActionResult io_write_piece_all_kinds(Piece* piece, Puzzle puzzle) {
  if (!piece) return IO_FAILURE;
  char* filename = malloc(sizeof(char) * (strlen(IO_STORE_ROOT_PATH) + 13));
  filename[0] = '\0';
  strcat(filename, IO_STORE_ROOT_PATH);
  strcat(filename, (char[]){piece->name, '\0'});
  strcat(filename, ".piece.txt");

  Puzzle puzzle_final = puzzle ? puzzle : puzzle_make();

  BinaryCount* bc = game_put_piece_all_kinds_all_rotate_into_puzzle(puzzle_final, piece);
  io_write_binary_list(bc->binaries, filename);
  if (!puzzle) free(puzzle_final);
  binary_count_free(bc);
  free(filename);

  return IO_SUCCESS;
}
