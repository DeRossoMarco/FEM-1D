# FEM-1D

### About

Advanced Methods for Scientific Computing course project (professor Luca Formaggia)

Politecnico di Milano A.Y. 2022/2023 - Master degree in HPCE

---

### Student

Marco De Rosso

---

- ## Running instruction

    1. Create a directory `build` in the workspace.
    2. Execute the command `cmake ..` from inside the folder created.
    3. Execute the command `make`.
    4. Launch the simulation with `./FEM-1D`.

> **[OpenMP](https://www.openmp.org) is required** to launch the simulation with implemented parallel feature.

- ## Plotting solution

    1. Go to `script` directory.
    2. Launch the command `python3 plot.py`.
    3. The solution will be visualized in an interactive window and saved as `.pdf` in the `build` folder.

> To plot solution [numpy](https://numpy.org) and [matplotlib](https://matplotlib.org) Python packages are required.

- ## Simulation example

    The `main` class shows an exemple of how to use the implemented classes in order to solve a diffusion problem in 1D and in time through the Finite Element method.

- ## Mathematical problem

    The mathematical problem that the project intends to solve with a numerical approach is a parabolic partial differential equation in 1D with development over time.

    $\begin{cases} \frac{\delta}{\delta t}u-\frac{\delta}{\delta x}(\mu \frac{\delta}{\delta x}u)+cu=f \\ u(x,0)=u^0(x) \end{cases}$

    With $x\in(0,L)$ and $t\in(0,T)$. In general $\mu=\mu(x)$, $c=c(x)$ and $f=f(x,t)$. The boundary condition can be Dirichlet or Neumann type. Notice that at least one of the two must be Dirichlet in order to have a single solution to the problem.

    At $x=0$:

    $\begin{cases} u(0,t)=g_1(t) \\ or \\ -\mu\frac{\delta u}{\delta x}(0, t)=q_1(t) \end{cases}$

    At $x=L$:

    $\begin{cases} u(L,t)=g_2(t) \\ or \\ -\mu\frac{\delta u}{\delta x}(L, t)=q_2(t) \end{cases}$


- ## Class implemented
    
    ### FE space
    
    There are classes that manage the finite element space which are `mesh` and `base functions`. The second in particular has been implemented in order to return a functional that represents the base function of the Galerkin function space $X_h^1$ associated with a specific mesh element.

    ### Boundary

    These are two classes that allow you to define and apply the appropriate boundary conditions for the problem. One of the two conditions must be Dirichlet boundary condition, otherwise the problem has infinite solutions up to a constant and the solver is not able to solve the linear system.

   ### Functions

   In this package are implemented all the functions that define the problem and that are used in the composition of the linear system. Functions are wrappers for `std::function`. The `operator()` was overloaded in order to return the value of the function for a specific value of space or time, depending on function type. 

   ### Quadrature

   The quadrature class allows to calculate in an approximate way the integrals for the functions defined before and the base functions. The algorithm used for quadrature is the two-point Gauss-Legendre algorithm. You have to provide a `std::function<double(double)` and two extremes for quadrature to the static function of the class. The function returns the approximate value of the integral of the function in the given interval.

   ### FE

   Here all the classes useful for the Galerkin Finite Elements Method are defined, in addition a solver for tridiagonal systems with Thomas algorithm is implemented. There is also a class that allows you to use a tridiagonal matrix in a totally transparent way, allowing you to save a lot of memory space.

   ### Timing

   For the timing report, has been implemented a class that prints the results both on standard out and on file for speedup plot. The output file is saved in `build/` directory. The timing function of OpenMP was used to record the execution time.