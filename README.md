# Dots Programming Language (MVP)

**Dots** is a minimalist, self-bootstrapping programming core written in C. It defines language as a set of behaviors—registered, remembered, and executed at runtime.  
*Language is behavior.*

------

## Features

- `run()` – executes `.so` functions from the keyword registry
- `run_print()` – executes and prints return values (`int` or `char*`)
- `keyword()` – registers new keywords from C source files
- Persistent memory via `.keywords.mem`
- Shared object files (`.so`) are auto-generated and loaded
- Self-bootstrapping mechanism using behavior accumulation
- Entirely written in C for direct control

> Both `.keywords.mem` and `.so` files are automatically created during execution. No manual preparation required.

------

## Build & Run

Tested on: **Ubuntu 24.04.2 LTS**

### Build with Makefile

Ensure the `Makefile` is present. Then run:

```bash
make
```

This will compile all files into an executable named `dots`.

### Manual build

```bash
gcc -Wall -fPIC main.c start.c interpreter.c keyword.c keywordlist.c photolist.c -ldl -o dots_lang
```

------

## Usage (Dots Script Syntax v0.1)

Dots is a behavior-driven scripting language. Its core mechanism revolves around registering functions using `keyword` blocks, and executing them via `run()` or `run_print()`.

### 1. Basic Structure

A Dots script consists of one or more `keyword` blocks. Each block includes:

- A function name (keyword)
- A C function definition enclosed in triple quotes (code)

Supported runtime actions include executing functions, printing results, and listing behaviors.

### 2. Example Script

```dots
keyword hi
code: """
char* hi() { return "Hello from memory!"; }
"""

keyword add
code: """
int add(int a, int b) { return a + b; }
"""

run_print("hi")
run("add", 7, 5)
list()
```

### 3. Semantic Reference

- `keyword NAME`  
  Registers a new function named `NAME`. Must be followed by a `code:` block.
- `code: """ ... """`  
  Encloses a standard C function. No `main()` function required.
  - `char* hi()` is used with `run_print()` (returns string)
  - `int add(int, int)` is used with `run()` (returns integer)
- `run("name", a, b)`  
  Calls an integer-returning function with two integer parameters.
- `run_print("name")`  
  Calls a string-returning function and prints the result.
- `list()`  
  Lists all registered functions, including those restored from `.keywords.mem`.

### 4. Memory System

- All `keyword` definitions are saved to `.keywords.mem`;
- On next startup, Dots will automatically restore the functions and recompile them;
- Behaviors are remembered permanently, even across sessions.

### 5. Style Recommendations

- Separate each `keyword` block with a blank line;
- Use commas to separate parameters;
- Scripts must use the `.dots` extension;
- Use `main.dots` or `test.dots` as primary entry scripts.

------



### 6. Behavior Persistence Tips

- **The first time you run a script**, all `keyword` and `code` blocks must be fully written in the file—just like in the example script above.  
  This allows Dots to compile and remember each behavior via `.so` files and `.keywords.mem`.
- **After the first run**, you can simplify future scripts by only writing:

```dots
run("add")
run_print("hi")
```

Dots will automatically recover the definitions and run the remembered behavior.

> In other words: **define once, call forever.**

### 7. How to Run Scripts

- All script content (including `keyword`, `code`, and `run()` commands) must be written in a `.dots` file.
- After compiling with `make`, you can execute the script using:

```bash
./dots_lang your_script.dots
```

For example:

```bash
./dots_lang example.dots
```

This will trigger Dots to compile, load, and execute all defined behaviors within the script.

## 

> Programming is behavior. Language is memory.

Dots redefines language as a structure of runtime behavior. It does not begin with syntax, but with control—building from function registration and persistent memory.

It aims to eventually become a system that controls machines as directly as assembly, while preserving the abstraction power of higher-level languages.

In Dots, there is no `main()`. Instead, programs begin with `start()`, reflecting a flat structure where all modules are equal. There is no hierarchy—only initiation.

> **Language is behavior. But one day, language must become machine code.**  
> Machines should adapt to human intent—not the other way around.

------

Dots may be poorly written—even broken.  
But it realizes its core idea: **language is behavior**.  
You can laugh at it—then go write something better.

------

## Author

**Tang Tian (唐天)**  
Undergraduate in Finance, Yangtze University  
Self-taught programmer with a focus on systems, language design, and the philosophy of computing.

> May the dots you connect today change the world tomorrow.

------

**This might be poorly written. It might even be broken.**  
But it works, and it dares to say: *language is behavior.*  
So go ahead — fork it, fight it, fix it.  
Or build your own version that runs better and thinks deeper.

------

**This language isn’t written very well. It’s probably a bit messy.**  
But it runs, and it tries to say something simple: **language is behavior.**

If it makes you curious — even just a little —  
feel free to try it.  
Fork it, fix it, or write your own version.

Think of it as a small experiment in language,  
and maybe, a bit of fun.
