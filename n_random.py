#!/usr/bin/python

import numpy as np
import itertools
import random

def find_orig_coords(n):
    coords = []
    for i in range(n):
        curr_point = [0]*n
        curr_point[i] = 1
        coords.append(np.array(curr_point))
    return coords

def center_origin(coords):
    n = len(coords)
    for i in range(n):
        coords[i] = [coords[i][j] - [x/n for x in [1]*n][j] for j in range(n)]
    return coords

def crossproduct(x,y):
    n = len(n)
    epsilon = levi_cevita_tensor(n)
    cross_prod = [0]*n
    for i in range(n):
        for j in range(n):
            for k in range(n):
                cross_prod[i] += epsilon[i][j][k]*x[j]*y[k]
    return cross_prod
                
def rotate_away_last_dim(orig):
    rotated = []
    n = len(orig)

    # first find the normal to the plane in these coordinates
    #normal_vec = [1/np.sqrt(n)] * n

    # component of normal perpendicular to z
    #n_perp = [1/np.sqrt(n-1)] * n
    #n_perp[-1] = 0

    cos_theta = 1/np.sqrt(n)

    m1 = np.zeros((n,n))
    for i in range(n):
        m1[i][n-1] = 1
        m1[n-1][i] = -1
    m1[n-1][n-1] = 0
    #print("M1:", m1)

    m2 = np.ones((n,n))
    for i in range(n):
        m2[i][n-1] = 0
        m2[n-1][i] = 0
    m2[n-1][n-1] = n-1
    #print("M2:", m2)
    
    rotation = np.identity(n) - 1/np.sqrt(n) * m1 + (cos_theta - 1)/(n-1) * m2

    rotated = []
    for v in orig:
        rotated.append(np.matmul(rotation,v))

    return rotated
    
def normalized(vecs):
    return [normalize(v) for v in vecs]

def normalize(v):
    norm = np.linalg.norm(v)
    if norm == 0: 
       return v
    return v / norm
        

        

def levi_cevita_tensor(dim):   
    arr=np.zeros(tuple([dim for _ in range(dim)]))
    for x in itertools.permutations(tuple(range(dim))):
        mat = np.zeros((dim, dim), dtype=np.int32)
        for i, j in zip(range(dim), x):
            mat[i, j] = 1
        arr[x]=int(np.linalg.det(mat))
    return arr

def sum_check(vecs):
    sum = 0
    for v in vecs:
        sum += v
    return np.sqrt(np.dot(sum,sum))

def angles_check(vecs):
    angles = []
    n = len(vecs)
    for i in range(n):
        for j in range(i+1, n):
            angles.append(abs(np.dot(vecs[i], vecs[j])))
    return np.mean(angles), np.std(angles)
    
def main():
    n = 6
    coords = find_orig_coords(n)
    origin_centered = center_origin(coords)
    #print("CENTERED:", origin_centered)
    rotated = rotate_away_last_dim(origin_centered)
    #print("ROTATED:", rotated)
    final = normalized(rotated)
    print("FINAL SIMPLEX POINTS:", final)
    print("SIMPLEX SUM CHECK:", sum_check(final))
    print("SIMPLEX ANGLE CHECK:", angles_check(final))

    num_points = 100*n
    random_vecs = []
    for _ in range(num_points):
        rawvec = normalize(np.random.rand(n))
        for i in range(n):
            if random.random() >= 0.5:
                rawvec[i] = -rawvec[i]
        random_vecs.append(rawvec)


    #print("RANDOM VECS:", random_vecs)
    print("RANDOM SUM CHECK:", sum_check(random_vecs))
    print("RANDOM ANGLE CHECK:", angles_check(random_vecs))

    


     
if __name__ == '__main__':
    main()
