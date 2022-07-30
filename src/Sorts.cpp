#include "Sorts.h"
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
void Sorts::quickSort(std::vector<Song>& songs){
    //Kickstart recursive chain
    recursiveQuickSort(songs, 0, songs.size() - 1);
}
void Sorts::timSort(std::vector<Song>& songs){

}