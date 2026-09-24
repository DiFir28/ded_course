# Repository for Dedinskii course in MIPT

For build curent developing file : `./build`
For start curent developing file with default params: `./main`
## Implemented functionas
 * Buble sort (for any types)
 * Quick sort (for any types)
 * Dinamic array
 * Hashing
 * Handler for read and write file
## №1 Task: Onegin
### Built and Run:
Built: `./built_Onegin`  
Run: `./Onegin bookName.txt`  
If bookName doesn't set in cli argument, default bookName is *Onegin.txt*  
$${\color{red} File \space must \space contain \space only \space ASCII \space symbols}$$  
### Realisation:
File sort with 2 ways for compare speed.
1) Sorting array of pointer on begining of lines using character‑by‑character search.
2) Sorting array of struct usign copare with hashing line.
#### Hashing:
After read text from file, code create array with struct, that contain pointer to begin of line and hash,  for every line of text with more tah 1 alphabet letter.  
Hash allow compare 8 byte of hash (more than 12 letters) at once and allso clean line from useless for comparing symbols like: .,"'().
Hash is bit order, that every 5 bit is a symbol.  
Hash rule: Hash code = (ASCII code of upped case letter) - 64  
a ~ A ~ ASCII 65 ~ HASH 00001 (1)  
b ~ B ~ ASCII 66 ~ HASH 00010 (2)  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;•••  
z ~ Z ~ ASCII 90 ~ HASH 11010 (26)  
### Output:
Sorted text writed in 2 file by sorted ways:
1) `OutputLine.txt`
2) `OutputHash.txt`  
Files struct:
```
Sorted lines from begin to end
////////////////
Sorted lines from end to begin
////////////////
Original text
```
