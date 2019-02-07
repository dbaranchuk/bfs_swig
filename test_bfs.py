import numpy as np
import bfs

def bfs_test(maxelements, MaxM, nq, margin, nt):
    initial_vertex_ids = np.array([0]*nq)
    gts = np.array([99]*nq)

    edges = -np.ones((maxelements, MaxM)).astype('int32')
    for i in range(maxelements):
        size = np.random.choice(MaxM, size=1)[0] + 1
        edges[i][:size] = np.random.choice(maxelements, size=size)

    distances = -np.ones((nq, maxelements)).astype('int64')
    bfs.bfs(edges, initial_vertex_ids, gts, distances, margin, nt)
    print(distances)

bfs_test(100, 5, 1000000, 1, 4)