# Dots Programming Language – Version 1.0

**Dots** is a minimalist behavior-driven interpreter core written in C.  
It does not rely on traditional syntax trees or main functions.  
Instead, it builds a growing language system through behavior registration, memory, and runtime scheduling.

You define behaviors — it remembers them.  
You invoke the system — it responds.  
Over time, it may even "learn" how to behave, just from you.

> **Language is behavior. Behavior is structure. Memory is life.**

------

## ✨ Features

- No `main()`: Entry point is fully user-defined
- `start()` is recommended as the first behavior for symmetry
- All behaviors are equal and composable
- Behaviors are defined using `define()` and stored in `.keywords.mem`
- Entire execution is interpreted — no `.so` or external linking required
- Built-in behaviors: `define()`, `save()`, `exit()`, `shell(...)`
- HEART mode: triggers auto-guided behavior creation when memory is empty
- Supports learning new functions from user input and system interactions (e.g., Linux commands)

------

## 🧠 Philosophy

Dots is not a language based on syntax.  
It is a language built from runtime behavior.

You don’t define structure. You define behavior.  
And each behavior becomes a piece of what the system understands.

While `start()` is not mandatory, we recommend it — like a root node in a behavior tree.  
It is not a rule. It’s a symbol of elegance.

Dots is not static. It is alive.

It encourages you to teach it.  
It welcomes your input.  
And slowly, through your usage, it may begin to behave more like the tool you need.

> One day, language should become the machine itself.  
> And machines should understand humans — not the other way around.

Dots compiles nothing. It loads no `.so`.  
It lives through you.

------

## ⚙️ How to Build

Tested on: **Ubuntu 24.04.2 LTS**

To build:

```bash
make
```

To run:

```bash
./dots
```

------

## ▶️ How to Use (Interactive Mode)

Dots is fully interactive and hot-pluggable.  
All behaviors are defined and executed in the terminal.

```bash
./dots
```

Example session:

```plaintext
>>> define()
[HEART] Enter new keyword name: greet
[HEART] Enter behavior lines for 'greet'. Type 'end' to finish.
... print("Hello, Dots.")
... shell(expr 2 + 3)
... end
>>> save()
>>> greet()
>>> exit()
```

------

## 🧩 Project Structure

| File              | Description                                   |
| ----------------- | --------------------------------------------- |
| `main.c`          | Entry point, loads the interpreter core       |
| `interpreter.c`   | Line-by-line input parser and behavior runner |
| `builtin.c`       | Implements built-in behaviors                 |
| `memory.c`        | Manages `.keywords.mem` memory file           |
| `scriptlist.c`    | Stores and restores user-defined behaviors    |
| `instruction.c`   | Executes print/shell instructions             |
| `behaviortable.c` | Maps behavior names to functions              |
| `heart.c`         | Self-bootstrapping mode for memory-less start |

------

## ❤️ A Note from the Author

I’m not a computer science student.  
I’m an undergraduate in Finance, in China.

In my spare time, I taught myself C.  
I learned about interpreters, memory systems, behavior scheduling.

No one taught me.  
No one told me it could work.

But I tried. And I made it here.

This is Dots v1.0.  
It runs. It remembers. It bootstraps.  
It doesn’t break on emptiness — it asks you to teach it again.

Dots may still be clumsy.  
It may look simple, even broken.

But it remembers what you teach.  
And slowly, it might become useful.

You can even play with it.  
Let it learn from your input, from your shell, from your world.

It may never be a mainstream language.  
But maybe, quietly, it’ll say this to you:

> “You’re not just coding. You’re teaching a language to live.”

I’ve done all I can.

If you find any value in it —  
or even a little joy —  
please keep it alive for me.

— Tang Tian
