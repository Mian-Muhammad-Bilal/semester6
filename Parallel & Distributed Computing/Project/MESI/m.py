import parallel
# Constants
NUM_CACHES = 5
ARRAY_SIZE = 10

# Define cache block states
MODIFIED = 'M'
EXCLUSIVE = 'E'
SHARED = 'S'
INVALID = 'I'

# Main memory (shared memory)
shared_memory = [0] * ARRAY_SIZE

# Cache arrays and states
cache = [[None] * ARRAY_SIZE for _ in range(NUM_CACHES)]
cache_state = [[INVALID] * ARRAY_SIZE for _ in range(NUM_CACHES)]


def display_system_state():
    print("Main Memory:")
    print(shared_memory)
    print("\nCaches:")
    for i in range(NUM_CACHES):
        print(f"Cache {i}:")
        print(cache[i])
        print(f"Cache State:")
        print(cache_state[i])
    print("\n")


def read_data(cache_id, index):
    current_state = cache_state[cache_id][index]
    if current_state == MODIFIED or current_state == EXCLUSIVE or current_state == SHARED:
        print(f"Cache {cache_id} read from index {index}")
        return cache[cache_id][index]
    elif current_state == INVALID:
        print(f'''Cache {cache_id} read miss for index {
              index}. Requesting data from other caches or main memory...''')
        for other_cache_id in range(NUM_CACHES):
            if other_cache_id != cache_id and cache_state[other_cache_id][index] != INVALID:
                # Update current cache
                cache[cache_id][index] = cache[other_cache_id][index]
                cache_state[cache_id][index] = SHARED
                print(f"Cache {cache_id} updated from Cache {other_cache_id}")
                return cache[cache_id][index]
        # If data not found in any other cache, read from main memory
        cache[cache_id][index] = shared_memory[index]
        cache_state[cache_id][index] = EXCLUSIVE
        print(f"Cache {cache_id} read from Main Memory")
        return cache[cache_id][index]


def write_data(cache_id, index, data):
    current_state = cache_state[cache_id][index]
    if current_state == MODIFIED or current_state == EXCLUSIVE:
        print(f"Cache {cache_id} write to index {index} with data {data}")
        cache[cache_id][index] = data
        shared_memory[index] = data
        cache_state[cache_id][index] = MODIFIED
        for other_cache_id in range(NUM_CACHES):
            if other_cache_id != cache_id:
                cache_state[other_cache_id][index] = INVALID
        print(
            f"Cache {cache_id} updated and broadcasted invalidation to other caches")
    elif current_state == SHARED:
        print(f"Cache {cache_id} write to index {index} with data {data}")
        cache[cache_id][index] = data
        shared_memory[index] = data
        cache_state[cache_id][index] = MODIFIED
        for other_cache_id in range(NUM_CACHES):
            if other_cache_id != cache_id:
                cache_state[other_cache_id][index] = INVALID
        print(
            f"Cache {cache_id} updated and broadcasted invalidation to other caches")
    elif current_state == INVALID:
        print(f'''Cache {cache_id} write miss for index {
              index}. Requesting data from other caches or main memory...''')
        for other_cache_id in range(NUM_CACHES):
            if other_cache_id != cache_id and cache_state[other_cache_id][index] != INVALID:
                # Update current cache
                cache[cache_id][index] = cache[other_cache_id][index]
                cache_state[cache_id][index] = SHARED
                print(f"Cache {cache_id} updated from Cache {other_cache_id}")
                cache[cache_id][index] = data
                shared_memory[index] = data
                cache_state[cache_id][index] = MODIFIED
                for other_cache_id in range(NUM_CACHES):
                    if other_cache_id != cache_id:
                        cache_state[other_cache_id][index] = INVALID
                print(
                    f"Cache {cache_id} updated and broadcasted invalidation to other caches")
                return
        # If data not found in any other cache, read from main memory
        cache[cache_id][index] = data
        shared_memory[index] = data
        cache_state[cache_id][index] = MODIFIED
        for other_cache_id in range(NUM_CACHES):
            if other_cache_id != cache_id:
                cache_state[other_cache_id][index] = INVALID
        print(
            f"Cache {cache_id} updated and broadcasted invalidation to other caches")


def main():
    while True:
        display_system_state()
        cache_id = int(input("Select a cache (0-4) or 'q' to quit: "))
        if cache_id == 'q':
            break
        if cache_id < 0 or cache_id >= NUM_CACHES:
            print("Invalid cache selection. Please select a cache between 0 and 4.")
            continue
        index = int(
            input(f"Select an index to read/write (0-{ARRAY_SIZE - 1}): "))
        if index < 0 or index >= ARRAY_SIZE:
            print(f'''Invalid index. Please select an index between 0 and {
                  ARRAY_SIZE - 1}.''')
            continue
        action = input("Select action: 'r' for read, 'w' for write: ").lower()
        if action == 'r':
            read_data(cache_id, index)
        elif action == 'w':
            data = int(input("Enter data to write: "))
            write_data(cache_id, index, data)
        else:
            print("Invalid action. Please select 'r' for read or 'w' for write.")


if __name__ == "__main__":
    main()
