#include "Sorts.h"
#include <algorithm>
using namespace std;

void Sorts::recursiveQuickSort(std::vector<Song*>& songs, int start, int end){
    //Do nothing if start and end have passed each other
    if (start < end) {
        //First partition the data based on a pivot point (chosen as the first element)
        int pIndex = partition(songs, start, end);
        //Recursively partition the first and second halves of data
        recursiveQuickSort(songs, start, pIndex - 1);
        recursiveQuickSort(songs, pIndex + 1, end);
    }
}
int Sorts::partition(std::vector<Song*>& songs, int start, int end) {
    //Initialize up and down pointers
    int up = start + 1;
    int down = end;
    //Repeatedly swap data points based on pivot point until there are two halves
    do {
        while ((songs[up]->score >= songs[start]->score) && (up != end)) {
            up++;
        }
        while ((songs[down]->score <= songs[start]->score) && (down != start)) {
            down--;
        }
        if (up < down) {
            Song* temp = songs[up];
            songs[up] = songs[down];
            songs[down] = temp;
        }
    } while (up < down);
    //Swap pivot with last greater element and return the new pivot index
    Song* temp = songs[start];
    songs[start] = songs[down];
    songs[down] = temp;
    return down;
}
void Sorts::insertionSort(std::vector<Song*>& songs, int start, int end) {
    for (int i = start + 1; i < end; i++) {
        Song* temp = songs[i];
        int j = i - 1;
        while (j >= start && songs[j]->score < temp->score) {
            songs[j + 1] = songs[j];
            j--;
        }
        songs[j + 1] = temp;
    }
}
void Sorts::merge(std::vector<Song*>& songs, int start, int mid, int end) {
    //Create temporary arrays which will be merged
    int length1 = mid - start + 1;
    int length2 = end - mid;
    Song* temp1[length1];
    Song* temp2[length2];
    for (int i = 0; i < length1; i++) {
        temp1[i] = songs[start + i];
    }
    for (int i = 0; i < length2; i++) {
        temp2[i] = songs[mid + i + 1];
    }
    //Merge both temp arrays back into larger vector, moving pointers as appropriate
    int i = 0;
    int j = 0;
    int k = start;
    while (i < length1 && j < length2) {
        if (temp1[i]->score >= temp2[j]->score) {
            songs[k] = temp1[i];
        }
        else {
            songs[k] = temp2[j];
            j++;
        }
        k++;
    }
    //Finish copying any excess elements
    while (i < length1) {
        songs[k] = temp1[i];
        k++;
        i++;
    }
    while (j < length2) {
        songs[k] = temp2[j];
        k++;
        j++;
    }
}
void Sorts::quickSort(std::vector<Song*>& songs){
    //Kickstart recursive chain
    recursiveQuickSort(songs, 0, songs.size() - 1);
}
void Sorts::timSort(std::vector<Song*>& songs){
    //Experimentally determined "run" constant, defining the length of runs to be sorted individually
    const int RUN_LENGTH = 64;
    //Insertion sort chunks of 64 data points
    for (int i = 0; i < songs.size(); i += RUN_LENGTH) {
        insertionSort(songs, i, min(i + RUN_LENGTH - 1, (int)songs.size() - 1));
    }
    //Merge together individually sorted chunks by repeatedly doubling scope of the merge operation; start at 64
    for (int size = RUN_LENGTH; size < songs.size(); size *= 2) {
        //For every scope, merge together adjacent chunks
        for (int i = 0; i < songs.size(); i += size * 2) {
            int midIndex = i + size - 1;
            int endIndex = min(i + (size * 2) - 1, (int)songs.size() - 1);
            //Only merge if middle index is in bounds, else the "left-out" section will be merged later
            if (midIndex < endIndex) {
                merge(songs, i, midIndex, endIndex);
            }
        }
    }
}