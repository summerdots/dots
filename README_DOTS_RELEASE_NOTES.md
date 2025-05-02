
# Dots Programming Language (MVP)

**Dots** is a minimalist, self-bootstrapping programming core written in C. It defines language as a set of behaviors—registered, remembered, and executed at runtime.  
*Language is behavior.*

---

## Features

- `run()` – executes `.so` functions from the keyword registry
- `run_print()` – executes and prints return values (`int` or `char*`)
- `keyword()` – registers new keywords from C source files
- Persistent memory via `.keywords.mem`
- Shared object files (`.so`) are auto-generated and loaded
- Self-bootstrapping mechanism using behavior accumulation
- Entirely written in C for direct control

> Both `.keywords.mem` and `.so` files are automatically created during execution. No manual preparation required.

---

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

---

## Executing Scripts

To run a `.dots` script:

```bash
./dots_lang example.dots
```

Example script:

```dots
keyword("add", "add.c");
run("add");
run_print("add");
```

---



## Example

A working demonstration is available in the [`example/`](./example) folder.  
It includes:

- A sample `.dots` script
- A C source code block registered as behavior using triple quotes
- A runtime output screenshot

To run a `.dots` script:

```bash
./dots_lang example.dots
```

Example script:

```dots
keyword hi
code: """char* hi() { return "Hello from memory!"; }"""

run_print("hi")
```

> Note: In the current version of Dots, C code must be written in a **single line inside triple quotes** due to parser limitations.


### Advanced Script Format Notes

Dots currently supports multiline C code blocks using triple-quoted strings.  
To ensure correct parsing, please follow these rules:

1. The line that starts with `code:` must be immediately followed by a line containing only triple quotes.  
2. The code block must be cleanly formatted (avoid Windows-style \r\n or mixed encodings).  
3. The closing triple quotes must also be on their own line, not combined with a return or brace.

**Example:**
```dots
keyword hi
code: """ 
char* hi() {
    return "Hello, Dots!";
}
"""

run_print("hi")
```



## Philosophy

> Programming is behavior. Language is memory.

Dots redefines language as a structure of runtime behavior. It does not begin with syntax, but with control—building from function registration and persistent memory.

It aims to eventually become a system that controls machines as directly as assembly, while preserving the abstraction power of higher-level languages.

In Dots, there is no `main()`. Instead, programs begin with `start()`, reflecting a flat structure where all modules are equal. There is no hierarchy—only initiation.

> **Language is behavior. But one day, language must become machine code.**  
> Machines should adapt to human intent—not the other way around.

---

Dots may be poorly written—even broken.  
But it realizes its core idea: **language is behavior**.  
You can laugh at it—then go write something better.

---

## Author

**Tang Tian (唐天)**  
Undergraduate in Finance, Yangtze University  
Self-taught programmer with a focus on systems, language design, and the philosophy of computing.

> May the dots you connect today change the world tomorrow.

---

**This might be poorly written. It might even be broken.**  
But it works, and it dares to say: *language is behavior.*  
So go ahead — fork it, fight it, fix it.  
Or build your own version that runs better and thinks deeper.

---

**This language isn’t written very well. It’s probably a bit messy.**  
But it runs, and it tries to say something simple: **language is behavior.**

If it makes you curious — even just a little —  
feel free to try it.  
Fork it, fix it, or write your own version.

Think of it as a small experiment in language,  
and maybe, a bit of fun.
