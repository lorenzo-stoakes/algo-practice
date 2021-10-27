#include <cmath>
#include <iostream>
#include <vector>

int find_min_av_slice(const std::vector<int>& A)
{
    int bestInd = 0;

    int sum = A[0] + A[1];
    int n = 2;
    double bestAv = (double)sum / n;

    int index = 0;

    for (int i = 2; i < (int)A.size(); i++) {
        int val = A[i];
        int prev = A[i-1];

        sum += val;
        n++;

        double expandedAv = (double)sum / n;
        double newAv = ((double)val + prev) / 2;

        //std::cout << "saw " << val << " expanded = " << expandedAv << " new = " << newAv << " n = " << n << std::endl;

        double av;
        if (newAv < expandedAv && std::fabs(newAv - expandedAv) > 1e-10) {
            //std::cout << "CHOOSE new from " << i - 1 << std::endl;
            index = i - 1;
            sum = prev + val;
            n = 2;
            av = newAv;
        } else {
            //std::cout << "CHOOSE expand from " << index << std::endl;
            av = expandedAv;
        }

        if (av < bestAv && std::fabs(av - bestAv) > 1e-10) {
            bestAv = av;
            bestInd = index;
        }
    }

    return bestInd;
}

int main()
{
	std::cout << find_min_av_slice({10, 10, -1, 2, 4, -1, 2, -1 }) << std::endl;
	std::cout << find_min_av_slice({ 4, 2, 2, 5, 1, 5, 8 }) << std::endl;

	return 0;
}
