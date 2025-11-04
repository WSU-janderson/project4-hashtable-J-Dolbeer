#include "HashTable.h"
#include <algorithm>
#include <iostream>

HashTable::HashTable(size_t initCapacity) : table(initCapacity), numItems(0) {
    generateOffsets();
}

size_t HashTable::hash(const std::string& key) const {
    size_t sum = 0;
    for (char c : key) sum += static_cast<size_t>(c);
    return sum % table.size();
}

void HashTable::generateOffsets() {
    offsets.clear();
    for (size_t i = 1; i < table.size(); ++i) offsets.push_back(i);

    std::mt19937 rng(42); // deterministic pseudo-random
    std::shuffle(offsets.begin(), offsets.end(), rng);
}

void HashTable::resizeIfNeeded() {
    if (alpha() >= 0.5) {
        size_t newCap = table.size() * 2;
        std::vector<std::shared_ptr<HashTableBucket>> oldTable(table.size());
        for (size_t i = 0; i < table.size(); ++i) {
            oldTable[i] = table[i].lock();
        }
        table.resize(newCap);
        for (auto& wptr : table) wptr.reset();
        generateOffsets();
        numItems = 0;
        rehashAll(oldTable);
    }
}

void HashTable::rehashAll(const std::vector<std::shared_ptr<HashTableBucket>>& oldTable) {
    for (auto& bucket : oldTable) {
        if (bucket && !bucket->isEmpty()) insert(bucket->getKey(), bucket->getValue());
    }
}

bool HashTable::insert(const std::string& key, const size_t& value) {
    if (value == 9999) return false; // reserved value
    resizeIfNeeded();
    size_t home = hash(key);

    for (size_t i = 0; i <= offsets.size(); ++i) {
        size_t idx = (home + (i == 0 ? 0 : offsets[i - 1])) % table.size();
        auto ptr = table[idx].lock();
        if (!ptr) { // empty
            table[idx] = std::make_shared<HashTableBucket>(key, value);
            ++numItems;
            return true;
        } else if (!ptr->isEmpty() && ptr->getKey() == key) {
            return false; // duplicate
        } else if (ptr->isEAR()) {
            table[idx] = std::make_shared<HashTableBucket>(key, value);
            ++numItems;
            return true;
        }
    }
    return false;
}

bool HashTable::remove(const std::string& key) {
    size_t home = hash(key);

    for (size_t i = 0; i <= offsets.size(); ++i) {
        size_t idx = (home + (i == 0 ? 0 : offsets[i - 1])) % table.size();
        auto ptr = table[idx].lock();
        if (!ptr) return false;
        if (!ptr->isEmpty() && ptr->getKey() == key) {
            ptr->makeEAR();
            --numItems;
            return true;
        }
    }
    return false;
}

bool HashTable::contains(const std::string& key) const {
    size_t home = hash(key);
    for (size_t i = 0; i <= offsets.size(); ++i) {
        size_t idx = (home + (i == 0 ? 0 : offsets[i - 1])) % table.size();
        auto ptr = table[idx].lock();
        if (!ptr) return false;
        if (!ptr->isEmpty() && ptr->getKey() == key) return true;
    }
    return false;
}

std::optional<size_t> HashTable::get(const std::string& key) const {
    size_t home = hash(key);
    for (size_t i = 0; i <= offsets.size(); ++i) {
        size_t idx = (home + (i == 0 ? 0 : offsets[i - 1])) % table.size();
        auto ptr = table[idx].lock();
        if (!ptr) return std::nullopt;
        if (!ptr->isEmpty() && ptr->getKey() == key) return ptr->getValue();
    }
    return std::nullopt;
}

size_t& HashTable::operator[](const std::string& key) {
    size_t home = hash(key);
    for (size_t i = 0; i <= offsets.size(); ++i) {
        size_t idx = (home + (i == 0 ? 0 : offsets[i - 1])) % table.size();
        auto ptr = table[idx].lock();
        if (ptr && !ptr->isEmpty() && ptr->getKey() == key) return ptr->getValue();
    }
    throw std::runtime_error("Key not found");
}

std::vector<std::string> HashTable::keys() const {
    std::vector<std::string> ks;
    for (auto& wptr : table) {
        auto ptr = wptr.lock();
        if (ptr && !ptr->isEmpty()) ks.push_back(ptr->getKey());
    }
    return ks;
}

double HashTable::alpha() const { return static_cast<double>(numItems) / table.size(); }
size_t HashTable::capacity() const { return table.size(); }
size_t HashTable::size() const { return numItems; }

void HashTable::rehashBackwards() {
    std::vector<std::shared_ptr<HashTableBucket>> oldTable(table.size());
    for (size_t i = 0; i < table.size(); ++i) oldTable[i] = table[i].lock();
    table.clear();
    table.resize(oldTable.size());
    generateOffsets();
    numItems = 0;

    // sort oldTable in reverse ASCII sum order
    std::vector<std::shared_ptr<HashTableBucket>> sorted;
    for (auto& b : oldTable) if (b && !b->isEmpty()) sorted.push_back(b);

    std::sort(sorted.begin(), sorted.end(), [](const auto& a, const auto& b){
        auto sumA = std::accumulate(a->getKey().begin(), a->getKey().end(), 0);
        auto sumB = std::accumulate(b->getKey().begin(), b->getKey().end(), 0);
        return sumA > sumB;
    });

    for (auto& b : sorted) insert(b->getKey(), b->getValue());
}

std::ostream& operator<<(std::ostream& os, const HashTable& ht) {
    for (size_t i = 0; i < ht.table.size(); ++i) {
        auto ptr = ht.table[i].lock();
        if (ptr && !ptr->isEmpty()) os << "Bucket " << i << ": " << *ptr << "\n";
    }
    return os;
}
