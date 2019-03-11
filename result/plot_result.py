import numpy as np
import matplotlib.pyplot as plt



def plot_fig(x, y, x_c, x_label, y_label, out_file, exact=None):
    plt.figure()
    plt.plot(x, y, '.', color='b')
    plt.axvline(x=x_c, color='r', linestyle='--')

    if exact is not None:
        plt.plot(x, exact, color='lime')

    plt.xlabel(x_label, fontsize=16)
    plt.ylabel(y_label, fontsize=16)
    plt.xticks(fontsize=12)
    plt.yticks(fontsize=12)
    plt.grid(True)
    plt.savefig(out_file, bbox_inches='tight')
    plt.close()



if __name__ == '__main__':
   
    # Load the data
    file_path = 'data.txt'
    data = np.loadtxt(file_path, delimiter=',')

    n = data.shape[0]
    print("Number of data = ", n)
    T = np.zeros(n)
    E = np.zeros(n)
    M = np.zeros(n)
    C = np.zeros(n)
    X = np.zeros(n)
    for i in range(n):
        T[i] = data[i][0]
        E[i] = data[i][2]
        M[i] = data[i][3]
        C[i] = data[i][4]
        X[i] = data[i][5]


    # Critical temperature
    Tc = 2/np.log(1+np.sqrt(2))

    x_label = r'$k_{B}T \; / \; J$'
    x_label = r'$T$'

    
    # Plot energy per spin against temperature
    plot_fig(T, E, Tc, x_label, r'$E \; / \; N$', 'Ene_vs_T.png')

    # Plot absolute magnetization per spin against temperature
    plot_fig(T, np.abs(M), Tc, x_label, r'$|M| \; / \; N$', 'Mag_vs_T.png')
 
    # Plot heat capacity per spin against temperature
    plot_fig(T, C, Tc, x_label, r'$C \; / \; N$', 'Cap_vs_T.png')

    # Plot magnetic susceptibility per spin against temperature
    plot_fig(T, X, Tc, x_label, r'$\chi \; / \; N$', 'Sus_vs_T.png')

