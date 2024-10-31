//
//  main.cpp
//  OS_lab2_threads
//
//  Created by Michael Malinovsky on 26.10.24.
//

#include <iostream>
#include <thread>
#include <future>
using namespace std;

pair<int, int> calc_min_max(int* arr, int size){
    int mod = size%2, min = arr[0], max = arr[0], i;
    for(i = 0; i < size/2; i++){
        if(arr[2*i] > arr[2*i+1]){
            if(arr[2*i] > max) max = arr[2*i];
            std::this_thread::sleep_for(7ms);
            if(arr[2*i+1] < min) min = arr[2*i+1];
            std::this_thread::sleep_for(7ms);

        }
        else{
            if(arr[2*i+1] > max) max = arr[2*i+1];
            std::this_thread::sleep_for(7ms);

            if(arr[2*i] < min) min = arr[2*i];
            std::this_thread::sleep_for(7ms);

        }
    }
    
    if (mod == 1){
        if(arr[2*i] > max) max = arr[2*i];
        if(arr[2*i] < min) min = arr[2*i];
    }
    cout << "max = " << max << endl << "min = " << min << endl;
    pair result(min, max);
    return result;
}

int calc_average(int* arr, int size){
    int sum = 0;
    for(int i = 0; i < size; i++){
        sum += arr[i];
        std::this_thread::sleep_for(12ms);
    }
    cout << "average = " << sum/size << endl;
    return sum/size;
}
int main(int argc, const char * argv[]) {
    int size;
    cin >> size;
    int* arr = new int[size];
    for (int i = 0; i < size; i++){
        cin >> arr[i];
    }
//    , average(calc_average);
//    promise<pair<int,int>> p;
    future <pair<int,int>> ret1 = async(launch::async, calc_min_max, arr, size);
    pair<int, int> p = ret1.get();
    future <int> ret2 = async(launch::async, calc_average, arr, size);
    int t = ret2.get();
    for(int i = 0; i<size; i++){
        if(p.first == arr[i]) arr[i] = t;
        if(p.second == arr[i]) arr[i] = t;
    }
    for(int i = 0; i<size; i++){
        cout << arr[i] << " ";
    }
//    auto f = p.get_future();
//    thread min_max(&calc_min_max, move(p));
//    min_max.join();
//    average.join();
//
    return 0;
}
