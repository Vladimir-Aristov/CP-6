#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <cmath>

template <typename TKey, typename TValue>
class HashTable {
private:
    std::vector<std::list<std::pair<TKey, TValue>>> table_;
    int capacity_;
    int size_;
    // used in hash_func for double numbers
    int inline hash1(int value) {
        return value % size_;
    }
    int inline hash2(int value, int m) {
        return m - (value % m);
    }
public:
    HashTable() {
        table_ = std::vector<std::list<std::pair<TKey, TValue>>>(100);
        capacity_ = 13;
        size_ = 100;
    }
    ~HashTable() {
        table_.clear();
    }
    size_t hash_function(const int& key) {
        return static_cast<size_t>((int) key * 97 % size_);
    }
    size_t hash_function(const float& key) {
        return static_cast<size_t>((hash1(key) + 3 * (hash2(key, 97))) % size_);
    }
    size_t hash_function(const double & key) {
        return static_cast<size_t>((hash1(key) + 3 * (hash2(key, 97))) % size_);
    }
    size_t hash_function(const std::string& key) {
        unsigned int p = 127;
        int M = 97;
        unsigned long hash = 0;
        for (int i = 0; i < key.size(); i++) {
            hash += key[i]*(unsigned long)pow(p,i) % M;
        }
        hash = hash % M;
        return static_cast <size_t> (hash);

    }
    void Insert(const TKey& key_val, const TValue& el_val) {
        size_t pos = hash_function(key_val);
        table_[pos].push_back(std::make_pair(key_val, el_val));
    }
    const TValue Search(const TKey& key) {
        size_t pos = hash_function(key);
        for (auto elem : table_[pos]) {
            if (elem.first == key) {
                return elem.second;
            }
        }
    }
    void OutPut() const {
        for (auto list : table_) {
            for (auto pair : list) {
                std::cout << pair.first << " " << pair.second << std::endl;
            }
        }
    }
    void Delete(TKey key) {
        size_t pos = hash_function(key);
        int i = 0;
        auto it = table_[pos].begin();
        std::cout << "Deleting" << std::endl;
        for (auto elem : table_[pos]) {
            std::cout << "Searching" << std::endl;
            if (elem.first == key) {
                std::cout << "Found: " << elem.first << " - "
                << elem.second << std::endl;
                std::advance(it, i);
                table_[pos].erase(it);
                break;
            }
            i += 1;
        }
    }
    const TValue operator[](const TKey& key) {
        size_t pos = hash_function(key);
        for (auto elem: table_[pos]) {
            if (elem.first == key) {
                return elem.second;
            }
        }
//        TValue tval = table_[pos][0].second;
//        table_[pos].insert(std::make_pair(key, tval)); // default value
//        return tval;
    }
};

int main() {
    HashTable<std::string, std::string> cyclist_names;
    cyclist_names.Insert("Tadej", "Pogacar");
    cyclist_names.Insert("Aleksandr", "Vlasov");
    cyclist_names.Insert("Stefan", "Kung");
    cyclist_names.OutPut();
    std::cout << "\n";
    cyclist_names.Delete("Stefan");
    std::cout << "\n";
    std::cout << "Deleted cyclist" << "\n";
    cyclist_names.OutPut();
    std::cout << "\n";
    HashTable<std::string, int> marks;
    marks.Insert("Karnaushenko", 11);
    std::cout << "Michael's mark: " << marks.Search("Karnaushenko") << std::endl;
    marks.Insert("Gainutdinov", 12);
    std::cout << "Rasul's mark: " <<marks["Gainutdinov"] << std::endl;

}