w//
// Created by Ryder garcia on 10/23/25.
//


//defines the Minheap structure that is used to manage node indices by their corresponding weights
//heap ensures the mallest weight always stays at the root

#ifndef HEAP_H
#define HEAP_H

#include <iostream>
using namespace std;

struct MinHeap {
    int data[64];
    int size;

    MinHeap() { size = 0; }

    void push(int idx, int weightArr[]) {
        // TODO: insert index at end of heap, restore order using upheap()
        data[size] = idx; //insert at end of heap

        upheap(size, weightArr); //flip heap upward
        size++; //+ heap size

    }

    int pop(int weightArr[]) { //check for underflow
        // TODO: remove and return smallest index
        // Replace root with last element, then call downheap()
        if (size ==0) {
            cerr << "Error: Heap underflow!\n"; //error mssge if heap = empty
            exit(1); //exit the program
        }

        int smallest = data[0]; // save root index(min)
        size--; // - decrease heap size

        data[0] = data[size]; // move last element to root

        downheap(0, weightArr); //flip heap downward
        return smallest; //rturn smallest node index
    }

    void upheap(int pos, int weightArr[]) {
        // TODO: swap child upward while smaller than parent
        while (pos > 0) {
            int parent = (pos - 1) /2; //parent index formula

            if (weightArr[data[pos]] < weightArr[data[parent]]) { //compare childs and parents weights
                swap(data[pos], data[parent]); //swap if child < parents
                pos = parent; //increase to parents position
            } else {
                break; //if order = correct, stop
            }
        }
    }

    void downheap(int pos, int weightArr[]) {
        // TODO: swap parent downward while larger than any child
        while (true) { //calculate right and left child
            int left = 2 * pos + 1;
            int right = 2 * pos +2;
            int smallest = pos; //assume the current node is = smallest

            if (left < size && weightArr[data[left]] < weightArr[data[smallest]])
                smallest = left; //compare with left child

            if (right < size && weightArr[data[right]] < weightArr[data[smallest]])
                smallest = right; //compare wiht right child

            if (smallest != pos) { //if there is a smaller child -> swap then continue
                swap(data[pos], data[smallest]);
                pos = smallest; //move down to the new position
            } else {
                break; // if heap is satsfied = stop
            }

        }

    }
};

#endif