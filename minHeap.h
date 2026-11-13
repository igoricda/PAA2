#ifndef MINHEAP_H
#define MINHEAP_H

#include <utility>
#include <vector>

// Fila de prioridades mínima = heap binário clássico (Cormen cap. 6),
// montado sobre a biblioteca padrão: a construção e a extração do mínimo
// usam std::make_heap / std::pop_heap. A única parte escrita à mão é o
// DECREASE-KEY (a subida do elemento), que o std::priority_queue não
// oferece.
//
// O vetor pos_[v] guarda o índice atual do vértice v dentro do heap,
// o que permite localizar o elemento e aplicar o DECREASE-KEY em O(log V).
class MinPriorityQueue {
public:
    using Node = std::pair<int, int>;  // (distância, vértice)

    // BUILD-MIN-HEAP: insere todos os vértices 0..n-1 com as chaves dist.
    MinPriorityQueue(int n, const std::vector<int>& dist);

    // EXTRACT-MIN: remove e devolve o vértice de menor chave.
    Node ExtractMin();

    // DECREASE-KEY: reduz a chave de um vértice que está no heap.
    void DecreaseKey(int vertex, int key);

    bool Empty() const;
    int Size() const;

private:
    // Ordem total (dist, vértice): garante caminho único nas descidas
    // do heap, o que mantém pos_ correto após cada operação.
    struct GreaterKey {
        bool operator()(const Node& a, const Node& b) const
        {
            if (a.first != b.first) {
                return a.first > b.first;
            }
            return a.second > b.second;
        }
    };

    std::vector<Node> heap_;
    std::vector<int> pos_;
    std::vector<int> path_;
    GreaterKey greater_;
};

#endif
