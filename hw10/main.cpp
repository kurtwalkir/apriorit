

/*
void func( std::array<int, 7> &A, int low, int high) 
{
    // For lines 7 - 9 time complecsity is O(1)
    int i = low; // O(1)
    int j = high; // O(1)
    int x = A[(low+high)/2];// O(1)
    do {
        while(A[i] < x) ++i; // O(N)
        while(A[j] > x) --j; // O(N)
        if(i <= j) { // Time complexity of line 15-17 will be O(1)
            int temp = A[i];
            A[i] = A[j];
            A[j] = temp;
            i++; j--;
        }
    } while(i < j); // O(N)

      if(low < j) //recursion
         func(A, low, j); O
      if(i < high) //recursion
         func(A, i, high); // Time complexity of line 22-25 O(2^N)
  }
*/

//Conclusion. It looks like a complecsity will be O(2^N +N)

/*
    Pick the container for storing data of telephone book. It should allow to search the data about a person by his phone number.
    Explain why you chose this container. Explanation should contain list of container operations and their complexity in O notation.
*/

#include <map>

using namespace std;

int main(int argc, char const *argv[])
{
    std::map<string, string> tBook{};
    tBook.insert(std::move(pair<string, string>("12345678", "Alex"))); //Insertion time log(N)
    tBook.insert(std::move(pair<string, string>("87456123", "Hanna")));
    tBook.insert(std::move(pair<string, string>("14785236", "Maksym")));

    cout << "Phone number:" << tBook["12345678"]; // Search time log(N)

    tBook.erase("12345678"); // Deletion time log(N)
    return 0;
}
/*
    For this task I would prefer to use std::map , because complexity of inserting/removing/searching operation are log(N).
*/