#include "Sorts.h"
using namespace std;

void Sorts::recursiveQuickSort(std::vector<Song>& songs, int start, int end){
    if (start < end) {
        int pIndex = partition(songs, start, end);
        recursiveQuickSort(songs, start, pIndex - 1);
        recursiveQuickSort(songs, pIndex + 1, end);
    }
}
int Sorts::partition(std::vector<Song>& songs, int start, int end) {

}
void Sorts::quickSort(std::vector<Song>& songs){
    recursiveQuickSort(songs, 0, songs.size() - 1);
}
void Sorts::timSort(std::vector<Song>& songs){

}