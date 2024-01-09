#pragma once

#include "hash_table.h"
#ifndef CHAT_H
#define CHAT_H

#include <iostream>
#include <vector>
#include <openssl/sha.h>
using namespace std;

class AuthData {
public:
    AuthData(const std::string& login, const std::string& password);

    const string& getLogin() const;
    const unsigned char* getHash() const;
};

class HashTable {
public:
    HashTable(int size);
    HashTable() {};
    void insert(const string& login, const unsigned char* hash);
    bool login(const string& login, const string& password);

private:
    struct Node {
        string login;
        unsigned char hash[SHA_DIGEST_LENGTH];
        bool occupied;
    };

    int tableSize;
    vector<Node> table;

    int hashFunction(const string& login);
    int quadraticProbe(int hash, int attempt);
};

class Chat {
public:
    Chat() {};
    void registerUser(const string& login, const string& password);
    bool login(const string& login, const string& password);

private:
    HashTable hashTable;
};

#endif 

