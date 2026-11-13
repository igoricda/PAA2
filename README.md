# Grafos — Dijkstra × Bellman-Ford (Grupo 6)

Implementação em C++17 no modelo clássico do Cormen (cap. 24),
com `min-heap` binário no Dijkstra: a fila de prioridades usa os
algoritmos de heap da biblioteca padrão (`std::make_heap`,
`std::pop_heap`) e implementa apenas o `DECREASE-KEY` (subida do
elemento) sobre um mapa de posições. Ciclo negativo testado no
Bellman-Ford. Origem única `s = 0` para todos os grafos.

## Estrutura

| Arquivo | Papel |
| --- | --- |
| `graph.h/.cpp` | `Graph` (matriz + lista de adjacência + lista de arcos) e `BuildGraph` |
| `fileUtils.h/.cpp` | Leitura do formato de entrada (`N` + matriz `N×N`) |
| `minHeap.h/.cpp` | Fila de prioridades mínima = heap binário (BUILD-MIN-HEAP, EXTRACT-MIN, DECREASE-KEY) |
| `shortestPaths.h/.cpp` | INITIALIZE-SINGLE-SOURCE, RELAX, DIJKSTRA, BELLMAN-FORD, PRINT-PATH |
| `dijkstra.cpp` | Programa individual (teste de um arquivo) |
| `bellmanFord.cpp` | Programa individual (teste de um arquivo) |
| `main.cpp` | Benchmark (6 reps, média das últimas 5) |
| `gerar_graficos.py` | Gera os PNGs a partir dos CSVs |
| `resultadosDijkstra_grafos.csv` | Médias do Dijkstra (`n;tempo`) |
| `resultadosBellmanFord_grafos.csv` | Médias do Bellman-Ford (`n;tempo`) |
| `images/` | Variantes linear/log (linhas e barras) para escolha |
| `input/` | Entradas extraídas do rar (`Entrada 10.txt` … `Entrada 1500.txt`) |
| `Makefile` | `make all` → `main dijkstra bellmanFord` |

## Compilar e executar

```sh
make
./dijkstra                  # ./input/Entrada 10.txt
./bellmanFord
./dijkstra "./input/Entrada 100.txt"
rm -f resultados*.csv && ./main   # benchmark: 6 reps/tamanho, média das 5 últimas
python3 gerar_graficos.py         # gera images/*.png (linear + log)
```

## Entradas

Matriz de adjacência ponderada, não direcionada: primeiro inteiro `N`,
seguido de `N×N` inteiros separados por espaço. `0` indica ausência de
aresta; demais valores são pesos não negativos (máx = N−1). Todas as
matrizes são simétricas, com diagonal nula e conexas a partir de 0.

Tamanhos: 10, 25, 50, 75, 100, 150, 200, 250, 300, 400, 500, 650,
800, 1000, 1500.

## Notas

- Em empates de menor caminho, os vetores `pred` (e, portanto, os
  caminhos impressos) podem diferir entre os algoritmos; o critério
  de validação é a igualdade das distâncias (seção 6.2).
- O Bellman-Ford executa exatamente `|V|−1` rodadas (sem early-exit)
  para preservar o custo clássico `O(V·E)`.
- `std::priority_queue` não expõe `DECREASE-KEY` (nem acesso aos
  elementos internos). Para manter o heap binário clássico e o
  `DECREASE-KEY` real, `MinPriorityQueue` (em `minHeap.h/.cpp`) usa
  `std::make_heap`/`std::pop_heap` para a construção e a extração do
  mínimo e escreve à mão apenas a subida do `DECREASE-KEY`, com um vetor
  `pos_` que localiza o vértice no heap em `O(1)`. Todas as operações
  ficam em `O(log V)` (build em `O(V)`), com uma única entrada por
  vértice (sem duplicatas).
