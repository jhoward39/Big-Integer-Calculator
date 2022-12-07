main.out: BigInt.cpp calculator.cpp main.cpp
	@$(CXX) -g -Wall $(CXXFLAGS) $^ -o $@

test.out: BigInt.cpp calculator.cpp test_driver.cpp
	@$(CXX) -g -Wall $(CXXFLAGS) $^ -o $@

format:
	@clang-format -i *.cpp *.h

clean:
	@rm -f *.out

impl.out: BigIntImpl.cpp calculatorimpl.cpp test_driver.cpp
	@$(CXX) -g -Wall $(CXXFLAGS) $^ -o $@
