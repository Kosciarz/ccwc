# CCWC

This is a C++ implementation of the wc Linux tool written by me.

It supports four different options:

1. `-c`: Count the number of bytes in the input file.
2. `-l`: Count the number of lines in the input file.
3. `-w`: Count the number of words in the input file.
4. `-m`: Count the number of characters in the input file.

## Installation

To use CCWC:

1. Clone the git repository:

    ```sh
    git clone https://github.com/Kosciarz/ccwc.git
    ```

2. Build the executable:

    ```sh
    make
    ```

## Usage

To use CCWC, run the executable with one of the supported options and a file path:

```sh
./ccwc -c example.txt
./ccwc -l example.txt
./ccwc -w example.txt
./ccwc -m example.txt
```

You can also use it with input from `stdin`:

```sh
echo "Hello, world!" | ./ccwc -w
```

To display the help message:

```sh
./ccwc --help
```

## What I learned

- How to use Make and create a simple Makefile to build my project.

- How to use the C++ filesystem library for file operations.

- Handling wide character streams with `std::wifstream`.

- Implementing basic command-line argument parsing in C++.

- Using `std::locale` and `std::codecvt_utf8` for UTF-8 file handling.
