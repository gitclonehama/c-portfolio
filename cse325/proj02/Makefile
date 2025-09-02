# Build main project executable
proj02: proj02.cpp
	g++ -o proj02 -Wall proj02.cpp

# Variables for test files
TARGET = proj02
SRC = source
DEST = destination
EXP = expected
OUT = program_output

test: $(TARGET)
	@echo ""
	@echo "============================="
	@echo "===== RUNNING ALL TESTS ====="
	@echo "============================="
	@echo ""


	@rm -f $(SRC) $(DEST) $(EXP) $(OUT)
	@echo "Test 1 (no src, no dest)"

	@echo "============================="
	@echo "EXPECTED:"
	@echo "ERROR (src file does not exit)"
	@echo ""
	@echo "RECEIVED:"
	@-./$(TARGET) $(SRC) $(DEST) > $(OUT) 2>&1 || true
	@cat $(OUT)
	@echo "============================="
	@echo ""


	@rm -f $(SRC) $(DEST) $(EXP) $(OUT)
	@echo "Test 2 (src, no dest)"
	@echo "SOURCE FILE CONTENT" > $(SRC)

	@echo "============================="
	@echo "EXPECTED:"
	@echo "SRC == DEST"
	@echo "SOURCE FILE CONTENT" > $(EXP)
	@echo ""
	@echo "RECEIVED:"
	@-./$(TARGET) $(SRC) $(DEST) > $(OUT) 2>&1 || true
	@cat $(OUT)
	@echo ""
	@diff $(DEST) $(EXP) > /dev/null 2>&1 \
	&& echo "============ PASS ===========" \
	|| (echo "============ FAIL ==========="; echo "DIFFERENCE:"; diff $(DEST) $(EXP))
	@echo ""


	@rm -f $(SRC) $(DEST) $(EXP) $(OUT)
	@echo "Test 3 (src, dest, no params)"
	@echo "SOURCE FILE CONTENT" > $(SRC)
	@echo "DESTINATION FILE CONTENT" > $(DEST)

	@echo "============================="
	@echo "EXPECTED:"
	@echo "ERROR (destination exists && no params)"
	@echo ""
	@echo "RECEIVED:"
	@-./$(TARGET) $(SRC) $(DEST) > $(OUT) 2>&1 || true
	@cat $(OUT)
	@echo "============================="
	@echo ""


	@rm -f $(SRC) $(DEST) $(EXP) $(OUT)
	@echo "Test 4 (src, dest, -a)"
	@echo "SOURCE FILE CONTENT" > $(SRC)
	@echo "DESTINATION FILE CONTENT" > $(DEST)

	@echo "============================="
	@echo "EXPECTED:"
	@echo "DEST = DEST + SRC"
	@echo "DESTINATION FILE CONTENT" > $(EXP)
	@echo "SOURCE FILE CONTENT" >> $(EXP)
	@echo ""
	@echo "RECEIVED:"
	@-./$(TARGET) $(SRC) $(DEST) -a > $(OUT) 2>&1 || true
	@cat $(OUT)
	@echo ""
	@diff $(DEST) $(EXP) > /dev/null 2>&1 \
	&& echo "============ PASS ===========" \
	|| (echo "============ FAIL ==========="; echo "DIFFERENCE:"; diff $(DEST) $(EXP))
	@echo ""

	@rm -f $(SRC) $(DEST) $(EXP) $(OUT)
	@echo "Test 5 (src, dest, -t)"
	@echo "SOURCE FILE CONTENT" > $(SRC)
	@echo "DESTINATION FILE CONTENT" > $(DEST)

	@echo "============================="
	@echo "EXPECTED:"
	@echo "DEST = SRC"
	@echo "SOURCE FILE CONTENT" > $(EXP)
	@echo ""
	@echo "RECEIVED:"
	@-./$(TARGET) $(SRC) $(DEST) -t > $(OUT) 2>&1 || true
	@cat $(OUT)
	@echo ""
	@diff $(DEST) $(EXP) > /dev/null 2>&1 \
	&& echo "============ PASS ===========" \
	|| (echo "============ FAIL ==========="; echo "DIFFERENCE:"; diff $(DEST) $(EXP))
	@echo ""

	@rm -f $(SRC) $(DEST) $(EXP) $(OUT)
	@echo "Test 6 (src, dest, -b)"
	@echo "SOURCE FILE CONTENT" > $(SRC)
	@echo "DESTINATION FILE CONTENT" > $(DEST)

	@echo "============================="
	@echo "EXPECTED:"
	@echo "ERROR (incomplete -b)"
	@-./$(TARGET) $(SRC) $(DEST) -b > $(OUT) 2>&1 || true
	@echo ""
	@echo "RECEIVED:"
	@cat $(OUT)
	@echo "============================="
	@echo ""

	@rm -f $(SRC) $(DEST) $(EXP) $(OUT)
	@echo "Test 7 (src, dest, -b 100)"
	@echo "SOURCE FILE CONTENT" > $(SRC)
	@echo "DESTINATION FILE CONTENT" > $(DEST)

	@echo "============================="
	@echo "EXPECTED:"
	@echo "ERROR: (DEST exits, params required)"
	@echo "DESTINATION FILE CONTENT" > $(EXP)
	@echo ""
	@echo "RECEIVED:"
	@-./$(TARGET) $(SRC) $(DEST) -b 100 > $(OUT) 2>&1 || true
	@cat $(OUT)
	@echo ""
	@diff $(DEST) $(EXP) > /dev/null 2>&1 \
	&& echo "============ PASS ===========" \
	|| (echo "============ FAIL ==========="; echo "DIFFERENCE:"; diff $(DEST) $(EXP))
	@echo ""

	@rm -f $(SRC) $(DEST) $(EXP) $(OUT)
	@echo "Test 8 (src, dest, -b 10ab)"
	@echo "SOURCE FILE CONTENT" > $(SRC)
	@echo "DESTINATION FILE CONTENT" > $(DEST)

	@echo "============================="
	@echo "EXPECTED:"
	@echo "ERROR: (Incomplete -b)"
	@echo ""
	@echo "RECEIVED:"
	@-./$(TARGET) $(SRC) $(DEST) -b 10ab > $(OUT) 2>&1 || true
	@cat $(OUT)
	@echo "============================="
	@echo ""

	@rm -f $(SRC) $(DEST) $(EXP) $(OUT)
	@echo "Test 9 (src, dest, -t -a)"
	@echo "SOURCE FILE CONTENT" > $(SRC)
	@echo "DESTINATION FILE CONTENT" > $(DEST)
	
	@echo "============================="
	@echo "EXPECTED:"
	@echo "ERROR (both -t -a)"
	@echo "DESTINATION FILE CONTENT" > $(EXP)
	@echo ""
	@echo "RECEIVED:"
	@-./$(TARGET) $(SRC) $(DEST) -t -a > $(OUT) 2>&1 || true
	@cat $(OUT)
	@echo ""
	@diff $(DEST) $(EXP) > /dev/null 2>&1 \
	&& echo "============ PASS ===========" \
	|| (echo "============ FAIL ==========="; echo "DIFFERENCE:"; diff $(DEST) $(EXP))
	@echo ""

	@rm -f $(SRC) $(DEST) $(EXP) $(OUT)
	@echo "Test 10 (src, dest, -a -t)"
	@echo "SOURCE FILE CONTENT" > $(SRC)
	@echo "DESTINATION FILE CONTENT" > $(DEST)
	
	@echo "============================="
	@echo "EXPECTED:"
	@echo "ERROR (both -a -t)"
	@echo "DESTINATION FILE CONTENT" > $(EXP)
	@echo ""
	@echo "RECEIVED:"
	@-./$(TARGET) $(SRC) $(DEST) -a -t > $(OUT) 2>&1 || true
	@cat $(OUT)
	@echo ""
	@diff $(DEST) $(EXP) > /dev/null 2>&1 \
	&& echo "============ PASS ===========" \
	|| (echo "============ FAIL ==========="; echo "DIFFERENCE:"; diff $(DEST) $(EXP))
	@echo ""

	@rm -f $(SRC) $(DEST) $(EXP) $(OUT)
	@echo "Test 11 (src, dest, -b 0 -a)"
	@echo "SOURCE FILE CONTENT" > $(SRC)
	@echo "DESTINATION FILE CONTENT" > $(DEST)
	
	@echo "============================="
	@echo "EXPECTED:"
	@echo "ERROR (-b has to be > 0)"
	@echo "DESTINATION FILE CONTENT" > $(EXP)
	@echo ""
	@echo "RECEIVED:"
	@-./$(TARGET) $(SRC) $(DEST) -b 0 > $(OUT) 2>&1 || true
	@cat $(OUT)
	@echo ""
	@diff $(DEST) $(EXP) > /dev/null 2>&1 \
	&& echo "============ PASS ===========" \
	|| (echo "============ FAIL ==========="; echo "DIFFERENCE:"; diff $(DEST) $(EXP))
	@echo ""

	@rm -f $(SRC) $(DEST) $(EXP) $(OUT)
	@echo "Test 12 (src, dest, -b 1 -a)"
	@echo "SOURCE FILE CONTENT" > $(SRC)
	@echo "DESTINATION FILE CONTENT" > $(DEST)
	
	@echo "============================="
	@echo "EXPECTED:"
	@echo "DEST == DEST + SRC"
	@echo "DESTINATION FILE CONTENT" > $(EXP)
	@echo "SOURCE FILE CONTENT" >> $(EXP)
	@echo ""
	@echo "RECEIVED:"
	@-./$(TARGET) $(SRC) $(DEST) -b 1 -a > $(OUT) 2>&1 || true
	@cat $(OUT)
	@echo ""
	@diff $(DEST) $(EXP) > /dev/null 2>&1 \
	&& echo "============ PASS ===========" \
	|| (echo "============ FAIL ==========="; echo "DIFFERENCE:"; diff $(DEST) $(EXP))
	@echo ""


	@rm -f $(SRC) $(DEST) $(EXP) $(OUT)
	@echo "Test 13 (src, dest, -b 300 -a)"
	@echo "SOURCE FILE CONTENT" > $(SRC)
	@echo "DESTINATION FILE CONTENT" > $(DEST)
	
	@echo "============================="
	@echo "EXPECTED:"
	@echo "DEST == DEST + SRC"
	@echo "DESTINATION FILE CONTENT" > $(EXP)
	@echo "SOURCE FILE CONTENT" >> $(EXP)
	@echo ""
	@echo "RECEIVED:"
	@-./$(TARGET) $(SRC) $(DEST) -b 300 -a > $(OUT) 2>&1 || true
	@cat $(OUT)
	@echo ""
	@diff $(DEST) $(EXP) > /dev/null 2>&1 \
	&& echo "============ PASS ===========" \
	|| (echo "============ FAIL ==========="; echo "DIFFERENCE:"; diff $(DEST) $(EXP))
	@echo ""


	@rm -f $(SRC) $(DEST) $(EXP) $(OUT)
	@echo "Test 14 (src, dest, -b 1 -t)"
	@echo "SOURCE FILE CONTENT" > $(SRC)
	@echo "DESTINATION FILE CONTENT" > $(DEST)
	
	@echo "============================="
	@echo "EXPECTED:"
	@echo "DEST == SRC"
	@echo "SOURCE FILE CONTENT" > $(EXP)
	@echo ""
	@echo "RECEIVED:"
	@-./$(TARGET) $(SRC) $(DEST) -b 1 -t > $(OUT) 2>&1 || true
	@cat $(OUT)
	@echo ""
	@diff $(DEST) $(EXP) > /dev/null 2>&1 \
	&& echo "============ PASS ===========" \
	|| (echo "============ FAIL ==========="; echo "DIFFERENCE:"; diff $(DEST) $(EXP))
	@echo ""


	@rm -f $(SRC) $(DEST) $(EXP) $(OUT)
	@echo "Test 15 (src, dest, -b 300 -t)"
	@echo "SOURCE FILE CONTENT" > $(SRC)
	@echo "DESTINATION FILE CONTENT" > $(DEST)
	
	@echo "============================="
	@echo "EXPECTED:"
	@echo "DEST == SRC"
	@echo "SOURCE FILE CONTENT" > $(EXP)
	@echo ""
	@echo "RECEIVED:"
	@-./$(TARGET) $(SRC) $(DEST) -b 300 -t > $(OUT) 2>&1 || true
	@cat $(OUT)
	@echo ""
	@diff $(DEST) $(EXP) > /dev/null 2>&1 \
	&& echo "============ PASS ===========" \
	|| (echo "============ FAIL ==========="; echo "DIFFERENCE:"; diff $(DEST) $(EXP))
	@echo ""


	@rm -f $(SRC) $(DEST) $(EXP) $(OUT)
	@echo "Test 16 (src, -b 300 -t, dest)"
	@echo "SOURCE FILE CONTENT" > $(SRC)
	@echo "DESTINATION FILE CONTENT" > $(DEST)
	
	@echo "============================="
	@echo "EXPECTED:"
	@echo "DEST == SRC"
	@echo "SOURCE FILE CONTENT" > $(EXP)
	@echo ""
	@echo "RECEIVED:"
	@-./$(TARGET) $(SRC) -b 300 -t $(DEST) > $(OUT) 2>&1 || true
	@cat $(OUT)
	@echo ""
	@diff $(DEST) $(EXP) > /dev/null 2>&1 \
	&& echo "============ PASS ===========" \
	|| (echo "============ FAIL ==========="; echo "DIFFERENCE:"; diff $(DEST) $(EXP))
	@echo ""


	@rm -f $(TARGET) $(SRC) $(DEST) $(EXP) $(OUT)


clean:
	rm -f $(TARGET) $(SRC) $(DEST) $(EXP) $(OUT)
