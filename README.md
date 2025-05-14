# Dots 2.0

Dots is a minimalist behavior-structured programming language. It is not a traditional scripting or compiled language. It is structure-first, execution-driven, and behavior-composed. Though still very limited and primitive, this version marks the final edition of Dots.

## Philosophy

Dots is not designed to compete with established programming languages. Instead, it explores a new path of expressing logic and computation through "behaviors" — small, modular units of logic linked structurally. It emphasizes:

- Structure over syntax
- Behavior over function
- Growth over completeness

## Features

- Behavior-structured language core
- Built-in lazy evaluation (non-strict, only runs when explicitly triggered)
- First-class behaviors with parameters
- In-place variable resolution with `$var`
- Basic control structures: `if`
- Simple math operations: `add`, `sub`, `gt`, `lt`
- Dynamic variable setting via `set`
- Behavior registration introspection: `list`, `explain`
- Self-growth model with `start*` behavior modules
- Inspired in part by ideas from Haskell and ML

## Runtime Environment

- OS: Unix-based (macOS or Linux)
- Compiler: GCC or Clang (C99 or later)
- Terminal: Bash / Zsh recommended

## Run Instructions

```bash
make clean
make
./dotsc examples/test.dots     # Compile .dots file into modules
./dots                         # Run the interpreter
```

## Example Dots Script

```dots
start*: say_hello(name) {
    print("Hello_world")
}

start*: do_math(x, y) {
    add($x, $y)
    sub($x, $y)
    gt($x, $y)
    lt($x, $y)
}

start*: test_logic(flag) {
    if(flag) {
        print("Flag is true.")
    }
    if("false") {
        print("This should not be printed.")
    }
}

start*: inspect() {
    list()
    explain("say_hello")
    explain("add")
}

start*: main() {
    print("Running full demo...")
    say_hello()
    do_math(42, 7)
    test_logic("true")
    inspect()
    print("Demo complete.")
}

start*: start() {
    main()
}
```

## Built-in Behaviors

- `print(x)` – Print a value (supports `$var` substitution)
- `set(name, value)` – Set variable in current context
- `add(x, y)`, `sub(x, y)` – Arithmetic
- `gt(x, y)`, `lt(x, y)` – Boolean comparison
- `if(cond)` – Conditional execution
- `list()` – Show all registered behaviors
- `explain(name)` – Show info about a behavior
- `exit()` – Terminate program

## Note

This project is very likely incomplete and may contain bugs or design flaws. You are welcome to laugh at it — and hopefully, write something even better.

I’ve done my best. Thank you for reading this far.

– Tang Tian
