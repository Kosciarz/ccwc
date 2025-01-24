# CCWC

This is a C++ implementation of the `wc` Linux tool written by me.

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

You can use CCWC with a file or standard input.

### With a file

-Linux
    ```sh
    ./ccwc -c filename.txt  # Count bytes
    ./ccwc -l filename.txt  # Count lines
    ./ccwc -w filename.txt  # Count words
    ./ccwc -m filename.txt  # Count characters
    ```

-Windows
    ```bash
    .\ccwc.exe -c filename.txt  # Count bytes
    .\ccwc.exe -l filename.txt  # Count lines
    .\ccwc.exe -w filename.txt  # Count words
    .\ccwc.exe -m filename.txt  # Count characters
    ```

### With standard input

```sh
echo "Hello World" | ./ccwc -w  # Count words from standard input
```

## What I learned
