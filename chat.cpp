#include "chat.h"

AuthData::AuthData(const string& login, const string& password) {
    this->login = login;
    SHA1(reinterpret_cast<const unsigned char*>(password.c_str()), password.length(), hash);
}

const string& AuthData::getLogin() const {
    return login;
}

const unsigned char* AuthData::getHash() const {
    return hash;
}

HashTable::HashTable(int size) : tableSize(size), table(size) {}

void HashTable::insert(const string& login, const unsigned char* hash) {
    int index = hashFunction(login);
    int attempt = 1;

    while (table[index].occupied) {
        index = (index + quadraticProbe(index, attempt)) % tableSize;
        attempt++;
    }

    table[index].login = login;
    memcpy(table[index].hash, hash, SHA_DIGEST_LENGTH);
    table[index].occupied = true;
}

bool HashTable::login(const string& login, const string& password) {
    int index = hashFunction(login);
    int attempt = 1;

    while (table[index].occupied) {
        if (table[index].login == login) {
            unsigned char inputHash[SHA_DIGEST_LENGTH];
            SHA1(reinterpret_cast<const unsigned char*>(password.c_str()), password.length(), inputHash);

            if (memcmp(table[index].hash, inputHash, SHA_DIGEST_LENGTH) == 0) {
                cout << "Login successful for user: " << login << endl;
                return true;
            }
            else {
                cout << "Login failed. Incorrect password for user: " << login << endl;
                return false;
            }
        }

        index = (index + quadraticProbe(index, attempt)) % tableSize;
        attempt++;
    }

    cout << "Login failed. User not found: " << login << endl;
    return false;
}

int HashTable::hashFunction(const string& login) 
{
    const int multiplier = 31;
    int hash = 0;

    for (char c : login) {
        hash = multiplier * hash + c;
    }

    return hash % tableSize;
}

int HashTable::quadraticProbe(int hash, int attempt) 
{
    return attempt * attempt;
}

void Chat::registerUser(const string& login, const string& password) {
    AuthData authData(login, password);
    hashTable.insert(authData.getLogin(), authData.getHash());
}

bool Chat::login(const string& login, const string& password) {
    return hashTable.login(login, password);
}
