#include "chat.h"

int main() {
    Chat chat;

    chat.registerUser("user1", "password1");
    chat.registerUser("user2", "password2");

    chat.login("user1", "password1");
    chat.login("user2", "wrong_password");
    chat.login("user3", "password3");

    return 0;
}