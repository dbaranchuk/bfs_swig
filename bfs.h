#include <vector>
#include <cstdio>
#include <queue>
#include <iostream>
#include <assert.h>
#include <omp.h>

typedef unsigned idx_t;

struct Vertex{
    idx_t vertex_id;
    std::vector<idx_t> prev_vertex_ids;

    bool is_visited = false;
    size_t min_path_length = 0;
};

void bfs(int maxelements, int MaxM, long *edges,  // matrix [maxelements, MaxM]
         int k, long *initial_vertex_ids,         // vector [n_queries]
         int m, long *gts,                        // vector [n_queries]
         int d1, int d2, long *distances,         // matrix [n_queries, maxelements]
         int *margin,                             // number
         int *nt);                                // number