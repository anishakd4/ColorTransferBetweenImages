Instructions to Run and test code

The cPlusPlusCode folder contains the cpp code and Cmakelists.txt file. The pythonCode folder contains the python code.

We will use Terminal for executing below commands

# How to run C++ code
### Change to cPlusPlusCode folder
cd cPlusPlusCode

### make build directory
mkdir build

### Change to the build folder
cd build

### Configure CMAKE
cmake ..

### BUILD project
cmake --build . --config Release

### come out of the build directory
cd ..

### Execute programs
./build/colorTransferBetweenImage


# How to run Python Code
### Change to the pythonCode folder
cd pythonCode

### Run the code
python3 colorTransferBetweenImage.py
