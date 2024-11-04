#ifndef HEAPSORT_H
#define HEAPSORT_H

#include <vector>
#include "Product.h"

// Функция для создания max-heap
void heapify(std::vector<Product*>& products, int n, int i);

// Функция пирамидальной сортировки
void heapSort(std::vector<Product*>& products);

#endif // HEAPSORT_H
