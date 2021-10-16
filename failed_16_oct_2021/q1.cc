// you can use includes, for example:
// #include <algorithm>

#include <algorithm>

// you can write to stdout for debugging purposes, e.g.
// cout << "this is a debug message" << endl;

int solution(vector<int> &A, int K) {
    int min = 1000000001;
    int max = -1;

    for (int a : A) {
        if (a < min)
            min = a;

        if (a > max)
            max = a;
    }

    // Consider best case.
    std::vector<int> copy = A;
    std::sort(copy.begin(), copy.end());

    int start = 0;
    int end = A.size() - 1;
    for (int i = 0; i < K; i++) {
        if (copy[end] - copy[start + 1] <
            copy[end - 1] - copy[start])
            start++;
        else
            end--;
    }

    int best = copy[end] - copy[start];

    // Maybe try max heap, min heap and some sliding range?

    // Incorrect but as a start...
    return best;
}
