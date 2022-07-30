#pragma once
#include <vector>

class Sorts {
private:
    static void recursiveQuickSort(std::vector<Song>& songs, int start, int end);
    static int partition(std::vector<Song>& songs, int start, int end);
public:
    static void quickSort(std::vector<Song>& songs);
    static void timSort(std::vector<Song>& songs);
};
