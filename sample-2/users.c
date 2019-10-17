// Simple example to show:
// Memory allocation
// Buffers
// Structures

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct user {
    char username[64];
    char password_salt[8];
    char password_hash[64];
    char favorite_drink[128];
    char super_power[128];
    char weakness[128];
};

/**
 * @brief Reads a user from the provided file descriptor
 * 
 * @param fp File to read from
 * @returns User structure or NULL
 */
struct user *read_user(FILE *fp)
{
    struct user *new_user = malloc(sizeof(struct user));
    if (NULL != new_user) {
        if (fread(new_user, sizeof(struct user), 1, fp) != sizeof(struct user)) {
            // Failed to read sufficient data
            free(new_user);
            new_user = NULL;
        }
    }
    return new_user;
}

/**
 * @brief Reads in a bunch of users
 * 
 * @param fp File to read from
 * @param user_array User structure or NULL
 * @param max_users maximum number of users to read in
 * 
 * @returns Number of users read
 */
unsigned int read_multiple_users(FILE *fp, struct user **user_array, unsigned int max_users) 
{
    unsigned int num_users;
    
    if (NULL == fp || NULL == user_array) {
        return 0;
    }

    for (num_users = 0; num_users < max_users; num_users++) {
        user_array[num_users] = read_user(fp);
        // If we fail at reading a user, bail
        if (NULL == user_array[num_users]) {
            break;
        }
    }

    return num_users;
}

/**
 * @brief Prints out the various users
 * 
 * @param user_array Null terminated list of users
 */
void print_users(struct user **user_array)
{
    unsigned int idx;
    if (NULL == user_array) {
        return;
    }

    for (idx = 0; NULL != user_array[idx]; idx++) {
        struct user *curr = user_array[idx];
        printf("User %-2u: %s:\n", idx, curr->username);
        printf("hash: %s\n", curr->password_hash);
        printf("Favorite drink: %s\n", curr->favorite_drink);
        printf("Warning, this person has the following superpower: %s\n\n", curr->super_power);
    }
}

struct user *user_list[64];
int main(int argc, char *argv[]) 
{
    if (2 != argc) {
        printf("Usage: %s <USER_LIST>\n", argv[0]);
        exit(1);
    }

    printf("Reading from %s\n", argv[1]);
    FILE *fp = fopen(argv[1], "rb");
    memset(user_list, 0, sizeof(user_list));

    read_multiple_users(fp, user_list, sizeof(user_list)/sizeof(user_list[0]));
    fclose(fp);
    print_users(user_list);
}
