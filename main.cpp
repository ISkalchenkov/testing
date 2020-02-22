#include <iostream>
#include <vector>
#include <sstream>

class SplitString {
public:
    explicit SplitString(const std::string& str);
    ~SplitString() = default;
    void AddField(size_t pos, const std::string& str);
    void RemoveField(size_t pos);
    void ChangeField(size_t pos, const std::string& str);
    void print();
    std::string toSplitString();
private:
    std::vector<std::string> fields;
};

SplitString::SplitString(const std::string &str) : fields(0){
    std::stringstream stream(str);
    std::string temp;
    while(std::getline(stream, temp, '\t')) {
        if (!temp.empty()) {
            fields.push_back(std::move(temp));
        }
    }
}

void SplitString::AddField(size_t pos, const std::string &str) {
    if (pos > fields.size() - 1)
        return;
    auto iterator = fields.begin() + pos;
    fields.insert(iterator, str);
}

void SplitString::print() {
    int i = 0 ;
    for (auto & field : fields) {
        std::cout << "№"<< i++ << ": "<<   field << "|" << std::endl;
    }
}

void SplitString::RemoveField(size_t pos) {
    if (pos > fields.size() - 1)
        return;
    auto iterator = fields.begin() + pos;
    fields.erase(iterator);
}

void SplitString::ChangeField(size_t pos, const std::string &str) {
    if (pos > fields.size() - 1)
        return;
    fields[pos] = str;
}

std::string SplitString::toSplitString() {
    std::string ret;
    for (auto & field : fields) {
        ret += "|" + field;
    }
    return ret;
}

int main() {
    std::vector<SplitString> strings;
    std::string temp;
    std::cout << "***Command reference: 1-AddField new field; 2-ChangeField field; 3-delete field***\n" << std::endl;
    std::cout << "***Enter strings. To end the entry press Enter***" << std::endl; 
    while (std::getline(std::cin, temp) && !temp.empty()) {
        strings.emplace_back(temp);
    }
    int i = 0;
    for (auto & str : strings) {
        std::cout << i++ << ": "<< str.toSplitString() << std::endl;
    }

    char command = '0';
    std::cout << "Enter command: ";

    while (std::cin >> command) {
        std::string newString;
        size_t str = 0, field = 0;
        std::cout << "Enter string and field number: ";
        std::cin >> str >> field;
        std::cin.ignore();
        switch (command) {
            case '1':
                std::cout << "Enter new string: ";
                std::getline(std::cin, newString);
                strings[str].AddField(field, newString);
                break;
            case '2':
                std::cout << "Enter new string: ";
                std::getline(std::cin, newString, '\n');
                strings[str].ChangeField(field, newString);
                break;
            case '3':
                strings[str].RemoveField(field);
                break;
            default:
                std::cout << "Unknown command!" << std::endl;
                command = 0;
                break;
        }
        i = 0;
        for (auto & str : strings) {
        std::cout << i++ << ": "<< str.toSplitString() << std::endl;
    }
        std::cout << "\nEnter command: ";
    }
    return 0;
}
