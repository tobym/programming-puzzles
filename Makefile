CC=g++
CFLAGS=-Wall

permutations: permutations.cc
	$(CC) $(CFLAGS) permutations.cc -o permutations

phoneWords: phoneWords.cc
	$(CC) $(CFLAGS) phoneWords.cc -o phoneWords

oddWord:
	ruby odd-word/odd_word.rb odd-word/input.txt

oddWord2:
	ruby odd-word/odd_word.rb odd-word/spacey.txt

.PHONY: oddWord oddWord2
