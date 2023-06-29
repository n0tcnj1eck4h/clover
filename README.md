# clover
Clover is a simple tree-walk interpreter of an arbitrary scripting language.

## Features
### Basic arithmetic and string operations
```
> print "2 + 2 squared is equal to: " + (2 + 2)**2;
2 + 2 squared is equal to: 16
```

### Variables
```
> set foo = "bar";
> print foo;
bar
```

### Control flow
```
> set i = 3; while i > 0 { print i; set i = i - 1; }; \
  if i == 0 { print "The countdown has finished"; } else { crash; }
3
2
1
The countdown has finished
```
# Example
Print the first 20 numbers in the Fibonacci sequence
```
set x = 1;
set y = 1;

print x;
set i = 0;
while i < 20 {
  print y;
  set t = y;
  set y = x + y;
  set x = t;
  set i = i + 1;
}
```

# Usage
The program can be compiled using GNU Make. After it's compiled you can run it without any arguments to enter it's REPL or pass a filename of a script you would like to run.
```
$ ./interpreter fib.txt
```
