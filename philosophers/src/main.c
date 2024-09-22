#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

// Assuming these are declared globally
pthread_mutex_t mutex;
int balance = 0;

void* deposit(void* amount) {
    int deposit_amount = *(int*)amount;

    // Lock the mutex before updating the balance
    pthread_mutex_lock(&mutex);

    // Critical section
    balance += deposit_amount;

    // Unlock the mutex after updating the balance
    pthread_mutex_unlock(&mutex);

    return NULL;
}

// write the new balance (after as simulated 1/4 second delay)
void write_balance(int new_balance)
{
  usleep(250000);
  balance = new_balance;
}

int read_balance() {
    return balance;
}

int main() {
    pthread_t thread1;
    pthread_t thread2;

    // Initialize the mutex
    pthread_mutex_init(&mutex, NULL);

    // The deposit amounts... the correct total afterwards should be 500
    int deposit1 = 300;
    int deposit2 = 200;

    // Create threads to run the deposit function with these deposit amounts
    pthread_create(&thread1, NULL, deposit, (void*) &deposit1);
    pthread_create(&thread2, NULL, deposit, (void*) &deposit2);

    // Join the threads
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // Destroy the mutex
    pthread_mutex_destroy(&mutex);

    // Output the balance after the deposits
    int after = read_balance();
    printf("After: %d\n", after);

    return 0;
}