# Constants
NUM_CACHES = 4
ARRAY_SIZE = 20

# Define cache line states
INVALID = 'I'
SHARED = 'S'
MODIFIED = 'M'
EXCLUSIVE = 'E'

# Shared array (main memory)
main_memory = [0] * ARRAY_SIZE

# Cache arrays
cache = [[None] * ARRAY_SIZE for _ in range(NUM_CACHES)]
cache_state = [[INVALID] * ARRAY_SIZE for _ in range(NUM_CACHES)]


def display_system_state():
    print("Main Memory:")
    print(main_memory)
    print("\nCaches:")
    for i in range(NUM_CACHES):
        print(f"Cache {i}:")
        print(cache[i])
        print(f"Cache State:")
        print(cache_state[i])
    print("\n")


def read_from_cache(cache_id, index):
    if cache_state[cache_id][index] == INVALID:
        cache[cache_id][index] = main_memory[index]
        cache_state[cache_id][index] = EXCLUSIVE
        for j in range(NUM_CACHES):
            if j != cache_id and cache_state[j][index] == EXCLUSIVE:
                cache_state[j][index] = SHARED
                cache_state[cache_id][index] = SHARED
    elif cache_state[cache_id][index] == SHARED:
        pass
    elif cache_state[cache_id][index] == EXCLUSIVE:
        pass
    elif cache_state[cache_id][index] == MODIFIED:
        pass
    print(f"Cache {cache_id} reads from index {index}")


def write_to_cache(cache_id, index, value):
    if cache_state[cache_id][index] == INVALID or cache_state[cache_id][index] == SHARED:
        cache[cache_id][index] = value
        main_memory[index] = value
        cache_state[cache_id][index] = MODIFIED
        for j in range(NUM_CACHES):
            if j != cache_id:
                cache_state[j][index] = INVALID
    elif cache_state[cache_id][index] == EXCLUSIVE:
        cache[cache_id][index] = value
        main_memory[index] = value
        cache_state[cache_id][index] = MODIFIED
    elif cache_state[cache_id][index] == MODIFIED:
        cache[cache_id][index] = value
        main_memory[index] = value
    print(f"Cache {cache_id} writes to index {index}")


def main():
    while True:
        display_system_state()
        choice = input("Select a cache (0-3) or 'q' to quit: ")
        if choice.lower() == 'q':
            break
        if not choice.isdigit() or int(choice) not in range(NUM_CACHES):
            print("Invalid choice. Please select a cache (0-3).")
            continue
        cache_id = int(choice)
        print(f"Cache {cache_id} State:")
        print(cache_state[cache_id])
        index = int(input("Select an index to read/write (0-99): "))
        if index not in range(ARRAY_SIZE):
            print("Invalid index. Please select an index (0-99).")
            continue
        action = input("Select action: 'r' for read, 'w' for write: ").lower()
        if action == 'r':
            read_from_cache(cache_id, index)
        elif action == 'w':
            value = int(input("Enter value to write: "))
            write_to_cache(cache_id, index, value)
        else:
            print("Invalid action. Please select 'r' for read or 'w' for write.")


if __name__ == "__main__":
    main()
