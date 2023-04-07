# Quadratic equation solver

## Compilation
To compile the program type:
```bash
make -f makefile
```
* note: you need to satisfy all the dependencies from `requirements.txt`
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
echo '4,5,9' > inputfile
echo '-2,4,0.6' >> inputfile
# as many lines as you need
# or you can use given 'examples.txt'
```
Then type:
```bash
./build.out -f inputfile -o outputfile
```
For help type:
```bash
./build.out --help
```
