## CONTENTS

<!-- TOC -->

- [FILE STRUCTURE](#file-structure)
- [CLASS STRUCTURE](#class-structure)
- [CODE FORMATTING](#code-formatting)
- [HEADER GUARDS](#header-guards)
- [INCLUDES](#includes)
- [INDENTATION](#indentation)
- [NAMING](#naming)

<!-- /TOC -->

## FILE STRUCTURE

Sections SHOULD be ordered as:
- documentation
- `#include`(s)
- `#define`(s)
- `typedef`(s)
- `class`(es)

2 blank lines SHOULD separate each section

## CLASS STRUCTURE

Visibility SHOULD be ordered as:
- `public`
- `protected`
- `private`

Entities SHOULD be ordered as:
- `const`(s)
- `enum`(s)
- `struct`(s)
- field (s)
- method (s)

## CODE FORMATTING

See the [.clang-format](../.clang-format) file.

## HEADER GUARDS

MUST be placed in every header.

MUST be formatted as `<PATH>_<FILENAME>_<EXTENSION>_`.

## INCLUDES

`#include`(s) SHOULD be ordered from specific to general:
- own header
- own library
- external libraries
- c++ standard
- c standard

All system _and_ external library headers MUST be in the `<header>` form.

All other headers MUST be in the `"header"` form.

## INDENTATION

MUST be 4 spaces.

## NAMING

|             |            |
|-------------|------------|
| `namespace` | PascalCase |
| `class`     | PascalCase |
| `struct`    | PascalCase |
| `#define`   | UPPER_CASE |
| `const`     | UPPER_CASE |
| `enum`      | UPPER_CASE |
| field       | camelCase  |
| variable    | camelCase  |
| method      | snake_case |
| function    | snake_case |
