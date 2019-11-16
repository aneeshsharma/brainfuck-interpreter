# brainfuck-interpreter
An interpreter for the freakin' brainfuck langauge implemented in C (for performance reasons).

## How to install?

Clone the repo to your local repo -

```
git clone https://github.com/aneeshsharma/brainfuck-interpreter.git
```

Now navigate to the directory and install

```
cd brainfuck-interpreter
make install
```

`brainfuck` is now insalled! It's as simple as that.

Now execute any program by executing the command as -

```
brainfuck <program-name> [mem_size]
```

Where, `<porgram-name>` - the program to execute
`[mem_size]` - the memory to allocate to the program (within range - 32 bytes to 2MB if not it defualts to 2KB)

Try out the sample program given -

```
brainfuck hello_world.bf
```

(While in the correct directory)

### Credits

The hello world program is from the Wikipedia page for brainfuck - [Brainfuck on Wikipedia](https://en.wikipedia.org/wiki/Brainfuck)
