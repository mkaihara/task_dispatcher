# task_dispatcher
This code reads the tasks from a json file and dispatches the tasks by calling the corresponding object function.


## Installation

Once the respository is cloned locally, go the folder and type the following commands
```
mkdir build
cd build
cmake ..
make
```
Then you can run with the example json file that is located in the main folder by typing 
```
./task_dispatcher ../tasks.json
```
The output should be:
```
21 
22 
18 
5 
```
