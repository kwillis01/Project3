#include <chrono>
#include <iostream>
using namespace std;
using namespace std::chrono;

//Example function
void Function(){
    int sum = 0;
    for(int i = 0; i < 10000; i++){
        sum = sum + i;
    }
}

int main(){                                            //Citation: GeeksforGeeks: Measure execution time of a function in C++
    auto start = high_resolution_clock::now();         //url: https://www.geeksforgeeks.org/measure-execution-time-function-cpp/
    Function();                             //call to function
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(stop-start);
    cout << "Time taken: " << duration.count() << " nanoseconds" << endl;  //Print the amount of nanoseconds Function() took to run
    return 0;
}