CC = gcc
CFLAGS = -Wall -Wextra -std=c11
SRCS = blackjack.c playbj.c

OBJS = $(SRCS:.c=.o)

EXEC = playbj

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)

.PHONY: all clean