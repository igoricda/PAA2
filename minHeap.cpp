#include "minHeap.h"

#include <algorithm>

MinPriorityQueue::MinPriorityQueue(int n, const std::vector<int>& dist)
{
    heap_.reserve(n);

    for (int v = 0; v < n; ++v) {
        heap_.push_back({dist[v], v});
    }

    // BUILD-MIN-HEAP da stdlib (O(n)).
    std::make_heap(heap_.begin(), heap_.end(), greater_);

    // O make_heap reordena o vetor: o mapa de posições é montado depois.
    pos_.assign(n, -1);
    for (int i = 0; i < n; ++i) {
        pos_[heap_[i].second] = i;
    }
}

MinPriorityQueue::Node MinPriorityQueue::ExtractMin()
{
    // O mínimo é a raiz do heap.
    Node top = heap_.front();

    // Antes do pop_heap, guarda o caminho que a descida vai percorrer:
    // sempre pelo filho de menor chave, já no heap sem a raiz (tamanho
    // heap_.size() - 1). Só os nós desse caminho trocam de posição.
    path_.clear();

    int sizeAfter = static_cast<int>(heap_.size()) - 1;
    int i = 0;

    for (;;) {
        path_.push_back(i);

        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left >= sizeAfter) {
            break;
        }

        int smallest = left;
        if (right < sizeAfter && greater_(heap_[left], heap_[right])) {
            smallest = right;
        }

        i = smallest;
    }

    // std::pop_heap move a raiz para o fim e refaz o heap em O(log n).
    std::pop_heap(heap_.begin(), heap_.end(), greater_);
    heap_.pop_back();

    pos_[top.second] = -1;

    // Atualiza pos_ apenas para os nós que ficaram no caminho.
    int newSize = static_cast<int>(heap_.size());
    for (int idx : path_) {
        if (idx < newSize) {
            pos_[heap_[idx].second] = idx;
        }
    }

    return top;
}

void MinPriorityQueue::DecreaseKey(int vertex, int key)
{
    int i = pos_[vertex];

    if (i < 0) {
        return;  // vértice já extraído do heap
    }

    // Atualiza a chave e sobe o elemento (sift-up), trocando com o pai
    // enquanto o pai for maior na ordem do heap. O(log n).
    heap_[i].first = key;

    while (i > 0) {
        int parent = (i - 1) / 2;

        if (!greater_(heap_[parent], heap_[i])) {
            break;
        }

        std::swap(heap_[i], heap_[parent]);
        pos_[heap_[i].second] = i;
        pos_[heap_[parent].second] = parent;
        i = parent;
    }
}

bool MinPriorityQueue::Empty() const
{
    return heap_.empty();
}

int MinPriorityQueue::Size() const
{
    return static_cast<int>(heap_.size());
}
