import os
import subprocess
import sys
import re

class TestResult:
    def __init__(self, name, passed, output, error, failure_details=None):
        self.name = name
        self.passed = passed
        self.output = output
        self.error = error
        self.failure_details = failure_details if failure_details else []

def compile_program():
    if not os.path.exists("proj06.cpp"):
        print("Error: 'proj06.cpp' not found in the current directory.")
        sys.exit(1)
    print("Compiling proj06.cpp...")
    compile_cmd = ["g++", "proj06.cpp", "-o", "proj06", "-Wall", "-Werror"]
    result = subprocess.run(compile_cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
    if result.returncode != 0:
        print("Compilation failed with the following error:")
        print(result.stderr)
        sys.exit(1)
    print("Compilation successful.\n")

def create_test_files():
    test_input_a = (
        "LDR 5 ebd8\n"
        "STR 4 0ac2\n"
        "LDR a 0ad0\n"
    )
    with open("testA.txt", "w") as f:
        f.write(test_input_a)

    test_input_b = (
        "LDR 7 12f0\n"
        "STR 3 2580\n"
        "LDR e 3fc0\n"
        "STR f 0000\n"
    )
    with open("testB.txt", "w") as f:
        f.write(test_input_b)

    test_input_c = (
        "LDR 0 0000\n"
        "LDR 1 0002\n"
        "STR 2 0004\n"
        "LDR 3 1000\n"
    )
    with open("testC.txt", "w") as f:
        f.write(test_input_c)

    test_input_d = (
        "STR 8 abcd\n"
        "STR 9 ef01\n"
    )
    with open("testD.txt", "w") as f:
        f.write(test_input_d)

    initial_ram_1 = (
        "0000 00 01 02 03 04 05 06 07 08 09 0a 0b 0c 0d 0e 0f\n"
        "0010 10 11 12 13 14 15 16 17 18 19 1a 1b 1c 1d 1e 1f\n"
    )
    with open("initialRAM1.txt", "w") as f:
        f.write(initial_ram_1)

    initial_ram_2 = (
        "0000 ff ee dd cc bb aa 99 88 77 66 55 44 33 22 11 00\n"
        "1000 01 23 45 67 89 ab cd ef fe dc ba 98 76 54 32 10\n"
    )
    with open("initialRAM2.txt", "w") as f:
        f.write(initial_ram_2)

    print("Test files created successfully.\n")

def validate_output(output, expected_patterns):
    failed_patterns = []
    
    for pattern in expected_patterns:
        if not re.search(pattern, output, re.MULTILINE):
            failed_patterns.append(pattern)
    
    return (len(failed_patterns) == 0, failed_patterns)

def run_test_case(test_case):
    print(f"Running test case: {test_case['name']}")
    cmd = ["./proj06"] + test_case["args"]
    
    try:
        result = subprocess.run(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, timeout=10)
        print("Standard Output:")
        print(result.stdout)
        if result.stderr:
            print("Standard Error:")
            print(result.stderr)
            
        passed = True
        failed_details = []
        
        # Check output patterns if specified
        if "expected_patterns" in test_case:
            passed, failed_patterns = validate_output(result.stdout, test_case["expected_patterns"])
            
            # Add details about failed patterns
            if not passed:
                for pattern in failed_patterns:
                    failed_details.append(f"Missing expected pattern: {pattern}")
            
        # Check error message if specified
        if "expected_error" in test_case:
            error_match = re.search(test_case["expected_error"], result.stderr)
            if error_match is None:
                passed = False
                failed_details.append(f"Expected error pattern: {test_case['expected_error']}")
                failed_details.append(f"Actual error: {result.stderr}")
            
        print(f"Test {'PASSED' if passed else 'FAILED'}")
        
        # Print failure details if any
        if not passed:
            print("\nWHY THE TEST FAILED:")
            for detail in failed_details:
                print(f"- {detail}")
        
        print("-" * 40 + "\n")
        
        return TestResult(test_case["name"], passed, result.stdout, result.stderr, failed_details)
        
    except subprocess.TimeoutExpired:
        print("Error: Test case timed out.")
        print("-" * 40 + "\n")
        return TestResult(test_case["name"], False, "", "Test timed out")

def cleanup():
    files_to_remove = [
        "proj06", 
        "testA.txt", "testB.txt", "testC.txt", "testD.txt",
        "initialRAM1.txt", "initialRAM2.txt"
    ]
    for filename in files_to_remove:
        if os.path.exists(filename):
            try:
                os.remove(filename)
                print(f"Removed: {filename}")
            except Exception as e:
                print(f"Warning: Could not remove {filename}. Error: {e}")
    print("\nCleanup complete.")

def print_summary(results):
    total = len(results)
    passed = sum(1 for r in results if r.passed)
    
    print("\n" + "=" * 50)
    print(f"TEST SUMMARY: {passed}/{total} tests passed")
    print("=" * 50)
    
    for i, result in enumerate(results, 1):
        status = "PASSED" if result.passed else "FAILED"
        print(f"{i}. {result.name}: {status}")
    
    print("=" * 50)
    
    if passed == total:
        print("All tests passed! 🎉")
    else:
        print(f"{total - passed} tests failed. Review the output above for details.")
    print("=" * 50)

def main():
    results = []
    try:
        compile_program()
        create_test_files()
        
        test_cases = [
            {
                "name": "Basic Test A - Simple instruction processing",
                "args": ["-input", "testA.txt"],
                "expected_patterns": [
                    r"LDR 5 ebd8 3af 3 0",
                    r"STR 4 0ac2 02b 0 2",
                    r"LDR a 0ad0 02b 2 0"
                ]
            },
            {
                "name": "Basic Test B - With debug flag",
                "args": ["-debug", "-input", "testB.txt"],
                "expected_patterns": [
                    r"LDR 7 12f0",
                    r"STR 3 2580",
                    r"LDR e 3fc0",
                    r"STR f 0000"
                ]
            },
            {
                "name": "Basic Test C - With RAM initialization",
                "args": ["-ram", "initialRAM1.txt", "-input", "testC.txt"],
                "expected_patterns": [
                    r"LDR 0 0000 000 0 0",
                    r"LDR 1 0002 000 0 2",
                    r"STR 2 0004 000 0 4",
                    r"LDR 3 1000 040 0 0",
                    r"0000: 00 01 02 03 04"
                ]
            },
            {
                "name": "Basic Test D - With RAM and debug",
                "args": ["-ram", "initialRAM2.txt", "-input", "testD.txt", "-debug"],
                "expected_patterns": [
                    r"STR 8 abcd 2af 1 5",
                    r"STR 9 ef01 3bc 0 1",
                    r"0000: ff ee dd cc"
                ]
            },
            {
                "name": "Error Test - Missing input file",
                "args": ["-input", "nonexistent.txt"],
                "expected_error": r"Error: Could not open input file"
            },
            {
                "name": "Error Test - Missing RAM file",
                "args": ["-ram", "nonexistent.txt", "-input", "testA.txt"],
                "expected_error": r"Error: Could not open RAM file"
            },
            {
                "name": "Error Test - No input specified",
                "args": ["-debug"],
                "expected_error": r"Error: Input file not specified"
            }
        ]
        
        for test in test_cases:
            results.append(run_test_case(test))
            
    finally:
        print_summary(results)
        cleanup()

if __name__ == "__main__":
    main()