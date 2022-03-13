# task_dispatcher
This code reads the tasks from a json file and dispatches the tasks by calling the corresponding object function.


## Installation

Clone the repository with the following command:
```
git clone https://github.com/mkaihara/task_dispatcher.git
```
Once the respository is cloned, go the folder and type the following commands
```
cd task_dispatcher
mkdir build
cd build
cmake ..
make
```
Then you can run the json example file that is located in the main folder by typing 
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

## Format of the input json file
The current implementation recognizes the following tasks:
```
ADD -> addition of 2 numbers
SUB -> subtraction of 2 numbers
MUL -> multiplication of 2 numbers
DIV -> division of 2 numbers
```
The json file should follow the following format:
```
{
  "tasks": [
    {
      "type": "ADD",
      "num1": 12,
      "num2": 9
    },
    {
      "type": "SUB",
      "num1": 30,
      "num2": 8
    },
    {
      "type": "MUL",
      "num1": 3,
      "num2": 6
    },
    {
      "type": "DIV",
      "num1": 15,
      "num2": 3
    }
  ]
}
```
## Tested environment
```
gcc version 10.3.0
cmake version 3.16.3
#40~20.04.1-Ubuntu SMP Mon Mar 7 09:18:32 UTC 2022
```
