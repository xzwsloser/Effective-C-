src = $(wildcard *.cpp)
out = $(patsubst %.cpp,%,${src})
ALL: ${out}
%:%.cpp
	g++ $< -o $@ -Wall -g
clean:
	-rm -rf ${out}
.PYHONY: clean ALL 