#include <iostream>
#include <unordered_map>
#include <list>
#include <utility>

class LFUCache {
public:
    LFUCache(int capacity) : capacity(capacity), min_freq(0) {}

    int get(int key) {
        if (key_to_val_freq.find(key) == key_to_val_freq.end()) {
            return -1; // Key not found
        }
        // Update the frequency of the key
        updateFrequency(key);
        return key_to_val_freq[key].first;
    }

    void put(int key, int value) {
        if (capacity <= 0) return;

        if (key_to_val_freq.find(key) != key_to_val_freq.end()) {
            // Key already exists, update the value and frequency
            key_to_val_freq[key].first = value;
            updateFrequency(key);
        } else {
            if (key_to_val_freq.size() >= capacity) {
                // Remove the least frequently used item
                int key_to_remove = freq_to_keys[min_freq].front();
                freq_to_keys[min_freq].pop_front();
                key_to_val_freq.erase(key_to_remove);
            }
            // Insert the new key with frequency 1
            key_to_val_freq[key] = {value, 1};
            freq_to_keys[1].push_back(key);
            min_freq = 1;
        }
    }

private:
    void updateFrequency(int key) {
        int old_freq = key_to_val_freq[key].second;
        int new_freq = old_freq + 1;

        // Remove the key from the old frequency list
        freq_to_keys[old_freq].remove(key);

        // If the old frequency list is empty and it was the minimum frequency, update min_freq
        if (freq_to_keys[old_freq].empty() && old_freq == min_freq) {
            min_freq++;
        }

        // Add the key to the new frequency list
        freq_to_keys[new_freq].push_back(key);

        // Update the frequency in the key_to_val_freq map
        key_to_val_freq[key].second = new_freq;
    }

    int capacity;
    int min_freq;
    std::unordered_map<int, std::pair<int, int>> key_to_val_freq; // key -> {value, frequency}
    std::unordered_map<int, std::list<int>> freq_to_keys; // frequency -> list of keys
};

// Example usage
int main() {
    LFUCache cache(2); // Capacity of 2

    cache.put(1, 1);
    cache.put(2, 2);
    std::cout << cache.get(1) << std::endl; // returns 1
    cache.put(3, 3); // evicts key 2
    std::cout << cache.get(2) << std::endl; // returns -1 (not found)
    std::cout << cache.get(3) << std::endl; // returns 3
    cache.put(4, 4); // evicts key 1
    std::cout << cache.get(1) << std::endl; // returns -1 (not found)
    std::cout << cache.get(3) << std::endl; // returns 3
    std::cout << cache.get(4) << std::endl; // returns 4

    return 0;
}