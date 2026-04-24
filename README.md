<h1 align="center">
  Python JSON → C Header Converter
</h1>
<p align="center">
  <a href="#introduction">Introduction</a> •
  <a href="#project-progress">Project Progress</a> •
  <a href="#what-ive-learned">What I've Learned</a> •
  <a href="#build">Build</a>
</p>

---

## Introduction

This project is a Python CLI tool that reads a peripheral configuration file (JSON or YAML)
and generates C boilerplate header files using Jinja2 templating.

It was developed to learn core Python tooling — file I/O, data validation, templating,
and CLI design — in a practical embedded-systems context using real peripheral definitions
from MCU datasheets.

The main focus is building a clean, validated pipeline: config in, C code out.

---

## Project Progress

### Milestones

| # | Milestone | Status |
|---|-----------|--------|
| **1** | Read a JSON file and print its contents | ✅ Done |
| **2** | Add Pydantic validation to reject badly formed input | ✅ Done |
| **3** | Understand what a peripheral header should look like | ✅ Done |
| **4** | Create a peripheral header based on what you've learnt | ✅ Done |
| **5** | Write a Jinja2 template that produces a C header file | 🔄 In Progress |
| **6** | Connect them — config in, C code out | ⬜ Planned |
| **7** | Wrap it in a Click CLI | ⬜ Planned |
| **8** | Push to GitHub with a proper README | ⬜ Planned |

### Current Features

- Reads a JSON peripheral config file
- Validates the config against Pydantic models (`Peripheral`, `Register`)
- Enforces valid C identifier names via regex pattern matching
- Rejects invalid input with clear, descriptive error messages

### Planned Features

- Jinja2 template rendering to produce `.h` files
- Support for multiple peripheral types (UART, GPIO, SPI, etc.)
- YAML config support alongside JSON
- Click CLI interface with argument handling
- Pydantic Logfire observability integration

---

## What I've Learned

### Part 1 — JSON File I/O
- Reading and parsing JSON files in Python using the `json` module
- Understanding Python file handling with `with open(...) as f`

### Part 2 — Pydantic Validation

**What is Pydantic?**
Pydantic is a data validation library for Python. You define a model — a class describing
the expected shape and types of your data — and Pydantic validates any incoming data
against it automatically.

```python
from pydantic import BaseModel, Field

class Register(BaseModel):
    offset: int = Field(ge=0)
    name: str = Field(pattern="^[A-Za-z_][A-Za-z0-9_]*$")

class Peripheral(BaseModel):
    name: str = Field(pattern="^[A-Za-z_][A-Za-z0-9_]*$")
    base_address: int
    size: int
    enabled: bool
    registers: list[Register]
```

Calling `Peripheral(**data)` will raise a `ValidationError` with a clear message
if anything is missing, the wrong type, or fails a constraint.

**Key things learned:**
- Nested Pydantic models for structured data
- Python class definition order — a class must be defined before it can be referenced
- Using `Field(pattern=...)` to enforce valid C identifiers via regex
- The difference between `ge=0` (≥ 0) and `gt=0` (> 0) — relevant for register offsets,
  which can legitimately start at 0

**Valid vs Invalid JSON:**

```json
// ❌ Bad — common mistakes
{
    name: "UART0",               // keys must be quoted
    "base_address": 0x40002000,  // hex literals not valid in JSON
    "enabled": True,             // must be lowercase true
    "registers": [
        {"offset": 0, "name": "CR",}  // trailing comma
    ]
}
```

```json
// ✅ Good
{
    "name": "UART0",
    "base_address": 1073750016,
    "size": 256,
    "enabled": true,
    "registers": [
        {"offset": 0, "name": "CR"}
    ]
}
```

---

## Build

### Requirements

- Python 3.11+
- pip

### Dependencies

This project uses:

- **Pydantic** for config validation
- **Jinja2** for C header templating
- **Click** for the CLI interface *(coming in milestone 5)*

Install all dependencies via pip:

```bash
pip install -r requirements.txt
```

### Running from Source

#### 1. Clone the Repository

```bash
git clone https://github.com/LewisNA14/<repo-name>.git
cd <repo-name>
```

#### 2. Set up a virtual environment

```bash
python -m venv .venv
source .venv/bin/activate  # Linux / macOS
.venv\Scripts\activate     # Windows
```

#### 3. Install dependencies

```bash
pip install -r requirements.txt
```

#### 4. Run the tool

```bash
python main.py
```
