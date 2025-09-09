CFLAGS = -I src -Wall -Wextra -std=c11
TESTCFLAGS = -I src -I third_party/unity/src -Wall -Wextra -std=c11 -DUNITY_OUTPUT_COLOR

#EXECUTABLES
MAIN = main
TEST_COLOR = test_color
TEST_PARTICLE = test_particle
TEST_PARTICLESYSTEM = test_particlesystem

# src files
SRC = src/main.c src/particle.c src/color.c src/particlesystem.c src/image.c

all:
	gcc $(CFLAGS) $(SRC) -o main

test_color:
	gcc $(TESTCFLAGS) tests/test_color.c src/color.c third_party/unity/src/unity.c -o $(TEST_COLOR)
	./$(TEST_COLOR)

test_particle:
	gcc $(TESTCFLAGS) tests/test_particle.c src/color.c src/particle.c third_party/unity/src/unity.c -o $(TEST_PARTICLE)
	./$(TEST_PARTICLE)

test_particlesystem:
	gcc $(TESTCFLAGS) tests/test_particlesystem.c src/particlesystem.c src/color.c src/particle.c third_party/unity/src/unity.c -o $(TEST_PARTICLESYSTEM)
	./$(TEST_PARTICLESYSTEM)

test_all: test_particle test_color test_particlesystem

clean:
	rm -f $(MAIN) $(TEST_COLOR) $(TEST_PARTICLE) $(TEST_PARTICLESYSTEM)