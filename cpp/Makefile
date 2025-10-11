CXX = clang++
STD = -std=c++23 

aho_corasick_test: aho_corasick_test.cpp aho_corasick.hpp
	$(CXX) $(STD) -g -fsanitize=address $<

sparse_table_test: sparse_table_test.cpp sparse_table.hpp
	$(CXX) $(STD) -g -fsanitize=address $<