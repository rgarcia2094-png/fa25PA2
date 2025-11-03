//
// Created by Ryder Garcia on 10/20/25.
//

//program reads texts from input.txt then analyzes how often each letter appears,
//then encodes it using binary codes
//common letters get shorter codes and uncommon letters get longer codes
#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include "heap.h"
using namespace std;

// Global arrays for node information
const int MAX_NODES = 64;
int weightArr[MAX_NODES];
int leftArr[MAX_NODES];
int rightArr[MAX_NODES];
char charArr[MAX_NODES];

// Function prototypes
void buildFrequencyTable(int freq[], const string& filename);
int createLeafNodes(int freq[]);
int buildEncodingTree(int nextFree);
void generateCodes(int root, string codes[]);
void encodeMessage(const string& filename, string codes[]);

int main() {
    int freq[26] = {0};

    // Step 1: Read file and count letter frequencies
    buildFrequencyTable(freq, "input.txt");

    // Step 2: Create leaf nodes for each character with nonzero frequency
    int nextFree = createLeafNodes(freq);

    // Step 3: Build encoding tree using your heap
    int root = buildEncodingTree(nextFree);

    // Step 4: Generate binary codes using an STL stack
    string codes[26];
    generateCodes(root, codes);

    // Step 5: Encode the message and print output
    encodeMessage("input.txt", codes);

    return 0;
}

/*------------------------------------------------------
    Function Definitions (Students will complete logic)
  ------------------------------------------------------*/

// Step 1: Read file and count frequencies
void buildFrequencyTable(int freq[], const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: could not open " << filename << "\n";
        exit(1);
    }

    char ch;
    while (file.get(ch)) {
        // Convert uppercase to lowercase
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';

        // Count only lowercase letters
        if (ch >= 'a' && ch <= 'z')
            freq[ch - 'a']++;
    }
    file.close();

    cout << "Frequency table built successfully.\n";
}

// Step 2: Create leaf nodes for each character
int createLeafNodes(int freq[]) {
    int nextFree = 0;
    for (int i = 0; i < 26; ++i) {
        if (freq[i] > 0) {
            charArr[nextFree] = 'a' + i;
            weightArr[nextFree] = freq[i];
            leftArr[nextFree] = -1;
            rightArr[nextFree] = -1;
            nextFree++;
        }
    }
    cout << "Created " << nextFree << " leaf nodes.\n";
    return nextFree;
}

// Step 3: Build the encoding tree using heap operations
int buildEncodingTree(int nextFree) {
    // TODO:

    MiniHeap heap; //creation of mini heap object

    for (int i = 0; i < nextFree; ++i) //push all nodes into the heap
    heap.push(i);
    // 3. While the heap size is greater than 1:
    while (heap.size >1) { // combine the smallest pairs until one node remains
        int left = heap.pop();
        int right = heap.pop();

    //create new parent node
    charArr[nextFree] = '*'; //marks the internal node marker
    weightArr[nextFree] = weightArr[left] + weightArr[right]; //both childs combined
    leftArr[nextFree] = left; //left child
    rightArr[nextFree] = right; //right child

    heap.push(nextFree); //push new parent into the existing heap
    nextFree++; // increment index
    }

    return -1; // placeholder
}

// Step 4: Use an STL stack to generate codes
void generateCodes(int root, string codes[]) {
    // TODO:
    if (root ==-1) return; //check if tree = empty

    //stack will hold nodeIndex, currentCode
    stack<pair<int, string>> st;
    st.push({root, ""}); //start traversal

    while (!st.empty()) { //keep going until stack is empty
    auto [node, code] = st.top(); //take top element
    st.pop();

    //if leaf node has no children
    if (leftArr[node] == -1 && rightArr[node] == -1) {
        if (charArr[node] >= 'a' && charArr[node] <= 'z') // store the genrated code for the chosen character
        codes[charArr[node] - 'a'] = code;
    } else {
    // push to the right direction first, then in the left direction so that the left is first, +1
    if (rightArr[node] != -1)
        st.push([rightArr[node],code + "1"});
    if (leftArr[node] != -1) // push left child, +0
        st.push({leftArr[node], code + "0"});
    }
  }
}

// Step 5: Print table and encoded message
void encodeMessage(const string& filename, string codes[]) {
    cout << "\nCharacter : Code\n";
    for (int i = 0; i < 26; ++i) {
        if (!codes[i].empty())
            cout << char('a' + i) << " : " << codes[i] << "\n";
    }

    cout << "\nEncoded message:\n";

    ifstream file(filename);
    char ch;
    while (file.get(ch)) {
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';
        if (ch >= 'a' && ch <= 'z')
            cout << codes[ch - 'a'];
    }
    cout << "\n";
    file.close();
}