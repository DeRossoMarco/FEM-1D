# Some Notes #
- Code compiles and runs without issues, readme is well done
- A do not understand the need of `CFunction`. Yet, why not make it as a functor, i.e. defining a call operator?
This way, it would behave as a function.
- The same for `DiffusionCoefficient`. There is no need to extend to zero outside the interval [0,L],
in a finite element code you will only call the function for values of x inside the domain!. So the case x outside
the domain can be excluded. In your code you call an if statement all the times you need to call the forcing function or 
the  coefficient. This is inefficient, since an if statement is costly (mush more than an arithmetic operation).
- You do not really need two different class for Dirichlet and Neumann, since the type of data needed in the two cases
is the same. A simpler technique is tho create a class `BoundaryCOndition` that stores for instance un enumerator, that
provides the way to distinguish how to use the member data. Alternatively, you couls have used olimorphism, inheriting from
an abstract base class. Your choice is less flexible.
- Code

````
  #pragma omp parallel for
  for (std::size_t k = 0; k < N; ++k) {
  #pragma omp atomic
            matrix(k, k) += compute_local_contribute(mesh, c, mi, k, k, k);

            matrix(k, k + 1) += compute_local_contribute(mesh, c, mi, k, k + 1, k);

            matrix(k + 1, k) += compute_local_contribute(mesh, c, mi, k + 1, k, k);

  #pragma omp atomic
            matrix(k + 1, k + 1) += compute_local_contribute(mesh, c, mi, k + 1, k + 1, k);
        }

````
is wrong. Firt of all, I do not know whether such a complex expression can be made really atomic. But 
here you are not guaranteed that two different threads enter the two atomic regions. You need an named critical section here.
````
  #pragma omp parallel for
  for (std::size_t k = 0; k < N; ++k) {
  #pragma omp critical one
             matrix(k, k) += compute_local_contribute(mesh, c, mi, k, k, k);

            matrix(k, k + 1) += compute_local_contribute(mesh, c, mi, k, k + 1, k);

            matrix(k + 1, k) += compute_local_contribute(mesh, c, mi, k + 1, k, k);

  #pragma omp critical one
            matrix(k + 1, k + 1) += compute_local_contribute(mesh, c, mi, k + 1, k + 1, k);
        }

````
- `BaseFunc` is a class with only public static member functions. Effectively, 
 is then nothing more than a namespace. You could have just used functions, no need of a class.
- Setting the dimention of the probelm as a template value allows to have fixed side matrices, thus 
some efficiency gain. But at the price of a very rigid code. You cannot define the size of the probelm rutime,
- by reading it from a file, for instance.
- You have assumed uniform mesh in your mesh class. In general, mesh can be non uniform.
- In `[&, mesh, i] (double x) -> double { ... }` you are capturing everything by reference except `mesh` and `i` by copy. You should capture everything by reference.


# Minor Stuff #
- You should comment more the code, in particular give a briaf descriotion of the classes/methods/function, parameters etc.
- `Mesh::operator[]` does not have a clear meaning, `operator`s should be implemented only when it is clear what they mean
- You are outputting too much data with `std::setprecision(20)` for doubles, they do not have more than 17 significant digits. In general you should use `std::setprecision(std::numeric_limits<decltype(value)>::max_digits10)` to serialize/deserialize a variable `value`
- The following code is clear but does not scale well since you are creating many temporary objects. Since you are employing a uniform mesh you could at least locally save some variables to avoid recomputing them.
```cpp
Quadrature::two_point_quadrature(
                    [&] (double x) -> double {
                        return
                            mi.value(x) * 
                            BaseFunc::d_func(mesh, i)(x) *
                            BaseFunc::d_func(mesh, j)(x);
                    },
                    mesh[k],
                    mesh[k + 1]
                )
```
