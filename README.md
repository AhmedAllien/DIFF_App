# DIFF_App

DIFF is a C++ program that compares two input text files and shows the differences.

# Specifications
The program should be able to handle plain text files of any size.
The program should be able to handle input files with different line endings (e.g., CR, LF, CRLF).
The program should output the differences between the two input files in a human-readable format.
The program should provide the user with the option to ignore certain types of differences, such as white space or letter case.
The program should display the differences in a clear and readable format, such as side-by-side comparison or colored highlighting.
The program should be able to handle input files that are encoded in different character sets (e.g., UTF-8, ISO-8859-1).
The program should provide the user with the option to output the differences to a file or copy them to the clipboard.

# How to Run

## Using Qt Creator
1. Open the DIFF project in Qt Creator.
2. Build the project by clicking on the hammer icon or by pressing Ctrl + B.
3. Run the program by clicking on the green play button or by pressing Ctrl + R.

## Other Methods
1. Open a terminal or command prompt.
2. Navigate to the directory where the DIFF program is located.
3. Build the program by running the command qmake && make.
4. Run the program by running the command ./DIFF.

# Usage
1. Select the reference file by clicking on the "Browse" button next to "Reference File".
2. Select the test file by clicking on the "Browse" button next to "Test File".
3. Choose the comparison options, such as ignoring white space or letter case.
4. Click on the "Compare" button to compare the files.
5. View the differences in the text box below the "Compare" button.
6. Optionally, save the differences to a file by clicking on the "Save Differences" button.
