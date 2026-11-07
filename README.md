# Grafos — Dijkstra × Bellman-Ford (Grupo 6)

Implementação em C++17 no modelo clássico do Cormen (cap. 24),
com `min-heap` binário no Dijkstra e teste de ciclo negativo no
Bellman-Ford. Origem única `s = 0` para todos os grafos.

## Estrutura (espelho do trabalho LCS)

| Arquivo | Papel |
| --- | --- |
| `graph.h/.cpp` | `Graph` (matriz + lista de adjacência + lista de arcos) e `BuildGraph` |
| `fileUtils.h/.cpp` | Leitura do formato de entrada (`N` + matriz `N×N`) |
| `minHeap.h/.cpp` | Min-heap clássico (BUILD-MIN-HEAP, EXTRACT-MIN, DECREASE-KEY) |
| `shortestPaths.h/.cpp` | INITIALIZE-SINGLE-SOURCE, RELAX, DIJKSTRA, BELLMAN-FORD, PRINT-PATH |
| `dijkstra.cpp` | Programa individual (vide `pdlcs.cpp` no LCS) |
| `bellmanFord.cpp` | Programa individual (vide `reclcs.cpp` no LCS) |
| `main.cpp` | Benchmark no formato LCS (6 reps, média das últimas 5) |
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

- Benchmark no formato do LCS: `PrepareCsvOutput`/`LastSize` com
  retomada por último tamanho, leitura fora da seção cronometrada,
  6 execuções com a primeira descartada (média das 5 últimas).
- Em empates de menor caminho, os vetores `pred` (e, portanto, os
  caminhos impressos) podem diferir entre os algoritmos; o critério
  de validação é a igualdade das distâncias (seção 6.2).
- O Bellman-Ford executa exatamente `|V|−1` rodadas (sem early-exit)
  para preservar o custo clássico `O(V·E)`.
