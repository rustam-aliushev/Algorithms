/**
 * @mainpage Bubble, heat, quick sorts comparision
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <tuple>
#include <cmath>
#include <chrono>

using namespace std;

/**
 * @brief Function for reading data from file
 * @param filename Name of the read file
 * @param n Table size
 * @return Table from the file
*/
vector<tuple<string, string, int, int>> read_csv(const string& filename, int n) {
    vector<tuple<string, string, int, int>> data;
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        getline(file, line); // Пропускаем заголовок
        for (int i = 0; i < n; i++) {
            getline(file, line);
            stringstream ss(line);
            string firstname, lastname;
            int year, pagecount;
            getline(ss, firstname, ',');
            getline(ss, lastname, ',');
            ss >> year;
            ss.ignore();
            ss >> pagecount;
            data.emplace_back(firstname, lastname, year, pagecount);
        }
        file.close();
    }
    return data;
}


/**
 * @brief Overload of operator > for given table
 * @param t1 First compared table
 * @param t2 Second compared table
 * @return Result of comparision
 */
bool operator>(const tuple<string, string, int, int>& t1, const tuple<string, string, int, int>& t2) {
    if (get<0>(t1) > get<0>(t2)) return true;
    else if (get<0>(t1) == get<0>(t2)) {
        if (get<1>(t1) > get<1>(t2)) return true;
        else if (get<1>(t1) == get<1>(t2)) {
            if (get<2>(t1) > get<2>(t2)) return true;
            else return false;
        } else return false;
    } else return false;
}


/**
 * @brief Overload of operator < for given table
 * @param t1 First compared table
 * @param t2 Second compared table
 * @return Result of comparision
 */
bool operator<(const tuple<string, string, int, int>& t1, const tuple<string, string, int, int>& t2) {
    if (get<0>(t1) < get<0>(t2)) return true;
    else if (get<0>(t1) == get<0>(t2)) {
        if (get<1>(t1) < get<1>(t2)) return true;
        else if (get<1>(t1) == get<1>(t2)) {
            if (get<2>(t1) < get<2>(t2)) return true;
            else return false;
        } else return false;
    } else return false;
}

/**
 * @brief Overload of operator >= for given table
 * @param t1 First compared table
 * @param t2 Second compared table
 * @return Result of comparision
 */
bool operator>=(const tuple<string, string, int, int>& t1, const tuple<string, string, int, int>& t2) {
    if (get<0>(t1) >= get<0>(t2)) return true;
    else return false;
}

/**
 * @brief Overload of operator <= for given table
 * @param t1 First compared table
 * @param t2 Second compared table
 * @return Result of comparision
 */
bool operator<=(const tuple<string, string, int, int>& t1, const tuple<string, string, int, int>& t2) {
    if (get<0>(t1) <= get<0>(t2)) return true;
    else return false;
}

/**
 * @brief Overload of operator == for given table
 * @param t1 First compared table
 * @param t2 Second compared table
 * @return Result of comparision
 */
bool operator==(const tuple<string, string, int, int>& t1, const tuple<string, string, int, int>& t2) {
    if (get<0>(t1) == get<0>(t2) and get<1>(t1) == get<1>(t2) and get<2>(t1) == get<2>(t2)) return true;
    else return false;
}

/**
 * @brief Bubble sort
 * @param data Sorted table
 * @param n Size of the table
 * @return Duration of sorting
 */
double bubble_sort(vector<tuple<string, string, int, int>> data, int n){
    auto start = chrono::high_resolution_clock::now();

    for (int i = n-1; i>1; i--){
        for (int j = 0; j < i; j++){
            if ( data[j] > data[j+1] ){
                auto temp = data[j+1];
                data[j+1] = data[j];
                data[j] = temp;
            }
        }
    }

    string name = "/Users/Rustam/CLionProjects/untitled5/sorted/" + to_string(n) + "_bubble_sorted.csv";
    ofstream file(name);
    for (tuple tpl : data){
        file << get<0>(tpl) << "," << get<1>(tpl) << "," << get<2>(tpl) << "," << get<3>(tpl) << "\n";
    }
    file.close();

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    double res = duration.count();
    return res;
}

/**
 * @brief Helping function for heap sort, turns binary tree into binary heap
 * @param data Sorted table
 * @param n Size of the table
 * @param i vertex of the heap
 */
void heapify(vector<tuple<string, string, int, int>> &data, int n, int i){
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && data[left] > data[largest])
        largest = left;

    if (right < n && data[right] > data[largest])
        largest = right;

    if (largest != i)
    {
        auto temp = data[largest];
        data[largest] = data[i];
        data[i] = temp;

        heapify(data, n, largest);
    }

}

/**
 * @brief Heap Sort
 * @param data Sorted table
 * @param n Size of the table
 * @return Duration of sorting
 */
double heap_sort(vector<tuple<string, string, int, int>> data, int n){
    auto start = chrono::high_resolution_clock::now();

    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(data, n, i);

    for (int i = n - 1; i >= 0; i--)
    {
        auto temp = data[0];
        data[0] = data[i];
        data[i] = temp;

        heapify(data, i, 0);
    }

    string name = "/Users/Rustam/CLionProjects/untitled5/sorted/" + to_string(n) + "_heap_sorted.csv";
    ofstream file(name);
    for (tuple tpl : data){
        file << get<0>(tpl) << "," << get<1>(tpl) << "," << get<2>(tpl) << "," << get<3>(tpl) << "\n";
    }
    file.close();

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    double res = duration.count();
    return res;
}

/**
 * @brief Helping function for quick sort, partition
 * @param data Sorted table
 * @param low Lower bound of partitoning
 * @param high Higher border of partitioning
 * @return divising border
 */
int partition(vector<tuple<string, string, int, int>> &data, int low, int high) {
    auto pivot = data[(low + high) / 2];
    int i = low - 1;
    int j = high + 1;

    while (true) {
        do {
            i++;
        } while (data[i] < pivot);

        do {
            j--;
        } while (data[j] > pivot);

        if (i >= j) {
            return j;
        }

        auto temp  = data[i];
        data[i] = data[j];
        data[j] = temp;
    }
}

/**
 * @brief Quick sort
 * @param data Sorted table
 * @param low Lower border for partitioning
 * @param high Higher border for partitioning
 */
void quick_sort(vector<tuple<string, string, int, int>> &data, int low, int high) {
    if (low < high) {
        int pi = partition(data, low, high);

        quick_sort(data, low, pi);
        quick_sort(data, pi + 1, high);
    }
}

/**
 * @brief Quick sort
 * @param data Sorted table
 * @param n Size of the table
 * @return Duration of sorting
 */
double quick_sort(vector<tuple<string, string, int, int>> data, int n){
    auto start = chrono::high_resolution_clock::now();

    quick_sort(data, 0, n-1);

    string name = "/Users/Rustam/CLionProjects/untitled5/sorted/" + to_string(n) + "_quick_sorted.csv";
    ofstream file(name);
    for (tuple tpl : data){
        file << get<0>(tpl) << "," << get<1>(tpl) << "," << get<2>(tpl) << "," << get<3>(tpl) << "\n";
    }
    file.close();

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    double res = duration.count();
    return res;
}

/**
 * @brief main function
 * @return 0
 */
int main() {

    //reading data
    int sizes[7] {100, 500, 1000, 5000, 10000, 50000, 100000};
    vector<tuple<string, string, int, int>> data[7];
    for (int i = 0; i < 7; i++){
        string file;
        file = "/Users/Rustam/CLionProjects/untitled5/sourse/" + to_string(sizes[i]) + ".csv";
        data[i] = read_csv(file, sizes[i]);
    }

    vector<double> bubble_time, heap_time, quick_time;
    for (int i = 0; i < 7; i++){
        //sorts
        double bubble = bubble_sort(data[i], sizes[i]);
        double heap = heap_sort(data[i], sizes[i]);
        double quick = quick_sort(data[i], sizes[i]);

        //vectors with durations
        bubble_time.push_back(bubble);
        heap_time.push_back(heap);
        quick_time.push_back(quick);
    }

    //printing results
    cout << "Пузырьковое время:";
    for (int i = 0; i < 7; i++){
        cout << bubble_time[i] << " ";
    }
    cout << endl;

    cout << "Пирамидальное время:";
    for (int i = 0; i < 7; i++){
        cout << heap_time[i] << " ";
    }
    cout << endl;

    cout << "Быстрое время:";
    for (int i = 0; i < 7; i++){
        cout << quick_time[i] << " ";
    }
    cout << endl;


    return 0;
}