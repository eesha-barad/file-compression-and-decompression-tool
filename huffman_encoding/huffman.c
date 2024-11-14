#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TREE_HT 256
#define BUFFER_SIZE 4096

// Huffman tree node structure
struct MinHeapNode {
    unsigned char data;
    unsigned freq;
    struct MinHeapNode *left, *right;
};

// Min heap structure for Huffman tree
struct MinHeap {
    unsigned size;
    unsigned capacity;
    struct MinHeapNode** array;
};

// Create a new min heap node
struct MinHeapNode* newNode(unsigned char data, unsigned freq) {
    struct MinHeapNode* temp = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));
    temp->left = temp->right = NULL;
    temp->data = data;
    temp->freq = freq;
    return temp;
}

// Create a min heap
struct MinHeap* createMinHeap(unsigned capacity) {
    struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (struct MinHeapNode**)malloc(minHeap->capacity * sizeof(struct MinHeapNode*));
    return minHeap;
}

// Swap two min heap nodes
void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b) {
    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

// Heapify a node
void minHeapify(struct MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left]->freq < minHeap->array[smallest]->freq)
        smallest = left;

    if (right < minHeap->size && minHeap->array[right]->freq < minHeap->array[smallest]->freq)
        smallest = right;

    if (smallest != idx) {
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

// Extract minimum value node
struct MinHeapNode* extractMin(struct MinHeap* minHeap) {
    struct MinHeapNode* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    --minHeap->size;
    minHeapify(minHeap, 0);
    return temp;
}

// Insert a node into the min heap
void insertMinHeap(struct MinHeap* minHeap, struct MinHeapNode* minHeapNode) {
    ++minHeap->size;
    int i = minHeap->size - 1;
    while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq) {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    minHeap->array[i] = minHeapNode;
}

// Build a min heap
void buildMinHeap(struct MinHeap* minHeap) {
    int n = minHeap->size - 1;
    for (int i = (n - 1) / 2; i >= 0; --i)
        minHeapify(minHeap, i);
}

// Create and build a min heap from given data and frequency arrays
struct MinHeap* createAndBuildMinHeap(unsigned char data[], int freq[], int size) {
    struct MinHeap* minHeap = createMinHeap(size);
    for (int i = 0; i < size; ++i)
        minHeap->array[i] = newNode(data[i], freq[i]);
    minHeap->size = size;
    buildMinHeap(minHeap);
    return minHeap;
}

// Build the Huffman tree
struct MinHeapNode* buildHuffmanTree(unsigned char data[], int freq[], int size) {
    struct MinHeapNode *left, *right, *top;
    struct MinHeap* minHeap = createAndBuildMinHeap(data, freq, size);

    while (minHeap->size != 1) {
        left = extractMin(minHeap);
        right = extractMin(minHeap);
        top = newNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        insertMinHeap(minHeap, top);
    }
    return extractMin(minHeap);
}

// Generate Huffman codes
void generateCodes(struct MinHeapNode* root, unsigned char code[], int top, unsigned char codes[][MAX_TREE_HT], int codeLength[]) {
    if (root->left) {
        code[top] = '0';
        generateCodes(root->left, code, top + 1, codes, codeLength);
    }

    if (root->right) {
        code[top] = '1';
        generateCodes(root->right, code, top + 1, codes, codeLength);
    }

    if (!(root->left) && !(root->right)) {
        code[top] = '\0';
        strcpy((char *)codes[root->data], (char *)code);
        codeLength[root->data] = top;
    }
}

void findHuffmanCode(unsigned char codes[][MAX_TREE_HT], int codeLength[], char target){
	if (codeLength[(unsigned char)target] > 0) {
		printf("Huffman code of '%c': %s\n", target, codes[(unsigned char)target]);
	} 
	else {
		printf("%c not found", target);
	}
}

void writeBits(FILE *out, unsigned char *buffer, int *bufferIndex, int *bitCount, unsigned char bit) {
    *buffer |= (bit << (7 - *bitCount));
    (*bitCount)++;
    if (*bitCount == 8) {
        fputc(*buffer, out);
        *buffer = 0;
        *bitCount = 0;
    }
    (*bufferIndex)++;
}

// Compress a file
void compressFile(const char* inputFile, const char* outputFile) {
    FILE *in = fopen(inputFile, "rb");
    if (!in) {
        perror("Could not open input file");
        return;
    }

    int freq[256] = {0};
    int ch;
    while ((ch = fgetc(in)) != EOF)
        freq[ch]++;

    unsigned char data[256];
    int freqList[256], size = 0;
    for (int i = 0; i < 256; ++i) {
        if (freq[i]) {
            data[size] = i;
            freqList[size++] = freq[i];
        }
    }

    struct MinHeapNode* root = buildHuffmanTree(data, freqList, size);

    unsigned char codes[256][MAX_TREE_HT] = {{0}};
    int codeLength[256] = {0};
    unsigned char code[MAX_TREE_HT];
    generateCodes(root, code, 0, codes, codeLength);

    fseek(in, 0, SEEK_SET);
    FILE *out = fopen(outputFile, "wb");
    if (!out) {
        perror("Could not open output file");
        fclose(in);
        return;
    }

    fwrite(&size, sizeof(int), 1, out);
    fwrite(data, sizeof(unsigned char), size, out);
    fwrite(freqList, sizeof(int), size, out);

    unsigned char buffer = 0;
    int bufferIndex = 0, bitCount = 0;

    while ((ch = fgetc(in)) != EOF) {
        unsigned char *currentCode = codes[ch];
        for (int i = 0; i < codeLength[ch]; i++) {
            writeBits(out, &buffer, &bufferIndex, &bitCount, currentCode[i] - '0');
        }
    }

    if (bitCount > 0)
        fputc(buffer, out);

    fclose(in);
    fclose(out);
    printf("File compressed successfully.\n");
}

// Decompress a file
void decompressFile(const char* inputFile, const char* outputFile) {
    FILE *in = fopen(inputFile, "rb");
    if (!in) {
        perror("Could not open input file");
        return;
    }

    int size;
    fread(&size, sizeof(int), 1, in);

    unsigned char data[256];
    int freq[256];
    fread(data, sizeof(unsigned char), size, in);
    fread(freq, sizeof(int), size, in);

    struct MinHeapNode* root = buildHuffmanTree(data, freq, size);

    FILE *out = fopen(outputFile, "wb");
    if (!out) {
        perror("Could not open output file");
        fclose(in);
        return;
    }

    struct MinHeapNode* currentNode = root;
    int bit, byteRead;
    while ((byteRead = fgetc(in)) != EOF) {
        for (int i = 7; i >= 0; i--) {
            bit = (byteRead >> i) & 1;
            currentNode = (bit == 0) ? currentNode->left : currentNode->right;

            if (!currentNode->left && !currentNode->right) {
                fputc(currentNode->data, out);
                currentNode = root;
            }
        }
    }

    fclose(in);
    fclose(out);
    printf("File decompressed successfully.\n");
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s <c/d> <input_file> <output_file>\n", argv[0]);
        return 1;
    }

    int freq[256] = {0};
    unsigned char data[256];
    int freqList[256], size = 0;

    if (argv[1][0] == 'c' || argv[1][0] == 'x') {
        FILE *inFile = fopen(argv[2], "rb");
        if (!inFile) {
            perror("Could not open input file");
            return 1;
        }

        int ch;
        while ((ch = fgetc(inFile)) != EOF)
            freq[ch]++;

        fclose(inFile);

        for (int i = 0; i < 256; ++i) {
            if (freq[i]) {
                data[size] = i;
                freqList[size++] = freq[i];
            }
        }
		
        struct MinHeapNode* root = buildHuffmanTree(data, freqList, size);
        unsigned char codes[256][MAX_TREE_HT] = {{0}};
        int codeLength[256] = {0};
        unsigned char code[MAX_TREE_HT];
        generateCodes(root, code, 0, codes, codeLength);

        if (argv[1][0] == 'c') {
            compressFile(argv[2], argv[3]); 
        }
 
		else if (argv[1][0] == 'x') {
            unsigned char target;
            printf("Enter character for which you want the Huffman code: ");
            scanf(" %c", &target);  
            findHuffmanCode(codes, codeLength, target);
        }
    } 
	
	else if (argv[1][0] == 'd') {
        decompressFile(argv[2], argv[3]);
    } 
	
	else {
        printf("Invalid option. Use 'c' for compress, 'd' for decompress\n");
    }

    return 0;
}