
all: nester-linked-list.gcc nester-linked-list.clang

nester-linked-list.gcc: main.cpp
	g++ -ggdb3 -Wall -Wextra -Werror -std=c++11 -o $(@) $(^)

nester-linked-list.clang: main.cpp
	clang++ -ggdb3 -Wall -Wextra -Werror -std=c++11 -o $(@) $(^)

clean:
	rm -f nester-linked-list.{gcc,clang}
