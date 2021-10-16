// you can use includes, for example:
// #include <algorithm>

// you can write to stdout for debugging purposes, e.g.
// cout << "this is a debug message" << endl;

#include <array>

namespace
{
    // the opposite sides of dice always sum to 7.
    int opposite(int face)
    {
        return 7 - face;
    }

    bool tryTurn(std::array<int, 7> countA, std::array<int, 7> countB, int count, int delta)
    {
        std::cout << "count=" << count << std::endl;

        if (delta == 0)
            return true;
        if (count <= 0)
            return false;

        // Try turning A.
        for (int i = 1; i <= 6; i++) {
            if (countA[i] == 0)
                continue;

            delta -= i;
            countA[i]--;
            for (int j = 1; j <= 6; j++) {
                if (j == i)
                    continue;
                delta += j;
                if (tryTurn(countA, countB, count - 1, delta))
                    return true;
                delta -= j;
            }
            // Turn back.
            countA[i]++;
        }

        // Try turning B.
        for (int i = 1; i <= 6; i++) {
            if (countB[i] == 0)
                continue;

            delta -= i;
            countB[i]--;
            for (int j = 1; j <= 6; j++) {
                if (j == i)
                    continue;
                delta += j;
                if (tryTurn(countA, countB, count - 1, delta))
                    return true;
                delta -= j;
            }
            // Turn back.
            countB[i]++;
        }

        // We failed.
        return false;
    }
}

int solution(std::vector<int>& A, std::vector<int>& B)
{
    // Start with raw/inefficient solution we can iterate on.

    std::array<int, 7> countA = { 0 };
    std::array<int, 7> countB = { 0 };

    for (int a: A) {
        countA[a]++;
    }

    for (int b : B) {
        countB[b]++;
    }

    // Prune.

    int totalUnique = 0;
    int sumA = 0;
    int sumB = 0;
    for (int i = 1; i <= 6; i++) {
        int currA = countA[i];
        int currB = countB[i];
        int delta = currA > currB ? currA - currB : currB - currA;

        countA[i] -= delta;
        countB[i] -= delta;

        totalUnique += delta;
        sumA += countA[i] * i;
        sumB += countB[i] * i;
    }

    int totalDelta = sumA > sumB ? sumA - sumB : sumB - sumA;
    std::cout << "totalDelta=" << totalDelta << std::endl;

    // Try every swap.
    for (int numTurns = 0; numTurns <= totalUnique; numTurns++) {
        if (tryTurn(countA, countB, numTurns, totalDelta))
            return numTurns;
    }

    return -1;
}
