# №2 Task: Stack
## Built and Run:
Built from repository folder: `./Stack/built_Stack`  
Run from repository folder: `./Stack`  
All **dumps** will be write in is `dump.txt`  
## Implementation:
Additional for base functionality of stack realised next:  
* Support stacks of different types
* Verefying of correctness on input stack before every changes in them
* Usind canary protection and checking data hash for interupt external influence
* Using data dumping in every function
### Data types:  
For set type of steck use `#define STACK_TYPE`  
Supported types:
* STACK_INT as int
* STACK_CHAR as char
* STACK_DOUBLE as double
* STACK_PTR as char_ptr
### Supported flags:
* `#define STACK_DEBUG` define as 1 for unable stack safe his creation data (name, file and line)
* `#define STACK_BIRDIE` define as 1 for unable canary protection
* `#define STACK_HASH` define as 1 for unable hashing protection  
### Hashing:  
To verify the correctness of the stack, the following is used djb2 hashing of data and stack struct
## Output:
