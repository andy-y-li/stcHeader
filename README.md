## Transfer STC head file to SDCC

Transfer STC (Keil) head file to SDCC.



### Installation

```
$ ./configure

$ make

$ make install
```



### Usage

```
stcHeader [-h] [ -s source_header] [ -d dest_header] 
-h			: this help
-s			: source header
-d			: dest header(default: stdout)

e.g
$ stcHeader -s stc8.h -d sdcc_stc8.h
```

