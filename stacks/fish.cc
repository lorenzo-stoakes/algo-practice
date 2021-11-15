#include <iostream>
#include <vector>

/*
 * You are given two non-empty arrays A and B consisting of N integers. Arrays A
 * and B represent N voracious fish in a river, ordered downstream along the
 * flow of the river.
 *
 * The fish are numbered from 0 to N − 1. If P and Q are two fish and P < Q,
 * then fish P is initially upstream of fish Q. Initially, each fish has a
 * unique position.
 *
 * Fish number P is represented by A[P] and B[P]. Array A contains the sizes of
 * the fish. All its elements are unique. Array B contains the directions of the
 * fish. It contains only 0s and/or 1s, where:
 *
 * 0 represents a fish flowing upstream,
 * 1 represents a fish flowing downstream.
 *
 * If two fish move in opposite directions and there are no other (living) fish
 * between them, they will eventually meet each other. Then only one fish can
 * stay alive − the larger fish eats the smaller one. More precisely, we say
 * that two fish P and Q meet each other when P < Q, B[P] = 1 and B[Q] = 0, and
 * there are no living fish between them. After they meet:
 *
 * If A[P] > A[Q] then P eats Q, and P will still be flowing downstream,
 * If A[Q] > A[P] then Q eats P, and Q will still be flowing upstream.
 *
 * We assume that all the fish are flowing at the same speed. That is, fish
 * moving in the same direction never meet. The goal is to calculate the number
 * of fish that will stay alive.
 */

int count_surviving_fish(const std::vector<int>& A, const std::vector<int>& B)
{
    int alive = A.size();

    std::vector<int> downstream_stack;

    for (size_t i = 0; i < A.size(); i++) {
        int size = A[i];
        int dir = B[i];

        // Downstream fish just get added to the stack. When an upstream fish comes we
        // work our way through them.
        if (dir == 1) {
            downstream_stack.push_back(size);
            continue;
        }

        // At this point the fish in question is 1. upstream 2. we have a downstream fish to face them.
        while (!downstream_stack.empty()) {
            alive--; // One has to die.
            int downstream_size = downstream_stack.back();
            if (downstream_size > size) // If downstream fish wins we just move on to next.
                break;
            downstream_stack.pop_back();
        }
    }

    return alive;
}

int main()
{
	std::cout << count_surviving_fish({ 4, 3, 2, 1, 5 }, { 0, 1, 0, 0, 0 }) << std::endl;
}
