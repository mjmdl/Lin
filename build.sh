CC=gcc
CFLAGS="-Wall -Wextra -pedantic"
LFLAGS=""
SRCS="./source/main.c ./source/file.c ./source/token.c ./source/lexer.c ./source/string.c"
TARGET=lin

$CC $CFLAGS -o $TARGET $SRCS $LFLAGS
