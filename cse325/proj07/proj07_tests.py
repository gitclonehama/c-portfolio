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

def write_file(filename, content):
    """Helper function to write content to a file."""
    try:
        with open(filename, "w") as f:
            f.write(content)
    except IOError as e:
        print(f"Error writing to file {filename}: {e}")
        sys.exit(1)

def compile_program():
    """Compile the proj07.cpp program."""
    if not os.path.exists("proj07.cpp"):
        print("Error: 'proj07.cpp' not found in the current directory.")
        sys.exit(1)
    print("Compiling proj07.cpp...")
    compile_cmd = ["g++", "proj07.cpp", "-o", "proj07", "-Wall", "-Werror"]
    result = subprocess.run(compile_cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
    if result.returncode != 0:
        print("Compilation failed with the following error:")
        print(result.stderr)
        sys.exit(1)
    print("Compilation successful.\n")

def create_input_test_files():
    """Create the instruction input test files."""
    # Test 1: From instructor
    test_input = ("""\
        LDR 5 ebd8
        STR 4 0ac2
        LDR a 0ad0""")
    write_file("input1.txt", test_input)
    
    # Test 2: From edStem
    test_input2 = ("""\
        LDR 1 3000
        STR 1 3010
        LDR 2 3010""")
    write_file("input2.txt", test_input2)

def create_ram_files():
    """Create the initial RAM state files."""
    
    initial_ram1 = ("""\
    0000 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
    0010 00 00 00 00 00 00 00 00 00 00 00 00 70 00 00 00
    0020 00 00 00 00 6d 00 00 00 00 00 00 00 00 00 00 00
    0030 00 ff 00 00 00 00 00 00 00 00 00 00 00 00 00 23
    0040 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
    0050 7b 00 23 cc 89 0a 00 ef 00 ff 00 00 00 00 00 00
    0060 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
    0070 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00""")
    write_file("ram1.txt", initial_ram1)
    
    initial_ram2 = ("""\
    0000 01 00 01 00 01 00 01 00 01 00 00 00 00 00 00 69
    3000 12 34 56 78 9A BC DE F0 11 22 33 44 55 66 77 88""")
    write_file("ram2.txt", initial_ram2)

def create_test_files():
    """Create all test files needed for the test case."""
    create_input_test_files()
    create_ram_files()
    print("\nTest files created successfully.\n")

def validate_output(output, expected_patterns):
    failed_patterns = []
    
    for pattern in expected_patterns:
        if not re.search(pattern, output, re.MULTILINE | re.IGNORECASE):
            failed_patterns.append(pattern)
    
    return (len(failed_patterns) == 0, failed_patterns)

def run_test_case(test_case):
    print(f"Running test case: {test_case['name']}")
    cmd = ["./proj07"] + test_case["args"]
    
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
        "proj07", 
        "input1.txt", "ram1.txt",
        "input2.txt", "ram2.txt"
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
        print(f"{i}. {status}: {result.name}")
    
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
                "name": "Error Test - No input specified",
                "args": ["-debug"],
                "expected_error": r"Error: Input file not specified"
            },
            {
                "name": "Error Test - Missing input file",
                "args": ["-input", "nonexistent.txt"],
                "expected_error": r"Error: Could not open input file"
            },
            {
                "name": "Error Test - Missing RAM file",
                "args": ["-ram", "nonexistent.txt", "-input", "input1.txt"],
                "expected_error": r"Error: Could not open RAM file"
            },
            {
                "name": "Test 1     - Valid RAM & input w/ -debug",
                "args": ["-ram", "ram1.txt", "-input", "input1.txt", "-debug"],
                "expected_patterns": [
                    r"LDR 5 ebd8 3af 3 0 M 0000",
                    r"STR 4 0ac2 02b 0 2 M 0000",
                    r"LDR a 0ad0 02b 2 0 M 0000",

                    # Register values check
                    r"R0: 0000",
                    r"R1: 0000",
                    r"R2: 0000"
                ]
            },
            {
                "name": "Test 2     - Valid RAM & input",
                "args": ["-ram", "ram2.txt", "-input", "input2.txt"],
                "expected_patterns": [
                    # LDR 1 3000 - First access to address 3000
                    r"LDR 1 3000 0c0 0 0 M 1234",
                    
                    # STR 1 3010 - First access to address 3010
                    r"STR 1 3010 0c0 2 0 M 1234",
                    
                    # LDR 2 3010 - Second access to address 3010 (just stored there)
                    r"LDR 2 3010 0c0 2 0 H 1234",

                    # Register values check
                    r"R0: 0000",
                    r"R1: 1234",
                    r"R2: 1234"
                ]
            }
        ]
        
        for test in test_cases:
            results.append(run_test_case(test))
            
    finally:
        print_summary(results)
        cleanup()

if __name__ == "__main__":
    main()