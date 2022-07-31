#pragma once
#include "Song.h"
#include <vector>

class Sorts {
private:
    //Quicksort helper functions
    static void recursiveQuickSort(std::vector<Song*>& songs, int start, int end);
    static int partition(std::vector<Song*>& songs, int start, int end);
    //Timsort helper functions
    static void insertionSort(std::vector<Song*>& songs, int start, int end);
    static void merge(std::vector<Song*>& songs, int start, int mid, int end);
public:
    //In-place quicksort that sorts a vector of songs by score in DESCENDING order
    static void quickSort(std::vector<Song*>& songs);
    //Hybrid sorting algorithm which combines the strengths of both insertion sort and merge sort (DESCENDING order)
    static void timSort(std::vector<Song*>& songs);
};