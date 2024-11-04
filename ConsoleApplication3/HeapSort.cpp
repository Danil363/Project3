#include "HeapSort.h"

void heapify(std::vector<Product*>& products, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && products[left]->getPrice() > products[largest]->getPrice())
        largest = left;

    if (right < n && products[right]->getPrice() > products[largest]->getPrice())
        largest = right;

    if (largest != i) {
        std::swap(products[i], products[largest]);
        heapify(products, n, largest);
    }
}

void heapSort(std::vector<Product*>& products) {
    int n = products.size();

    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(products, n, i);

    for (int i = n - 1; i > 0; i--) {
        std::swap(products[0], products[i]);
        heapify(products, i, 0);
    }
}
