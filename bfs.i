%module bfs

%{
    #define SWIG_FILE_WITH_INIT
    #include "bfs.h"
%}

%include "numpy.i"
%include "typemaps.i"

%init %{
    import_array();
%}

%apply (int DIM1, int DIM2, long* IN_ARRAY2) {(int maxelements, int MaxM, long *edges)}
%apply (int DIM1, long* IN_ARRAY1) {(int k, long *initial_vertex_ids),
                                    (int m, long *gts),
                                    (int l, long *margin),
                                    (int t, long *nt)}
%apply (int DIM1, int DIM2, long* INPLACE_ARRAY2) {(int d1,  int d2, long *distances)}
%apply int *INPUT {int *margin, int *nt}

%include "bfs.h"
