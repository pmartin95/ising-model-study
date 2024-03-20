# The Ising Model in N-Dimensions

This project is a C++ demo I want to do to study the Ising model.

## Build Instructions

First, run the setup script `setup.sh`.

```bash
./setup.sh
```

You may need to run the `chmod +x setup.sh` if you get an executable error. After you get that to work, `cd` in the `build` directory. Then type,

```bash
cmake ..
```

That will create the Makefile. Then build by typing `make`. The executable should be called `Ising2D`. This can be run from the command line, assuming you are still in the build directory, with,

```bash
./Ising2D
```
