#include "bfs.h"

/*
* BFS for optimal paths construction
*/

void bfs(int maxelements, int MaxM, long *edges,  // matrix [maxelements, MaxM]
         int k, long *initial_vertex_ids,         // vector [n_queries]
         int m, long *gts,                        // vector [n_queries]
         int d1, int d2, long *distances,         // matrix [n_queries, maxelements]
         int *margin,                             // number
         int *nt)                                 // number
{
    assert(k == m == d1);
    assert(maxelements == d2);
    assert(*nt > 0 && *margin >= 0);

    #pragma omp parallel for num_threads(*nt)
    for (int q = 0; q < k; q++){
        size_t min_path_length = maxelements;
        size_t current_depth = 0;
        idx_t initial_vertex_id = *(initial_vertex_ids+q), gt = *(gts+q);

        std::vector <Vertex> forward_vertices(maxelements);
        std::queue <std::pair<size_t, idx_t>> forward_queue;

        forward_queue.push({current_depth, initial_vertex_id});
        forward_vertices[initial_vertex_id].vertex_id = initial_vertex_id;
        forward_vertices[initial_vertex_id].is_visited = true;

        size_t forward_counter = 0;
        // Forward pass
        while (!forward_queue.empty()) {
            current_depth = forward_queue.front().first;
            Vertex *vertex = forward_vertices.data() + forward_queue.front().second;
            forward_queue.pop();

            if (vertex->vertex_id == gt)
                min_path_length = vertex->min_path_length;

            if (current_depth == min_path_length + *margin)
                break;

            long *data = edges + vertex->vertex_id * MaxM;
            for (int i = 0; i < MaxM; i++) {
                if (*(data + i) == -1)
                    break;

                idx_t next_vertex_id = *(data + i);
                if (next_vertex_id != gt &&
                    (vertex->min_path_length + 1) == min_path_length + *margin)
                    continue;

                Vertex *next_vertex = forward_vertices.data() + next_vertex_id;
                next_vertex->prev_vertex_ids.push_back(vertex->vertex_id);

                if (next_vertex->is_visited)
                    continue;

                next_vertex->vertex_id = next_vertex_id;
                next_vertex->is_visited = true;
                next_vertex->min_path_length = vertex->min_path_length + 1;
                forward_queue.push({current_depth + 1, next_vertex_id});
                forward_counter++;
            }
        }

        // Backward pass
        current_depth = 0;
        min_path_length = maxelements;
        std::queue <std::pair<size_t, idx_t>> backward_queue;
        std::vector <Vertex> backward_vertices(maxelements);
        backward_vertices[gt].vertex_id = gt;
        backward_vertices[gt].is_visited = true;

        backward_queue.push({current_depth, gt});

        size_t backward_counter = 0;
        while (!backward_queue.empty()) {
            current_depth = backward_queue.front().first;
            Vertex *vertex = backward_vertices.data() + backward_queue.front().second;
            backward_queue.pop();

            // check if is enterpoint
            if (vertex->vertex_id == initial_vertex_id)
                min_path_length = vertex->min_path_length;

            if (current_depth == min_path_length + *margin)
                break;

            for (idx_t prev_vertex_id : forward_vertices[vertex->vertex_id].prev_vertex_ids) {
                if (prev_vertex_id != initial_vertex_id &&
                    (vertex->min_path_length + 1) == min_path_length + *margin)
                    continue;

                Vertex *backward_vertex = backward_vertices.data() + prev_vertex_id;
                if (backward_vertex->is_visited)
                    continue;

                backward_vertex->vertex_id = prev_vertex_id;
                backward_vertex->is_visited = true;
                backward_vertex->min_path_length = vertex->min_path_length + 1;
                backward_queue.push({current_depth + 1, prev_vertex_id});
                backward_counter++;
            }
        }
        for (int i = 0; i < maxelements; i++) {
            if (!backward_vertices[i].is_visited || !forward_vertices[i].is_visited)
                continue;
            if (backward_vertices[i].min_path_length +
                forward_vertices[i].min_path_length > min_path_length + *margin)
                continue;
            distances[q*maxelements + i] = backward_vertices[i].min_path_length;
        }
    }
}