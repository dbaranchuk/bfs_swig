import numpy as np
import bfs
import time

def bfs_test(maxelements, MaxM, nq, margin, nt):
    initial_vertex_ids = np.array([0]*nq, dtype='int32')
    gts = np.array([99]*nq, dtype='int32')

    edges = -np.ones((maxelements, MaxM)).astype('int32')
    for i in range(maxelements):
        size = np.random.choice(MaxM, size=1)[0] + 1
        edges[i][:size] = np.random.choice(maxelements, size=size)
    distances = -np.ones((nq, maxelements)).astype('int32')

    t0 = time.time()
    bfs.bfs(edges, initial_vertex_ids, gts, distances, margin, nt)
    print('Time: %f' % (time.time() - t0))
    print(distances)


def bfs_visited_ids_test(maxelements, MaxM, nq, max_path_length, nt):
    # Generate random gts
    gts = np.random.choice(maxelements, size=nq).astype('int32')

    # Generate random graph
    edges = -np.ones((maxelements, MaxM)).astype('int32')
    for i in range(maxelements):
        size = np.random.choice(MaxM, size=1)[0] + 1
        edges[i][:size] = np.random.choice(maxelements, size=size)

    # Generate random visited ids
    visited_ids = -np.ones((nq, max_path_length)).astype('int32')
    for i in range(nq):
        path_length = np.random.choice(max_path_length, size=1)[0] + 1
        visited_ids[i][:path_length] = np.random.choice(maxelements, size=path_length)

    # Init distances
    distances = -np.ones((nq, max_path_length)).astype('int32')

    t0 = time.time()
    bfs.bfs_visited_ids(edges, gts, distances, visited_ids, nt)
    print('Time: %f' % (time.time() - t0))
    print(distances)


bfs_test(100, 5, 10000, 1, 1)
bfs_visited_ids_test(100, 5, 10000, 10, 1)