# C++ Polytech

Repository for C++ practical course projects.

## Compilation
To compile the program type:
```bash
make -f makefile
```
## Testing
```bash
make tests1
./sqrt_tests.out

make tests2
./solve_tests.out
```
## Execution
Then to run it in interactive mode type:
```bash
./build.out
```
To feed in file with coefficients firstly create the file:
```bash
echo '4 5 9' > inputfile
```
Then type:
```bash
cat inputfile | ./build.out | tail -n 1 > outputfile
```
