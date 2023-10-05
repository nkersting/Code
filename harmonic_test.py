#!/usr/bin/python

from functools import partial
from ndim_vecs import *
import matplotlib.pyplot as plt



def harmonic_2D(x):
    return x[0]*x[0] - x[1]*x[1]

def anharmonic_2D(x):
    return x[0]*x[0] + x[1]*x[1]

def harmonic_ND(n, x):
    sum = 0
    for i in range(n):
        sum += x[i]*x[i]*(-1)**(i)
    return sum

def anharmonic_ND(n, x):
    sum = 0
    for i in range(n):
        sum += x[i]*x[i]
    return sum

def harmonic2_ND(n, x):
    prod = 1
    for i in range(n):
        if i%2 == 0:
            prod *= np.sin(x[i])
        else:
            prod *= np.exp(x[i])
    return prod

def anharmonic2_ND(n, x):
    prod = 1
    for i in range(n):
        if i%2 == 0:
            prod *= 1
        else:
            prod *= np.exp(x[i])
    return prod


def random_aharmoniticity(fn, num_trials, num_random, mag, n):
    
    avg_aharmoniticity = 0
    for _ in range(num_trials):
        random_point = random_vecs(1, mag, n)[0]
        r_vecs = random_vecs(num_random, 1, n)
        aharmoniticity = 0
        for r in r_vecs:
            aharmoniticity += fn(r + random_point)
        aharmoniticity /= num_random
        aharmoniticity -= fn(random_point)
        avg_aharmoniticity += abs(aharmoniticity)
    avg_aharmoniticity /= num_trials 
    return avg_aharmoniticity

def simplex_aharmoniticity(fn, num_trials, mag, n, r_vecs):
    avg_aharmoniticity = 0
    for _ in range(num_trials):
        random_point = random_vecs(1, mag, n)[0]
        aharmoniticity = 0
        for r in r_vecs:
            aharmoniticity += fn(r + random_point)
        aharmoniticity /= len(r_vecs)
        aharmoniticity -= fn(random_point)
        avg_aharmoniticity += abs(aharmoniticity)
    avg_aharmoniticity /= num_trials
    return avg_aharmoniticity

def main():

    
    num_tests = 10
    mag = 1
    num_trials = 1000
 

    r_harms = []
    r_aharms = []
    s_harms = []
    s_aharms = []
    s_n_harms = []
    s_n_aharms = []
    r_n_harms = []
    r_n_aharms = []
    nvals = [2,4,8, 16, 32, 64, 128]
    for n in nvals:
        print(f"Dimension {n} Results:")
        
        harmonic_f = partial(harmonic2_ND, n)
        anharmonic_f = partial(anharmonic2_ND, n)
        num_random = 2*n
        super_vecs = normalized(rotate_away_last_dim(center_origin(find_orig_coords(n+1))))
        r_vecs = [s[:-1] for s in super_vecs] # drop the auxiliary last coordinate
        r_vecs = r_vecs + [-x for x in r_vecs] # add the anti-simplex
        
        for i in range(num_tests):
            r_harms.append(random_aharmoniticity(harmonic_f, num_trials, num_random, mag, n))
            r_aharms.append(random_aharmoniticity(anharmonic_f, num_trials, num_random, mag, n))
            s_harms.append(simplex_aharmoniticity(harmonic_f, num_trials, mag, n, r_vecs))
            s_aharms.append(simplex_aharmoniticity(anharmonic_f, num_trials, mag, n, r_vecs))

        print("MEAN RANDOM  HARM: ", np.mean(r_harms), np.std(r_harms)/np.sqrt(num_tests))
        print("MEAN SIMPLEX HARM: ", np.mean(s_harms), np.std(s_harms)/np.sqrt(num_tests))    
        print("MEAN RANDOM  AHARM: ", np.mean(r_aharms), np.std(r_aharms)/np.sqrt(num_tests))
        print("MEAN SIMPLEX AHARM: ", np.mean(s_aharms), np.std(s_aharms)/np.sqrt(num_tests))

        s_n_aharms.append(np.mean(s_aharms))
        s_n_harms.append(np.mean(s_harms))
        r_n_aharms.append(np.mean(r_aharms))
        r_n_harms.append(np.mean(r_harms))


    """
    s_n_harms =[0,0,0,0,0,0,0]
    r_n_harms = [8.17, 6.11, 4.74, 3.81, 3.14, 2.67, 2.3]
    #s_n_harms =[.127, .085, .057, .043, .034, .029, .024]
    #r_n_harms = [.611, .413, .281, .211, .169, .141, .120]
    nvals = [2,4,8, 16, 32, 64, 128]
    fig = plt.figure()
    ax1 = fig.add_subplot(111)
    plt.title("Random vs. Simplex Harmoniticity \n Harmonic f = x^2 - y^2 + z^2 - ...")
    #plt.title("Random vs. Simplex Harmoniticity \n Harmonic f = sin(x)exp(y)sin(z)...")
    plt.xlabel("dimension")
    plt.ylabel("Harmoniticity")
    plt.plot(nvals, s_n_harms, color='blue', label="simplex", marker='o')
    plt.plot(nvals, r_n_harms, color='red', label="random", marker='o')
    #plt.text(7,8,"f = x^2 - y^2 + z^2 - ...")
    plt.savefig('harmonics_polynomial.eps', format='eps')
    #plt.savefig('harmonics_exp.eps', format='eps')
    plt.legend()
    plt.show()
    

    

    s_n_aharms =[1,1,1,1,1,1,1]
    r_n_aharms = [8.17, 6.14, 4.81, 3.93, 3.35, 2.96, 2.67]
#    s_n_aharms =[.375, .358, .340, .325, .311, .299, .287]
#    r_n_aharms = [.655, .581, .532, .497, .471, .454, .440]
    nvals = [2,4,8, 16, 32, 64, 128]
    fig = plt.figure()
    ax1 = fig.add_subplot(111)
    #plt.title("Random vs. Simplex Harmoniticity \n NON-harmonic f = exp(x+y+z+...)")
    plt.title("Random vs. Simplex Harmoniticity \n NON-harmonic f = x^2 + y^2 + z^2 + ...")
    plt.xlabel("dimension")
    plt.ylabel("Harmoniticity")
    plt.plot(nvals, s_n_aharms, color='blue', label="simplex", marker='o')
    plt.plot(nvals, r_n_aharms, color='red', label="random", marker='o')
    #plt.text(20,.6,"f = exp(x+y+z+...)")
    #plt.savefig('anharmonics_exp.eps', format='eps')
    plt.savefig('anharmonics_polynomial.eps', format='eps')
    plt.legend()
    plt.show()

    """


if __name__ == "__main__":
    main()
